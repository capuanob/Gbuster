//
// Created by bailey on 5/9/20.
//

#ifndef GBUSTER_BINARY_H
#define GBUSTER_BINARY_H
static const unsigned int BYTES_IN_WORD = 4;

#include <cstdint>
#include <string>
#include <sstream>
#include <vector>
#include <cstring> // memset
#include <cmath> // pow

using byte = uint8_t;

enum class Endian {
    SYSTEM, BIG, LITTLE
};

namespace bin {

    // Unsigned integers for bitwise operations, makes linter happy :)
    extern uint8_t U8;
    extern uint8_t U16;
    extern uint8_t U24;
    extern uint8_t U32;

    /*
     * Internal representation of a word (aka 4 bytes), with useful helper functions and overrides
     * Stored and operated on in little-endian
     */
    class Word;

    // ALL HELPER FUNCTIONS ASSUME LITTLE-ENDIAN ORDERING
    Word itow(uint32_t val); // Converts a 32-bit integer value to a little-endian Word
    uint32_t btoi(const byte* bytes); // Converts a little-endian array of bytes (4) to a 32-bit big-endian int
    std::vector<Word> i64tw(uint64_t src); // Splits a 64-bit integer into a host-endian vector of 8 bytes.

    bool systemIsLittleEndian(); // Determines whether or not the host CPU is big or little endian.

    class Word {
    public:
        [[nodiscard]] uint32_t value() const; // Returns 32-bit little-endian value

        [[nodiscard]] constexpr inline bool isFull() const { return ip >= BYTES_IN_WORD; } // True if the word cannot store any additional bytes
        void add(byte b); // Inserts a byte in little-endian order.

        Word(const byte* lBytes, int byteCount, Endian type = Endian::SYSTEM); // Array-based constructor
        Word(std::initializer_list<byte> lBytes, Endian type = Endian::SYSTEM); // Initializer list constructor
        Word() = default; // Default constructor

        Word operator+(const Word& other) const;
        Word operator|(const Word& other) const;
        Word operator~() const;
        Word operator&(const Word& other) const;
        Word operator^(const Word& other) const;
        inline const byte& operator[](std::size_t idx) const { return bytes[idx]; }

        byte bytes[4] = {0, 0, 0, 0}; // Holds byte values
    private:
        int ip = 0; // Point to insert next byte into bytes array.

        void append(byte b); // Adds a byte to the bytes array (if not already full)
        void ensureLittleEndian(Endian type); // Converts a newly constructed Word to little endian, if type so requires
    };
}

#endif //GBUSTER_BINARY_H
