//
// Created by james on 2018/9/12.
//

#include <iostream>
#include <vector>
#include <map>


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

	for ( auto it = num_prin.begin(); it != num_prin.end(); ++it)
	{
		cout << it->first << " : " << it->second << endl;
	}

	string find_name = "010\n"
					   "020\n"
					   "022\n"
					   "023\n"
					   "024\n"
					   "027\n"
					   "028\n"
					   "029\n"
					   "311\n"
					   "351\n"
					   "371\n"
					   "471\n"
					   "531\n"
					   "551\n"
					   "571\n"
					   "591\n"
					   "731\n"
					   "771\n"
					   "791\n"
					   "851\n"
					   "871\n"
					   "891\n"
					   "898\n"
					   "951\n"
					   "971";
	vector<string> have_name = split_vector(find_name, '\n');

	for (auto item : have_name)
	{
		cout << num_prin[item]  << ",";
	}

	vector<string> find_in_map;
	for (auto item: have_name)
	{
		find_in_map.push_back(item);
	}

	cout << endl;



}

