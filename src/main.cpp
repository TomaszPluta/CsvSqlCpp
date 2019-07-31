#include <stdio.h>
#include "CsvSql.h"


int main(int argc, char **argv)
{
    CsvSql csvSqlConnector;
    csvSqlConnector.Connect("host",  "usr", "pwd", "testDB");
    csvSqlConnector.SendQuerry("SELECT CustomerName, City FROM Customers");

	printf("hello world\n");
	return 0;
}
