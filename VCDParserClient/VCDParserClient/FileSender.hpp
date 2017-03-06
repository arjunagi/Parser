//
//  FileSender.hpp
//  VCDParserClient
//
//  Created by Karthik Ashok Arjunagi on 3/4/17.
//  Copyright © 2017 Karthik Ashok Arjunagi. All rights reserved.
//

#ifndef FileSender_hpp
#define FileSender_hpp

#include <string>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

/*
 * Class which handles reading the file data and sending it across the socket to the server. 
 */

class FileSender {
    
    string dir; // relative directory location of the logs
    
public:
    FileSender();
    void sendFiles(local::stream_protocol::socket&);
    
private:
    stringstream getFileContent(string, std::ifstream &);
    size_t writeContentsToSocket(stringstream &, local::stream_protocol::socket &);
    
};

#endif /* FileSender_hpp */
