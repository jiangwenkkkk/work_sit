#ifndef _HIVE_API_H_
#define _HIVE_API_H_
#include "arrow/dbi/hiveserver2/service.h"
#include "arrow/dbi/hiveserver2/session.h"
#include "arrow/dbi/hiveserver2/thrift-internal.h"
#include "arrow/dbi/hiveserver2/operation.h"
#include "arrow/status.h"
#include "common/util.h"
#include "common/Logger.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/Util/Application.h"
#include "common/ApplicationConfig.h"

using namespace arrow;
using namespace arrow::hiveserver2;
using namespace std;

const int Max_HiveServer=20;

class ConnectInfo
{
    public:
      string  mhost;
			int port;
};


class C_HiveApi
{
	public:
		C_HiveApi();
		~C_HiveApi();	
		bool Insert(string insertsql);
		bool Connect(const int partition);  
		bool DisConnect(); 	
	  			
	private:	
		bool Wait(const std::unique_ptr<Operation>& op,
            		Operation::State state = Operation::State::FINISHED, int sleep_us = 10000,
            		int max_retries = 10);
            		
		bool DealHostPort(string input);
		bool GetHostPort(const int partition);
    bool TryConnect(const int index) ; 
    bool TryInsert(string insertsql);	
	private:
				
		std::unique_ptr<Service> service_;
		std::unique_ptr<Session> session_;
		//string m_hivehost;
		//int m_port;
		int m_conn_timeout;
		string m_user;
		string m_passwd;
		string m_authmode;
		ProtocolVersion protocol_version;
		HS2ClientConfig config_;
		ConnectInfo m_ConnInfo[Max_HiveServer];
		int i_hivenum;
		int i_partition;

};
#endif