//
// Created by bailey on 5/23/20.
//

#ifndef GBUSTER_CONSTANTS_H
#define GBUSTER_CONSTANTS_H

enum class HashType {
    MD5 = 0,
    SHA1
};

class Constants {
public:
    static constexpr const int ALPHA_COUNT = 26;
    static constexpr const int NUM_COUNT = 10;
    static constexpr const int SYMBOL_COUNT = 33;
    static constexpr const int MAX_CHARS = (ALPHA_COUNT * 2) + NUM_COUNT + SYMBOL_COUNT + 1; // Extra 1 for \0 as 0
    static constexpr const int MAX_PASSWORD_LEN = 20;
};


#endif //GBUSTER_CONSTANTS_H
