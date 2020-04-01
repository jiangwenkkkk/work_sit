//
// Created by james on 2018/9/12.
//

#include <gtest.h>
#include <iostream>
#include "find_data.h"
#include <fstream>

using namespace std;

TEST(a, b)
{
	cout << "adfasdfasdfasfh" << endl;
}

TEST(ofstream_t, u)
{
	ofstream cout_file("tmp");
	cout_file << "hello" << endl;
}

//TEST(exe_echo, t)
//{
//	execl("/bin/ls","ls","-l",NULL);
//}