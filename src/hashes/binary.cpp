//
// Created by bailey on 5/9/20.
//

#include "binary.h"

uint8_t bin::U8 = 8;
uint8_t bin::U16 = 16;
uint8_t bin::U24 = 24;
uint8_t bin::U32 = 32;

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

std::vector<bin::Word> bin::i64Tw(uint64_t src) {
    std::vector<byte> bytes;
    std::vector<Word> words;

    for (unsigned int i = 0; i < 8; ++i)
        bytes.push_back( (src >> (i * U8)) & static_cast<unsigned int>(0xFF));

    words.emplace_back(Word({bytes[0], bytes[1], bytes[2], bytes[3]}));
    words.emplace_back(Word({bytes[4], bytes[5], bytes[6], bytes[7]}));

    return words;
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
        w.append(bytes[i] | other[i]);

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
    return itow(value() + other.value());
}

uint32_t bin::Word::value() const {
    return btoi(bytes);
}


void bin::Word::ensureLittleEndian(Endian type) {
    bool needsConversion = (type == Endian::System && !systemIsLittleEndian()) || (type == Endian::Big);

    if (needsConversion)
        std::reverse(bytes, bytes + BYTES_IN_WORD);
}


void bin::Word::add(byte b) {
    if (systemIsLittleEndian())
        bytes[ip++] = b;
    else {
        ++ip;
        bytes[BYTES_IN_WORD - ip] = b;
    }
}