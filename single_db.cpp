//
// Created by james on 2018/10/27.
//


#include <MySqlQuery.h>
#include <iostream>
#include "MySqlQuery.h"

using namespace std;

class SingleDb{
private:
	SingleDb();

public:
	static MySqlQuery& getInstance()
	{

		MySqlDataBase mySqlDataBase;

		mySqlDataBase.init( "10.37.54.84", "userinfo", "CHY_userinfo@123", "USERINFO", "utf8", 8100 );
		try {
			mySqlDataBase.connect();
		} catch ( MySqlQuery_Exception& excep ) {
			cout << excep.errorInfo;
		}

		//初始化mysql对象并建立连接

		static MySqlQuery instance( &mySqlDataBase);
		return instance;
	}
};

int main()
{

}