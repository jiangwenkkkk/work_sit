//
// Created by james on 2018/9/11.
//

#include <mysql.h>
#include <iostream>
#include <string>

using namespace std;
extern "C"{
const char *	STDCALL mysql_get_client_info(void);
};

void finist_with_error(MYSQL *con)
{
	cout << mysql_error(con) << __LINE__ << endl;
	mysql_close(con);
	exit(1);
}
int main()
{
	MYSQL *con = mysql_init(NULL);

	if (con == NULL) {
		cout << __LINE__ << "err" << endl;
	}

	if (mysql_real_connect(con, "10.142.234.129", "roam", "roam@123", "ROAM_DATA", 9018, NULL, 0) ==  NULL) {
//	if (mysql_real_connect(con, "127.0.0.1", "root", "55668899", "test_poco_mysql", 3306, NULL, 0) ==  NULL) {
		cout << mysql_errno(con) << __LINE__ << endl;
		mysql_close(con);
		exit;
	}

	string query = "select distinct mlog.input_file  from message_log mlog\n"
				   "where  mlog.CREATE_TIME >=1536202800\n"
				   "and substr(mlog.input_file,16,3)=931\n"
				   "AND mlog.MODE_CODE LIKE '11*_%' ESCAPE'*'";

	if(mysql_query(con, query.c_str()))
		finist_with_error(con);

	MYSQL_RES * result = mysql_store_result(con);

	if (result == NULL)
		finist_with_error(con);

	int num_fields = mysql_num_fields(result);

	MYSQL_ROW row;

	while ((row = mysql_fetch_row(result)))
	{
		for(int i = 0; i < num_fields; i++)
		{
			printf("%s ", row[i] ? row[i] : "NULL");
		}
		printf("\n");
	}

	mysql_free_result(result);

	mysql_close(con);
	exit(0);

}
