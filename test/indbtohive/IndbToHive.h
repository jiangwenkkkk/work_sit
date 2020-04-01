#ifndef _INDB_TO_HIVE_H_
#define _INDB_TO_HIVE_H_

#include <Poco/Task.h>


//日志

//告警
#include "AlertMgr.h"
#include "common/CResMgr.h"
#include "OffSetMgr.h"
#include "common/Logger.h"
#include "common/ApplicationConfig.h"
#include "common/KafkaConsumer.h"
#include "common/BolKafkaFactory.h"
#include "common/util.h"
#include "proto/DistributeMessage.pb.h"
#include "FileHandle.h"

#include <Poco/Exception.h>
#include <Poco/Format.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/StringTokenizer.h>
#include <Poco/Path.h>
#include <Poco/File.h>
#include <Poco/String.h>
#include <Poco/Timestamp.h>


class IndbToHiveTask : public Poco::Task
{
public:
    IndbToHiveTask( );

    virtual void runTask();

private:
		bool InitRedis();
		KafkaConsumer::Ptr createConsumer()	;
		bool Write(std::vector<string>vec_cdr);
		bool UpdateOffSet(std::map<string,int>map_offset);
		void RecordOffSet(const char *sTopic, int iPartition, int64_t iOffSet,std::map<string,int64_t>&map_offset);
		bool CommitOffSet(std::map<string,int64_t>map_offset);
		std::string ltos(long l);
		std::string GetSystemDate();	
		long diffday(char *dt1,char *dt2);	

private:
		C_OffSetMgr	g_offsetmgr;//redis更新断点/
    AlertMgr    _alertMgr;  // 告警
		C_FileHandle g_filemgr; 
		string m_filename ;
		string m_procode;
		int i_partition;

};	
#endif