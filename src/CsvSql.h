#pragma once

#include <string>
#include <vector>

class CsvSql {
private:
    std::vector<std::string> GetTokesFromQuerry(std::string querry);
    void RemoveCharsFromStr(std::string &s, char c);

public:
    CsvSql ();
    void Connect(std::string host,  std::string user, std::string password ,std::string  dataBase);
    std::string  SendQuerry(std::string querry);
};