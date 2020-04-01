/****************************************************
*@brief:MySqlQuery demo
*@autor:lvlv
*@date:2016.06.12
*@MySQL version:MySQL Community Server 5.6.30 (GPL)
****************************************************/

#include <string.h>
#include <iostream>
#include <string>
using namespace std;

#include "MySqlQuery.h"

extern "C"{
int	 sprintf(char * __restrict, const char * __restrict, ...) __printflike(2, 3) __swift_unavailable("Use snprintf instead.");

}

int query()
{
	MySqlDataBase mySqlDataBase;
	mySqlDataBase.init( "127.0.0.1", "root", "55668899", "test_poco_mysql", "utf8", 3306 );
	try {
		mySqlDataBase.connect();
	} catch ( MySqlQuery_Exception& excep ) {
		cout << excep.errorInfo;
		return -1;
	}

    //初始化mysql对象并建立连接
	MySqlQuery mySqlQuery( &mySqlDataBase );;


	char sql[2048] = { 0 };

//	sprintf( sql,
//			 "select ifnull(a.ORG_ID,0) ORG_ID, "
//			 "substr(replace(a.channel_name,CONCAT(char(13),char(10)),' ') ,1,100)	channel_name,"
//			 "ifnull(a.CHANNEL_CLASS, '') CHANNEL_CLASS, "
//			 "ifnull(a.region_id, 0) region_id "
//			 "from CHANNEL a where a.org_id=:ORG_ID"
//		   );


//	try {
//		mySqlQuery.setSQL( sql );
//		mySqlQuery.setParameter( "ORG_ID", 51001875 );
//		mySqlQuery.open();
//		int i = 0;
//		while ( mySqlQuery.next() ) {
//			i++;
//			char a[1024] = {0};
//			sprintf( a, "%s", mySqlQuery.field( "channel_name" ).asString().c_str() );
//			char b[1024] = {0};
//			sprintf( b, "%s", mySqlQuery.field( 2 ).asString().c_str() );
//			//printf("%s\n",mySqlQuery.field("channel_name").asString());
//			//printf("%s\n",mySqlQuery.field(2).asString());
//			printf( "%ld	%s	%s	%ld \n", mySqlQuery.field( "ORG_ID" ).asLong(),
//					a,
//					b, mySqlQuery.field( "region_id" ).asLong() );
//		}
//		printf( "Total	：%d \n", i );
//		mySqlQuery.close();
//	} catch ( MySqlQuery_Exception& excep ) {
//		cout << excep.errorInfo;
//		return -1;
//	}

	sprintf( sql,
			 "SELECT * FROM Test"
	);
	try {
		mySqlQuery.setSQL( sql );
		mySqlQuery.setParameter( "ORG_ID", 51001875 );
		mySqlQuery.open();
		int i = 0;
		while ( mySqlQuery.next() ) {
			i++;
			char a[1024] = {0};
			sprintf( a, "%s", mySqlQuery.field( "id" ).asString().c_str() );
			char b[1024] = {0};
			sprintf( b, "%s", mySqlQuery.field( "name" ).asString().c_str() );
			//printf("%s\n",mySqlQuery.field("channel_name").asString());
			//printf("%s\n",mySqlQuery.field(2).asString());
			printf( "%ld	%s	%s	%s \n", mySqlQuery.field( "id" ).asLong(),
					a,
					b, mySqlQuery.field( "name" ).asString().c_str() );
		}
		printf( "Total	：%d \n", i );
		mySqlQuery.close();
	} catch ( MySqlQuery_Exception& excep ) {
		cout << excep.errorInfo;
		return -1;
	}
	return 0;

}


int insert()
{
	MySqlDataBase mySqlDataBase;
	mySqlDataBase.init( "127.0.0.1", "root", "55668899", "test_poco_mysql", "utf8", 3306 );
	try {
		mySqlDataBase.connect();
	} catch ( MySqlQuery_Exception& excep ) {
		cout << excep.errorInfo;
		return -1;
	}

    //初始化mysql对象并建立连接
	MySqlQuery mySqlQuery( &mySqlDataBase );;


	char sql[2048] = { 0 };

//	sprintf( sql,
//			 "insert  into `ip_whitelist`(`id`,`ip`,`iptype`) values (4,'183.208.24.115',1);"
//		   );
//
	sprintf( sql,
			 "insert  into `Test`(`id`,`name`) values (4,'183.208.24.115');"
		   );
	try {
		int num = 0;
		mySqlQuery.setSQL( sql );
		mySqlQuery.execute(num);
	    mySqlQuery.commit();
		mySqlQuery.close();

		cout << "num:" << num << endl;
	} catch ( MySqlQuery_Exception& excep ) {
		cout << excep.errorInfo;
		return -1;
	}
	return 0;

}


int createtable()
{
	MySqlDataBase mySqlDataBase;
	mySqlDataBase.init( "127.0.0.1", "root", "55668899", "test_poco_mysql", "utf8", 3306 );
	try {
		mySqlDataBase.connect();
	} catch ( MySqlQuery_Exception& excep ) {
		cout << excep.errorInfo;
		return -1;
	}

	//初始化mysql对象并建立连接
	MySqlQuery mySqlQuery( &mySqlDataBase );


	char sql[2048] = { 0 };

	sprintf( sql,
			 "CREATE TABLE `account_statement` ("
  "`id` int(10) NOT NULL AUTO_INCREMENT,"
  "`ip` varchar(50) DEFAULT NULL COMMENT '请求ip地址',"
  "`account_id` int(10) DEFAULT NULL COMMENT '用户账户id',"
  "`user_id` int(10) DEFAULT NULL COMMENT '用户id',"
  "`plan_id` int(10) DEFAULT NULL COMMENT '套餐id',"
  "`money` decimal(10,2) DEFAULT NULL COMMENT '对账金额',"
  "`merchantId` varchar(50) DEFAULT NULL COMMENT '对账第三方',"
  "`status` int(4) DEFAULT NULL COMMENT '1:未对账，2已对账',"
  "`create_time` datetime DEFAULT NULL COMMENT '创建时间',"
  "`account_time` datetime DEFAULT NULL COMMENT '对账时间',"
  "PRIMARY KEY (`id`)"
") ENGINE=InnoDB DEFAULT CHARSET=utf8;"
		   );
	try {
		int num = 0;
		mySqlQuery.setSQL( sql );
		mySqlQuery.execute(num);
		mySqlQuery.commit();
		mySqlQuery.close();
		cout << "num:" << num << endl;
	} catch ( MySqlQuery_Exception& excep ) {
		cout << excep.errorInfo;
		return -1;
	}
	return 0;

}

int main( int argc, char* argv[] )
{

//    createtable();
//    insert();
    query();
    
    return 0;
}
