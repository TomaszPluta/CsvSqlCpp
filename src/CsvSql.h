#pragma once

#include <string>
#include <vector>




class Querry{
private:
    std::string _querryData;
    void RemoveCharsFromStr(std::string &s, char c);

public:

    Querry(std::string querrry);
     std::vector<std::string> GetTokens();
    std::vector<std::string> GetColumnsFromHeader(std::string header);
    std::vector<int> GetQuerredColumnsNumbers(std::vector<std::string> tableColumns, std::vector<std::string> querredColumns);
        std::string GetFieldsFromSelectedColumns(std::vector<int> clmnsNb, std::string tableName);
};


class CsvSql {
private:




public:
    CsvSql ();
    
    void Connect(std::string host,  std::string user, std::string password ,std::string  dataBase);
    std::string  SendQuerry(Querry querry);
};

