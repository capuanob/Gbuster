//
// Created by bailey on 5/9/20.
//

#ifndef GBUSTER_MD5_H
#define GBUSTER_MD5_H

#include <string>
#include <vector>
#include <iostream>
#include <list>
#include "binary.h"

using namespace bin;

// Four-word buffer used to compute the message digest. Little-endian, hex values given
static const Word A({Byte("01"), Byte("23"), Byte("45"), Byte("67")});
static const Word B({Byte("89"), Byte("ab"), Byte("cd"), Byte("ef")});
static const Word C({Byte("fe"), Byte("dc"), Byte("ba"), Byte("98")});
static const Word D({Byte("76"), Byte("54"), Byte("32"), Byte("10")});

// Four auxiliary functions
inline Word F(Word X, Word Y, Word Z) { return (X & Y) | (~X & Z); } // Conditional
inline Word G(Word X, Word Y, Word Z) { return (X & Z) | (Y & ~Z); }
inline Word H(Word X, Word Y, Word Z) { return X ^ Y ^ Z; }
inline Word I(Word X, Word Y, Word Z) { return Y ^ (X | ~Z); }

const unsigned int T[] = {
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

std::vector<Byte> split64(uint64_t src);

class Message;
class md5;

/**
 * Assumptions
 * A "word" is a 32-bit quantity
 * A "byte" is an eight-bit quantity
 * Bytes are stored in LITTLE-ENDIAN
 */
class md5 {

public:
    static std::string getDigest(const std::string& msg);

    static Message paddedToBytes(const std::string &basicString, unsigned int count, unsigned int origLen);
};

class Message {
public:
    void add(const Byte& byte);
    void add(const std::vector<Byte>& bytes);
    template <typename ...T>
    void emplace(T&& ...args);

    Message() = default;
    void printDebug();
private:
    std::list<Byte> bytes;
};

#endif //GBUSTER_MD5_H
