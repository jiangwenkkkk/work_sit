//MySqlQuery.h
 
#ifndef __MYSQL_QUERY_H__
#define __MYSQL_QUERY_H__
 
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <vector>
#include <string>
using namespace std;
 
#include <mysql.h>

const int PREFETCH_ROWS = 200;
/*********************
*@brief 数据库异常类
**********************/
class MySqlQuery_Exception //: public TC_Exception
{
public:
 MySqlQuery_Exception(const string &sBuffer):errorInfo(sBuffer){errSQL[0]='\0'; errNo=0; m_iErrCode=-1;}; //: TC_Exception(sBuffer){};
 ~MySqlQuery_Exception() throw(){}; 
 
 string errorInfo;

 const char *getErrMsg() {return errorInfo.c_str();};
 const char *getErrSrc() const{return errorInfo.c_str();};
int getErrCode() {return -1;};

private:
char    errSQL[4*1024+1];           //发生错误的sql语句
int errNo;                                      //错误号
int m_iErrCode;
};
 
/***********************
* @brief 数据库配置接口
***********************/
struct DBConf
{
 
 string _host;//主机地址
 string _user; //用户名 
 string _password;//密码
 string _database; //数据库
 string _charset; //字符集
 int _port;//端口
 int _flag; //客户端标识
 
 /*****************
 * @brief 构造函数
 *****************/
 DBConf():_port(0), _flag(0){}
 
 /**********************************
 * @brief 读取数据库配置. 
 * @param mpParam 存放数据库配置的map 
 * dbhost: 主机地址
 * dbuser:用户名
 * dbpass:密码
 * dbname:数据库名称
 * dbport:端口
 **********************************/
 void loadFromMap(const map<string, string> &mpParam)
 {
 map<string, string> mpTmp = mpParam;
 
 _host = mpTmp["dbhost"];
 _user = mpTmp["dbuser"];
 _password = mpTmp["dbpass"];
 _database = mpTmp["dbname"];
 _charset = mpTmp["charset"];
 _port = atoi(mpTmp["dbport"].c_str());
 _flag = 0;
 
 if(mpTmp["dbport"] == "")
 {
 _port = 3306;
 }
 }
};

class MySqlDataBase
{
public:
 MySqlDataBase();
 
 MySqlDataBase(const string& sHost, const string& sUser = "", const string& sPasswd = "", const string& sDatabase = "", const string &sCharSet = "", int port = 0, int iFlag = 0);
 
 /**
 * @brief 构造函数. 
 * @param tcDBConf 数据库配置
 */
 MySqlDataBase(const DBConf& tcDBConf);
 
 /**
 * @brief 析构函数.
 */
 ~MySqlDataBase();
 
 /**
 * @brief 初始化. 
 * 
 * @param sHost 主机IP
 * @param sUser 用户
 * @param sPasswd 密码
 * @param sDatebase 数据库
 * @param port 端口
 * @param iUnixSocket socket
 * @param iFlag 客户端标识
 * @return 无
 */
 void init(const string& sHost, const string& sUser = "", const string& sPasswd = "", const string& sDatabase = "", const string &sCharSet = "", int port = 0, int iFlag = 0);
 
 /**
 * @brief 初始化. 
 * 
 * @param tcDBConf 数据库配置
 */
 void init(const DBConf& tcDBConf);
 
 /**
 * @brief 连接数据库. 
 * 
 * @throws MySqlQuery_Exception
 * @return 无
 */
 void connect();
 
 void close();
 
 /**
 * @brief 断开数据库连接. 
 * @return 无
 */
 void disconnect();

 /**
 * @brief 直接获取数据库指针. 
 * 
 * @return MYSQL* 数据库指针
 */
 MYSQL *getMysql();
 /**
 * 是否已经连接
 */
 bool m_bConnected;
 MYSQL_RES *_pMysqlRes;        // MySQL结果集
private:
 
 /**
 * 数据库指针
 */
 MYSQL *m_pstMql;
 
 /**
 * 数据库配置
 */
 DBConf _dbConf;

};
/**************************************************************
* @brief:MySQL数据库操作类 
* @feature:非线程安全，通常一个线程一个MySqlQuery对象；
* 对于insert/update可以有更好的函数封装，保证SQL注入；
* MySqlQuery::DB_INT表示组装sql语句时，不加””和转义；
* MySqlQuery::DB_STR表示组装sql语句时，加””并转义；
**************************************************************/
class MySqlQuery{
 
public:
 /**
 * @brief 构造函数
 */
 MySqlQuery(MySqlDataBase *oradb); 
 /**
 * @brief 析构函数.
 */
 ~MySqlQuery();
 
 string getVariables(const string &sName);
 
 /**
 * @brief 直接获取数据库指针. 
 * 
 * @return MYSQL* 数据库指针
 */
 MYSQL *getMysql();
 
 /**
 * @brief 字符转义. 
 * 
 * @param sFrom 源字符串
 * @param sTo 输出字符串
 * @return 输出字符串
 */
 string escapeString(const string& sFrom);
 
 /**
 * @brief 更新或者插入数据. 
 * 
 * @param sSql sql语句
 * @throws MySqlQuery_Exception
 * @return
 */
 void execute(const string& sSql);
 
 void close();                                                   //关闭SQL语句，以准备接收下一个sql语句
 void setSQL(const char *inSqlstmt);                             //设置Sqlstatement
 void open(int prefetchRows=0);          //打开SQL SELECT语句返回结果集PREFETCH_ROWS
 bool next();                                                    //移动到下一个记录
 bool execute(int iters=1);                            //执行非SELECT语句,没有返回结果集
 bool commit();                                                  //事务提交
 bool rollback();

 int  rowsAffected() { return mysql_affected_rows(_pstMql);};   //DELETE/UPDATE/INSERT语句修改的记录数目

 /**
 * @brief mysql的一条记录
 */
 class MysqlRecord
 {
 public:
 /**
 * @brief 构造函数.
 * 
 * @param record
 */
 MysqlRecord(const map<string, string> &record);
 
 /**
 * @brief 获取数据，s一般是指数据表的某个字段名 
 * @param s 要获取的字段
 * @return 符合查询条件的记录的s字段名
 */
 const string& operator[](const string &s);
 protected:
 const map<string, string> &_record;
 };
 
 /**
 * @brief 查询出来的mysql数据
 */
 class MysqlData
 {
 public:
 /**
 * @brief 所有数据.
 * 
 * @return vector<map<string,string>>&
 */
 vector<map<string, string> >& data();
 
 /**
 * 数据的记录条数
 * 
 * @return size_t
 */
 size_t size();
 
 /**
 * @brief 获取某一条记录. 
 * 
 * @param i 要获取第几条记录 
 * @return MysqlRecord类型的数据，可以根据字段获取相关信息，
 */
 MysqlRecord operator[](size_t i);
 
 protected:
 vector<map<string, string> > _data;
 };
 
 
 class MysqlFiled
 {
 	public:
 		enum_field_types type;
 		string sValue;
 		std::string asString();
    double  asFloat();
    int     asInteger();
    long    asLong();

    void        asClobBufferUTF16(unsigned char* &pDataBuf, unsigned int *bufLength, bool bReplace=true){};//TODO
 };
 /**
 * @brief Query Record. 
 * 
 * @param sSql sql语句
 * @throws MySqlQuery_Exception
 * @return MysqlData类型的数据，可以根据字段获取相关信息
 */
 MysqlData queryRecord(const string& sSql);
 
 /**
 * @brief 定义字段类型， 
 * DB_INT:数字类型 
 * DB_STR:字符串类型
 */
 enum FT
 {
 DB_INT, 
 DB_STR, 
 };
 
 /**
 * 数据记录
 */
 typedef map<string, pair<FT, string> > RECORD_DATA;
 
 /**
 * @brief 更新记录. 
 * 
 * @param sTableName 表名
 * @param mpColumns 列名/值对
 * @param sCondition where子语句,例如:where A = B
 * @throws MySqlQuery_Exception
 * @return size_t 影响的行数
 */
 size_t updateRecord(const string &sTableName, const map<string, pair<FT, string> > &mpColumns, const string &sCondition);
 
 /**
 * @brief 插入记录. 
 * 
 * @param sTableName 表名
 * @param mpColumns 列名/值对
 * @throws MySqlQuery_Exception
 * @return size_t 影响的行数
 */
 size_t insertRecord(const string &sTableName, const map<string, pair<FT, string> > &mpColumns);
 
 /**
 * @brief 替换记录. 
 * 
 * @param sTableName 表名
 * @param mpColumns 列名/值对
 * @throws MySqlQuery_Exception
 * @return size_t 影响的行数
 */
 size_t replaceRecord(const string &sTableName, const map<string, pair<FT, string> > &mpColumns);
 
 /**
 * @brief 删除记录. 
 * 
 * @param sTableName 表名
 * @param sCondition where子语句,例如:where A = B
 * @throws MySqlQuery_Exception
 * @return size_t 影响的行数
 */
 size_t deleteRecord(const string &sTableName, const string &sCondition = "");
 
 /**
 * @brief 获取Table查询结果的数目. 
 * 
 * @param sTableName 用于查询的表名
 * @param sCondition where子语句,例如:where A = B
 * @throws MySqlQuery_Exception
 * @return size_t 查询的记录数目
 */
 size_t getRecordCount(const string& sTableName, const string &sCondition = "");
 
 /**
 * @brief 获取Sql返回结果集的个数. 
 * 
 * @param sCondition where子语句,例如:where A = B
 * @throws MySqlQuery_Exception
 * @return 查询的记录数目
 */
 size_t getSqlCount(const string &sCondition = "");
 
 /**
 * @brief 存在记录. 
 * 
 * @param sql sql语句
 * @throws MySqlQuery_Exception
 * @return 操作是否成功
 */
 bool existRecord(const string& sql);
 
 /**
 * @brief 获取字段最大值. 
 * 
 * @param sTableName 用于查询的表名
 * @param sFieldName 用于查询的字段
 * @param sCondition where子语句,例如:where A = B
 * @throws MySqlQuery_Exception
 * @return 查询的记录数目
 */
 int getMaxValue(const string& sTableName, const string& sFieldName, const string &sCondition = "");
 
 /**
 * @brief 获取auto_increment最后插入得ID. 
 * 
 * @return ID值
 */
 long lastInsertID();
 
 /**
 * @brief 构造Insert-SQL语句. 
 * 
 * @param sTableName 表名
 * @param mpColumns 列名/值对
 * @return string insert-SQL语句
 */
 string buildInsertSQL(const string &sTableName, const map<string, pair<FT, string> > &mpColumns);
 
 /**
 * @brief 构造Replace-SQL语句. 
 * 
 * @param sTableName 表名
 * @param mpColumns 列名/值对
 * @return string insert-SQL语句
 */
 string buildReplaceSQL(const string &sTableName, const map<string, pair<FT, string> > &mpColumns);
 
 /**
 * @brief 构造Update-SQL语句. 
 * 
 * @param sTableName 表名
 * @param mpColumns 列名/值对
 * @param sCondition where子语句
 * @return string Update-SQL语句
 */
 string buildUpdateSQL(const string &sTableName,const map<string, pair<FT, string> > &mpColumns, const string &sCondition);
 
 /**
 * @brief 获取最后执行的SQL语句.
 * 
 * @return SQL语句
 */
 string getLastSQL() { return _sLastSql; }
 
 /**
 * @brief 获取查询影响数
 * @return int
 */
 size_t getAffectedRows();
protected:
 /**
 * @brief copy contructor，只申明,不定义,保证不被使用 
 */
 MySqlQuery(const MySqlQuery &tcMysql);
 
 /**
 * 
 * @brief 只申明,不定义,保证不被使用
 */
 MySqlQuery &operator=(const MySqlQuery &tcMysql);
 
public:
	MysqlFiled field(int index);
	MysqlFiled field(char const *fieldName);
	void setParameter(const char *paramName, const char* paramValue, bool isOutput = false);
  void setParameter(const char *paramName, int paramValue, bool isOutput = false);
  void setParameter(const char *paramName, long paramValue, bool isOutput = false);
  void setParameter(const char *paramName, double paramValue, bool isOutput = false) ;
  int fieldCount();
private:
 
 /**
 * 数据库指针
 */
 MYSQL *_pstMql;
 MYSQL_RES *_pMysqlRes;        // MySQL结果集
 MYSQL_ROW  _pMysqlRow;        // MySQL一行结果
 MySqlDataBase *db;
 /**
 * 数据库配置
 */
 DBConf _dbConf;
 
 /**
 * 是否已经连接
 */
 bool _bConnected;
 
 /**
 * 最后执行的sql
 */
 string _sLastSql;
 
	//执行的SQL
	string _fSqlStmt;
	//单条记录值
	vector<MysqlFiled> vFieldValue;
	//字段名称
	vector<string> vFields;
 
};

class auto_dbclose {
public:
	auto_dbclose(MySqlQuery *p) :
			ptr(p) {
	}

	MySqlQuery & operator*() const {
		return *ptr;
	}
	MySqlQuery * operator->() const {
		return ptr;
	}
	~auto_dbclose() {
		ptr->close();
	}
private:
	MySqlQuery *ptr; // raw ptr to object
};

#endif //__MYSQL_QUERY_H__
