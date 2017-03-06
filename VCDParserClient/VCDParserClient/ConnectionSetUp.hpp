//
//  ConnectionSetUp.hpp
//  VCDParserClient
//
//  Created by Karthik Ashok Arjunagi on 3/4/17.
//  Copyright © 2017 Karthik Ashok Arjunagi. All rights reserved.
//

/*
 * This class:
 * 1. Initilaizes the Unix socket and connects to the end point
 * 2. Provides a method to access the socket object
 * 3. Provides a method to explicitly close the socket 
 */

#ifndef ConnectionSetUp_hpp
#define ConnectionSetUp_hpp

#include <boost/asio.hpp>

using namespace boost::asio;

class ConnectionSetUp {
    
    //Create the unix socket and connect to the end point
    boost::asio::io_service io_service;
    local::stream_protocol::endpoint ep;
    local::stream_protocol::socket socket;
    
public:
    ConnectionSetUp();
    void setUpUnixSocket();
    local::stream_protocol::socket& getSocket();
    void closeSocket();
    
};

#endif /* ConnectionSetUp.hpp */
