//
// Created by james on 2018/9/16.
//

//
// Created by james on 2018/9/16.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
int main()
{
	ofstream sh_ma("newfile5.sh");

	sh_ma << "#!/usr/bin/env bash\n"
			 "i1=0\n"
			 "i2=0\n"
			 "i3=0\n"
			 "i4=0\n"
			 "i5=0\n"
			 "i6=0\n"
			 "i7=0\n"
			 "i8=0\n"
			 "i9=0\n"
			 "i10=0\n"
			 "i11=0\n"
			 "i12=0\n"
			 "i13=0\n"
			 "i14=0\n"
			 "i15=0\n"
			 "i16=0\n"
			 "i17=0\n"
			 "i18=0\n"
			 "i19=0\n"
			 "i20=0\n"
			 "i21=0\n"
			 "i22=0\n"
			 "i23=0\n"
			 "i24=0\n"
			 "i25=0\n"
			 "i26=0\n"
			 "i27=0\n"
			 "i28=0\n"
			 "i29=0\n"
			 "i30=0\n"
			 "i31=0\n";

	sh_ma << "a1=100\n"
			 "a2=100\n"
			 "a3=100\n"
			 "a4=100\n"
			 "a5=100\n"
			 "a6=100\n"
			 "a7=100\n"
			 "a8=100\n"
			 "a9=100\n"
			 "a10=100\n"
			 "a11=100\n"
			 "a12=100\n"
			 "a13=100\n"
			 "a14=100\n"
			 "a15=100\n"
			 "a16=100\n"
			 "a17=100\n"
			 "a18=100\n"
			 "a19=100\n"
			 "a20=100\n"
			 "a21=100\n"
			 "a22=100\n"
			 "a23=100\n"
			 "a24=100\n"
			 "a25=100\n"
			 "a26=100\n"
			 "a27=100\n"
			 "a28=100\n"
			 "a29=100\n"
			 "a30=100\n"
			 "a31=100";

	sh_ma << "\n"
			 "while true\n"
			 "do\n\n\n";

	string map_name = "010\n"
					  "020\n"
					  "021\n"
					  "022\n"
					  "023\n"
					  "024\n"
					  "025\n"
					  "027\n"
					  "028\n"
					  "029\n"
					  "311\n"
					  "351\n"
					  "371\n"
					  "431\n"
					  "451\n"
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
					  "931\n"
					  "951\n"
					  "971\n"
					  "991\n";

	string file_num_s = "60\n"
						"5\n"
						"30\n"
						"30\n"
						"30\n"
						"15\n"
						"15\n"
						"15\n"
						"15\n"
						"15\n"
						"30\n"
						"20\n"
						"60\n"
						"30\n"
						"30\n"
						"30\n"
						"60\n"
						"20\n"
						"30\n"
						"60\n"
						"10\n"
						"30\n"
						"30\n"
						"60\n"
						"30\n"
						"60\n"
						"30\n"
						"20\n"
						"30\n"
						"20\n"
						"20";
	vector<string> file_num;
	vector<string> vs;

	vs =split_vector(map_name, '\n');
	file_num = split_vector(file_num_s, '\n');
	int b = 1;


	for (int i = 0; i < 31; ++i, ++b) {
		string i_num;
		i_num.clear();

		i_num = "i"+to_string(b);

		string a_num;
		a_num.clear();
		a_num = "a"+to_string(b);



		string item;



		item = 	i_num+"=$(($"+i_num+"+1))\n"
					  "if [ \"$"+i_num+"\" -eq "+file_num[i]+" ]\n"
					  "then\n"
					  "touch -m /data1/sr/roam_in/file/LNIG_*"+vs[i]+".00$"+a_num+".*\n"
					  "mv /data1/sr/roam_in/file/LNIG_*"+file_num[i]+".00$"+a_num+".* /data1/sr/roam_in/"+vs[i]+"/\n"
					  +i_num+"=0\n"
					  +a_num+"=$(($"+a_num+"+1))\n"
					  "fi";


		sh_ma << item << endl << endl;

		vs[i];
	}

	sh_ma << "echo \"sleep\"\n"
			 "sleep 1\n"
			 "done";

}