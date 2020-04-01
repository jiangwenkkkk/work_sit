#include "FileHandle.h"

/*
** partition : 天_省份号
** file			 : 按小时或者话单条数+时间戳
*/

using Poco::XML::DOMParser;
using Poco::XML::InputSource;
using Poco::XML::Document;
using Poco::XML::NodeIterator;
using Poco::XML::NodeFilter;
using Poco::XML::NodeList;
using Poco::XML::Node;
using Poco::XML::AutoPtr;
using util_func::appConfig;
	
C_FileHandle::C_FileHandle()
{
		//协议
		//m_hivehost  = util_func::appConfig().getString( "hdfs.host" );
		//m_port=	util_func::appConfig().getInt( "hdfs.port" );
		m_path=util_func::appConfig().getString( "hdfs.path");			
		m_user=util_func::appConfig().getString( "hdfs.user");
			
		if(	m_path.at(m_path.length()-1)!='/')
		{
				m_path+="/";
		}
		m_tmpformat=util_func::appConfig().getString( "hdfs.tempformat");
		m_file=NULL;
		
		m_table=util_func::appConfig().getString( "tableinfo.tablename" );
		m_database=util_func::appConfig().getString( "tableinfo.database" );				
		
}

C_FileHandle::~C_FileHandle()
{

}

bool C_FileHandle::DisConnect()
{
		if(hdfsDisconnect(m_hdfs)!=0)
		{
				FLOG<<"DisConnect hdfs error"<<ENDL;
				return false;
		}
		#ifdef WITH_HIVE		
		if(!g_hive.DisConnect())
		{
				FLOG<<"DisConnect hiveserver2 error"<<ENDL;	
				return false;
		}	
		#endif	
		return true;
}

bool C_FileHandle::Write(string provice_code,string data_id,string filename,vector<string>vec_cdr)
{

		if(m_file==NULL)
		{
				string sPath;
				m_dataid.clear();
				m_dataid=data_id;
				m_provice.clear();
				m_provice=provice_code;
				sPath=m_path+"date_no="+data_id+"/"+"provinceid="+provice_code+"/";	
				if(hdfsExists(m_hdfs, sPath.c_str())!=0)
				{
						return false;
				}			
				m_srcfile.clear();
				m_srcfile=sPath+m_tmpformat+filename;
				m_dstfile.clear();
				m_dstfile=sPath+filename;
				
				if(!Open(m_srcfile.c_str()))
				{
						return false;
				}
		}
		string cdrbuff;
		for(int i=0;i<vec_cdr.size();i++)
		{
				cdrbuff+=vec_cdr[i]+"\n";
		}
		//FLOG<<"write begin..."<<ENDL;
		if(hdfsWrite(m_hdfs,m_file,(void*)(cdrbuff.c_str()),cdrbuff.length())==-1)
		{
				return false;
		}
		//FLOG<<"write end..."<<ENDL;
		return true;	
}

bool C_FileHandle::InitParam(map<string,string>&map_config)
{
		string xmlfile1=util_func::appConfig().getString( "xmlpath.xmlpath1");			
		string xmlfile2=util_func::appConfig().getString( "xmlpath.xmlpath2");	
		if(	!parseConfPairs(xmlfile1,map_config)	)
		{
				FLOG<<"deal xml file"<<xmlfile1<<"error"<<ENDL;
				return false;
		}	
		if(	!parseConfPairs(xmlfile2,map_config)	)
		{
				FLOG<<"deal xml file"<<xmlfile2<<"error"<<ENDL;
				return false;
		}	
		return true;		
}



bool C_FileHandle::Connect(const int parttion)
{
		map<string,string>map_conf;
		map_conf.clear();
		if(!InitParam(map_conf))
		{
				return false;
		}
			
		struct hdfsBuilder *pbld = hdfsNewBuilder(); //Create an HDFS builder.      
   	map<string,string>::iterator iter;
   	for(iter=map_conf.begin();iter!=map_conf.end();iter++)
   	{
    		hdfsBuilderConfSetStr( pbld, iter->first.c_str(), iter->second.c_str() ); 
    }              
  	//使用builder配置的hadoop集群地址 
		hdfsBuilderSetNameNode( pbld,  "default" ); 
		hdfsBuilderSetUserName(pbld,m_user.c_str());
		
		m_hdfs= hdfsBuilderConnect(pbld);
		//m_hdfs=hdfsConnectAsUser(m_hivehost.c_str(), m_port,m_user.c_str());
		if(m_hdfs==NULL)
		{
				FLOG<<"connect hdfs error"<<ENDL;
				return false;
		}
		#ifdef WITH_HIVE	
		//连接hiveserver2
		if(!g_hive.Connect(parttion))
		{
				FLOG<<"connect hiveserver2 error"<<ENDL;	
				return false;
		}
		#endif
		return true;
}

bool C_FileHandle::MoveFile()
{
		if(!Close())
		{
				return false;
		}
		if(hdfsRename(m_hdfs,m_srcfile.c_str(), m_dstfile.c_str())!=0)
		{
				FLOG<<"move"<<m_srcfile<<"to"<<m_dstfile<<ENDL;
				return false;
		}
		
		// 发送日志信息
		if ( !_loggerMgr.send( LogAlertpb::Log_LogType_OUT, m_dstfile ) ) 
		{
		    FLOG << "failed to send logger message" << ENDL;
		}
		_loggerMgr.reset();	
			
		CommitAnalyze()	;
		m_dataid.clear();
		m_provice.clear();			
		m_srcfile.clear();
		m_dstfile.clear();
		
		return true;
}

bool C_FileHandle::Open(const char* path) 
{
		m_file= hdfsOpenFile(m_hdfs, path ,O_WRONLY|O_CREAT,0,0,0);	
		if(m_file==NULL)
		{
				FLOG<<"open"<<path<<"error"<<ENDL;
				return false;
		}
		return true;
}

bool C_FileHandle::Close()
{
		if(hdfsCloseFile(m_hdfs,m_file)!=0)
		{
				return false;
		}
		m_file=NULL;
		return true;
}

bool C_FileHandle::CommitAnalyze()
{
		#ifdef WITH_HIVE	
		FLOG << "commit hiveserver2 Analyze begin...." << ENDL;
		string commitsql;
		commitsql="analyze table "+m_database+"."+m_table +" partition ( date_no='" + m_dataid +"',provinceid='"+m_provice+"' )" + " compute statistics ";

		if(!g_hive.Insert(commitsql))
		{
				FLOG<<"excute sql:"<<commitsql<<"error"<<ENDL;
				return false;
		}
		if ( !_loggerMgr.send( LogAlertpb::Log_LogType_OUT, m_dstfile ) ) {
		    FLOG << "failed to send logger message" << ENDL;
		}	
		FLOG << "commit hiveserver2 Analyze end...." << ENDL;	
		#endif	
		return true;
}

bool C_FileHandle::parseConfPairs(string xmlFile, std::map<string, string>& conf) 
{
    try 
    {
        std::ifstream in(xmlFile);
        InputSource src(in);
        DOMParser parser;
        AutoPtr<Document> pDoc = parser.parse(&src);
        NodeIterator it(pDoc, NodeFilter::SHOW_ELEMENT);
        Node* pNode = it.nextNode();
        NodeList* cNodeList = NULL;
        Node* cNode = NULL;
        std::string name;
        std::string value;
        
        while (pNode)
        {
            if (pNode->nodeName() == "property")
            {
                cNodeList = pNode->childNodes();
                for (int i = 0; i < cNodeList->length(); i++) {
                    cNode = cNodeList->item(i);
                    if (cNode->nodeName() == "name") {
                        name = cNode->childNodes()->item(0)->nodeValue();
                    }
                    if (cNode->nodeName() == "value") {
                        value = cNode->childNodes()->item(0)->nodeValue();
                    }
                }
                conf[name] = value;
            }
            pNode = it.nextNode();
        }
    } 
    catch (Poco::Exception e) 
    {
        FLOG << e.displayText() << ENDL;
        return false;
    }
    return true;
}
