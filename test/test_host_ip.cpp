//#include <stdio.h>
//#include <unistd.h>
//#include <netdb.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//
//int main() {
//	char hname[128];
//	struct hostent *hent;
//	int i;
//
//	gethostname(hname, sizeof(hname));
//
//	//hent = gethostent();
//	hent = gethostbyname(hname);
//
//	printf("hostname: %s/naddress list: ", hent->h_name);
//	for(i = 0; hent->h_addr_list[i]; i++) {
//		printf("%s/t", inet_ntoa(*(struct in_addr*)(hent->h_addr_list[i])));
//	}
//	return 0;
//}

#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>

using  namespace std;

int main (int argc, const char * argv[]) {
	struct ifaddrs * ifAddrStruct=NULL;
	void * tmpAddrPtr=NULL;
	getifaddrs(&ifAddrStruct);
	int i = 0;
	string ip_p;
	while (ifAddrStruct!=NULL) {
		++i;
	//	cout << ++i <<  " ";
		struct sockaddr *sap = ifAddrStruct->ifa_addr;
		if (sap->sa_family==AF_INET) { // check it is IP4
			// is a valid IP4 Address
			tmpAddrPtr=&((struct sockaddr_in *)sap)->sin_addr;
			char addressBuffer[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
		//	printf("%s IP Address %s/n", ifAddrStruct->ifa_name, addressBuffer);
			if (i == 12)
			{
				ip_p = addressBuffer;
			}

		} else if (sap->sa_family==AF_INET6) { // check it is IP6
			// is a valid IP6 Address
			tmpAddrPtr=&((struct sockaddr_in *)sap)->sin_addr;
			char addressBuffer[INET6_ADDRSTRLEN];
			inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
		//	printf("%s IP Address %s/n", ifAddrStruct->ifa_name, addressBuffer);
			if (i == 12)
			{
				ip_p = addressBuffer;
			}
		}


		ifAddrStruct=ifAddrStruct->ifa_next;
	//	std::cout << endl;
	}

//	cout << " ip is : " <<  ip_p;

	int len = ip_p.length();
	char last[2]={0};
	last[0]=ip_p[len-2];
	last[1]=ip_p[len-1];
	string ip_last_two = last;
	cout << "ip_two_is: " << ip_last_two << endl;

	return 0;
}

string last_ip_two()
{
	struct ifaddrs * ifAddrStruct=NULL;
	void * tmpAddrPtr=NULL;
	getifaddrs(&ifAddrStruct);
	int i = 0;
	string ip_p;
	while (ifAddrStruct!=NULL) {
		++i;
		struct sockaddr *sap = ifAddrStruct->ifa_addr;
		if (sap->sa_family==AF_INET) { // check it is IP4
			tmpAddrPtr=&((struct sockaddr_in *)sap)->sin_addr;
			char addressBuffer[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
			if (i == 12)
			{
				ip_p = addressBuffer;
			}

		} else if (sap->sa_family==AF_INET6) { // check it is IP6
			// is a valid IP6 Address
			tmpAddrPtr=&((struct sockaddr_in *)sap)->sin_addr;
			char addressBuffer[INET6_ADDRSTRLEN];
			inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
			if (i == 12)
			{
				ip_p = addressBuffer;
			}
		}


		ifAddrStruct=ifAddrStruct->ifa_next;
	}

	int len = ip_p.length();
	char last[2]={0};
	last[0]=ip_p[len-2];
	last[1]=ip_p[len-1];
	string ip_last_two = last;
	return ip_last_two;
}
