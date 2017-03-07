//
//  main.cpp
//  VCDParserClient
//
//  Created by Karthik Ashok Arjunagi on 2/25/17.
//  Copyright © 2017 Karthik Ashok Arjunagi. All rights reserved.
//

/*
 * Client which send VCD file data to the server at given interval.
 */

#include "ConnectionSetUp.hpp"
#include "FileSender.hpp"
#include <iostream>

using namespace std;

int main(int argc, const char * argv[]) {
    
    try{
        ConnectionSetUp connection;
        connection.setUpUnixSocket();
        
        FileSender fs;
        fs.sendFiles(connection.getSocket());
        
        connection.closeSocket();
    } catch (exception& e) {
        cerr <<"\nClient Exception: " << e.what() <<endl;
    } catch (boost::system::error_code ec) {
        //Exception thrown when connection to server failed
        cerr<< ec.message() << "\n";
    } catch (std::string s) {
        //Exception thrown when opening of socket failed.
        cerr<< s << "\n";
    }
    
    return 0;
}
