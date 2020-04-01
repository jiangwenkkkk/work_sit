//
// Created by james on 2018/9/17.
//

#include <gtest/gtest.h>
#include <sys/socket.h>
#include <regex>

using namespace std;

void hello(int) {
	cout << "hello";
}

TEST(excel_t, t) {
	execl("/bin/ls", "ls", "-l", NULL);
}

TEST(unixtime, t) {
	time_t a;
	cout << time(&a);

//	auto tm = localtime(&a);
//
//	cout << a;
}

TEST(singnal_, t) {
	//sigaction();
	cout << ",................" << endl;
	signal(SIGHUP, hello);
	sleep(10000000000);
//	void
//	(
//			*signal
//			(int,
//					void (*)(int)
//			)
//
//	)
//			(int);

}

TEST(time_t_a, ta) {
	time_t tim;
	time_t a = time(&tim);
}

TEST(time_t, mktime_t) {
	struct tm a;
	time_t now = time(NULL);
	struct tm *now_tm = localtime(&now);
	struct tm ab = *now_tm;
	ab.tm_min = ab.tm_min + 1;
	time_t zn = mktime(&ab);


}

TEST(socketparit, t) {
	int fd[2];
	socketpair(AF_UNIX, SOCK_STREAM, 0, fd);

	char buf[100] = {"hello"};
	send(fd[0], buf, 6, 0);

	recv(fd[1], buf + 10, 6, 0);

	while (1) {
	}
}


class a {
public:
	~a() {
		cout << __func__ << endl;
	}

};

class b : public a {
public:
	~b() {
		cout << __func__ << endl;
	}
};

TEST(test_vir_a, destr) {
	{
		cout << __func__ << endl;


		//	a a1;
//		a* a1 = new b;
//		delete(a1);

		b b1;
	}

	cout << __func__ << endl;
}

TEST(test_ptherd_spin, lock) {


}

TEST(strpbrk_t, t) {
	char *a = "abcde";
	char *p = strpbrk(a, "b");
}

TEST(strcasecmp_t, t) {
	char *str1 = "STRING";
	char *str2 = "string";
	int result;

	result = strcasecmp(str1, str2);

	if (result == 0)
		printf("Strings compared equal.\n");
	else if (result < 0)
		printf("\"%s\" is less than \"%s\".\n", str1, str2);
	else
		printf("\"%s\" is greater than \"%s\".\n", str1, str2);

}

TEST(strspn_t, t) {
	int i;
	char strtext[] = "129th";
	char cset[] = "1234567890";

	i = strspn(strtext, cset);
	printf("The initial number has %d digits.\n", i);
}

TEST(regex_t, t) {
	std::string s("this subject has a submarine as a subsequence");
	std::smatch m;
	std::regex e("\\b(sub)([^ ]*)");   // matches words beginning by "sub"

	std::cout << "Target sequence: " << s << std::endl;
	std::cout << "Regular expression: /\\b(sub)([^ ]*)/" << std::endl;
	std::cout << "The following matches and submatches were found:" << std::endl;

	while (std::regex_search(s, m, e)) {
		for (auto x = m.begin(); x != m.end(); x++)
			std::cout << x->str() << " ";
		std::cout << "--> ([^ ]*) match " << m.format("$2") << std::endl;
		s = m.suffix().str();
	}

//	---------------------
//			作者：没有开花的树
//	来源：CSDN
//	原文：https://blog.csdn.net/mycwq/article/details/18838151
//	版权声明：本文为博主原创文章，转载请附上博文链接！

}

TEST(regex_t, all) {

	if (std::regex_match("subject", std::regex("(sub)(.*)")))
		std::cout << "string literal matched\n";

	std::string s("subject");
	std::regex e("(subj)(.*)");
	if (std::regex_match(s, e))
		std::cout << "string object matched\n";

	if (std::regex_match(s.begin(), s.end(), e))
		std::cout << "range matched\n";

	std::cmatch cm;    // same as std::match_results<const char*> cm;
	std::regex_match("subject", cm, e);
	std::cout << "string literal with " << cm.size() << " matches\n";
	for (auto item : cm)
	{
		cout << item << endl;
	}
	std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
	std::regex_match(s, sm, e);
	std::cout << "string object with " << sm.size() << " matches\n";
	for (auto item : sm)
	{
		cout << item << endl;
	}

	std::regex_match(s.cbegin(), s.cend(), sm, e);
	std::cout << "range with " << sm.size() << " matches\n";
	for (auto item : sm)
	{
		cout << item << endl;
	}

	// using explicit flags:
	std::regex_match("subject", cm, e, std::regex_constants::match_default);

	std::cout << "the matches were: ";
	for (unsigned i = 0; i < sm.size(); ++i) {
		std::cout << "[" << sm[i] << "] ";
	}

	std::cout << std::endl;



//		---------------------
//				作者：没有开花的树
//		来源：CSDN
//		原文：https://blog.csdn.net/mycwq/article/details/18838151
//		版权声明：本文为博主原创文章，转载请附上博文链接！
}

TEST(regex_app, t)
{
	std::string fnames[] = {"foo.txt", "bar.txt", "baz.dat", "zoidberg"};
	std::regex txt_regex("[a-z]+\\.txt");

	for (const auto &fname : fnames) {
		std::cout << fname << ": " << std::regex_match(fname, txt_regex) << '\n';
	}

	// Extraction of a sub-match
	std::regex base_regex("([a-z]+)\\.txt");
	std::smatch base_match;

	for (const auto &fname : fnames) {
		if (std::regex_match(fname, base_match, base_regex)) {
			// The first sub_match is the whole string; the next
			// sub_match is the first parenthesized expression.
			if (base_match.size() == 2) {
				std::ssub_match base_sub_match = base_match[1];
				std::string base = base_sub_match.str();
				std::cout << fname << " has a base of " << base << '\n';
			}
		}
	}

	// Extraction of several sub-matches
	std::regex pieces_regex("([a-z]+)\\.([a-z]+)");
	std::smatch pieces_match;

	for (const auto &fname : fnames) {
		if (std::regex_match(fname, pieces_match, pieces_regex)) {
			std::cout << fname << '\n';
			for (size_t i = 0; i < pieces_match.size(); ++i) {
				std::ssub_match sub_match = pieces_match[i];
				std::string piece = sub_match.str();
				std::cout << "  submatch " << i << ": " << piece << '\n';
			}
		}
	}

}

TEST(regex_t, match_)
{
	std::regex db_regex("hello_[0-9]");
	vector<std::string> names= {"hello_1", "hello_2", "hello"};

	cout << endl;
	for (auto const& item : names)
	{
		cout << item << ": " << std::regex_match(item, db_regex) << endl;
	}
}

TEST(str_cstr_data, diff)
{
	string name = "tom";
	int a = 10;
	printf("%s%d", name.c_str(), a);
	printf("%s", name.data(), a);
}

TEST(test_cout, another_line)
{
	std::cout << "hello";
}

TEST(add_num, v_t)
{
	std::vector<int> a ={373, 640, 213, 91, 359, 69, 2004, 414, 840, 221, 304, 78, 348, 88, 70, 80, 163, 418, 279, 190,
						 742, 758, 459, 214, 128, 13, 62, 243, 50, 25, 64};
	
	int sum = 0;
	for (auto item : a)
	{
		sum+=item;
	}
	std::cout << sum;


}