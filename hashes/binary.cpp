//
// Created by bailey on 5/9/20.
//

#include "binary.h"

uint8_t bin::htoi(const std::string& hex) {
    unsigned int x;
    std::stringstream ss;
    ss << std::hex << hex;
    ss >> x;
    return static_cast<uint8_t>(x);
}

bin::Byte::Byte(uint8_t value) : value(value) {}


bin::Byte::Byte(const std::string& hexValue) : value(htoi(hexValue)) {}

void bin::Word::append(const bin::Byte &b) {
    if (ip >= bytes + BYTES_IN_WORD)
        throw std::out_of_range("This word is already completely filled.");
    *ip++ = b;
}

bin::Word::Word(const Byte* pBytes, int byteCount, bool usesLittleEndian) : isLittleEndian(usesLittleEndian) {
    int startIndex = BYTES_IN_WORD - byteCount; // Account for leading zeros.
    Byte temp[4];
    std::copy(pBytes, pBytes + byteCount, temp);

    if (usesLittleEndian)
        std::reverse(temp, temp + BYTES_IN_WORD);

    for (int i = startIndex; i < BYTES_IN_WORD && i < byteCount + startIndex; ++i, ++ip)
        bytes[i] = temp[i];
}


bin::Word::Word(std::initializer_list<Byte> lBytes, bool usesLittleEndian) : isLittleEndian(usesLittleEndian) {
    int byteCount = static_cast<int>(lBytes.size());
    int startIndex = BYTES_IN_WORD - byteCount; // Account for leading zeros.

    if (usesLittleEndian)
        for (int i = byteCount; i < BYTES_IN_WORD && i >= startIndex; --i, ++ip)
            bytes[3 - i + startIndex] = lBytes.begin()[i];
    else
        for (int i = startIndex; i < BYTES_IN_WORD && i < byteCount + startIndex; ++i, ++ip)
            bytes[i] = lBytes.begin()[i];
}

bin::Word bin::Word::operator|(const bin::Word &other) const {
    bool canCompute = isLittleEndian == other.isLittleEndian;
    if (!canCompute)
        throw std::logic_error("Words must be of same endianness and size");

    Word w(isLittleEndian); // Currently empty, but endianness is properly setup.

    for (int i = 0; i < BYTES_IN_WORD; i++)
        w.append(bytes[i] ^ other[i]);

    return w;
}

bin::Word bin::Word::operator~() const{
    Word w(bytes, size(), isLittleEndian);
    for (auto& byte : w.bytes)
        byte = ~byte;
    return w;
}

bin::Word bin::Word::operator&(const bin::Word &other) const{
    bool canCompute = isLittleEndian == other.isLittleEndian;
    if (!canCompute)
        throw std::logic_error("Words must be of same endianness and size");

    Word w(isLittleEndian);

    for (int i = 0; i < BYTES_IN_WORD; i++)
        w.append(bytes[i] & other[i]);

    return w;
}

bin::Word bin::Word::operator^(const bin::Word &other) const {
    bool canCompute = isLittleEndian == other.isLittleEndian;
    if (!canCompute)
        throw std::logic_error("Words must be of same endianness and size");

    Word w(isLittleEndian);

    for (int i = 0; i < BYTES_IN_WORD; i++)
        w.append(bytes[i] ^ other[i]);

    return w;
}

inline std::size_t bin::Word::size() const {
    return bytes - ip;
}

bin::Word::Word(bool usesLittleEndian) {
    this->isLittleEndian = usesLittleEndian;
}

