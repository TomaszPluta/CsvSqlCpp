#include <string>

#pragma once
class CsvSql {
private:
    void RemoveWhitespace(std::string &s);
    void RemoveComma(std::string &s);
public:
    CsvSql ();
    void Connect(std::string host,  std::string user, std::string password ,std::string  dataBase);
    std::string  SendQuerry(std::string querry);
};