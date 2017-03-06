//
//  main.cpp
//  VCDParserServerUnitTests
//
//  Created by Karthik Ashok Arjunagi on 3/2/17.
//  Copyright © 2017 Karthik Ashok Arjunagi. All rights reserved.
//

#include <stdio.h>

#include "gtest/gtest.h"

GTEST_API_ int main(int argc, char **argv) {
    printf("Running main() from gtest_main.cc\n");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
