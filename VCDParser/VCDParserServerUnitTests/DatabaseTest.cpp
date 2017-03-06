//
//  DatabaseTest.cpp
//  VCDParserServer
//
//  Created by Karthik Ashok Arjunagi on 3/5/17.
//  Copyright © 2017 Karthik Ashok Arjunagi. All rights reserved.
//
#include <stdio.h>
#include <boost/filesystem.hpp>
#include <sqlite3.h>
#include "gtest/gtest.h"
#include "Database.hpp"

using namespace std;
using namespace boost::filesystem;


//Fixture which is set up and torn down before each test case
class DatabaseTest : public ::testing::Test {
    
public:
    
    string currDir;
    string dbName;
    Database db;
    DatabaseTest() : currDir(boost::filesystem::current_path().string()), dbName(currDir + "/test.db"), db(dbName) {
    }
    
    ~DatabaseTest() {
        sqlite3_close(&db.getDb());
        remove(dbName);
    }
    
};

/*
 * Test the constructor. 
 * The return code of opening the db successfully should be 0.
 */
TEST_F(DatabaseTest, ConstructorTest) {
    sqlite3 *tempDb = &db.getDb();
    int rc = sqlite3_open(dbName.c_str(), &tempDb);
    EXPECT_EQ(rc, 0);
}

/* Test creation of table.
 * Creates a table and checks its existence by trying to read data from it.
 */
TEST_F(DatabaseTest, CreateTable) {
    string query = "SELECT name FROM sqlite_master WHERE type='table' AND name='vcd';";
    sqlite3_stmt *stmt;
    sqlite3_prepare(&db.getDb(), query.c_str(), query.size(), &stmt, NULL);
    EXPECT_EQ(sqlite3_step(stmt), SQLITE_ROW);
}

/*
 * Test insertion of a row into the database.
 * Successful insertion will return SQLITE_DONE
 */
TEST_F(DatabaseTest, Insert) {
    string insertQuery = "INSERT INTO vcd (timestamp, data_point,value) VALUES ('1234', 'abc', '1.2.3');";
    sqlite3_stmt *insertStmt;
    sqlite3_prepare(&db.getDb(), insertQuery.c_str(), insertQuery.size(), &insertStmt, NULL);
    EXPECT_EQ(sqlite3_step(insertStmt), SQLITE_DONE);
}
