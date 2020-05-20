//
// Created by bailey on 5/9/20.
//

#ifndef GBUSTER_MD5_H
#define GBUSTER_MD5_H

#include <string>
#include <iostream>
#include <iomanip>
#include "binary.h"

using namespace bin;

constexpr int WORDS_IN_BLOCK = 16;

constexpr unsigned int T[] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be ,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

constexpr unsigned int S[] = {
        7, 12, 17, 22, 7, 12, 17, 22,
        7, 12, 17, 22, 7, 12, 17, 22,
        5, 9, 14, 20, 5, 9, 14, 20,
        5, 9, 14, 20, 5, 9, 14, 20,
        4, 11, 16, 23, 4, 11, 16, 23,
        4, 11, 16, 23, 4, 11, 16, 23,
        6, 10, 15, 21, 6, 10, 15, 21,
        6, 10, 15, 21, 6, 10, 15, 21
};

// Four MD5 auxiliary functions
inline Word F(Word X, Word Y, Word Z) { return (X & Y) | (~(X) & Z); } // Conditional
inline Word G(Word X, Word Y, Word Z) { return (X & Z) | (Y & ~Z); }
inline Word H(Word X, Word Y, Word Z) { return X ^ Y ^ Z; }
inline Word I(Word X, Word Y, Word Z) { return Y ^ (X | ~Z); }

inline Word LEFT_ROTATE(const Word wrd, unsigned int amt) {
    return itow((wrd.value() << amt) | (wrd.value() >> (U32 - amt)));
}

inline Word FF(const Word& a, const Word& b, const Word& c,
        const Word& d, const Word& blk, unsigned int shiftAmt, unsigned int tableVal) {
    return b + LEFT_ROTATE(a + F(b,c,d) + blk + itow(tableVal), shiftAmt);
}

inline Word GG(const Word& a, const Word& b, const Word&c,
        const Word& d, const Word& blk, unsigned int shiftAmt, unsigned int tableVal) {
    return b + LEFT_ROTATE(a + G(b,c,d) + blk + itow(tableVal), shiftAmt);
}

inline Word HH(const Word& a, const Word& b, const Word&c,
               const Word& d, const Word& blk, unsigned int shiftAmt, unsigned int tableVal) {
    return b + LEFT_ROTATE(a + H(b,c,d) + blk + itow(tableVal), shiftAmt);
}

inline Word II(const Word& a, const Word& b, const Word&c,
               const Word& d, const Word& blk, unsigned int shiftAmt, unsigned int tableVal) {
    return b + LEFT_ROTATE(a + I(b,c,d) + blk + itow(tableVal), shiftAmt);
}

/*
 * Internal representation of a byte-stream message to be hashed.
 * Comes with helper functions for QoL abstraction
 */
class Message;

/*
 * Solution suite providing MD5 functionality
 */
class md5 {
public:
    // Four-word buffer used to compute the message digest.

    static std::string getDigest(const std::string &msg);
};

/*
 * Abstracted collection for storing 16 words
 */
class Block {
public:
    void add(byte b); // Adds a byte to the most recent block's word.
    void add(const Word& w); // Appends a word
    [[nodiscard]] constexpr inline Word at(int idx) const { return words[idx]; }
    [[nodiscard]] constexpr inline bool isFull() const { return (ip > WORDS_IN_BLOCK) ||
        (ip == WORDS_IN_BLOCK && words[ip - 1].isFull()); } // True if the block cannot store any more bytes

    Block(); // Default constructor, zeros properties out

    Word& back(); // Returns the last added word in the block
private:
    Word words[16]; // Holds words of a block
    int ip = 1; // Point for inserting next word
};

/*
 * Abstracted collection for storing and processing input to MD5 algorithm.
 */
class Message {
public:
    Message(const std::string& msg, unsigned int zeroBytesCount, unsigned int msgBitLen);
    void add(byte b); // Adds a byte to the most recent message's block
    void add(const Word& w); // Adds a word to the most recent message's block
    [[nodiscard]] inline bool empty() const { return chunks.empty(); }
    Block popBlock(); // Removes and returns the next block
private:
    std::vector<Block> chunks;
};

#endif //GBUSTER_MD5_H
