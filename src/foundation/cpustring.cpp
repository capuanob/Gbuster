//
// Created by bailey on 5/20/20.
//

#include "cpustring.h"

hash::string::string(unsigned long len) {
    if (!isInitialized)
        throw std::logic_error("hash::string::Reset must be called before construction");
    m_len = len;
    m_str.resize(m_len, '\0');
}

hash::string::string(const char *value, unsigned long len) {
    if (!isInitialized)
        throw std::logic_error("hash::string::Reset must be called before construction");
    m_len = len;
    m_str.resize(m_len, '\0');

    // Copy contents of char array into vector
    for (int i = 0; i < len; ++i)
        m_str[i] = value[i];
}

const hash::string& hash::string::operator++() {
    // Value is stored in little-endian for faster use of default ==

    for (auto& chr : m_str) {
        if (chr == char_set.back()) { // At maximum value
            chr = char_set.front(); // Reset "bit"
        } else {
            if (chr == '\0') // New "bit"
                chr = char_set.front();
            else
                chr = char_set[char_idx[chr] + 1]; // Get next character from character set (safe as not last elem)
            break; // Incrementing done
        }
    }

    return *this;
}

void hash::string::Prepare(std::vector<char> &characters) {
    char_set = characters;
    char_idx.reserve(char_set.size());
    isInitialized = true;

    // Prepare index unordered map
    for (int i = 0; i < char_set.size(); ++i)
        char_idx.emplace(char_set[i], i);
}
