//
// Created by bailey on 5/9/20.
//

#ifndef GBUSTER_BINARY_H
#define GBUSTER_BINARY_H
static const int BYTES_IN_WORD = 4;

#include <cstdint>
#include <string>
#include <sstream>
#include <cstring> // memset

namespace bin {

    // Converts a hex value to its unsigned integer equivalent
    uint8_t htoi(const std::string& hex);

    struct Byte {
        uint8_t value; // Holds actual byte value (0 - 255)

        Byte() { this->value = 0; }
        explicit Byte(uint8_t value);
        explicit Byte(const std::string& hexValue);

        inline bool operator==(const Byte& other) const { return value == other.value; }
        inline Byte operator^(const Byte& other) const { return Byte(value ^ other.value); }
        inline Byte operator&(const Byte& other) const { return Byte(value & other.value); }
        inline Byte operator|(const Byte& other) const { return Byte(value | other.value); }
        inline Byte operator~() const { return Byte(~value); }
    };

    class Word {
    private:
        Byte bytes[4] = {Byte(0), Byte(0), Byte(0), Byte(0)}; // Holds byte values
        Byte* ip = bytes;
        bool isLittleEndian;
    public:
        void append(const Byte& b); // Adds a byte to the bytes array (if not already full)
        [[nodiscard]] inline std::size_t size() const;

        Word(const Byte* lBytes, int byteCount, bool usesLittleEndian = true); // Preferred constructor
        Word(std::initializer_list<Byte> lBytes, bool usesLittleEndian = true); // Initializer list constructor
        explicit Word(bool usesLittleEndian);

        Word operator|(const Word& other) const;
        Word operator~() const;
        Word operator&(const Word& other) const;
        Word operator^(const Word& other) const;
        inline const Byte& operator[](std::size_t idx) const { return bytes[idx]; }
    };
}

#endif //GBUSTER_BINARY_H
