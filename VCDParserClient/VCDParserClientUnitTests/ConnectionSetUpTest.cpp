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

/*
 * Test to verify that an error is thrown if connection to endpoint fails
 */
BOOST_AUTO_TEST_CASE(setUpUnixSocketTest) {
    
    ConnectionSetUp connect;
    std::string msg = "Connection refused";
    BOOST_CHECK_THROW(connect.setUpUnixSocket(), boost::system::error_code);
}
