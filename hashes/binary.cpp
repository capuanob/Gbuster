//
// Created by bailey on 5/9/20.
//

#include "binary.h"

uint32_t bin::btoi(const byte* bytes) {
    return static_cast<uint32_t>(bytes[0] | (bytes[1] << U8) | (bytes[2] << U16) | (bytes[3] << U24));
}

bin::Word bin::itow(uint32_t val) {
    byte bytes[4];
    //host-endian integer -> little-endian word

    auto *valPtr = reinterpret_cast<byte*>(&val);
    bytes[0] = valPtr[0];
    bytes[1] = valPtr[1];
    bytes[2] = valPtr[2];
    bytes[3] = valPtr[3];

    return Word(bytes, 4); // Let constructor handle host-endianness.
}

std::vector<byte> bin::i64tb(uint64_t src) {
    std::vector<byte> bytes;

    for (unsigned int i = 0; i < 8; ++i)
        bytes.push_back( (src >> (i * U8)) & static_cast<unsigned int>(0xFF));

    return bytes;
}

bool bin::systemIsLittleEndian() {
    int n = 1;
    return (*(char *)&n == 1);
}

void bin::Word::append(byte b) {
    if (ip >= BYTES_IN_WORD)
        throw std::out_of_range("This word is already completely filled.");
    bytes[ip++] = b;
}

bin::Word::Word(const byte* pBytes, int byteCount, Endian type) {
    unsigned int insertionIdx = BYTES_IN_WORD - byteCount;
    std::copy(pBytes, pBytes + byteCount, bytes + insertionIdx);
    ensureLittleEndian(type);
}


bin::Word::Word(std::initializer_list<byte> lBytes, Endian type) {
    unsigned int insertionIdx = BYTES_IN_WORD - lBytes.size();
    std::copy(lBytes.begin(), lBytes.end(), bytes + insertionIdx);
    ensureLittleEndian(type);
}

bin::Word bin::Word::operator|(const bin::Word &other) const {
    Word w;

    for (int i = 0; i < BYTES_IN_WORD; i++)
        w.append(bytes[i] ^ other[i]);

    return w;
}

bin::Word bin::Word::operator~() const{
    Word w;
    for (const auto byte : bytes)
        w.append(~byte);
    return w;
}

bin::Word bin::Word::operator&(const bin::Word &other) const{
    Word w;
    for (int i = 0; i < BYTES_IN_WORD; i++)
        w.append(bytes[i] & other[i]);

    return w;
}

bin::Word bin::Word::operator^(const bin::Word &other) const {
    Word w;
    for (int i = 0; i < BYTES_IN_WORD; i++)
        w.append(bytes[i] ^ other[i]);

    return w;
}

bin::Word bin::Word::operator+(const bin::Word &other) const {
    auto moddedVal = static_cast<uint32_t>((value() + other.value()) % static_cast<int>(pow(2, 32)));
    return itow(moddedVal);
}

uint32_t bin::Word::value() const {
    return btoi(bytes);
}

void bin::Word::ensureLittleEndian(Endian type) {
    bool needsConversion = (type == Endian::SYSTEM && !systemIsLittleEndian()) || (type == Endian::BIG);

    if (needsConversion)
        std::reverse(bytes, bytes + BYTES_IN_WORD);
}
