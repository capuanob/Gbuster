//
// Created by bailey on 5/20/20.
//

#ifndef GBUSTER_CPUSTRING_H
#define GBUSTER_CPUSTRING_H

#include <vector>
#include <unordered_map>
#include <stdexcept>

namespace hash {

    /*
     * Abstraction over c-style string for STL-free compatibiltiy with CPU and GPU hashing
     */
    class string {
    public:
        const string &operator++();
        inline bool operator==(const string &rhs) const {
            return this->m_str == rhs.m_str; // Length-equivalence is handled by vector's implementation of equality op
        }
        inline bool operator!=(const string &rhs) const { return !(*this == rhs); }

        string(unsigned long len) noexcept(false); // Initializer for an empty string
        string(const char* value, unsigned long len) noexcept(false); // Value initializer

        /**
         * MUST be called before use of string class
         * @param characters Set of characters to be used in creation of strings
         */
        static void Prepare(std::vector<char>& characters);

        /**
         * Empties out the static character set property of strings for the next usage
         */
        inline static void Reset() {
            char_set.clear();
            char_idx.clear();
            isInitialized = false;
        }

    private:
        static std::vector<char> char_set; // Set of characters that all strings can contain
        static std::unordered_map<char, unsigned long> char_idx; // Map containing indices of all character (faster lookup)
        static inline bool isInitialized = false; // Used for quick assurance that the string class has been prepared before using constructors
        unsigned long m_len; // Maximum length of the string
        std::vector<char> m_str; // Contains string contents

    };
}

#endif //GBUSTER_CPUSTRING_H
