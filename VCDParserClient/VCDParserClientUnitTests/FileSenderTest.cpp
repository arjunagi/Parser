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
#include "FileSender.hpp"

#include <iostream>

using namespace boost::filesystem;
using namespace std;


/*
 * Test to verify if the file contents retrieved is correct.
 * Note: It is assumed that an existing file is passed to getFileContent method.
 */
BOOST_AUTO_TEST_CASE(getFileContentShouldReturnCorrectContent) {
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
 * Test to verify if the file contents retrieved is empty for empty file name.
 */
BOOST_AUTO_TEST_CASE(getFileContentShouldReturnEmptyForEmptyFileName) {
    string fileName = "";
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
BOOST_AUTO_TEST_CASE(getFileContentShouldRetrieveFullFile) {
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
 * Test to verify if zero bytes is retrieved for an existing empty file.
 */
BOOST_AUTO_TEST_CASE(getFileContentShouldRetrieveZeroBytesForEmptyFile) {
    string fileName = "../../logs/52aa3d84-985c-4c57-ace1-c85251120227_00000000000000000_00028_VCD_0010.log";
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

