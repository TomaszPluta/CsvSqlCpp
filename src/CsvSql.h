#include <string>

#pragma once
class CsvSql {
    
public:
    CsvSql ();
    void Connect(std::string host,  std::string user, std::string password ,std::string  dataBase);
    std::string  SendQuerry(std::string querry);
};