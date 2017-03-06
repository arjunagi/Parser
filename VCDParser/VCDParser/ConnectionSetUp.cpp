//
//  ConnectionSetUp.cpp
//  VCDParserServer
//
//  Created by Karthik Ashok Arjunagi on 3/5/17.
//  Copyright © 2017 Karthik Ashok Arjunagi. All rights reserved.
//

/*
 * This class:
 * 1. Initilaizes the Unix socket and binds the acceptor to the endpoint to prepare it to accept connections.
 * 2. Provides a method to access the socket object
 * 3. Provides a method to explicitly close the socket
 */

#include "ConnectionSetUp.hpp"

//Initialize the socket and acceptor
ConnectionSetUp::ConnectionSetUp() : socket(io_service), acceptor(io_service, "/tmp/sock") {
    this->ep = "/tmp/sock";
}

/*
 * Be ready to accept any connection requests to the socket
 */
void ConnectionSetUp::setUpUnixSocket() {
    acceptor.accept(socket);
}

local::stream_protocol::socket& ConnectionSetUp::getSocket() {
    return this->socket;
}

void ConnectionSetUp::closeSocket() {
    this->socket.close();
}
