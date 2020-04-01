
#include "IndbToHive.h"

#include <cstring>
#include <memory>
#include <vector>
#include <chrono>
using std::chrono::system_clock;
using Poco::Timestamp;
#include <string>
#include <sstream>


using util_func::appConfig;
using Poco::replace;

IndbToHiveTask::IndbToHiveTask()
    : Poco::Task( "IndbToHiveTask" )
{
}

void IndbToHiveTask::runTask()
{
#define ALERT_THROW(result, desc) \
    if (!(result)) { \
        FLOG << desc << ENDL; \
        if (!_alertMgr.send(LogAlertpb::Alert::BUSI, desc)) { \
            FLOG << "failed to send alert message" << ENDL; \
        } \
        throw Poco::Exception( desc ); \
    }

    // 连接数据库  
		ALERT_THROW( InitRedis(), "failed to initredis" );

    // 创建消费者对象
		KafkaConsumer::Ptr consumer( createConsumer() );
		ALERT_THROW(consumer, "failed to create kafka consumer" );
		
		// 连接HDFS和hiveserver2
		ALERT_THROW( g_filemgr.Connect(i_partition), "failed to connect hdfs" );		
		
		//读取分区和写入hdfs、提交hdfs条件
		const int32_t maxMessageCount = util_func::appConfig().getInt( "frequency.count" );
		const std::chrono::seconds timeLimited = std::chrono::seconds(util_func::appConfig().getInt("frequency.time" ));
		const int32_t maxWriteCount=util_func::appConfig().getInt( "hdfs.cdrwritenum" );	
    
		int32_t messageCount = 0;		
		system_clock::time_point now = system_clock::now();	
		//跨天	
		string sstartdate=GetSystemDate();
		vector<string> vec_hql;
		string strhql;
		//记录提交redis 的kafka offset
		map<string,int64_t>map_offset;		
		
		while ( state() == TASK_RUNNING )
    {
       	std::shared_ptr<RdKafka::Message> msgptr;
        bool ret = consumer->consume( msgptr );
        // 消费失败?
        ALERT_THROW( ret, "failed to consume" );
        				
        // 消息分配失败
        if ( !msgptr ) 
        {
            FLOG << "failed consumed msgptr is null" << ENDL;
            continue;
        }

        // 消费到数据
       	if ( msgptr->len() ) 
        {
            // 分拣的话单
            distributepb::Bill bill;
            if ( !bill.ParseFromArray( msgptr->payload(), msgptr->len() ) ) 
            {
                auto errstr = Poco::format(
                                  "failed to parse proto message from message, "
                                  "topic: %s, partition: %d, offset: %ld",
                                  msgptr->topic_name(), msgptr->partition(),
                                  msgptr->offset() );
                ALERT_THROW( false, errstr );
            }

            // 排除错单
            if ( bill.ecrdflag() != 0 ) 
            {
                WLOG << "ignore error bill message: " << bill.DebugString() << ENDL;
                continue;
            }
						if(messageCount==0)
						{
								vec_hql.clear();
								map_offset.clear();	
                // 初始化超时下发开始时间
								now = system_clock::now();            		
								sstartdate=GetSystemDate();
            		m_procode	=	ltos(bill.provcode());
            		//记录开始日志时间
            		g_filemgr._loggerMgr.startTime( system_clock::to_time_t( now ) );									
						}
	    
            //解析bill里面的话单记录
						strhql.clear(); 
						
					  //strhql="1^18938100767^460010496100767^1111222233334444^255.255.0.1^CTLTE^FE010A0B^250142^100000^2001:0000:3238:DFE1:0063:0000:0000:0000^1^0^771^21^A^1000^1000^20180710170010^30^20180710170040^000000000^^460111A00091^59^^^^"+string("^")+ltos(11111)+string("^")+ltos(111111)+string("^")+""+string("^")+"LING025000";     
  
            strhql=bill.bill()+string("^")+ltos(bill.filerecvtime())+string("^")+ltos(bill.timestamp())+string("^")+""+string("^")+bill.srcfile();
            vec_hql.push_back(strhql);
      
						messageCount++;
						
            // 更新日志消费偏移
            g_filemgr._loggerMgr.updateOffset( msgptr->partition(), msgptr->offset() );
	
						//记录每个partition offset
						RecordOffSet(msgptr->topic_name().c_str(),msgptr->partition(), msgptr->offset(),map_offset);
	
    
      	}
        //写入hdfs
        if(vec_hql.size()>=maxWriteCount)
        {
    				ALERT_THROW( Write(vec_hql),"failed to call Write function");
        		vec_hql.clear();
        }

        // 是否满足提交hdfs文件和更新redis offset条件
        if ( messageCount >= maxMessageCount
             ||( diffday((char*)(sstartdate.c_str()),(char*)(GetSystemDate().c_str()) )>0 && messageCount > 0 )
             ||( system_clock::now() - now >= timeLimited && messageCount > 0 )
             ) 
       	{
       			if(vec_hql.size()!=0)
       			{
       					ALERT_THROW( Write(vec_hql),"failed to call Write function");
       			}
    				ALERT_THROW( g_filemgr.MoveFile(),"failed to call MoveFile function" );
						//更新offset		
   					ALERT_THROW(  CommitOffSet(map_offset),
                     "failed to call CommitOffSet function" );						
            // 清零
            messageCount = 0;
            now = system_clock::now();
            sstartdate=GetSystemDate();
            vec_hql.clear();
            map_offset.clear();
        }
    }

    // 程序退出时下发文件
    if ( messageCount > 0 ) 
    {
    		if(vec_hql.size()!=0)
    		{
    				ALERT_THROW( Write(vec_hql),"failed to call Write function");
    		}
    		ALERT_THROW( g_filemgr.MoveFile(),"failed to call InsertIntoHive function");
   			ALERT_THROW( CommitOffSet(map_offset ),"failed to call CommitOffSet function"  );
    		ALERT_THROW( g_filemgr.DisConnect(), "failed to disconnect hdfs" );
    	
    }
}



bool IndbToHiveTask::CommitOffSet(std::map<string,int64_t>map_offset)
{
		string sTopic;
		int iPartition;
		int64_t iOffSet;
		map<string,int64_t>::iterator iter;
		for(iter=map_offset.begin();iter!=map_offset.end();iter++)
		{
			
				Poco::StringTokenizer tok( iter->first,
                               "^", Poco::StringTokenizer::TOK_TRIM );
        if(tok.count()!=2)
        {
        		ELOG << "iter->first"<<"error"<< ENDL;
        		return false;        		
        }
        else
        {
        		sTopic=tok[0];
        		iPartition=stol(tok[1]);        		
        }	

				iOffSet=iter->second;
				
				if(!g_offsetmgr.SetTopicOffSet(sTopic.c_str(),iPartition,iOffSet))
				{
						WLOG << "set off set top: " << sTopic<<"partiton:" <<iPartition <<"offset:"<<iOffSet<< ENDL;
						return false;
				}
		}
		return true;
}

bool IndbToHiveTask::Write(std::vector<string>vec_cdr)
{
		string filename;
		
		Timestamp now;
		filename=m_filename+"_"+ltos(now.epochTime());
		if(!g_filemgr.Write(m_procode,GetSystemDate(),filename,vec_cdr))
		{
				return false;
		}
		return true;
}

// 创建文件管理对象
bool IndbToHiveTask::InitRedis()
{
		//获取变量
    auto instanceKey = Poco::format( "instance_%d_%d_%d",
                                     appConfig().getInt( app_conf::FLOW_ID ),
                                     appConfig().getInt( app_conf::PROGRAM_ID ),
                                     appConfig().getInt( app_conf::INSTANCE_ID ) );
    auto inMqdesc = appConfig().getString( app_conf::MQDESC_IN );

    FLOG << "in mqdesc: " << inMqdesc << ENDL;
    
    if(!g_offsetmgr.Init(const_cast<char*>( inMqdesc.c_str() ), 
    											const_cast<char*>( instanceKey.c_str() ),
    										  const_cast<char*>( appConfig().getString( "redis.host" ).c_str() ),
                         	const_cast<char*>( appConfig().getString( "redis.password" ).c_str() ))
                         	)
    {
    		FLOG << "init redis error"<< ENDL;
    		return false;
    }
    
    return true;
}

KafkaConsumer::Ptr IndbToHiveTask::createConsumer()
{
		//获取partition信息
		auto partition=appConfig().getString( app_conf::PARTITION_IN );
    Poco::StringTokenizer tok(partition, "#", Poco::StringTokenizer::TOK_TRIM );

    // 创建消费者对象
    TopicPartitionOffsetVec topicPartitionOffsets;
    auto topic = appConfig().getString( app_conf::TOPIC_IN );
    m_filename.clear();
    string strTmp=Poco::replace(partition,"#","");
    m_filename=topic+"_"+strTmp;
    
    for ( auto it = tok.begin(); it != tok.end(); ++ it ) 
    {
        TopicPartitionOffset of;
        of.topic = topic;
        std::stringstream( *it ) >> of.partition;
				if(it==tok.begin())
				{
						i_partition=0;
						i_partition=of.partition;
				}
        // 获取消费断点成功
        if ( g_offsetmgr.GetTopicOffSet( topic.c_str(), of.partition, of.offset ) ) 
        {
            of.offset += 1;
        }
        // 找不到则从最开始消费
        else 
        {
            of.offset = RdKafka::Topic::OFFSET_BEGINNING;
        }

        DLOG << "topic: " << topic << ", partition: " << of.partition
             << ", offset: " << of.offset << ENDL;

        topicPartitionOffsets.push_back( of );
    }

    BolKafkaFactory<> bolKafkaFactory( topicPartitionOffsets );

    // 创建消费者对象
    return bolKafkaFactory.createConsumer();
}

void IndbToHiveTask::RecordOffSet(const char *sTopic, int iPartition, int64_t iOffSet,std::map<string,int64_t>&map_offset)
{
		string skey;		
		skey=sTopic+string("^")+ltos(iPartition);
		map<string,int64_t>::iterator iter;
		iter=map_offset.find(skey);
		if(iter!=map_offset.end())
		{
				//更新
				iter->second=iOffSet;
		}
		else
		{
				//插入
				map_offset.insert ( std::pair<string,int>(skey,iOffSet) );
		}
		return;
}



std::string IndbToHiveTask::ltos(long l)
{
    ostringstream os;
    os<<l;
    string result;
    istringstream is(os.str());
    is>>result;
    return result;
}

std::string IndbToHiveTask::GetSystemDate()
{
	time_t timer;
	struct tm *today;

	timer = time(NULL);
	today = localtime(&timer);
	char CurrentDate[8+1];
	sprintf(CurrentDate,"%04d%02d%02d",today->tm_year + 1900,today->tm_mon+1,today->tm_mday);
	return string(CurrentDate);
}

long IndbToHiveTask::diffday(char *dt1,char *dt2)
{
    struct tm t;
    time_t t1,t2;
    char tmp[10];

    memcpy(tmp,dt1,4);      tmp[4]=0;
    t.tm_year=atoi(tmp)-1900;
    memcpy(tmp,dt1+4,2);    tmp[2]=0;
    t.tm_mon=atoi(tmp)-1;
    memcpy(tmp,dt1+6,2);    tmp[2]=0;
    t.tm_mday=atoi(tmp);
    t.tm_hour=0;
    t.tm_min=0;
    t.tm_sec=0;
    t.tm_isdst = 0;
    t1=mktime(&t);

    memcpy(tmp,dt2,4);      tmp[4]=0;
    t.tm_year=atoi(tmp)-1900;
    memcpy(tmp,dt2+4,2);    tmp[2]=0;
    t.tm_mon=atoi(tmp)-1;
    memcpy(tmp,dt2+6,2);    tmp[2]=0;
    t.tm_mday=atoi(tmp);
    t.tm_hour=0;
    t.tm_min=0;
    t.tm_sec=0;
    t.tm_isdst = 0;
    t2=mktime(&t);

    return (long)difftime(t2,t1)/(3600*24);
}


