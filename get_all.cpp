//
// Created by james on 2018/9/12.
//

#include <iostream>
#include <vector>
#include <map>
#include <fstream>


using namespace std;
const string all_prin = "安徽,福建,河南,宁夏,辽宁,四川,山东,江苏,内蒙古,广西,浙江,江西,湖北,黑龙江,上海,河北,天津,山西,吉林,陕西,贵州,云南,青海,海南,北京,广东,新疆,甘肃,重庆,西藏,湖南";


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


int main()
{
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

	vector<string> prin = split_vector(map_name, '\n');


	vector<vector<string>> pairs;
	for (auto item : prin)
	{
		pairs.push_back(split_vector(item, ','));
	}

	for (auto item : pairs)
	{
		num_prin.insert(make_pair(item[0], item[1]));
	}

//	for ( auto it = num_prin.begin(); it != num_prin.end(); ++it)
//	{
//		cout << it->first << " : " << it->second << endl;
//	}

	string find_name = "023\n"
					   "731\n"
					   "891\n"
					   "931";

	vector<string> have_name = split_vector(find_name, '\n');

	vector<string> find_in_map;

	ofstream To_file("show_data_of_province");


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
	vector<string> v_all_prin = split_vector(all_prin, ',');

	print_row(v_all_prin, find_in_map);

	cout << endl;


}

