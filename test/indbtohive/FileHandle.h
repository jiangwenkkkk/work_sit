#ifndef _FILE_HANDLE_API_H_
#define _FILE_HANDLE_API_H_

#include "LoggerMgr.h"
#include "common/util.h"
#include "common/Logger.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/Util/Application.h"
#include "common/ApplicationConfig.h"
#include "hdfs.h" 

#ifdef WITH_HIVE
#include "HiveApi.h"
#endif

#include <Poco/DOM/DOMParser.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/NodeIterator.h>
#include <Poco/DOM/NodeFilter.h>
#include <Poco/DOM/NodeList.h>
#include <Poco/DOM/AutoPtr.h>
#include <Poco/SAX/InputSource.h>
#include <Poco/Exception.h>
#include <iostream>
#include <fstream>


using namespace std;

class C_FileHandle
{
	public:
		C_FileHandle();
		~C_FileHandle();
		
		bool Connect(const int partition);  
		bool DisConnect(); 	
		bool Write(string provice_code,string data_id,string filename,vector<string>vec_cdr); 
		bool MoveFile();	
	private:	
		bool Open(const char* path);		
		bool Close(); 
		bool CommitAnalyze();
		bool InitParam(map<string,string>&map_config);
		bool parseConfPairs(string xmlFile, std::map<string, string>& conf)  ;
		
	public:
		LoggerMgr   _loggerMgr; // 日志		
      		
	private:	
		#ifdef WITH_HIVE		
		C_HiveApi  g_hive; //hiveserver	
		#endif
		string m_user;
		
		//提交元数据用		
		string m_dataid;
		string m_provice;
		string m_database;
		string m_table;
		
		//hdfs
		string m_path;
		string m_tmpformat;
		string m_srcfile;
		string m_dstfile;
		hdfsFS m_hdfs;
		hdfsFile m_file;		
		
};
#endif