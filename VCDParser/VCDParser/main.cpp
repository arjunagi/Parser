//
//  main.cpp
//  VCDParserServer
//
//  Created by Karthik Ashok Arjunagi on 2/25/17.
//  Copyright © 2017 Karthik Ashok Arjunagi. All rights reserved.
//

/*
 * Server which receives the VCD data, parses it and stores it in a file and also in SQLite DB.
 */

#include <iostream>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include "ReceivedDataHandler.hpp"
#include "ConnectionSetUp.hpp"

using namespace std;
using namespace boost::asio;
using namespace boost::filesystem;

int main(int argc, const char * argv[]) {
    
    //If using XCode - go to Product->Scheme->Edit Scheme -> Option -> Working Directory -> Select on Use custom Working Directory
    //and select it to be the location of this file (main.cpp)
    
    
    try {
        ::unlink("/tmp/sock");
        ConnectionSetUp connect;
        connect.setUpUnixSocket();
        ReceivedDataHandler dataHandler;
        
        while(true) {
            
            //Continue if data available to read in socket
            if(connect.getSocket().available() > 0) {
                boost::asio::streambuf data;
                boost::system::error_code error;
                
                // Read the all the available data from the socket.
                while (boost::asio::read(connect.getSocket(), data, boost::asio::transfer_at_least(connect.getSocket().available()), error)) {
                    cout<<"Received: " << data.size() <<"\n";
                    if(!error || error == boost::asio::error::eof)
                        dataHandler.storeDataToFileAndDB(data);
                    else
                        throw boost::system::system_error(error);
                }// end of while
                
            }//end of if
            
        }//end of while(true)
        
    }//end of try
    
    catch (const char* e) {
        cerr <<"\nTable Creation Exception: " << e <<endl;
    }
    catch (boost::system::system_error e) {
        cerr << "Error when reading from socket: " << e.what() << endl;
    }
    catch (std::exception& e) {
        cerr <<"\nServer Exception: " << e.what() <<endl;
    }
    
    
    return 0;
}
