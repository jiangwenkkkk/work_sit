#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const string all_prin = "安徽,福建,河南,宁夏,辽宁,四川,山东,江苏,内蒙古,广西,浙江,江西,湖北,黑龙江,上海,河北,天津,山西,吉林,陕西,贵州,云南,青海,海南,北京,广东,新疆,甘肃,重庆,西藏,湖南";

vector<string> split(const string& s, const char c)
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




int main() {
	vector<string> prince;

	string prin_name = "福建,广西,贵州,海南";


	vector<string> v_all_prin = split(all_prin, ',');

	vector<string> vP = split(prin_name, ',');



	print_row(v_all_prin, vP);

	return 0;
}

