//
//  ParserTest.cpp
//  VCDParserServer
//
//  Created by Karthik Ashok Arjunagi on 3/5/17.
//  Copyright © 2017 Karthik Ashok Arjunagi. All rights reserved.
//

#include <stdio.h>
#include "gtest/gtest.h"
#include "Parser.hpp"

/*
 * Tests if the first line of a file is parsed and stored in a vector<string>
 */
TEST(ParserTest, ParseFirstLineSuccessCase) {
    Parser p;
    string line = "# 52aa3d84-985c-4c57-ace1-c85251120227,pv=00000000000000000,ssn=0001,tsn=0001,type=VCD";
    vector<string> lineToCsv;
    lineToCsv.push_back("# 52aa3d84-985c-4c57-ace1-c85251120227");
    lineToCsv.push_back("pv=00000000000000000");
    lineToCsv.push_back("ssn=0001");
    lineToCsv.push_back("tsn=0001");
    lineToCsv.push_back("type=VCD");
    
    EXPECT_EQ(lineToCsv, p.parse_lines(line));
}

/*
 * Tests if the other lines of a file is parsed and stored in a vector<string>
 */
TEST(ParserTest, ParseOtherLinesSuccessCase) {
    Parser p;
    string line = "1293836887205,Lat,0";
    vector<string> lineToCsv;
    lineToCsv.push_back("1293836887205");
    lineToCsv.push_back("Lat");
    lineToCsv.push_back("0");

    EXPECT_EQ(lineToCsv, p.parse_lines(line));
}

/*
 * Tests if the file created has the name as expected.
 * Expected name format: uuid_vin_ssn_tsn_VCD.csv
 * Example: 52aa3d84-985c-4c57-ace1-c85251120227_00000000000000000_0001_0001_VCD.csv
 */
TEST(ParserTest, CreateFileSuccessCase) {
    Parser p;
    vector<string> lineToCsv;
    lineToCsv.push_back("# 52aa3d84-985c-4c57-ace1-c85251120227");
    lineToCsv.push_back("pv=00000000000000000");
    lineToCsv.push_back("ssn=0001");
    lineToCsv.push_back("tsn=0001");
    lineToCsv.push_back("type=VCD");
    string expectedFileName = "52aa3d84-985c-4c57-ace1-c85251120227_00000000000000000_0001_0001_VCD.csv";
    
    EXPECT_NE(expectedFileName, p.create_file(lineToCsv));
}

