#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <string>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>


#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Task.h"
#include "Poco/TaskManager.h"
#include "Poco/DateTimeFormatter.h"
#include <iostream>
#include "../log/log.h"

using Poco::Util::Application;
using Poco::Util::ServerApplication;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;
using Poco::Task;
using Poco::TaskManager;
using Poco::DateTimeFormatter;

using std::string;

class SampleTask : public Task {
private:
	std::vector<int> all_visitpro;
	std::vector<int> iIMIS;
	std::vector<int> iSgw;
	std::vector<int> iRat;
	std::vector<int> all_prin;
	std::vector<int> every_pro_billnum_in_one_file_;
	std::vector<std::string> chIMIS111;
	std::vector<std::string> chChargid;
	std::vector<std::string> chList;
	std::string chTime;
	std::string chHour;
	std::string chBill;   //话单记录内容
	std::string chStart;  //文件头
	std::string chEnd;    //文件尾
	std::string chFilename;
	std::string chFilenametmp;
	int file_num;                 //每个省生成文件数量
	int iSend;
	int chose_how_many_visit_pro;

	std::string strTime;
	std::string strHour;//每个文件结尾记录的条数\每个文件条数

private:
	void init() {
		all_visitpro =  {10, 20, 21, 22, 23, 24, 25, 27, 28, 29, 311, 351, 371, 431, 451, 471, 531, 551, 571, 591, 731,
											   771, 791, 851, 871, 891, 898, 931, 951, 971, 991};
		all_prin = {10, 20, 21, 22, 23, 24, 510, 27, 28, 29, 311, 351, 371, 431, 451, 471, 531, 551, 571, 591, 731,
					771, 791, 851, 871, 891, 898, 931, 951, 971, 991};
		iIMIS = {759589, 991776, 126753, 240496, 462594, 964469, 262578, 538588, 598806, 135229, 973919, 359798,
				 479594, 928243, 846407, 875694, 532253, 902076, 744424, 299211, 668934, 218231, 804021, 593576,
				 247602, 877069, 571361, 994766, 581542, 583334, 901025, 875685, 345731, 187797, 556496, 237694,
				 194643, 672446, 503743, 163448, 229096, 617949, 426622, 485928, 782921, 538221, 641153, 254846,
				 512541, 909848, 144274, 528712, 229183, 155674, 836668, 825386, 534644, 751441, 869515, 639784,
				 459407, 478509, 575955, 608548, 479324, 578225, 331394, 901821, 509927, 852623, 195951, 653245,
				 351918, 557629, 136031, 785395, 464231, 325162, 456427, 100176, 823362, 345205, 253374, 544649,
				 346769, 184015, 918667, 958664, 239619, 222948, 232238, 992629, 580553, 587328, 883124, 510069,
				 475162, 827138, 437507, 970706};

		iSgw = {1586, 5118, 9995, 8795, 8159, 2128, 7935, 8220, 8351, 9167, 7057, 7596, 4087, 9737, 7739, 8995,
				1086, 2993, 2801, 9169, 1794, 7974, 4577, 3945, 5294, 7728, 2709, 7626, 6019, 5160, 5689, 5158,
				38352, 88631, 49020, 91764, 38188, 33500, 49315, 69210};

		iRat = {33, 59, 99, 80};

		chIMIS111 = {"460110013831570", "460110403884278", "460110137120718", "460110031485677",
					 "460037951848508", "460110091515241", "460110156971421", "460110350853957",
					 "460110521746472", "460110583474276", "460110723772240", "460030258165588",
					 "460110903996310", "460110102047593", "460110797761375", "460110074726321",
					 "460030995412157", "460110230369902", "460110195005574", "460110260847395",
					 "460110382610279", "460110674593373", "460110721024149", "460110530533813",
					 "460110550248202", "460110570509095", "460110480900711", "460110603299887",
					 "460031207119873", "460110620052694", "460110643913275"};

//		every_pro_billnum_in_one_file_ = {373, 640, 213, 91, 359, 69, 2004, 414, 840, 221, 304, 78, 348, 88, 70, 80, 163, 418, 279,
//							190,
//							742, 758, 459, 214, 128, 13, 62, 243, 50, 25, 64};
//
		every_pro_billnum_in_one_file_ = {37, 64, 21, 9, 35, 6, 200, 41, 84, 22, 304, 78, 348, 88, 70, 80,
										  163, 418, 279,
										  190,
										  742, 758, 459, 214, 128, 13, 62, 243, 50, 25, 64};
		for (auto item : every_pro_billnum_in_one_file_) {
			iSend += item;
		}

		chChargid = {"FE010A0B", "FE010A0B", "FE010A0B", "FE010A0B", "FE010A0B", "FE010A0B"};

		chList = {
				"2001:0db8:85a3:08d3:1319:8a2e:0370:7343",
				"fe80:0:0:0:204:61ff:fe9d:f156",
				"fe80::201:61ff:fe9d:f156",
				"fe80:0:0:0:0204:61ff:254.157.241.86",
				"fe80::",
				"2001:0db8:85a3:08d3:1319:8a2e:0370:7341",
				"2001:0db8:85a3:08d3:1319:8a2e:0370:7342",
				"fe80::202:61ff:fe9d:f156",
				"2001:0db8:85a3:08d3:1319:8a2e:0370:7343",
				"2001:0db8:85a3:08d3:1319:8a2e:0370:7344",
				"2001:0db8:85a3:08d3:1319:8a2e:0370:7321",
				"2001:0db8:85a3:08d3:1319:8a2e:0370:7322",
				"fe80::203:61ff:fe9d:f156",
				"2001:0db8:85a3:08d3:1319:8a2e:0370:7323",
				"2001:0db8:85a3:08d3:1319:8a2e:0370:7324",
				"2001:0db8:85a3:08d3:1319:8a2e:0370:7331",
				"2001:0db8:85a3:08d3:1319:8a2e:0370:7332",
				"fe80::204:61ff:fe9d:f156",
				"2001:0db8:85a3:08d3:1319:8a2e:0370:2331",
				"2001:0db8:85a3:08d3:1319:8a2e:0370:3331"};

		Poco::Util::AbstractConfiguration &config(Poco::Util::Application::instance().config());
		file_num = config.getInt("file_num");

		chose_how_many_visit_pro = config.getInt("chose_how_many_visit_pro");
		set_time();
	}

	void set_time() {
		char chTime[16];
		char chHour[16];
		time_t tt = time(NULL);//造话单时间精确到分，防止重复
		tm *t = localtime(&tt);
		sprintf(chTime, "%d%02d%02d%02d%02d", t->tm_year + 1900,
				t->tm_mon + 1,
				t->tm_mday,
				t->tm_hour,
				t->tm_min);
		sprintf(chHour, "%d%02d%02d%02d", t->tm_year + 1900,
				t->tm_mon + 1,
				t->tm_mday,
				t->tm_hour);
		strTime = chTime;
		strHour = chHour;
	}

	void make_file(int visit_pro) {
		FLOG << "visit_pro is start: " << visit_pro << ENDL;
		string chFilenametmp_s;
		string chFilename_s;

		file_name_set(chFilenametmp_s, chFilename_s);

		int iList1 = 100000;  //本节点序列号
		int iCallNum = 100000;        //遍历开始序号


		std::string strFilename;
		std::string strFilenametmp;

		int FileNO = 0;

		while (FileNO < file_num)//一个省生成多个文件
		{
			FileNO++;
			std::string strStart;
			std::string chEnd;
			init_file(visit_pro, chFilenametmp_s, chFilename_s, strFilename, strFilenametmp, FileNO);

			std::cout << strFilenametmp << std::endl;

			FILE *fp;
			if (!(fp = fopen(strFilenametmp.c_str(), "w"))) {
				printf("Can not open %s\n", strFilename.c_str());
			} else {
				write_head(visit_pro, FileNO, fp);
				write_bill(visit_pro, iList1, iCallNum, FileNO, fp);
				write_tail(visit_pro, chEnd, FileNO, fp);
				fclose(fp);

				if (!rename(strFilenametmp.c_str(), strFilename.c_str()))//删除成功
				{
					printf("%s rename: %s\n", strFilenametmp.c_str(), strFilename.c_str());
				}
			}
		}

	}

	void init_file(int visit_pro, string &chFilenametmp_s, string &chFilename_s, std::string &strFilename,
				   std::string &strFilenametmp, int FileNO) {

		////LNIG_2018071018025.0006.00

		char chFilenametmp[1024] = {0};
		char chFilename[1024] = {0};
		sprintf(chFilenametmp, chFilenametmp_s.c_str(), strHour.c_str(),
				visit_pro,
				FileNO);
		printf("filename:%s\n", chFilenametmp);

		sprintf(chFilename, chFilename_s.c_str(), strHour.c_str(),
				visit_pro,
				FileNO);

		printf("filename:%s\n", chFilename);

		strFilenametmp = chFilenametmp;
		strFilename = chFilename;

	}

	void write_head(int visit_pro, int FileNO, FILE *fp) {
		char chStart[1024] = {0};
		sprintf(chStart, "10^46011%03d^46011000^%05d^%s0000^10\n", visit_pro,
				FileNO,
				strHour.c_str());

		fputs(chStart, fp);//写入数据
	}

	void file_name_set(string &chFilenametmp_s, string &chFilename_s) {
		std::string ip_last_tw_val = "32";
		chFilenametmp_s = "./~LNIG_%s%03d.%05d." + ip_last_tw_val;
		chFilename_s = "./LNIG_%s%03d.%05d." + ip_last_tw_val;

	}


	void write_bill(int visit_pro, int iList1, int iCallNum,
					int FileNO, FILE *fp) {


		char chBill[1024];   //话单记录内容
		memset(chBill, 0, sizeof(chBill));


		int i = 0;
		int j = 0;
		int iProCount = 0;
		while (i < 31)   //31个省记录
		{
			int location_pro = all_prin[i];

			printf("%d---%d\n", location_pro, visit_pro);

			while (iProCount < every_pro_billnum_in_one_file_[j])//每个省记录条数
			{
				memset(chBill, 0, sizeof(chBill));
				sprintf(chBill,
						"1^18938888888^%s^6201482934%d^255.255.0.1^CTLTE^%s^%d^100000^%s^1^0^%d^%d^A^1000^1000^%s10^30^%s40^000000000^^460111A00091^%d^192.168.0.0^^%s^\n",
						chIMIS111[i].c_str(),
						iList1,
						chChargid[0].c_str(),
						iIMIS[0],
						chList[0].c_str(),
						all_prin[i],
						visit_pro,
						strTime.c_str(),
						strTime.c_str(),
						iRat[0],
						strTime.c_str());

				fputs(chBill, fp);//写入数据
				iProCount++;
				iList1++;
				iCallNum++;
			}
			iProCount = 0;
			i++;
			j++;
		}
		printf("exit---%d\n", iCallNum);
		iCallNum = 100000;


		//90^46011025^46011000^0006^2^20180710170010^20180710170040^2000^2000^4000

	}

	void write_tail(int visit_pro, std::string strEnd, int FileNO, FILE *fp) {
		char chEnd[1024] = {0};
		sprintf(chEnd, "90^46011%03d^46011000^%05d^%d^%s10^%s10^%d^%d^%d\n", visit_pro,
				FileNO,
				iSend,
				strTime.c_str(),
				strTime.c_str(),
				iSend * 1000,
				iSend * 1000,
				iSend * 1000 * 2);
		strEnd = chEnd;
		fputs(strEnd.c_str(), fp);//写入数据
	}


public:

	SampleTask() : Task("SampleTask") {
	}

	void runTask() {
		init();

		int vistpro_index = 0;
		int visit_pro = 0;//拜访局省份号

		while (vistpro_index < chose_how_many_visit_pro) {
			visit_pro = all_visitpro[vistpro_index];
			printf("file%d:\n", vistpro_index, visit_pro);

			make_file(visit_pro);
			vistpro_index++;
		}
	}
};

//string last_ip_two() {
//	struct ifaddrs *ifAddrStruct = NULL;
//	void *tmpAddrPtr = NULL;
//	getifaddrs(&ifAddrStruct);
//	int i = 0;
//	string ip_p;
//	while (ifAddrStruct != NULL) {
//		++i;
//		struct sockaddr *sap = ifAddrStruct->ifa_addr;
//		if (sap->sa_family == AF_INET) { // check it is IP4
//			tmpAddrPtr = &((struct sockaddr_in *) sap)->sin_addr;
//			char addressBuffer[INET_ADDRSTRLEN];
//			inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
//			if (i == 12) {
//				ip_p = addressBuffer;
//			}
//
//		} else if (sap->sa_family == AF_INET6) { // check it is IP6
//			// is a valid IP6 Address
//			tmpAddrPtr = &((struct sockaddr_in *) sap)->sin_addr;
//			char addressBuffer[INET6_ADDRSTRLEN];
//			inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
//			if (i == 12) {
//				ip_p = addressBuffer;
//			}
//		}
//		ifAddrStruct = ifAddrStruct->ifa_next;
//	}
//	int len = ip_p.length();
//	char last[2] = {0};
//	last[0] = ip_p[len - 2];
//	last[1] = ip_p[len - 1];
//	string ip_last_two = last;
//	return ip_last_two;
//}
//
//


