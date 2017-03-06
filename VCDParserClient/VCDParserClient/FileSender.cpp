//
//  FileSender.cpp
//  VCDParserClient
//
//  Created by Karthik Ashok Arjunagi on 3/4/17.
//  Copyright © 2017 Karthik Ashok Arjunagi. All rights reserved.
//

#include "FileSender.hpp"
#include <boost/filesystem.hpp>
#include <iostream>

using namespace boost::filesystem;
using namespace std;

FileSender::FileSender() {
    this->dir = "../../logs/";
}

/*
 * Open the directory and send the files one by one
 * @param socket: The socket object to send the files.
 */
void FileSender::sendFiles(local::stream_protocol::socket& socket) {
    
    if (is_directory(dir))
    {
        //Read each file in the directory
        for (directory_iterator itr(dir); itr!=directory_iterator(); ++itr)
        {
            // Get the filename and its absolute path
            path p = itr->path().filename();
            string fileName = dir + p.string();
            
            //Send only the VCD files
            if(fileName.find("VCD") != string::npos) {
                if(file_size(itr->path()) == 0)
                    cout<<"\nEmpty file not sent: " + p.string() + "\n";
                else {
                    std::ifstream ifs;
                    stringstream fileContentStream = getFileContent(fileName, ifs);
                    
                    // Write the file contents to the socket
                    size_t bytesWritten = writeContentsToSocket(fileContentStream, socket);
                    cout<<"\nFile sent: "<< p.string() <<"\nBytes written: " << bytesWritten <<"\n";
                    
                    //If the entire contents of the file is sent, close the file stream
                    if(bytesWritten == file_size(itr->path())) {
                        ifs.close();
                        sleep(2);
                    }
                }
            }
            
        }//end of for
        
    }//end of if
    
    else {
        cout<<(exists(dir) ? "Found: " : "Not found: ")<< dir << "\n";
    }
}

/*
 * Retrives the contents from the file and return as a stringstream object
 * @param fileName: The name of the file whose contents have to be read.
 * @param ifs: The ifstream object which is initialized with the required file.
 * NOTE: File existence is guranteed since the file name is retrieved from dir iterator.
 *
 * @return File contents as stringstream object.
 */
stringstream FileSender::getFileContent(string fileName, std::ifstream &ifs) {
    
    std::stringstream fileContentStream;
    
    //Read the entrire contents of the file
    ifs.open(fileName);
    fileContentStream << ifs.rdbuf();
    
    return fileContentStream;
}

/*
 * Writes the file contents to the socket
 * @param fileContentStream: complete file contents in stringstream format
 * @param socket: socket to send the data
 *
 * @return The number of bytes that was written(sent) on the socket.
 */
size_t FileSender::writeContentsToSocket(stringstream &fileContentStream, local::stream_protocol::socket &socket) {
    return boost::asio::write(socket, boost::asio::buffer(fileContentStream.str(), fileContentStream.str().size()));
}
