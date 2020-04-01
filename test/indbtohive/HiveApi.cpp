#include "arrow/test-util.h"
#include "HiveApi.h"

using util_func::appConfig;
	
C_HiveApi::C_HiveApi()
{
		//协议
		protocol_version = ProtocolVersion::PROTOCOL_V7;
		//s_hivehost  10.130.236.18:10020;10.130.236.19:10000;10.130.236.20:10010
		string s_hivehost = util_func::appConfig().getString( "hive.host" );
		//del s_hivehost
		for (int i = 0; i < Max_HiveServer; i++)
		{		
				m_ConnInfo[i].port = 0;	
				m_ConnInfo[i].mhost="0";
		}	
		if(!DealHostPort(s_hivehost))
		{
				FLOG <<"indbtohive.ini"<< s_hivehost<<"error"<< ENDL;	
				exit(0);	
		}

		m_conn_timeout=util_func::appConfig().getInt( "hive.contimeout" );
		m_user=util_func::appConfig().getString( "hive.user");
		m_passwd=util_func::appConfig().getString( "hive.pwd");
		m_authmode=util_func::appConfig().getString( "hive.authmode");

}

C_HiveApi::~C_HiveApi()
{

}


bool C_HiveApi::DealHostPort(string input)
{
		string stmp;
		string sthost,stport;
		int pos;
		
		Poco::StringTokenizer tok(input, ";", Poco::StringTokenizer::TOK_TRIM );
		if(tok.count()==0)
		{
				ELOG << "indbtohive host error." << input << ENDL;
				return false;
		}
		for(int index=0;index<tok.count();index++)
		{
				stmp.clear();
				stmp=	tok[index];
				pos= stmp.find(":");

    		if (pos == std::string::npos)
    		{
        		ELOG << "indbtohive host error." << tok[index] << ENDL;
						return false;
    		}
			
				sthost=stmp.substr(0,pos);
				stport=stmp.substr(pos+1);
			  if(index < Max_HiveServer)
			  {
						m_ConnInfo[index].mhost = sthost;
						m_ConnInfo[index].port = stoi(stport);
				    i_hivenum=index+1;
					
				}
				else
				{
						ELOG << "too much hiveserver2 than"<<Max_HiveServer<<"other skip!" << ENDL;
				}
			
		}	
		
		return true;
}

bool C_HiveApi::DisConnect()
{
    session_->Close();
    service_->Close();
}

bool C_HiveApi::Insert(string insertsql)
{
		//如果执行语句失败
		if( !TryInsert(insertsql))
		{
				//测试链接是否好用
				if(	!TryInsert("show databases"))
				{
						DisConnect();
						if(!Connect(i_partition))
						{
								return false;
						}
						if( !TryInsert(insertsql))
						{
								return false;
						}
						
				}		
		}
		return true;
}

bool C_HiveApi::TryInsert(string insertsql)
{
		std::unique_ptr<Operation> insert_op;
		
		Status s=session_->ExecuteStatement(insertsql, &insert_op);
		if(!s.ok())
		{
				FLOG<<"hive Insert is error"<<s.message()<<ENDL;
				insert_op->Close();
				return false;
		}		
		if(!Wait(insert_op))
		{
				insert_op->Close();		
				return false;		
		}	
		insert_op->Close();
		return true;	
}

bool C_HiveApi::Connect(const int partition)
{
		int i_partition=partition;
		int itmp=i_partition%i_hivenum;
		int irand=itmp;
		if(!TryConnect(itmp))
		{
				//不成功，重试
				while( (--irand)>=0)
				{
						if(TryConnect(irand))
						{
								return true;	 						
						}
				}	
				//不成功，重试
				while( (++itmp)<i_hivenum)
				{
						if(TryConnect(itmp))
						{
								return true;	 						
						}
				}											 						
		}	
		else
		{
				return true;
		}	
		return false;
}

bool C_HiveApi::TryConnect(const int index)
{	
		
		Status s=Service::Connect(m_ConnInfo[index].mhost,m_ConnInfo[index].port, m_conn_timeout, protocol_version, &service_,m_user,m_passwd,m_authmode);

		if(!s.ok())
		{
				FLOG<<"hive connect is error"<<m_ConnInfo[index].mhost<<m_ConnInfo[index].port<<ENDL;
				FLOG<<"hive connect is error"<<s.message()<<ENDL;
				return false;
		}
		s=service_->OpenSession(m_user, config_, &session_);
		if(!s.ok())
		{
				FLOG<<"hive connect is error"<<s.message()<<ENDL;
				service_->Close();
				return false;
		}		
		return true;
}

bool C_HiveApi::Wait(const std::unique_ptr<Operation>& op,Operation::State state, 
									int sleep_us ,int max_retries ) 
{
		int retries = 0;
		Operation::State op_state;
		
		Status s=	op->GetState(&op_state);
		if(!s.ok())
		{
				return false;
		}	
				
		while (op_state != state && retries < max_retries) 
		{
				usleep(sleep_us);
				s=	op->GetState(&op_state);
				if(!s.ok())
				{
						return false;
				}	
				++retries;
		}
		
		if (op_state == state) 
		{
				return true;
		} 
		else 
		{
		    FLOG<<"Failed to reach state '" << OperationStateToString(state) << "' after "
		     << retries << " retries."<<ENDL;
				return false;
		}
		return true;
}
