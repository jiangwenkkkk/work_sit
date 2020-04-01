#include "OffSetMgr.h"

C_OffSetMgr::C_OffSetMgr()
{

}

bool C_OffSetMgr::Init(char *sBrokerList, char *sTopic,char *sRedisHost, char *sRedisPwd)
{
		m_pResMgr = new CResMgr(sRedisHost, sRedisPwd);
		
		memset(m_sBrokerList, 0, sizeof(m_sBrokerList));
		strcpy(m_sBrokerList, sBrokerList);
		
		memset(m_sTopic, 0, sizeof(m_sTopic));
		strcpy(m_sTopic, sTopic);	
			
		if (!m_pResMgr->CConnect()) 
		{				
				return false;
		}
		return true;	
}

C_OffSetMgr::~C_OffSetMgr()
{
		m_pResMgr->CDisConnect();
		delete m_pResMgr;
}


bool C_OffSetMgr::GetTopicOffSet(const char *sTopic, int iPartition, int64_t &iOffSet)
{
		char sKey[256];
		memset(sKey,0,sizeof(sKey));		
		sprintf(sKey, INTOHIVE_CONSUMED, m_sBrokerList, sTopic, iPartition);	
		if(!GetOffSet(string(sKey),iOffSet))
		{
				return false;				
		}
		return true;			
}

bool C_OffSetMgr::SetTopicOffSet(const char *sTopic, int iPartition, int64_t iOffSet)
{
		char sKey[256];
		memset(sKey,0,sizeof(sKey));	
		sprintf(sKey, INTOHIVE_CONSUMED, m_sBrokerList, sTopic, iPartition);			
		if(!SetOffSet(string(sKey),iOffSet))
		{
				return false;				
		}
		return true;		
}

bool C_OffSetMgr::GetOffSet(string  strKey, int64_t &iOffSet)
{
		try
		{
				if(m_pResMgr->CExistKey(strKey))
				{
						std::string strValue;
						m_pResMgr->CGetRes(strKey, strValue);
						iOffSet = atoll(strValue.c_str());
						return true;
				}	
		}
		catch(exception &e)
		{
				FLOG << "GetTopicOffSet redis error["<< e.what() << "]." << ENDL;
		}
		return false;
}
bool C_OffSetMgr::SetOffSet(string strKey, int64_t iOffSet)
{
		std::string strValue;
		strValue=m_pResMgr->ltos(iOffSet);	
		try
		{						
				m_pResMgr->CSetRes(strKey, strValue);
		}
		catch(exception &e)
		{
				FLOG << "SetTopicOffSet redis error["<< e.what() << "]." << ENDL;
				return false;
		}
		return true;			
}