//
// Created by james on 2018/9/30.
//


#include <zconf.h>
#include <iostream>

using namespace std;

int main()
{
	pid_t pid_a = fork();
	if (pid_a == 0)
	{
		_exit(0);
	}
	cout << "hello" << endl;

	int b;
	wait(&b);
	cout << "b" << b << endl;
	sleep(100);


}