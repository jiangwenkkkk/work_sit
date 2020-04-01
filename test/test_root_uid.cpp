//
// Created by james on 2018/9/28.
//

#include <unistd.h>
#include <iostream>

int main()
{
	uid_t uid = getuid();
	uid_t euid = geteuid();

	cout << "uid: " << uid << '\n' << "euid: " << euid;
}