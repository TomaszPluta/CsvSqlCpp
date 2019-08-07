#pragma once

#include <string>
#include <vector>

class CsvSql {
private:

    void RemoveCharsFromStr(std::string &s, char c);
    std::vector<std::string> GetColumnsFromHeader(std::string header);
    std::vector<int> GetQuerredColumnsNumbers(std::vector<std::string> tableColumns, std::vector<std::string> querredColumns);
    std::string GetFieldsFromSelectedColumns(std::vector<int> clmnsNb, std::string tableName);
public:
    CsvSql ();
    void Connect(std::string host,  std::string user, std::string password ,std::string  dataBase);
    std::string  SendQuerry(std::string querry);
};



class Querry{
private:
    
void RemoveCharsFromStr(std::string &s, char c);

public:
    std::vector<std::string> GetTokens(std::string querry);
    
};