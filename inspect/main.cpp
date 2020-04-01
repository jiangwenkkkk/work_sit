//
// Created by james on 2018/9/13.
//

#include <stdlib.h>

#include <string>
#include <vector>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

using namespace std;

//struct sockaddr_in {
//	__uint8_t	sin_len;
//	sa_family_t	sin_family;
//	in_port_t	sin_port;
//	struct	in_addr sin_addr;
//	char		sin_zero[8];
//};
//struct sockad
//	__uint8_t	sa_len;		/* total length */
//	sa_family_t	sa_family;	/* [XSI] address family */
//	char		sa_data[14];	/* [XSI] addr value (actually larger) */
//};
int main()
{

	unsigned int dwIPAddr ;
	dwIPAddr = inet_addr("192.168.4.111");
	hostent* hst = NULL;
	hst = gethostbyaddr(&dwIPAddr,4,AF_INET);

		struct hostent* he;
	struct netent* pn;

		pn = getnetbyaddr(1853062523, AF_INET6);
		if (pn != NULL)
			cout << pn->n_name;
	struct netent* tm = getnetbyname("www.baidu.com");


//	struct hostent* he;
//	struct netent* pn;
//	for (unsigned int i = 0; i < 4294967295; ++i){
//		pn = getnetbyaddr(123, AF_INET);
//		if (pn != NULL)
//			cout << pn->n_name;
//
//
//	}
//	pn = getnetbyaddr(123, AF_INET);
//
//	he = gethostent();
//	cout << he->h_name << endl;
//	for (int i = 0; i < he->h_length; ++i)
//	{
//		cout << *(he->h_addr_list)+i << endl;
//	}
//
	cout << sizeof(sockaddr) << endl;
	cout << sizeof(sockaddr_in) << endl;
//	cout << sizeof(unsigned short) << endl;
//	cout << sizeof(hostent) << endl;
	char str[INET_ADDRSTRLEN] = {0};

	unsigned int in_int = 1862576320;
	inet_pton(AF_INET, "123.125.115.110", &in_int);

	cout << in_int << endl;
  	const  char *p  = inet_ntop(AF_INET, (const void*)&in_int, str, 16);


	cout << p << endl;
//	int a = 100000;
//	int b = htonl(a);
//	std::cout << std::hex << a << ' '<<  b;

//   int sd = socket(AF_INET, SOCK_STREAM, 0);
//   char a[INET6_ADDRSTRLEN] ={0};
//   unsigned char buf[sizeof(struct in6_addr)];
//
//  int s =  inet_pton(AF_INET6, "0:0:0:0:0:FFFF:204.152.189.116", buf);
//
//   const char* p =  inet_ntop(AF_INET6, buf, a, INET6_ADDRSTRLEN);
//
//
//
//   std::cout << p << std::endl;
//	char hname[128];
//	struct hostent *hent;
//	int i;
//
//	gethostname(hname, sizeof(hname));
//
//	hent = gethostent();
////	hent = gethostbyname(hname);
//
//	printf("hostname: %s/naddress list: ", hent->h_name);
//	for(i = 0; hent->h_addr_list[i]; i++) {
//		printf("%s/t", inet_ntoa(*(struct in_addr*)(hent->h_addr_list[i])));
//		std::cout << std::endl;
//	}
//
//
//
//
//		setenv("LANG","C",1);
//		FILE * fp = popen("ifconfig", "r");
//		if (fp) {
//			char *p=NULL, *e; size_t n;
//			while ((getline(&p, &n, fp) > 0) && p) {
//				if (p = strstr(p, "inet ")) {
//					p+=5;
//					if (p = strchr(p, ':')) {
//						++p;
//						if (e = strchr(p, ' ')) {
//							*e='\0';
//							printf("%s\n", p);
//						}
//					}
//				}
//			}
//		}
//		pclose(fp);
//		return 0;

}
//
//#include <arpa/inet.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//int
//main(int argc, char *argv[])
//
//{
//	unsigned char buf[sizeof(struct in6_addr)];
//	int domain, s;
//	char str[INET6_ADDRSTRLEN];
//
//	if (argc != 3) {
//		fprintf(stderr, "Usage: %s {i4|i6|<num>} string\n", argv[0]);
//		exit(EXIT_FAILURE);
//	}
//
//	domain = (strcmp(argv[1], "i4") == 0) ? AF_INET :
//			 (strcmp(argv[1], "i6") == 0) ? AF_INET6 : atoi(argv[1]);
//
//	s = inet_pton(domain, argv[2], buf);
//	if (s <= 0) {
//		if (s == 0)
//			fprintf(stderr, "Not in presentation format");
//		else
//			perror("inet_pton");
//		exit(EXIT_FAILURE);
//	}
//
//	if (inet_ntop(domain, buf, str, INET6_ADDRSTRLEN) == NULL) {
//		perror("inet_ntop");
//		exit(EXIT_FAILURE);
//	}
//
//	printf("%s\n", str);
//
//	exit(EXIT_SUCCESS);
//}