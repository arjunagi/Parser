//
//  ConnectionSetUp.hpp
//  VCDParserServer
//
//  Created by Karthik Ashok Arjunagi on 3/5/17.
//  Copyright © 2017 Karthik Ashok Arjunagi. All rights reserved.
//

#ifndef ConnectionSetUp_hpp
#define ConnectionSetUp_hpp

#include <boost/asio.hpp>

using namespace boost::asio;

class ConnectionSetUp {
    
    //Create the unix socket and connect to the end point
    boost::asio::io_service io_service;
    local::stream_protocol::endpoint ep;
    local::stream_protocol::socket socket;
    local::stream_protocol::acceptor acceptor;
    
public:
    ConnectionSetUp();
    void setUpUnixSocket();
    local::stream_protocol::socket& getSocket();
    void closeSocket();
    
};

#endif /* ConnectionSetUp_hpp */
