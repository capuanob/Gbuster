//
// Created by bailey on 5/19/20.
//

#ifndef GBUSTER_CHARACTERSETS_H
#define GBUSTER_CHARACTERSETS_H

#endif //GBUSTER_CHARACTERSETS_H
#include <vector>
#include <array>
#include <algorithm>
#include "constants.h"

class CharacterSet {
private:
    static inline std::array<char, Constants::MAX_CHARS> combinedSet{'\0'};

    static inline constexpr const std::array<char, Constants::ALPHA_COUNT> loAlpha {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o' , 'p' , 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
    };

    static inline constexpr const std::array<char, Constants::ALPHA_COUNT> upAlpha {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };

    static inline constexpr const std::array<char, Constants::NUM_COUNT> numbers {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
    };

    static inline constexpr const std::array<char, Constants::SYMBOL_COUNT> symbols {
        ' ', '"', '!', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', ':',
        ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', '`', '{', '|', '}', '~'
    };
public:
    static void buildCharacterSet(bool lo, bool up, bool num, bool symbol) noexcept;
    static inline constexpr auto getChars() noexcept -> const std::array<char, Constants::MAX_CHARS>& { return combinedSet; }
};

