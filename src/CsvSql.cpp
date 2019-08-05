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


void CsvSql::RemoveCharsFromStr(std::string &s, char c)
{
    s.erase(std::remove(s.begin(), s.end(), c), s.end());
}


std::vector<std::string>  CsvSql::GetTokesFromQuerry(std::string querry)
{
    std::stringstream querryStream (querry);
    std::string token;
    std::vector<std::string> tokens;
    while(getline(querryStream, token, ' ')) {
        RemoveCharsFromStr(token, ',');
        tokens.push_back(token);
    }
    return tokens;
}



/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


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



/**
 * @brief 
 * @param querry
 * @return 
 */
std::string  CsvSql::SendQuerry(std::string querry)
{
    std::vector<std::string> tokens = GetTokesFromQuerry(querry);
    DebugPrintVector("tokens", tokens);

    std::string res;
    
    if (*tokens.begin()== "SELECT") {
        std::vector<std::string> columnsQuerry;
        int i =1;
        while ((tokens[i] != "FROM") && (i<tokens.size())) {
            std::string column = tokens[i];
            columnsQuerry.push_back(column);
            i++;
        }
        i++; //skip keyword "from"Nb
        std::string table = tokens[i];

        std::cout<<"table in use: "<<table<<std::endl;


        if (1) {
            std::fstream tableFile;
            tableFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            try {
                tableFile.open(table,  std::fstream::in | std::fstream::out | std::fstream::app);
            } catch(const std::ifstream::failure& e) {
                std::cerr << "Error: " << e.what();
            }

            std::string header;

            std::getline(tableFile, header) ;
            std::cout<<"header: "<<header<<std::endl;


            std::string column;
                        std::vector<std::string>columnsFile;
            std::stringstream headerStream(header);
            while(getline(headerStream, column, ',')) {
                RemoveCharsFromStr(column, ' ');
                columnsFile.push_back((column));
            }

            std::cout<<"columns: "<<std::endl;
            for (auto i : columnsFile) {
                std::cout<< "- "<<i <<std::endl;
            }
            std::cout<<std::endl;


            std::vector<int> clmnsNb;
            for (int i =0 ; i < columnsQuerry.size(); i++) {
                for (int j =0 ; j < columnsFile.size(); j++) {
                    if (columnsFile[j] == columnsQuerry[i]) {
                        clmnsNb.push_back(j);
                    }
                }
            }



            std::string line;
            std::ifstream tableFileIn(table);
            while( getline(tableFileIn,line) ) {
                int i = 0;
                std::stringstream ss(line);
                std::string field;
                while( getline(ss, field, ',')) {
                    if (field.empty()) {
                        break;
                    }
                    if ( (std::find(clmnsNb.begin(), clmnsNb.end(), i) !=clmnsNb.end())) {
                        RemoveCharsFromStr(field, ' ');
                        res += field + " ";
                    }
                    i++;
                }
                res +=  "\n";
            }



            std::cout<<"result:"<<std::endl<<res<<std::endl;


            std::cout<<std::endl;

        }
        return res;
    }
}
