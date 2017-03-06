//
//  Database.hpp
//  VCDParserServer
//
//  Created by Karthik on 2/28/17.
//  Copyright © 2017 Karthik Ashok Arjunagi. All rights reserved.
//

#ifndef Database_hpp
#define Database_hpp

#include <stdio.h>
#include <string>
#include <sqlite3.h>

using namespace std;

class Database {
    sqlite3 *db;
    string dirPath;
    const char* dbName;
    
public:
    Database(string dbName);
    ~ Database();
    sqlite3& getDb();
    void insert(string insertQuery);
    void otherQuery(string query);
    
private:
    void createTable();
    static int callback(void *NotUsed, int argc, char **argv, char **col_name);
};

#endif /* Database_hpp */
