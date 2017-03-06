//
//  ConnectionSetUpTest.cpp
//  VCDParserClientUnitTests
//
//  Created by Karthik Ashok Arjunagi on 3/4/17.
//  Copyright © 2017 Karthik Ashok Arjunagi. All rights reserved.
//

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/asio.hpp>
#include "ConnectionSetUp.hpp"

using namespace boost::asio;

//struct mockSocket {
//    
//    boost::asio::io_service io_service;
//    local::stream_protocol::endpoint ep;
//    local::stream_protocol::socket socket;
//    local::stream_protocol::acceptor acceptor;
//    
//    mockSocket(): socket(io_service), acceptor(io_service, ep) {
//        ::unlink("/tmp/sock");
//        this->ep = "/tmp/sock";
//        acceptor.accept(socket);
//    }
//    
//    ~mockSocket() {
////        ::unlink("/tmp/sock");
////        socket.close();
////        acceptor.close();
////        io_service.stop();
//    }
//};

/*
 * Test to verify that an error is thrown if connection to endpoint fails
 */
BOOST_AUTO_TEST_CASE(setUpUnixSocketTest) {
    
    ConnectionSetUp connect;
    std::string msg = "Connection refused";
    BOOST_CHECK_THROW(connect.setUpUnixSocket(), boost::system::error_code);
}
