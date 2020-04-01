//
// Created by james on 2018/9/12.
//

#ifndef FIND_USE_FIND_DATA_H
#define FIND_USE_FIND_DATA_H

#include <string>
#include <vector>
#include "MySqlQuery.h"

using namespace std;

namespace Ctc_data{
	const string all_prin = "安徽,福建,河南,宁夏,辽宁,四川,山东,江苏,内蒙古,广西,浙江,江西,湖北,黑龙江,上海,河北,天津,山西,吉林,陕西,贵州,云南,青海,海南,北京,广东,新疆,甘肃,重庆,西藏,湖南";

	vector<string> split_vector(const string& s, const char c);

	void print_row(vector<string>all, vector<string> one);

	class  Screen{
	public:
		void print_prov_name(){

		}
		void print_right()
		{

		}
		void print_num()
		{

		}
	};

	class Data_pro{
	public:
		int query_sended_pro_file(MySqlQuery &mysql, const string &prov_num);
		vector<string> get_sen_pro();
		vector<string> get_sen_pro_name();
		int query_dispatch_pro(MySqlQuery &mysql);

	private:
		vector<string> _send_pro_name_files;
		vector<string> _get_pro_name;

	};
	vector<string> have_sent_data_provin();


}


#endif //FIND_USE_FIND_DATA_H
