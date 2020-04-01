//
// Created by james on 2018/9/15.
//
#include <iostream>
#include <gtest.h>
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
#include <ifaddrs.h>


using namespace std;

TEST(hh,tt)
{
	cout << "hell" << endl;
}

TEST(gethostbyaddr_t, t)
{
	unsigned int dwIPAddr ;
	dwIPAddr = inet_addr("192.168.4.111");
	cout << dwIPAddr << endl;
	hostent* hst = NULL;
	hst = gethostbyaddr(&dwIPAddr,4,AF_INET);


	for (int i = 0; i < hst->h_length; ++i) {
		cout << *(hst->h_addr_list) << " " << *(hst->h_aliases) << endl;
	}
}

TEST(getnetbyaddr_t,t)
{
	struct hostent* he;
	struct netent* pn;
	unsigned int uIpAddr = 1862576320;

	pn = getnetbyaddr(uIpAddr, AF_INET);
	if (pn != NULL)
		cout << pn->n_name;

}

TEST(inet_ntop_t, t)
{
	unsigned int uIpAddr = 1862576320;
	char str[40] = {0};
	inet_ntop(AF_INET, &uIpAddr, str, INET_ADDRSTRLEN);
	cout << str << endl;
}

TEST(getaddrinfo_t, t)
{

	cout << endl;
	char *a = "www.kame.net";
	char *b = "http";
	struct addrinfo c;
	c.ai_family = AF_INET;
	c.ai_socktype = SOCK_STREAM;
	c.ai_flags = AI_ALL;
	c.ai_protocol = 0;
	c.ai_canonname = NULL;
	c.ai_addr = NULL;
	c.ai_next = NULL;
	const char *cause = NULL;

	struct addrinfo *res, *res0;
	int s;
	int ret = getaddrinfo(a, b, &c, &res0);
	for (res = res0; res; res = res->ai_next) {
		s = socket(res->ai_family, res->ai_socktype,
				   res->ai_protocol);
		if (s < 0) {
			cause = "socket";
			continue;
		}

		if (connect(s, res->ai_addr, res->ai_addrlen) < 0) {
			cause = "connect";
			close(s);
			s = -1;
			continue;
		}

		break;  /* okay we got one */
	}
}

TEST(host_ent, t)
{
	struct hostent* ph;
	for (int i = 0; i < 10; ++i) {
		ph = gethostent();
	}

//	char**p = ph->h_addr_list;
//	for (int i = 0; i < ph->h_length; ++i) {
//		cout << *(p++) << endl;
//	}
}

TEST(getnetbyaddr_ta, t)
{
	char *str = "123.125.115.110";
	unsigned int a;
	inet_pton(AF_INET, str, &a);
//	hostent *ph = gethostbyaddr();
//	struct netent* pn = getnetbyaddr(a, AF_INET);
}

TEST(getnetbyname_t, t)
{
//	struct netent* pn = getnetbyname("http://linux.uppbook.com");
//	struct hostent* pn = gethostbyname("linux.uppbook.com");
	struct hostent* pn = gethostbyname("baidu.com");
}

TEST(hms, t)
{
	struct ifaddrs*d;
	int a = getifaddrs(&d);
}

TEST(getaddrinfo_t, t)
{
	getaddrinfo()
}