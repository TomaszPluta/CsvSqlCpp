#include "iostream"
#include "CsvSql.h"


int main(int argc, char **argv)
{
    CsvSql csvSqlConnector;
    try {
        csvSqlConnector.Connect("host",  "usr", "pwd", "testDB");
        Querry querry("SELECT Name, City FROM Customers");
        std::string querryRes = csvSqlConnector.SendQuerry(querry);
        std::cout<<querryRes<<std::endl;
    } catch(...) {
        std::cout<<"database content error"<<std::endl;
    }


    return 0;
}
