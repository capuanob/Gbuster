//
// Created by bailey on 5/17/20.
//

#include "gtest/gtest.h"
#include "binary.h"
#include <iostream>
using namespace bin;

TEST(binary_tests, test_word_constructor) {
    std::cout << "Testing Word constructors..." << std::endl;

    // Test edge-case constructor w/o any bytes provided
    EXPECT_EQ(Word({}, Endian::LITTLE).value(), 0);
    EXPECT_EQ(Word({}, Endian::BIG).value(), 0);

    // Test partial word (ensure 0s are correctly handled)
    EXPECT_EQ(Word({0x80, 0xA6}, Endian::LITTLE).value(), 42624);
    EXPECT_EQ(Word({0x80, 0xA6}, Endian::BIG).value(), 32934);

    // Test full word
    EXPECT_EQ(Word({0X52, 0X42, 0x80, 0xA6}, Endian::LITTLE).value(), 2793423442);
    EXPECT_EQ(Word({0X52, 0X42, 0x80, 0xA6}, Endian::BIG).value(), 1380090022);

    std::cout << "PASSED!" << std::endl;
}