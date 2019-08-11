#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>



class Querry{
private:
    std::string _querryData;
public:
    Querry(std::string querrry);
     std::vector<std::string> GetTokens();
    std::vector<int> GetQuerredColumnsNumbers(std::vector<std::string> tableColumns, std::vector<std::string> querredColumns);
    std::string GetFieldsFromSelectedColumns(std::vector<int> clmnsNb, std::string tableName);
};



class QuerrySelect : public Querry
{
private:
    std::vector<std::string> tokens;
    std::vector<std::string>::iterator iter;
    std::vector<std::string> columnsQuerry;
    std::string tableInUse;
    std::string whereKeyword;

public:
};

class Table{
 private:
std::ifstream _tableFile;
std::vector<std::string> GetColumnsNames(void);
std::vector<int>GetSelectedColumnsNumbers(std::vector<std::string> tableColumns, std::vector<std::string> querredColumns);
std::string GetFieldsFromSelectedColumnsNumbers(std::vector<int> clmnsNb);
    
    
public:    
  Table (std::string tableName) ;
    std::string GetSelectedColumnsContent(std::vector<std::string> columns);
   void InsertContentIntoColumns(std::vector<std::string> content, std::vector<std::string> columns);
   
};



class CsvSql {
private:

public:
    CsvSql ();
    
    void Connect(std::string host,  std::string user, std::string password ,std::string  dataBase);
    std::string  SendQuerry(Querry querry);
};

