//
//  ConnectionSetUp.cpp
//  VCDParserClient
//
//  Created by Karthik Ashok Arjunagi on 3/4/17.
//  Copyright © 2017 Karthik Ashok Arjunagi. All rights reserved.
//

#include "ConnectionSetUp.hpp"

/*
 * This class:
 * 1. Initilaizes the Unix socket and connects to the end point
 * 2. Provides a method to access the socket object
 * 3. Provides a method to explicitly close the socket
 */


//Initialize the socket
ConnectionSetUp::ConnectionSetUp() : socket(io_service) {
}


/*
 * Connect to the predefined end point. 
 */
void ConnectionSetUp::setUpUnixSocket() {
    this->ep = "/tmp/sock";
    boost::system::error_code ec;
    this->socket.connect(ep, ec);
    if(ec) {
        throw ec;
    }
    if(! this->socket.is_open()) {
        throw std::string ("Error when connecting to end point");
    }
}

local::stream_protocol::socket& ConnectionSetUp::getSocket() {
    return this->socket;
}

void ConnectionSetUp::closeSocket() {
    this->socket.close();
}
