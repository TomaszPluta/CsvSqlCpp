#include <CsvSql.h>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>



/***********************************************************************************
 HELPERS DECLARATIONS 
************************************************************************************/
template<class T>
void DebugPrintVector(std::string vName, std::vector<T> & v);
void RemoveCharsFromStr(std::string &s, char c);


/***********************************************************************************
CLASS IMPLEMENTATION:  CSVSQL 
************************************************************************************/

CsvSql::CsvSql (){};

void CsvSql::Connect(std::string host,  std::string user, std::string password, std::string  dataBase)
{
    std::ifstream dbFile;
    dbFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        dbFile.open(dataBase.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
    } catch(const std::ifstream::failure& e) {
        std::cerr << "Error: " << e.what();
    }

    if ( dbFile.peek() == std::ifstream::traits_type::eof() ) {
        throw std::runtime_error("Could not open file");
    }

    std::vector<std::string> tables;
    std::string table;
    while(!dbFile.eof() &&(dbFile >> table)) {
        tables.push_back(table);
    }

    std::cout<<"database in use: " << dataBase<<std::endl;
    DebugPrintVector("tables", tables);
}



std::string  CsvSql::SendQuerry(Querry querry)
{
    std::vector<std::string> tokens = querry.GetTokens();
    DebugPrintVector("tokens", tokens);

    if (*tokens.begin()== "SELECT") {   //select querry should derive from base "QUERRY" class
        std::vector<std::string>::iterator iter = (std::find(tokens.begin(), tokens.end(), std::string("FROM")) );

        if (iter != tokens.end()) {
            std::vector<std::string> columnsQuerry (++tokens.begin(), iter) ;
            DebugPrintVector("columns in querry:", columnsQuerry);
            std::string tableInUse = *++iter;

            Table table(tableInUse);
            return   table.GetSelectedColumnsContent(columnsQuerry);
        }
    } else if (*tokens.begin()== "SELECT") {
        ///TODO;
        }
    return std::string(" ");
}



/***********************************************************************************
CLASS IMPLEMENTATION:  QUERRY 
************************************************************************************/


Querry::Querry(std::string querrry) : _querryData {querrry} {};

std::vector<std::string>  Querry::GetTokens()
{
    std::stringstream querryStream ( _querryData);
    std::string token;
    std::vector<std::string> tokens;
    while(getline(querryStream, token, ' ')) {
        RemoveCharsFromStr(token, ',');
        tokens.push_back(token);
    }
    return tokens;
}


/***********************************************************************************
CLASS IMPLEMENTATION:  Table 
************************************************************************************/

Table::Table (std::string tableName)
{
    _tableFile.open(tableName);
}


std::vector<std::string> Table::GetColumnsNames(void)
{
    std::string header;
    getline(_tableFile, header);
    std::stringstream headerStream(header);
    std::string column;
    std::vector <std::string>columns;
    while(getline(headerStream, column, ',')) {
        RemoveCharsFromStr(column, ' ');
        columns.push_back((column));
    }
    return columns;
}

std::vector<int>Table::GetSelectedColumnsNumbers(std::vector<std::string> tableColumns, std::vector<std::string> querredColumns)
{
    std::vector<int> clmnsNb;
    for (int i =0 ; i < querredColumns.size(); i++) {
        for (int j =0 ; j < tableColumns.size(); j++) {
            if (tableColumns[j] == querredColumns[i]) {
                clmnsNb.push_back(j);
            }
        }
    }
    return clmnsNb;
    
    }
    
    std::string Table::GetFieldsFromSelectedColumnsNumbers(std::vector<int> clmnsNb)
    {
        std::string querredFields;
        std::string line;
        while( getline(_tableFile, line) ) {
            int i = 0;
            std::stringstream ss(line);
            std::string field;
            while( getline(ss, field, ',')) {
                if ( (std::find(clmnsNb.begin(), clmnsNb.end(), i) !=clmnsNb.end())) {
                    RemoveCharsFromStr(field, ' ');
                    querredFields += field + " ";
                }
                i++;
            }
            querredFields +=  "\n";
        }
    
        return querredFields;
    }
    
std::string Table::GetSelectedColumnsContent(std::vector<std::string> selectedColumns)
{
    std::vector<std::string> columnsNames = GetColumnsNames();
    std::vector<int> clmnsNb = GetSelectedColumnsNumbers(columnsNames, selectedColumns);
    return GetFieldsFromSelectedColumnsNumbers(clmnsNb);
}



/*************************************************************************************
    HELPERS
*************************************************************************************/


template<class T>
void DebugPrintVector(std::string vName, std::vector<T> & v)
{
    std::cout<<vName<<": "<<std::endl;
    for (auto i : v) {
        std::cout<<"- "<<i<<std::endl;
    }
    std::cout<<std::endl;
}


void RemoveCharsFromStr(std::string &s, char c)
{
    s.erase(std::remove(s.begin(), s.end(), c), s.end());
}
