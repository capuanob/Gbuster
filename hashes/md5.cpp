//
// Created by bailey on 5/9/20.
//

#include "md5.h"
std::vector<Byte> split64(uint64_t src) {
    //FIXME: This doesn't work yet.
    uint8_t uBytes[8];
    std::vector<Byte> bytes;

    std::memcpy(uBytes, &src, sizeof src); // Split uint64_t into uint8_t(s)

    for (int i = 7; i >= 0; --i)
        bytes.emplace_back(uBytes[i]);

    return bytes;
}

std::string md5::getDigest(const std::string &msg) {
    unsigned int msgLen = msg.length() * sizeof(char) * 8; // Length of message in bits

    // Padding
    unsigned int zeroCount = 0;
    while ((msgLen + 1 + zeroCount) % 512 != 448) // Padding is always performed, a single 1-bit is always added.
        ++zeroCount;

    Message m = paddedToBytes(msg, zeroCount / 8, msgLen); // Specifies how many bytes to add

    m.printDebug();
    return "";
}

Message md5::paddedToBytes(const std::string &msg, unsigned int zeroCount, unsigned int origLen) {

    Message m;

    // Add message, each character is a byte.
    for (auto& chr : msg)
        m.emplace(static_cast<uint8_t>(chr));

    m.emplace(1); // Add 00000001

    for (int i = 0; i < zeroCount; ++i)
        m.emplace(0); // Add specified amount of zeros (until len mod 552 = 448)

    // Append 8 bytes of length
    // TODO: Unlikely, but if greater than 2^64, store low_order 64-bit
    std::vector<Byte> lenBytes = split64(static_cast<uint64_t>(origLen));
    m.add(lenBytes);

    return m;
}

void Message::add(const Byte &byte) {
    bytes.push_front(byte);
}

template<typename ...T>
void Message::emplace(T&& ...args) {
    bytes.emplace_front(std::forward<T>(args)...);
}

void Message::printDebug() {
    std::cout << "Length (in bits): " << bytes.size() * 8 << std::endl;
    for (auto& b : bytes)
        std::cout << static_cast<int>(b.value) << " ";
    std::cout << std::endl;
}

void Message::add(const std::vector<Byte>& byteVec) {
    for (const auto& b : byteVec)
        add(b);
}

