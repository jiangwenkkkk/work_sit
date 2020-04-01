//
// Created by james on 2018/9/18.
//

#include <signal.h>
#include <iostream>
#include <zconf.h>
#include <sys/socket.h>

using namespace std;


static int pipefd[2];

static void hello(int)
{
	cout << "hello";
	cout << endl;
	char buf[100] = {"hello"};
	send(pipefd[0], buf, 6, 0);
}

int main()
{
//	signal(1, hello);
//

	socketpair(AF_UNIX, SOCK_STREAM, 0, pipefd);



	 struct sigaction a ;
	a.__sigaction_u.__sa_handler = hello;
	a.sa_mask=1;
	a.sa_flags=SA_ONSTACK|SA_RESTART;

	sigaction(1, &a, NULL);

	char buf[100]={0};
	recv(pipefd[1], buf, 6, 0);
	cout << buf;
}