//
// Created by bailey on 5/20/20.
//

#include <algorithm>
#include "cpustring.h"

hash::string::string(unsigned long len) {
    if (!isInitialized)
        throw std::logic_error("hash::string::Reset must be called before construction");
    m_len = len;
    m_str.resize(m_len, '\0');
}

hash::string::string(const std::string& value, unsigned long len) {
    if (!isInitialized)
        throw std::logic_error("hash::string::Reset must be called before construction");
    m_len = len;
    m_str.resize(m_len, '\0');

    // Copy contents of char array into vector
    for (int i = 0; i < value.length(); ++i)
        m_str[i] = value[i];
}

const hash::string& hash::string::operator++() {
    // Value is stored in little-endian for faster use of default ==

    for (auto& chr : m_str) {
        if (chr == characterSet.char_set.back()) { // At maximum value
            chr = characterSet.char_set.front(); // Reset "bit"
        } else {
            if (chr == '\0') // New "bit"
                chr = characterSet.char_set.front();
            else
                chr = characterSet.char_set[getIndex(chr) + 1]; // Get next character from character set (safe as not last elem)
            break; // Incrementing done
        }
    }

    return *this;
}

unsigned long hash::string::getIndex(char c) {
    if ('a' <= c && c <= 'z')
        return characterSet.loOffset + (c - 'a');
    else if ('A' <= c && c <= 'Z')
        return characterSet.hiOffset + (c -'A');
    else if ('0' <= c && c <= '9')
        return characterSet.numOffset + (c - '0');
    else {
        return std::find(characterSet.char_set.begin() + characterSet.symbOffset, characterSet.char_set.end(), c)
               - characterSet.char_set.begin();
    }
}

hash::string::string(const hash::string &other) {
    m_len = other.m_len;
    m_str = other.m_str;
}

hash::string::operator std::string() {
    std::string s;
    s.reserve(m_len);
    std::vector<char>::iterator it;

    for (it = m_str.begin(); it != m_str.end() && *it != '\0'; ++it)
        s += *it;

    return s;
}

