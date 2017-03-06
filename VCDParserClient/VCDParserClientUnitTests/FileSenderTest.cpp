//
//  FileSenderTest.cpp
//  VCDParserClient
//
//  Created by Karthik Ashok Arjunagi on 3/4/17.
//  Copyright © 2017 Karthik Ashok Arjunagi. All rights reserved.
//


#define private public //EVIL EVIL EVIL

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
//#include <turtle/mock.hpp>
#include "FileSender.hpp"

#include <iostream>

using namespace boost::filesystem;
using namespace std;


/*
 * Test to verify if the file contents retrieved is correct.
 * Note: It is assumed that an existing file is passed to getFileContent method.
 */
BOOST_AUTO_TEST_CASE(testGetFileContentCorrectness) {
    string fileName = "../../logs/52aa3d84-985c-4c57-ace1-c85251120227_00000000000000000_0001_VCD_0001.log";
    std::ifstream ifs;
    ifs.open(fileName);
    stringstream fileContentStream;
    fileContentStream << ifs.rdbuf();
    ifs.close();
    
    FileSender fs;
    BOOST_TEST(fs.getFileContent(fileName, ifs).str() == fileContentStream.str());
}

/*
 * Test to verify if the entire file content is retrieved. 
 * This is done by comparing the retrived number of bytes with file size.
 * Note: It is assumed that an existing file is passed to getFileContent method.
 */
BOOST_AUTO_TEST_CASE(testGetFileContentSize) {
    string fileName = "../../logs/52aa3d84-985c-4c57-ace1-c85251120227_00000000000000000_0001_VCD_0001.log";
    std::ifstream file;
    file.open(fileName);
    stringstream fileContentStream;
    fileContentStream << file.rdbuf();
    size_t fileSize = fileContentStream.str().size();
    file.close();

    
    FileSender fs;
    std::ifstream ifs;
    BOOST_CHECK(fs.getFileContent(fileName, ifs).str().size() == fileSize);
    ifs.close();
}


/*
 * Test to verify if the entire file content is written to the socket.
 * This is done by comparing the file size with the return value of boost::asio::write().
 * Note: It is assumed that a non-zero size file is passed to writeContentsToSocket.
 */
//BOOST_AUTO_TEST_CASE(writeContentsToSocketSize) {
//    string fileName = "/Users/Karthik/Documents/c++ project/logs/52aa3d84-985c-4c57-ace1-c85251120227_00000000000000000_0001_VCD_0001.log";
//    FileSender fs;
//    std::ifstream ifs;
//    size_t fileSize = file_size(path(fileName));
//    
//    BOOST_CHECK(fs.writeContentsToSocket() == fileSize);
//    ifs.close();
//}
