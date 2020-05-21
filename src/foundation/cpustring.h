//
// Created by bailey on 5/20/20.
//

#ifndef GBUSTER_CPUSTRING_H
#define GBUSTER_CPUSTRING_H

#include <vector>
#include <stdexcept>
#include <string>
#include "characterSets.h"

namespace hash {

    /*
     * Abstraction over c-style string for STL-free compatibiltiy with CPU and GPU hashing
     */
    class string {
    public:

        // Operator overrides
        const string &operator++();
        inline bool operator==(const string &rhs) const {
            return this->m_str == rhs.m_str; // Length-equivalence is handled by vector's implementation of equality op
        }
        inline bool operator!=(const string &rhs) const { return !(*this == rhs); }
        explicit operator std::string();

        // Copy / Delete / Create constructors
        string() = default;
        string(const string& other); // Copy constructor
        explicit string(unsigned long len) noexcept(false); // Initializer for an empty string
        explicit string(const std::string& value, unsigned long len) noexcept(false); // Value initializer

        /**
         * MUST be called before use of string class
         * @param characters Set of characters to be used in creation of strings
         */
        inline static void Prepare(const CharacterSet& characters) {
            characterSet = characters;
            isInitialized = true;
        }

        /**
         * Empties out the static character set property of strings for the next usage
         */
        inline static void Reset() {
            characterSet.char_set.clear();
            isInitialized = false;
        }

        /**
         * Returns the characterSet index of a character in a hash::string
         * @param c Character from a hash::string to search for
         * @return an unsigned long index
         */
        static unsigned long getIndex(char c);

    private:
        static inline CharacterSet characterSet{false, false, false, false}; // Set of characters that all strings can contain
        static inline bool isInitialized = false; // Used for quick assurance that the string class has been prepared before using constructors

        unsigned long m_len = 0; // Maximum length of the string
        std::vector<char> m_str; // Contains string contents

    };
}

#endif //GBUSTER_CPUSTRING_H
