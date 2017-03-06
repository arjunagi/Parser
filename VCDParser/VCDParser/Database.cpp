//
//  Database.cpp
//  VCDParserServer
//
//  Created by Karthik on 2/28/17.
//  Copyright © 2017 Karthik Ashok Arjunagi. All rights reserved.
//

#include "Database.hpp"
#include <iostream>
#include <boost/filesystem.hpp>

using namespace std;

/*
 * Open a database with the given name. If open is succesful, create a table, 
 * else throw sqlite3_errmsg
 */
Database::Database(string db_name) {
    int rc = sqlite3_open_v2(db_name.c_str(), &db, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL);
    if(rc) throw sqlite3_errmsg(db);
    else  {
        cout<<"Database " << db_name <<" created!\n";
        createTable();
    }
}


/*
 * Explicit destructor to close the database and delete it.
 */
Database::~Database() {
    sqlite3_close(this->db);
}


/*
 * Retruns the sqlite3 object.
 */
sqlite3& Database::getDb() {
    return *db;
}


/*
 * Create a table "vcd" with columns: timestamp, data_point, value.
 * If creation failes, throw sqlite3_errmsg
 */
void Database::createTable() {
    string createTableQuery = "CREATE TABLE IF NOT EXISTS vcd (timestamp TEXT, data_point TEXT, value TEXT);";
    sqlite3_stmt *createStmt;
    sqlite3_prepare(this->db, createTableQuery.c_str(), createTableQuery.size(), &createStmt, NULL);
    if (sqlite3_step(createStmt) != SQLITE_DONE) throw sqlite3_errmsg(db);
}


/*
 * Insert into the database the data provided in the query.
 * @param insertQuery: SQL query to insert the vcd data into database.
 */
void Database::insert(string insertQuery) {
    sqlite3_stmt *insertStmt;
    sqlite3_prepare(db, insertQuery.c_str(), insertQuery.size(), &insertStmt, NULL);
    if (sqlite3_step(insertStmt) != SQLITE_DONE) cout << "Didn't Insert Items for query: \n" << insertQuery << endl;
}


/*
 * ****** NOT USED ******
 * Execute other queries.
 * @param query: SQL query to be executed
 */
void Database::otherQuery(string query) {
    char *err_msg = 0;
    int rc = sqlite3_exec(db, query.c_str(), Database::callback, 0, &err_msg);
    if( rc != SQLITE_OK ){
        cout << "SQL error: "<< err_msg << "\n";
        sqlite3_free(err_msg);
    }
}


/*
 * Callback method to print the database contents.
 * Callback method will be called for each record in the result of sqlite3_exec 
 * @param NotUsed: parameter not used here.
 * @param numOfCol: Number of columns in the database for the current record row
 * @param data: The row's data
 * @param colName: name of the column
 *
 * @return 0
 */
int Database::callback(void *NotUsed, int numOfCol, char **data, char **colName){
    for(int i=0; i<numOfCol; i++) {
        //Print out the row data.
        cout << colName[i] << " = " << (data[i] ? data[i] : "NULL") << "\n";
    }
    cout <<endl;
    return 0;
}
