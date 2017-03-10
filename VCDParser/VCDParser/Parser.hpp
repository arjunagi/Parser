//
//  Parser.hpp
//  VCDParserServer
//
//  Created by Karthik Ashok Arjunagi on 3/1/17.
//  Copyright © 2017 Karthik Ashok Arjunagi. All rights reserved.
//

#ifndef Parser_hpp
#define Parser_hpp

#include <string>
#include <algorithm>

using namespace std;

class Parser {
    
public:
    
    /*
     * Parse the lines to store the comma seperated values into vector
     * Example 1 (first line of every file): # 52aa3d84-985c-4c57-ace1-c85251120227,pv=00000000000000000,ssn=0001,tsn=0001,type=VCD
     * Example 2: 1293836887205,Lat,0
     */
    vector<string> parseLines(std::string line);
    
    /*
     * Create a new file to store the parsed values.
     * File name format: uuid_vin_ssn_tsn_VCD.csv
     * Example: 52aa3d84-985c-4c57-ace1-c85251120227_00000000000000000_0004_0002_VCD.csv
     */
    string createFile(vector<string> firstLineCsv);
};

#endif /* Parser_hpp */
