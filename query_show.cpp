//
// Created by james on 2018/9/12.
//

#include <iostream>
#include "find_data.h"
#include "MySqlQuery.h"

extern const string Ctc_data::all_prin;

int main()
{
	MySqlDataBase mySqlDataBase;
//	mySqlDataBase.init( "127.0.0.1", "root", "55668899", "test_poco_mysql", "utf8", 3306 );
	mySqlDataBase.init( "10.142.234.129", "roam", "roam@123", "ROAM_DATA", "utf8", 9018 );
	try {
		mySqlDataBase.connect();
	} catch ( MySqlQuery_Exception& excep ) {
		cout << excep.errorInfo;
		return -1;
	}

	//初始化mysql对象并建立连接
	MySqlQuery mySqlQuery( &mySqlDataBase );;

	Ctc_data::Data_pro data;
	data.query_sended_pro_file(mySqlQuery, "898");
	data.query_dispatch_pro(mySqlQuery);
	auto prov_names = data.get_sen_pro();



//
//	for (auto item : prov_names)
//	{
//		cout << item;
//	}

	for (auto item: data.get_sen_pro_name())
	{
		cout << item << endl;
	}

	string map_name = "010,北京\n"
					  "020,广东\n"
					  "021,上海\n"
					  "022,天津\n"
					  "023,重庆\n"
					  "024,辽宁\n"
					  "025,江苏\n"
					  "027,湖北\n"
					  "028,四川\n"
					  "029,陕西\n"
					  "311,河北\n"
					  "351,山西\n"
					  "371,河南\n"
					  "431,吉林\n"
					  "451,黑龙江\n"
					  "471,内蒙\n"
					  "531,山东\n"
					  "551,安徽\n"
					  "571,浙江\n"
					  "591,福建\n"
					  "731,湖南\n"
					  "771,广西\n"
					  "791,江西\n"
					  "851,贵州\n"
					  "871,云南\n"
					  "891,西藏\n"
					  "898,海南\n"
					  "931,甘肃\n"
					  "951,宁夏\n"
					  "971,青海\n"
					  "991,新疆";

	map<string, string> num_prin;

	vector<string> prin = Ctc_data::split_vector(map_name, '\n');


	vector<vector<string>> pairs;
	for (auto item : prin)
	{
		pairs.push_back(Ctc_data::split_vector(item, ','));
	}

	for (auto item : pairs)
	{
		num_prin.insert(make_pair(item[0], item[1]));
	}

//	for ( auto it = num_prin.begin(); it != num_prin.end(); ++it)
//	{
//		cout << it->first << " : " << it->second << endl;
//	}


	vector<string> have_name = data.get_sen_pro_name();

	vector<string> find_in_map;



	for (auto it = have_name.begin(), it_end = have_name.end(); it != it_end; ++it)
	{
		cout << num_prin[*it];
		if (it != (it_end-1))
			cout << ",";
		find_in_map.push_back(num_prin[*it]);
	}
	cout << "(" << have_name.size() << ")" << endl;


	cout << "have do precent: " << have_name.size()/30.0 << endl;
	cout << endl;
	vector<string> v_all_prin = Ctc_data::split_vector(Ctc_data::all_prin, ',');

	Ctc_data::print_row(v_all_prin, find_in_map);

	cout << endl;

}