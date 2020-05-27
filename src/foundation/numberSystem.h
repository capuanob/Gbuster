//
// Created by bailey on 5/23/20.
//

#ifndef GBUSTER_NUMBERSYSTEM_H
#define GBUSTER_NUMBERSYSTEM_H

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
    inline static int getBase() noexcept { return base; }
private:
    inline static int base{};

};


#endif //GBUSTER_NUMBERSYSTEM_H
