//
// Created by bailey on 5/9/20.
//

#include "md5.h"

std::string md5::getDigest(const std::string &msg) {
    unsigned int msgLen = msg.length() * sizeof(char) * 8; // Length of message in bits
    msgLen += 1; // Padding is always performed, a single 1-bit is always added.

    // Padding
    unsigned int zeroCount = 0;
    while (msgLen + zeroCount % 512 != 448)
        ++zeroCount;

    // Create a vector of bytes
    std::vector<Byte> msgBytes = paddedToBytes(msg, zeroCount);



}

std::vector<Byte> md5::paddedToBytes(const std::string &msg, unsigned int zeroCount) {
    std::vector<Byte> bytes;

    // Add message, each character is a byte.
    for (auto& chr : msg)
        bytes.emplace_back(static_cast<uint8_t>(chr));


    // Convert to little-endian

    /** TODO
     *  Thoughts
     *      How should bytes be held? Should it be abstracted into a collection thanks to endianness?
     *      How to handle that 1-bit? How does endianness work here?
     */
}

