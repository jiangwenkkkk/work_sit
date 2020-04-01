//MySqlQuery.cpp
 
#include "MySqlQuery.h"
 
#include <string.h>
#include <sstream>
 
using namespace std;

//比较2个字符串是否相同(不考虑大小写)
bool inline compareStrNoCase(const char *ori, const char *des) {
	int j, nLen1, nLen2;
	bool sameChar;
	nLen1 = strlen(ori);
	nLen2 = strlen(des);
	if (nLen1 != nLen2)
		return false;
	sameChar = true;
	for (j = 0; j < nLen1; j++)
		sameChar = sameChar && (toupper(ori[j]) == toupper(des[j]));
	return sameChar;
}

//## 字符串替换
string Replace(string &str,string sOld,string sNew)
{
	basic_string <char>::size_type index = 0;

	while((index=str.find(sOld.c_str(),index))!= -1)
	{
		str.replace(index,sOld.length(),sNew.c_str() );
		index = index + sNew.length();
	}

	return str;
}

MySqlDataBase::MySqlDataBase():m_bConnected(false)
{
 m_pstMql = mysql_init(NULL);
 _pMysqlRes = NULL;
}
 
MySqlDataBase::MySqlDataBase(const string& sHost, const string& sUser, const string& sPasswd, const string& sDatabase, const string &sCharSet, int port, int iFlag)
:m_bConnected(false)
{
 init(sHost, sUser, sPasswd, sDatabase, sCharSet, port, iFlag);
 
 m_pstMql = mysql_init(NULL);
 _pMysqlRes = NULL;
}
 
MySqlDataBase::MySqlDataBase(const DBConf& tcDBConf)
:m_bConnected(false)
{
 _dbConf = tcDBConf;
 
 m_pstMql = mysql_init(NULL);
 _pMysqlRes = NULL;
}
 
MySqlDataBase::~MySqlDataBase()
{
 if (m_pstMql != NULL)
 {
 mysql_close(m_pstMql);
 m_pstMql = NULL;
 }
 if(_pMysqlRes)
 {
 		mysql_free_result(_pMysqlRes);
 		_pMysqlRes = NULL;
 }
}
 
void MySqlDataBase::init(const string& sHost, const string& sUser, const string& sPasswd, const string& sDatabase, const string &sCharSet, int port, int iFlag)
{
 _dbConf._host = sHost;
 _dbConf._user = sUser;
 _dbConf._password = sPasswd;
 _dbConf._database = sDatabase;
 _dbConf._charset = sCharSet;
 _dbConf._port = port;
 _dbConf._flag = iFlag;
 if(_dbConf._charset == "")
 {
 		_dbConf._charset == "utf8";
 }
}
 
void MySqlDataBase::init(const DBConf& tcDBConf)
{
 _dbConf = tcDBConf;
}
 
void MySqlDataBase::connect()
{
 disconnect();
 
 if( m_pstMql == NULL)
 {
 m_pstMql = mysql_init(NULL);
 }
 
 //建立连接后, 自动调用设置字符集语句
 if(!_dbConf._charset.empty()) {
 if (mysql_options(m_pstMql, MYSQL_SET_CHARSET_NAME, _dbConf._charset.c_str())) {
 throw MySqlQuery_Exception(string("MySqlQuery::connect: mysql_options MYSQL_SET_CHARSET_NAME ") + _dbConf._charset + ":" + string(mysql_error(m_pstMql)));
 }
 }
 
 if (mysql_real_connect(m_pstMql, _dbConf._host.c_str(), _dbConf._user.c_str(), _dbConf._password.c_str(), _dbConf._database.c_str(), _dbConf._port, NULL, _dbConf._flag) == NULL) 
 {
 throw MySqlQuery_Exception("[MySqlQuery::connect]: mysql_real_connect: " + string(mysql_error(m_pstMql)));
 }
 
 m_bConnected = true;
 mysql_autocommit(m_pstMql,0);//0关闭自动提交  1自动提交
}

void MySqlDataBase::disconnect()
{
 if (m_pstMql != NULL)
 {
 mysql_close(m_pstMql);
 m_pstMql = mysql_init(NULL);
 }
 
 m_bConnected = false; 
}

MYSQL *MySqlDataBase::getMysql(void)
{
 return m_pstMql;
}

void MySqlDataBase::close()
{
	if(_pMysqlRes)
  {
 		mysql_free_result(_pMysqlRes);
 		_pMysqlRes = NULL;
  }
}

MySqlQuery::MySqlQuery(MySqlDataBase *oradb)
{
	db = oradb;
	_pstMql = oradb->getMysql();
	//db->close();
	_pMysqlRes = NULL;
}
MySqlQuery::~MySqlQuery()
{
	
}

string MySqlQuery::escapeString(const string& sFrom)
{
 if(!db->m_bConnected)
 {
 db->connect();
 }
 
 string sTo;
 string::size_type iLen = sFrom.length() * 2 + 1;
 char *pTo = (char *)malloc(iLen);
 
 memset(pTo, 0x00, iLen);
 
 mysql_real_escape_string(_pstMql, pTo, sFrom.c_str(), sFrom.length());
 
 sTo = pTo;
 
 free(pTo);
 
 return sTo;
}
 
MYSQL *MySqlQuery::getMysql(void)
{
 return _pstMql;
}
 
string MySqlQuery::buildInsertSQL(const string &sTableName, const RECORD_DATA &mpColumns)
{
 ostringstream sColumnNames;
 ostringstream sColumnValues;
 
 map<string, pair<FT, string> >::const_iterator itEnd = mpColumns.end();
 
 for(map<string, pair<FT, string> >::const_iterator it = mpColumns.begin(); it != itEnd; ++it)
 {
 if (it == mpColumns.begin())
 {
 sColumnNames << "`" << it->first << "`";
 if(it->second.first == DB_INT)
 {
 sColumnValues << it->second.second;
 }
 else
 {
 sColumnValues << "'" << escapeString(it->second.second) << "'";
 }
 }
 else
 {
 sColumnNames << ",`" << it->first << "`";
 if(it->second.first == DB_INT)
 {
 sColumnValues << "," + it->second.second;
 }
 else
 {
 sColumnValues << ",'" + escapeString(it->second.second) << "'";
 }
 }
 }
 
 ostringstream os;
 os << "insert into " << sTableName << " (" << sColumnNames.str() << ") values (" << sColumnValues.str() << ")";
 return os.str();
}
 
string MySqlQuery::buildReplaceSQL(const string &sTableName, const RECORD_DATA &mpColumns)
{
 ostringstream sColumnNames;
 ostringstream sColumnValues;
 
 map<string, pair<FT, string> >::const_iterator itEnd = mpColumns.end();
 for(map<string, pair<FT, string> >::const_iterator it = mpColumns.begin(); it != itEnd; ++it)
 {
 if (it == mpColumns.begin())
 {
 sColumnNames << "`" << it->first << "`";
 if(it->second.first == DB_INT)
 {
 sColumnValues << it->second.second;
 }
 else
 {
 sColumnValues << "'" << escapeString(it->second.second) << "'";
 }
 }
 else
 {
 sColumnNames << ",`" << it->first << "`";
 if(it->second.first == DB_INT)
 {
 sColumnValues << "," + it->second.second;
 }
 else
 {
 sColumnValues << ",'" << escapeString(it->second.second) << "'";
 }
 }
 }
 
 ostringstream os;
 os << "replace into " << sTableName << " (" << sColumnNames.str() << ") values (" << sColumnValues.str() << ")";
 return os.str();
}
 
string MySqlQuery::buildUpdateSQL(const string &sTableName,const RECORD_DATA &mpColumns, const string &sWhereFilter)
{
 ostringstream sColumnNameValueSet;
 
 map<string, pair<FT, string> >::const_iterator itEnd = mpColumns.end();
 
 for(map<string, pair<FT, string> >::const_iterator it = mpColumns.begin(); it != itEnd; ++it)
 {
 if (it == mpColumns.begin())
 {
 sColumnNameValueSet << "`" << it->first << "`";
 }
 else
 {
 sColumnNameValueSet << ",`" << it->first << "`";
 }
 
 if(it->second.first == DB_INT)
 {
 sColumnNameValueSet << "= " << it->second.second;
 }
 else
 {
 sColumnNameValueSet << "= '" << escapeString(it->second.second) << "'";
 }
 }
 
 ostringstream os;
 os << "update " << sTableName << " set " << sColumnNameValueSet.str() << " " << sWhereFilter;
 
 return os.str();
}
 
string MySqlQuery::getVariables(const string &sName)
{
 string sql = "SHOW VARIABLES LIKE '" + sName + "'";
 
 MysqlData data = queryRecord(sql);
 if(data.size() == 0)
 {
 return "";
 }
 
 if(sName == data[0]["Variable_name"])
 {
 return data[0]["Value"];
 }
 
 return "";
}
 
void MySqlQuery::execute(const string& sSql)
{
 /**
 没有连上, 连接数据库
 */
 if(!db->m_bConnected)
 {
 db->connect();
 }
 
 _sLastSql = sSql;
 
 int iRet = mysql_real_query(_pstMql, sSql.c_str(), sSql.length());
 if(iRet != 0)
 {
 /**
 自动重新连接
 */
 int iErrno = mysql_errno(_pstMql);
 if (iErrno == 2013 || iErrno == 2006)
 {
 db->connect();
 iRet = mysql_real_query(_pstMql, sSql.c_str(), sSql.length());
 }
 }
 
 if (iRet != 0)
 {
 throw MySqlQuery_Exception("[MySqlQuery::execute]: mysql_query: [ " + sSql+" ] :" + string(mysql_error(_pstMql))); 
 }
}
 
MySqlQuery::MysqlData MySqlQuery::queryRecord(const string& sSql)
{
 MysqlData data;
 
 /**
 没有连上, 连接数据库
 */
 if(!db->m_bConnected)
 {
 db->connect();
 }
 
 _sLastSql = sSql;
 
 int iRet = mysql_real_query(_pstMql, sSql.c_str(), sSql.length());
 if(iRet != 0)
 {
 /**
 自动重新连接
 */
 int iErrno = mysql_errno(_pstMql);
 if (iErrno == 2013 || iErrno == 2006)
 {
 db->connect();
 iRet = mysql_real_query(_pstMql, sSql.c_str(), sSql.length());
 }
 }
 
 if (iRet != 0)
 {
 throw MySqlQuery_Exception("[MySqlQuery::execute]: mysql_query: [ " + sSql+" ] :" + string(mysql_error(_pstMql))); 
 }
 
 MYSQL_RES *pstRes = mysql_store_result(_pstMql);
 
 if(pstRes == NULL)
 {
 throw MySqlQuery_Exception("[MySqlQuery::queryRecord]: mysql_store_result: " + sSql + " : " + string(mysql_error(_pstMql)));
 }
 
 vector<string> vtFields;
 MYSQL_FIELD *field;
 while((field = mysql_fetch_field(pstRes)))
 {
 vtFields.push_back(field->name);
 }
 
 map<string, string> mpRow;
 MYSQL_ROW stRow;
 
 while((stRow = mysql_fetch_row(pstRes)) != (MYSQL_ROW)NULL)
 {
 mpRow.clear();
 unsigned long * lengths = mysql_fetch_lengths(pstRes);
 for(size_t i = 0; i < vtFields.size(); i++)
 {
 if(stRow[i])
 {
 mpRow[vtFields[i]] = string(stRow[i], lengths[i]);
 }
 else
 {
 mpRow[vtFields[i]] = "";
 }
 }
 
 data.data().push_back(mpRow);
 }
 
 mysql_free_result(pstRes);
 
 return data;
}
 
size_t MySqlQuery::updateRecord(const string &sTableName, const RECORD_DATA &mpColumns, const string &sCondition)
{
 string sSql = buildUpdateSQL(sTableName, mpColumns, sCondition);
 execute(sSql);
 
 return mysql_affected_rows(_pstMql);
}
 
size_t MySqlQuery::insertRecord(const string &sTableName, const RECORD_DATA &mpColumns)
{
 string sSql = buildInsertSQL(sTableName, mpColumns);
 execute(sSql);
 
 return mysql_affected_rows(_pstMql);
}
 
size_t MySqlQuery::replaceRecord(const string &sTableName, const RECORD_DATA &mpColumns)
{
 string sSql = buildReplaceSQL(sTableName, mpColumns);
 execute(sSql);
 
 return mysql_affected_rows(_pstMql);
}
 
size_t MySqlQuery::deleteRecord(const string &sTableName, const string &sCondition)
{
 ostringstream sSql;
 sSql << "delete from " << sTableName << " " << sCondition;
 
 execute(sSql.str());
 
 return mysql_affected_rows(_pstMql);
}
 
size_t MySqlQuery::getRecordCount(const string& sTableName, const string &sCondition)
{
 ostringstream sSql;
 sSql << "select count(*) as num from " << sTableName << " " << sCondition;
 
 MysqlData data = queryRecord(sSql.str());
 
 long n = atol(data[0]["num"].c_str());
 
 return n;
 
}
 
size_t MySqlQuery::getSqlCount(const string &sCondition)
{
 ostringstream sSql;
 sSql << "select count(*) as num " << sCondition;
 
 MysqlData data = queryRecord(sSql.str());
 
 long n = atol(data[0]["num"].c_str());
 
 return n;
}
 
int MySqlQuery::getMaxValue(const string& sTableName, const string& sFieldName,const string &sCondition)
{
 ostringstream sSql;
 sSql << "select " << sFieldName << " as f from " << sTableName << " " << sCondition << " order by f desc limit 1";
 
 MysqlData data = queryRecord(sSql.str());
 
 int n = 0;
 
 if(data.size() == 0)
 {
 n = 0;
 }
 else
 {
 n = atol(data[0]["f"].c_str());
 }
 
 return n;
}
 
bool MySqlQuery::existRecord(const string& sql)
{
 return queryRecord(sql).size() > 0;
}
 
long MySqlQuery::lastInsertID()
{
 return mysql_insert_id(_pstMql);
}
 
size_t MySqlQuery::getAffectedRows()
{
 return mysql_affected_rows(_pstMql);
}
 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
MySqlQuery::MysqlRecord::MysqlRecord(const map<string, string> &record):_record(record){}
 
const string& MySqlQuery::MysqlRecord::operator[](const string &s)
{
 map<string, string>::const_iterator it = _record.find(s);
 if(it == _record.end())
 {
 throw MySqlQuery_Exception("field '" + s + "' not exists.");
 }
 return it->second;
}
 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
vector<map<string, string> >& MySqlQuery::MysqlData::data()
{
 return _data;
}
 
size_t MySqlQuery::MysqlData::size()
{
 return _data.size();
}
 
MySqlQuery::MysqlRecord MySqlQuery::MysqlData::operator[](size_t i)
{
 return MysqlRecord(_data[i]);
}

std::string MySqlQuery::MysqlFiled::asString()
{
	if(sValue == "")
	{
		return std::string("");
	}
	char chTemp[1024] = {0};
	switch (type) {
	case FIELD_TYPE_DATE:
	case FIELD_TYPE_DATETIME:
	case FIELD_TYPE_TIME:
	case FIELD_TYPE_TIMESTAMP:
		int year, month, day, hour, minute, second;
		sscanf(sValue.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);//2018-03-31 00:00:00
		sprintf(chTemp, "%04d%02d%02d%02d%02d%02d", year, month, day, hour, minute, second);
		break;
	default:
		sprintf(chTemp, "%s\0",sValue.c_str());
		break;
	}

	return std::string(chTemp);
}

double MySqlQuery::MysqlFiled::asFloat()
{
	return atof(sValue.c_str());
}

int MySqlQuery::MysqlFiled::asInteger()
{
	return atoi(sValue.c_str());
}

long MySqlQuery::MysqlFiled::asLong()
{
	return atol(sValue.c_str());
}


void MySqlQuery::close()
{
	//db->close();
	if(_pMysqlRes)
	{
		if(_pMysqlRes)
  	{
 			mysql_free_result(_pMysqlRes);
 			_pMysqlRes = NULL;
  	}
	}
	_fSqlStmt == "";
	//disconnect();
}

void MySqlQuery::setSQL(const char *inSqlstmt)
{
//	char chTmp[2048] = {0};
//	sprintf(chTmp, "%s", inSqlstmt);
	_fSqlStmt = string(inSqlstmt);
}

void MySqlQuery::open(int prefetchRows)
{
	/**
 没有连上, 连接数据库
 */
 if(!db->m_bConnected)
 {
 		db->connect();
 }
 int iRet = mysql_real_query(_pstMql, _fSqlStmt.c_str(), _fSqlStmt.length());
 if(iRet != 0)
 {
 		/**
 		自动重新连接
 		*/
 		int iErrno = mysql_errno(_pstMql);
 		if (iErrno == 2013 || iErrno == 2006)
 		{
 				db->connect();
 				iRet = mysql_real_query(_pstMql, _fSqlStmt.c_str(), _fSqlStmt.length());
 		}
 }
 
 if (iRet != 0)
 {
 		throw MySqlQuery_Exception("[MySqlQuery::open]: mysql_query: [ " + _fSqlStmt+" ] :" + string(mysql_error(_pstMql))); 
 }
 
 _pMysqlRes = NULL;
 if(prefetchRows == 0)
 {
 		_pMysqlRes = mysql_store_result(_pstMql);
 }
 else
 {	
 		_pMysqlRes = mysql_use_result(_pstMql);
 }
 
 if(_pMysqlRes == NULL)
 {
 		throw MySqlQuery_Exception("[MySqlQuery::open]: mysql_store_result: " + _fSqlStmt + " : " + string(mysql_error(_pstMql)));
 }
	
	vFields.clear();
 MYSQL_FIELD *field;
 while((field = mysql_fetch_field(_pMysqlRes)))
 {
 		vFields.push_back(field->name);
 }
}

bool MySqlQuery::next()
{
	vFieldValue.clear();
	if (_pMysqlRes)
  {
  	_pMysqlRow = mysql_fetch_row(_pMysqlRes);
  	if(_pMysqlRow == NULL)
  	{
  		//mysql_free_result(_pMysqlRes);
  		return false;
  	}
  	else
  	{
  		MYSQL_FIELD *fields=mysql_fetch_fields(_pMysqlRes);
  		MysqlFiled chTmpValue;
  		for(int i = 0; i < vFields.size(); i++)
  		{
  			chTmpValue.type=fields[i].type;
  			if(_pMysqlRow[i] == NULL)
  			{
  				chTmpValue.sValue = "";
  			}
  			else
  			{

  				chTmpValue.sValue = string(_pMysqlRow[i]);
  			}
  			
  			vFieldValue.push_back(chTmpValue);
  		}
  		return true;
  	}
  }
  else
  {
        return false;
  }
}

bool MySqlQuery::execute(int iters)
{
	if(!db->m_bConnected)
 {
 		db->connect();
 }
 
 int iRet = mysql_real_query(_pstMql, _fSqlStmt.c_str(), _fSqlStmt.length());
 if(iRet != 0)
 {
 		/**
 		自动重新连接
 		*/
 		int iErrno = mysql_errno(_pstMql);
 		if (iErrno == 2013 || iErrno == 2006)
 		{
 				db->connect();
 				iRet = mysql_real_query(_pstMql, _fSqlStmt.c_str(), _fSqlStmt.length());
 		}
 }
 
 if (iRet != 0)
 {
 		throw MySqlQuery_Exception("[MySqlQuery::open]: mysql_query: [ " + _fSqlStmt+" ] :" + string(mysql_error(_pstMql))); 
 }
 
 _pMysqlRes = mysql_store_result(_pstMql);
 if(_pMysqlRes)
 {
 		mysql_free_result(_pMysqlRes);
 		_pMysqlRes = NULL;
 }
 
 return true;
}

bool MySqlQuery::commit()
{
	if(_pstMql)
	{
		mysql_commit(_pstMql);
	}
	
}

bool MySqlQuery::rollback()
{
	mysql_rollback(_pstMql);
}

MySqlQuery::MysqlFiled MySqlQuery::field(int index)
{
	if(vFields.size() == 0)
	{
		throw MySqlQuery_Exception("Field(i): sql statement is not presented");
	}
	if ((index >= 0) && (index < vFields.size()))
		return vFieldValue[index];
	else
		throw MySqlQuery_Exception("field index out of bound when call Field(i)");
}

MySqlQuery::MysqlFiled MySqlQuery::field(char const *fieldName)
{
	bool found = false;
	if(vFields.size() == 0)
	{
		throw MySqlQuery_Exception("Field(*fieldName): sql statement is not presented");
	}
	int i;
	for (i = 0; i < vFields.size(); i++) {
		found = compareStrNoCase(vFields[i].c_str(), fieldName);
		if (found)
			break;
	}
	if (found)
		return vFieldValue[i];
	else
		throw MySqlQuery_Exception("field fieldName is not exesit");
}

void MySqlQuery::setParameter(const char *paramName, const char* paramValue, bool isOutput)
{
	char chTemp[128] = {0};
	sprintf(chTemp, ":%s", paramName);
	char chValue[1024] = {0};
	sprintf(chValue,"\'%s\'", paramValue);
	_fSqlStmt = Replace(_fSqlStmt, chTemp, chValue);
}

void MySqlQuery::setParameter(const char *paramName, int paramValue, bool isOutput)
{
	char chTemp[128] = {0};
	sprintf(chTemp, ":%s", paramName);
	char chValue[1024] = {0};
	sprintf(chValue,"%d", paramValue);
	_fSqlStmt = Replace(_fSqlStmt, chTemp, chValue);
}

void MySqlQuery::setParameter(const char *paramName, long paramValue, bool isOutput)
{
	char chTemp[128] = {0};
	sprintf(chTemp, ":%s", paramName);
	char chValue[1024] = {0};
	sprintf(chValue,"%ld", paramValue);
	_fSqlStmt = Replace(_fSqlStmt, chTemp, chValue);
}

void MySqlQuery::setParameter(const char *paramName, double paramValue, bool isOutput )
{
	char chTemp[128] = {0};
	sprintf(chTemp, ":%s", paramName);
	char chValue[1024] = {0};
	sprintf(chValue,"%f", paramValue);
	_fSqlStmt = Replace(_fSqlStmt, chTemp, chValue);
}

int MySqlQuery::fieldCount()
{
	return vFields.size();
}
