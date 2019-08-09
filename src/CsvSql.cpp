#include <CsvSql.h>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>


template<class T>
void DebugPrintVector(std::string vName, std::vector<T> & v)
{
    std::cout<<vName<<": "<<std::endl;
    for (auto i : v) {
        std::cout<<"- "<<i<<std::endl;
    }
    std::cout<<std::endl;
}



std::vector<std::string> Querry::GetColumnsFromHeader(std::string header)
{
    std::stringstream headerStream(header);
    std::string column;
    std::vector <std::string>columns;
    while(getline(headerStream, column, ',')) {
        RemoveCharsFromStr(column, ' ');
        columns.push_back((column));
    }

    return columns;
}

std::vector<int>Querry::GetQuerredColumnsNumbers(std::vector<std::string> tableColumns, std::vector<std::string> querredColumns)
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

std::string Querry::GetFieldsFromSelectedColumns(std::vector<int> clmnsNb, std::string tableName){
            std::string querredFields;
            std::string line;
            std::ifstream tableFileIn(tableName);
            while( getline(tableFileIn, line) ) {
                int i = 0;
                std::stringstream ss(line);
                std::string field;
                while( getline(ss, field, ',')) {
                    if (field.empty()) {
                        break;
                    }
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

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
Querry::Querry(std::string querrry) : _querryData{querrry}{};

void Querry::RemoveCharsFromStr(std::string &s, char c)
{
    s.erase(std::remove(s.begin(), s.end(), c), s.end());
}


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










//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief 
 * @param querry
 * @return 
 */
CsvSql::CsvSql ()
{

}


/**
 * @brief 
 * @param querry
 * @return 
 */
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


//class querry, class table.


/**
 * @brief 
 * @param querry
 * @return 
 */
std::string  CsvSql::SendQuerry(Querry querry)
{
    std::vector<std::string> tokens = querry.GetTokens();
    DebugPrintVector("tokens", tokens);

    std::string res;
    
    if (*tokens.begin()== "SELECT") {   //select querry derives from base "QUERRY" class
        std::vector<std::string> querredColumns;

     std::vector<std::string>::iterator  it = tokens.begin() +1 ;
    
std::vector<std::string>::iterator   itr = (std::find(tokens.begin(), tokens.end(), std::string("FROM")) );
 
if (itr != tokens.end()){
        std::vector<std::string> columns (++tokens.begin(), itr) ;
        DebugPrintVector("!columns!", columns);
}
     
//iterator vector.start()+1;
        
//        find in vector "FROM" (enum keyword)
//        get new vector between (start+1) and founded from.
//        That new vector is columns.
//        Next iterator is table in use
//        
//        
//        for (auto i : tokens){
//            while ( i != "FROM"){
//                std::vector(input_iterator, input_iterator), in your case foo = std::vector(myVec.begin () + 100000, myVec.begin () + 150000);
//            }
//        }
//        
//        while ((tokens[i] != "FROM") && (i<tokens.size())) {
//            querredColumns.push_back( tokens[i]);
//            i++;
//        }
//        i++; //skip keyword "from"Nb
//        std::string table = tokens[i];
//
//        std::cout<<"table in use: "<<table<<std::endl;
//
//
//        if (1) { 
//            std::fstream tableFile;
//            tableFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//            try {
//                tableFile.open(table,  std::fstream::in | std::fstream::out | std::fstream::app);
//            } catch(const std::ifstream::failure& e) {
//                std::cerr << "Error: " << e.what();
//            }
//
//            std::string header;
//            std::getline(tableFile, header) ;
//
//            std::vector<std::string> columns = GetColumnsFromHeader(header);
//            DebugPrintVector("columns", columns);
//
//            std::vector<int> clmnsNb = GetQuerredColumnsNumbers(columns,  querredColumns);
//
//           std::string querryRes =GetFieldsFromSelectedColumns(clmnsNb, table);
//            std::cout<<"result:"<<std::endl<<querryRes<<std::endl;
//
//            std::cout<<std::endl;
//
//        }
        return res;
    }
}
