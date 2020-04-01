#ifndef _OFF_SET_MGR_H_
#define _OFF_SET_MGR_H_
//Á¬½Óredis
#include "common/CResMgr.h"

#define INTOHIVE_CONSUMED "{hive}_c_%s_%s_%d"

class C_OffSetMgr{
	public:
			C_OffSetMgr();
			~C_OffSetMgr();
			bool Init(char *sBrokerList, char *sTopic,char *sRedisHost, char *sRedisPwd);
			bool GetTopicOffSet(const char *sTopic, int iPartition, int64_t &iOffSet);
			bool SetTopicOffSet(const char *sTopic, int iPartition, int64_t iOffSet);

	private:
			bool GetOffSet(string  strKey, int64_t &iOffSet);
			bool SetOffSet(string  strKey, int64_t iOffSet);
	private:
		
			CResMgr *m_pResMgr;
			char m_sTopic[512];                    //topic
			char m_sBrokerList[512];               //brokerlist			
};

#endif