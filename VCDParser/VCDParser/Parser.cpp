//
//  Parser.cpp
//  VCDParserServer
//
//  Created by Karthik Ashok Arjunagi on 3/1/17.
//  Copyright © 2017 Karthik Ashok Arjunagi. All rights reserved.
//

#include <boost/algorithm/string.hpp>
#include <boost/asio.hpp>
#include "Parser.hpp"

using namespace boost::asio;
using namespace std;


/*
 * Parse the lines to store the comma seperated values into vector
 * Example 1 (first line of every file): # 52aa3d84-985c-4c57-ace1-c85251120227,pv=00000000000000000,ssn=0001,tsn=0001,type=VCD
 * Example 2: 1293836887205,Lat,0
 *
 * @param line: The line to be parsed
 * @return: vector of values extracted form the csv line
 */
vector<string> Parser::parseLines(std::string line) {
    
    stringstream ss(line);
    vector<string> csvValues; //vector to store the csv values
    
    //Divide the line by ',' and store the sub-strings into a vector csv_values
    while(ss.good())
    {
        string substr;
        getline( ss, substr, ',' );
        csvValues.push_back( substr );
    }
    return csvValues;
    
}//end of parse_lines()

/*
 * Create a new file to store the parsed values.
 * File name format: uuid_vin_ssn_tsn_VCD.csv
 * Example: 52aa3d84-985c-4c57-ace1-c85251120227_00000000000000000_0004_0002_VCD.csv
 *
 * @param firstLineCsv: First line of the file
 * @return The new file name
 */
string Parser::createFile(vector<string> firstLineCsv) {

    if(firstLineCsv.size() == 0) return "";
    
    string newFileName;
    
    //Remove the "# " a the beginning of the line
    boost::erase_first(firstLineCsv[0], "# ");
    
    //Start creating the new file name beginning with the UUID
    newFileName.append(firstLineCsv[0]);
    
    //Iterate over rest of the vector and separate the key=value pairs. Append only the value part to the new file name
    for (std::vector<string>::const_iterator i = firstLineCsv.begin()+1; i != firstLineCsv.end(); ++i) {
        string query = *i;
        string value;
        size_t positionOfEquals = query.find("=");
        if(positionOfEquals != string::npos) {
            value = query.substr(positionOfEquals + 1);
            newFileName.append("_" + value);
        }
    }
    newFileName.append(".csv");  //Example new file name: 52aa3d84-985c-4c57-ace1-c85251120227_00000000000000000_0001_0001_VCD.csv
    return newFileName;
    
}// end of create_file
