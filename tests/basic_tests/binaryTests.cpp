//
// Created by bailey on 5/17/20.
//

#include "gtest/gtest.h"
#include "binary.h"
#include <iostream>
using namespace bin;

TEST(binary_tests, test_word_constructor) {
    // Test edge-case constructor w/o any bytes provided
    EXPECT_EQ(Word({}, Endian::LITTLE).value(), 0);
    EXPECT_EQ(Word({}, Endian::BIG).value(), 0);

    // Test partial word (ensure 0s are correctly handled)
    EXPECT_EQ(Word({0x80, 0xA6}, Endian::LITTLE).value(), 42624);
    EXPECT_EQ(Word({0x80, 0xA6}, Endian::BIG).value(), 32934);

    // Test full word
    EXPECT_EQ(Word({0X52, 0X42, 0x80, 0xA6}, Endian::LITTLE).value(), 2793423442);
    EXPECT_EQ(Word({0X52, 0X42, 0x80, 0xA6}, Endian::BIG).value(), 1380090022);
}

TEST(binary_tests, test_itow_eq) {
    // Test for max 32-bit unsigned integer
    EXPECT_EQ(itow(4294967295).value(), 4294967295);
    EXPECT_EQ(itow(0).value(), 0);
    EXPECT_EQ(itow(-1).value(), 4294967295); // Test underflow
    EXPECT_EQ(itow(4294967296).value(), 0); // Test overflow
    EXPECT_EQ(itow(50403103).value(), 50403103);
}

TEST(binary_tests, test_btoi_eq) {
    byte test[4] = { 0x42, 0x41, 0x40, 0x29 };
    EXPECT_EQ(btoi(test), 692076866);
}

TEST(binary_tests, test_i64tw_eq) {
    auto words1 = i64tw(0);
    EXPECT_EQ(words1[0].value(), 0);
    EXPECT_EQ(words1[1].value(), 0);

    auto words2 = i64tw(12884952290);
    EXPECT_EQ(words2[0].value(), 50402);
    EXPECT_EQ(words2[1].value(), 3);
}