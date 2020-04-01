//
// Created by james on 2018/9/12.
//

#include <iostream>
#include "MySqlQuery.h"
#include <fstream>
#include <regex>

using namespace std;


using NameNum = std::pair<string, int>;
using TableNumVc = vector<NameNum>;

class NodistTableNum {
private:
	TableNumVc datas;
	string m_like_table;
public:
	NodistTableNum(string like_table) : m_like_table(like_table) {}

	void setLikeTable(string like_table) {
		m_like_table = like_table;
	}

	TableNumVc getTabNum(MySqlQuery &db) {
		vector<string> sql_vc = get_sql(db);

		for (auto item : sql_vc) {
			db.setSQL(item.c_str());
			db.setParameter("ORG_ID", 51001875);
			db.open();
			while (db.next()) {
				//	datas.push_back(make_pair("11",11));
				pair<string, int> tmp = make_pair(db.field("table_name").asString().c_str(),
												  db.field("num").asLong());
				datas.push_back(tmp);
			}
		}
		return datas;
	}

//	vector<string, int> get_sum()
//	{
//		vector<string, int> sum_like;
//		for (auto item : datas)
//		{
//
//			if (item.first)
//		}
//	};

private:
	vector<string> get_sql(MySqlQuery &db) {
		vector<string> sqls;
//		string sql = "select concat(\n"
//					 "    'select \"',\n"
//					 "    TABLE_name,\n"
//					 "    '\" as table_name , count(distinct(UNIQ_NO)) as num from ',\n"
//					 "    TABLE_name,\n"
//					 "  \";\"\n"
//					 ") as sqla from information_schema.tables\n"
//					 "where TABLE_SCHEMA='userinfo2' AND TABLE_name REGEXP \""+m_like_table+"\"\n"
//					 "ORDER BY TABLE_name;";

		string sql = "select concat(\n"
					 "    'select \"',\n"
					 "    TABLE_name,\n"
					 "    '\" as table_name , count(1) as num from ',\n"
					 "    TABLE_name,\n"
					 "  \";\"\n"
					 ") as sqla from information_schema.tables\n"
					 "where TABLE_SCHEMA='userinfo2' AND TABLE_name REGEXP \"" + m_like_table + "\"\n"
																								"ORDER BY TABLE_name;";


//		string sql = "select concat(\n"
//					 "    'select  count(*) from ',\n"
//					 "    TABLE_name\n"
//					 ") as sqla from information_schema.tables\n"
//					 "where TABLE_SCHEMA='userinfo' AND TABLE_name like \"iot_serv_%\"\n"
//					 "ORDER BY TABLE_name;";

		cout << sql << endl;
		try {
			db.setSQL(sql.c_str());
			db.setParameter("ORG_ID", 51001875);
			db.open();
			int i = 0;
			while (db.next()) {
				i++;
				sqls.push_back(db.field("sqla").asString());
			}
			printf("Total	：%d \n", i);

		} catch (MySqlQuery_Exception &excep) {

			cout << excep.errorInfo;

		}
		return sqls;
	}
};


class TableNumView {
public:
	void printTableNum(TableNumVc tv) {
		for (auto item : tv) {
			cout << item.first << "\t" << item.second << endl;
		}

	}
};


class TableNumController {
private:
	NodistTableNum m_model;
	TableNumView m_view;
public:
	TableNumController(NodistTableNum model, TableNumView view) : m_model(model), m_view(view) {
	}

	void SetTableName(string table_name) {
		m_model.setLikeTable(table_name);
	}

	TableNumVc GetTableNumVc(MySqlQuery &db) {
		return m_model.getTabNum(db);
	}

	void UpdateView(MySqlQuery &db) {
		m_view.printTableNum(m_model.getTabNum(db));
	}
};

class con_info {
public:
	string ip;
	string user;
	string passwd;
	string db;
	int port;

};

void print_connect(con_info c_info) {
	cout << c_info.ip << "\t"
		 << c_info.user << "\t" <<
		 c_info.db << endl;
}

int main(int argc, char **argv) {


	streambuf *coutBuf = cout.rdbuf();

	ofstream of(argv[2]);
	// 获取文件out.txt流缓冲区指针
	streambuf *fileBuf = of.rdbuf();

	// 设置cout流缓冲区指针为out.txt的流缓冲区指针
	cout.rdbuf(fileBuf);

	MySqlDataBase mySqlDataBase;
//	mySqlDataBase.init( "127.0.0.1", "root", "55668899", "test_poco_mysql", "utf8", 3306 );
//	mySqlDataBase.init( "10.37.54.84", "userinfo", "CHY_userinfo@123", "USERINFO", "utf8", 8100 );
//	mySqlDataBase.init( "10.37.54.113", "userinfo", "CHY_userinfo@123", "USERINFO", "utf8", 8100 );

	con_info userinfo2_113  = {"10.37.54.113",
							   "userinfo2",
							   "CHY_userinfo123",
							   "USERINFO2",
							   8100 };
//	con_info userinfo2_113 = {"10.37.54.113",
//							  "userinfo",
//							  "CHY_userinfo@123",
//							  "USERINFO",
//							  8100};

	con_info all = userinfo2_113;

	print_connect(all);
	mySqlDataBase.init(all.ip, all.user, all.passwd,
					   all.db, "utf8", all.port);


	try {
		mySqlDataBase.connect();
	} catch (MySqlQuery_Exception &excep) {
		cout << excep.errorInfo;
		return -1;
	}

	//初始化mysql对象并建立连接
	MySqlQuery mySqlQuery(&mySqlDataBase);

	string tablename = argv[1];
	cout << tablename << endl;
	NodistTableNum model(tablename);
	TableNumView view;
	TableNumController controller(model, view);

	controller.UpdateView(mySqlQuery);

	mySqlQuery.close();

	of.flush();
	of.close();

	return 0;
}

//select  count(distinct(UNIQ_NO))  from  iot_product_offer_instance_31;