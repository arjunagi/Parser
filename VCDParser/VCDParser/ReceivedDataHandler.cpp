//
//  ReceivedDataHandler.cpp
//  VCDParserServer
//
//  Created by Karthik Ashok Arjunagi on 3/5/17.
//  Copyright © 2017 Karthik Ashok Arjunagi. All rights reserved.
//

#include "ReceivedDataHandler.hpp"
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>

/*
 * Get the current directory, create a database "vcd" and 
 * also create a directory "parsed_logs"
 */
ReceivedDataHandler::ReceivedDataHandler() : curr_dir(boost::filesystem::current_path().string()), db_name(curr_dir + "/vcd.db"), db(db_name) {
    boost::filesystem::create_directories("parsed_logs");
    parsed_logs_dir = curr_dir + "/parsed_logs";
}

/*
 * Parse the data and store it into a file and database. 
 * Note that the first line of data is used to create the new file in parsed_logs/ and is not stored in db.
 *
 * @param receivedStreamData: streambuf object with the received data
 */
void ReceivedDataHandler::storeDataToFileAndDB(boost::asio::streambuf &receivedStreamData) {
    
    std::istream is(&receivedStreamData);
    std::string line;
    string parsedFileName;
    std::fstream fs;
    
    // Convert the streambuf data to string format line by line
    while (std::getline(is, line)) {
        if(line.find("#") != string::npos) {
            // If the data contains "#", then it is the first line of the file. Use it to create a new file.
            // This line is not stored in the db.
            vector<string> first_line_csv= this->parser.parseLines(line);
            parsedFileName = parsed_logs_dir + "/" + this->parser.createFile(first_line_csv);
            fs.open(parsedFileName, std::fstream::out);
        }
        else {
            // For all other lines, parse the data and store it in the new file and in the db.
            if(fs.is_open()) fs << line << "\n";
            vector<string> next_line_csv = parser.parseLines(line);
            if(next_line_csv.size() > 3) cerr<<"\nMore than 3 elements in " << parsedFileName << "\n" << line << "\n";
            else {
                db.insert("INSERT INTO vcd (timestamp, data_point, value) VALUES ("
                          + quotesql(next_line_csv[0]) + ","
                          + quotesql(next_line_csv[1]) + ","
                          + quotesql(next_line_csv[2]) + ");");
            }
        }
    }//end of while
    
    fs.close();
    
}//end of storeDataToFileAndDB

/*
 * Helper method to add quotes to the variables in the SQL query
 */
string ReceivedDataHandler::quotesql( const string& s ) {
    return string("'") + s + string("'");
}
