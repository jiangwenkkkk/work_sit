#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

using std::string;

string last_ip_two() {
	struct ifaddrs *ifAddrStruct = NULL;
	void *tmpAddrPtr = NULL;
	getifaddrs(&ifAddrStruct);
	int i = 0;
	string ip_p;
	while (ifAddrStruct != NULL) {
		++i;
		struct sockaddr *sap = ifAddrStruct->ifa_addr;
		if (sap->sa_family == AF_INET) { // check it is IP4
			tmpAddrPtr = &((struct sockaddr_in *) sap)->sin_addr;
			char addressBuffer[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
			if (i == 12) {
				ip_p = addressBuffer;
			}

		} else if (sap->sa_family == AF_INET6) { // check it is IP6
			// is a valid IP6 Address
			tmpAddrPtr = &((struct sockaddr_in *) sap)->sin_addr;
			char addressBuffer[INET6_ADDRSTRLEN];
			inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
			if (i == 12) {
				ip_p = addressBuffer;
			}
		}
		ifAddrStruct = ifAddrStruct->ifa_next;
	}
	int len = ip_p.length();
	char last[2] = {0};
	last[0] = ip_p[len - 2];
	last[1] = ip_p[len - 1];
	string ip_last_two = last;
	return ip_last_two;
}


int main(int argc, char**argv) {
	int iOutPro = 0;//拜访局省份号
	int iInPro = 0;//归属地省份号
	int iCallNum = 100000;        //遍历开始序号
	int iList1 = 100000;  //本节点序列号
	int iFileNO = 0;          //文件序中列号
	int iCount = 750;                 //每个省生成文件数量
	int iSend = 50000;          //每个文件结尾记录的条数\每个文件条数

	char chTime[16];
	char chHour[16];
	char chBill[1024];   //话单记录内容
	char chStart[1024];  //文件头
	char chEnd[1024];    //文件尾
	char chFilename[64];
	char chFilenametmp[64];
	memset(chTime, 0, sizeof(chTime));
	memset(chHour, 0, sizeof(chHour));
	memset(chBill, 0, sizeof(chBill));
	memset(chStart, 0, sizeof(chStart));
	memset(chEnd, 0, sizeof(chEnd));
	memset(chFilename, 0, sizeof(chFilename));
	memset(chFilenametmp, 0, sizeof(chFilenametmp));

	FILE *fp;

	//单个文件31个省遍历
	int iList[32] = {10, 20, 21, 311, 371, 451, 531, 571, 591, 731, 771, 851};
	int iIMIS[128] = {759589, 991776, 126753, 240496, 462594, 964469, 262578, 538588, 598806, 135229, 973919, 359798,
					  479594, 928243, 846407, 875694, 532253, 902076, 744424, 299211, 668934, 218231, 804021, 593576,
					  247602, 877069, 571361, 994766, 581542, 583334, 901025, 875685, 345731, 187797, 556496, 237694,
					  194643, 672446, 503743, 163448, 229096, 617949, 426622, 485928, 782921, 538221, 641153, 254846,
					  512541, 909848, 144274, 528712, 229183, 155674, 836668, 825386, 534644, 751441, 869515, 639784,
					  459407, 478509, 575955, 608548, 479324, 578225, 331394, 901821, 509927, 852623, 195951, 653245,
					  351918, 557629, 136031, 785395, 464231, 325162, 456427, 100176, 823362, 345205, 253374, 544649,
					  346769, 184015, 918667, 958664, 239619, 222948, 232238, 992629, 580553, 587328, 883124, 510069,
					  475162, 827138, 437507, 970706};
	int iSgw[40] = {1586, 5118, 9995, 8795, 8159, 2128, 7935, 8220, 8351, 9167, 7057, 7596, 4087, 9737, 7739, 8995,
					1086, 2993, 2801, 9169, 1794, 7974, 4577, 3945, 5294, 7728, 2709, 7626, 6019, 5160, 5689, 5158,
					38352, 88631, 49020, 91764, 38188, 33500, 49315, 69210};
	int iRat[6] = {33, 59, 99, 80};

	int iList111[100] = {10, 20, 21, 22, 23, 24, 510, 27, 28, 29, 311, 351, 371, 431, 451, 471, 531, 551, 571, 591, 731,
						 771, 791, 851, 871, 891, 898, 931, 951, 971, 991};
	char chIMIS111[80][22] = {"460110013831570", "460110403884278", "460110137120718", "460110031485677",
							  "460037951848508", "460110091515241", "460110156971421", "460110350853957",
							  "460110521746472", "460110583474276", "460110723772240", "460030258165588",
							  "460110903996310", "460110102047593", "460110797761375", "460110074726321",
							  "460030995412157", "460110230369902", "460110195005574", "460110260847395",
							  "460110382610279", "460110674593373", "460110721024149", "460110530533813",
							  "460110550248202", "460110570509095", "460110480900711", "460110603299887",
							  "460031207119873", "460110620052694", "460110643913275"};
	int iCountNum[100] = {1866, 3202, 1066, 456, 1795, 346, 10020, 2070, 4201, 1106, 1521, 388, 1740, 440, 351, 402,
						  817, 2089, 1395, 951, 3708, 3788, 2295, 1069, 641, 64, 309, 1209, 251, 125, 319};
	char chChargid[8][22] = {"FE010A0B", "FE010A0B", "FE010A0B", "FE010A0B", "FE010A0B", "FE010A0B"};
	char chList[20][50] = {
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


	int i = 0;

	string ip_last_tw_val = "32";
	string chFilenametmp_s = "/jsdata/vnode/sr/roam_in/file/~LNIG_%s%03d.%05d." + ip_last_tw_val;
	string chFilename_s = "/jsdata/vnode/sr/roam_in/file/LNIG_%s%03d.%05d." + ip_last_tw_val;

	while (i < 12) {
		iOutPro = iList[i];
		printf("file%d:\n", i, iOutPro);
		while (iFileNO < iCount)//一个省生成多个文件
		{
			iFileNO++;

			////LNIG_2018071018025.0006.00

			sprintf(chFilenametmp, chFilenametmp_s.c_str(), chHour,
					iOutPro,
					iFileNO);
			printf("filename:%s\n", chFilenametmp);

			sprintf(chFilename, chFilename_s.c_str(), chHour,
					iOutPro,
					iFileNO);
			printf("filename:%s\n", chFilename);

			/*sprintf(chFilenametmp,"/data1/sr/roam_in/file/~LNIG_%s%03d.%05d.07",chHour,
			iOutPro,
			iFileNO);
			printf("filename:%s\n",chFilenametmp);

			sprintf(chFilename,"/data1/sr/roam_in/file/LNIG_%s%03d.%05d.07",chHour,
			iOutPro,
			iFileNO);
			printf("filename:%s\n",chFilename);*/

			//10^46011025^46011000^0006^20180710180000^10
			sprintf(chStart, "10^46011%03d^46011000^%05d^%s0000^10\n", iOutPro,
					iFileNO,
					chHour);

			if (!(fp = fopen(chFilenametmp, "w"))) {
				printf("Can not open %s\n", chFilename);
			} else {
				fputs(chStart, fp);//写入数据

				int i = 0;
				int j = 0;
				int iProCount = 0;
				while (i < 31)   //31个省记录
				{
					iInPro = iList111[i];

					printf("%d---%d\n", iInPro, iOutPro);
					while (iProCount < iCountNum[j])//每个省记录条数
					{
						memset(chBill, 0, sizeof(chBill));
						sprintf(chBill,
								"1^18938888888^%s^6201482934%d^255.255.0.1^CTLTE^%s^%d^100000^%s^1^0^%d^%d^A^1000^1000^20180710170110^30^20180710170140^000000000^^460111A00091^%d^192.168.0.0^^%s^\n",
								chIMIS111[i],
								iList1,
								chChargid[0],
								iIMIS[0],
								chList[0],
								iList111[i],
								iOutPro,
								iRat[0],
								chTime);

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
				sprintf(chEnd, "90^46011%03d^46011000^%05d^%d^20180710170110^20180710170110^%d^%d^%d\n", iOutPro,
						iFileNO,
						iSend,
						iSend * 1000,
						iSend * 1000,
						iSend * 1000 * 2);
				fputs(chEnd, fp);//写入数据
				fclose(fp);
				if (!rename(chFilenametmp, chFilename))//删除成功
				{
					printf("%s rename: %s\n", chFilenametmp, chFilename);
				}
			}
		}
		iFileNO = 0;
		i++;
	}
	return 0;
}

