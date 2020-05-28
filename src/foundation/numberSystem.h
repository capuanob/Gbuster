//
// Created by bailey on 5/28/20.
//

#ifndef PRACTICECPP20_NUMBERSYSTEM_H
#define PRACTICECPP20_NUMBERSYSTEM_H

#include <string>
#include <array>
#include <cmath>
#include "constants.h"
#include "characterSets.h"

using ull = unsigned long long;

class NumberSystem {
public:
    /*
     * From decimal to string
     */
    static auto toBase(ull value, std::array<unsigned char, Constants::MAX_PASSWORD_LEN> &result) noexcept -> unsigned int;

    inline constexpr static void setBase(int b) noexcept { base = b; }
    inline static auto getBase() noexcept -> int { return base; }
private:
    inline static int base{};

};


#endif //PRACTICECPP20_NUMBERSYSTEM_H
