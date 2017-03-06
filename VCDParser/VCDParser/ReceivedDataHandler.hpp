//
//  ReceivedDataHandler.hpp
//  VCDParserServer
//
//  Created by Karthik Ashok Arjunagi on 3/5/17.
//  Copyright © 2017 Karthik Ashok Arjunagi. All rights reserved.
//

#ifndef ReceivedDataHandler_hpp
#define ReceivedDataHandler_hpp

#include <boost/asio.hpp>
#include "Database.hpp"
#include "Parser.hpp"

using namespace boost::asio;
using namespace std;

class ReceivedDataHandler {
    string curr_dir;
    string db_name;
    string parsed_logs_dir;
    Parser parser;
    Database db;
    
public:
    ReceivedDataHandler();
    void storeDataToFileAndDB(boost::asio::streambuf &receivedStreamData);
    
private:
    string quotesql(const string& s);
    
};

#endif /* ReceivedDataHandler_hpp */
