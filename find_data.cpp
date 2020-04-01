//
// Created by james on 2018/9/12.
//

#include "find_data.h"
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include "MySqlQuery.h"

namespace Ctc_data{
	using namespace std;

	vector<string> split_vector(const string& s, const char c)
	{
		vector<string> re;
		string buf;
		for(auto n:s)
		{
			if (n != c) buf.push_back(n);
			else if(n == c && buf != "")
			{
				re.push_back(buf);
				buf = "";
			}
		}
		if (buf != "") re.push_back(buf);
		return re;
	}

	void print_row(vector<string>all, vector<string> one)
	{
		for(auto item : all)
		{
			if (find(one.begin(), one.end(), item) != one.end())
			{
				cout << "√" << "\t";
			} else{
				cout << "\t";
			}
		}
	}

	vector<string> have_sent_data_provin() {

		return vector<string>();
	}



//	int query()
//	{
//		MySqlDataBase mySqlDataBase;
//		mySqlDataBase.init( "127.0.0.1", "root", "55668899", "test_poco_mysql", "utf8", 3306 );
//		try {
//			mySqlDataBase.connect();
//		} catch ( MySqlQuery_Exception& excep ) {
//			cout << excep.errorInfo;
//			return -1;
//		}
//
//		//初始化mysql对象并建立连接
//		MySqlQuery mySqlQuery( &mySqlDataBase );;
//
//
//		char sql[2048] = { 0 };
//
//
//		sprintf( sql,
//				 "SELECT * FROM Test"
//		);
//		try {
//			mySqlQuery.setSQL( sql );
//			mySqlQuery.setParameter( "ORG_ID", 51001875 );
//			mySqlQuery.open();
//			int i = 0;
//			while ( mySqlQuery.next() ) {
//				i++;
//				char a[1024] = {0};
//				sprintf( a, "%s", mySqlQuery.field( "id" ).asString().c_str() );
//				char b[1024] = {0};
//				sprintf( b, "%s", mySqlQuery.field( "name" ).asString().c_str() );
//				//printf("%s\n",mySqlQuery.field("channel_name").asString());
//				//printf("%s\n",mySqlQuery.field(2).asString());
//				printf( "%ld	%s	%s	%s \n", mySqlQuery.field( "id" ).asLong(),
//						a,
//						b, mySqlQuery.field( "name" ).asString().c_str() );
//			}
//			printf( "Total	：%d \n", i );
//			mySqlQuery.close();
//		} catch ( MySqlQuery_Exception& excep ) {
//			cout << excep.errorInfo;
//			return -1;
//		}
//		return 0;
//
//	}


	int Data_pro::query_sended_pro_file(MySqlQuery &mySqlQuery, const string &prov_num) {
		char sql[2048] = {0};

	//	string prov_num = "371";
		string query = "select distinct mlog.input_file  from message_log mlog\n"
					   "where  mlog.CREATE_TIME >=1536202800\n"
					   "and substr(mlog.input_file,16,3)="+prov_num+"\n"
					   "AND mlog.MODE_CODE LIKE '11*_%' ESCAPE'*'";
		strcpy(sql, query.c_str());

		try{
			mySqlQuery.setSQL(sql);
			mySqlQuery.setParameter( "ORG_ID", 51001875 );
			mySqlQuery.open();
			int i = 0;
			while (mySqlQuery.next())
			{
				i++;
				char a[1024] = {0};
				_send_pro_name_files.push_back(mySqlQuery.field("input_file").asString());
			}
			printf( "Total	：%d \n", i );
			mySqlQuery.close();
		}catch ( MySqlQuery_Exception& excep ) {
			cout << excep.errorInfo;
			return -1;
		}
		return 0;
	}

	vector<string> Data_pro::get_sen_pro() {
		return _send_pro_name_files;
	}

	int Data_pro::query_dispatch_pro(MySqlQuery &mySqlQuery) {
		char sql[110480] = {0};
		string files;
		for (auto it = _send_pro_name_files.begin(), it_end = _send_pro_name_files.end(); it != it_end; ++it)
		{
			files += "'" + (*it) + "'";
			if (it != it_end-1)
			{
				files+=",";
			}
		}

//		files += "'LNIG_2018091216931.00056.01'";
//

		string query = "select  distinct substr(t.output_file,16,3) as id from message_log t\n"
					   "where  t.input_file in("+files+
					   ")\n"
					   "and t.mode_code like '%1000178%' ORDER BY substr(t.output_file,16,3);";

//		string query = "select  distinct substr(t.output_file,16,3) as id from message_log t\n"
//					   "where  t.input_file in('LNIG_2018091216931.00056.01',\n"
//					   "'LNIG_2018091216931.00056.01',\n"
//					   "'LNIG_2018091216931.00056.01')\n"
//					   "and t.mode_code like '%1000178%' ORDER BY substr(t.output_file,16,3);";
		strcpy(sql, query.c_str());


		try{
			mySqlQuery.setSQL(sql);
			mySqlQuery.setParameter( "ORG_ID", 51001875 );
			mySqlQuery.open();
			int i = 0;
			while (mySqlQuery.next())
			{
				i++;
				char a[1024] = {0};
				_get_pro_name.push_back(mySqlQuery.field("id").asString());
			}
			printf( "Total	：%d \n", i );
			mySqlQuery.close();
		}catch ( MySqlQuery_Exception& excep ) {
			cout << excep.errorInfo;
			return -1;
		}
		return 0;
	}

	vector<string> Data_pro::get_sen_pro_name() {
		return _get_pro_name;
	}
}

