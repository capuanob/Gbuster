//
// Created by bailey on 5/26/20.
//
#include "numberSystem.h"

auto NumberSystem::toBase(ull value, std::array<unsigned char, Constants::MAX_PASSWORD_LEN>& result) noexcept -> unsigned int {
    unsigned int i = 0;
    const auto& chars = CharacterSet::getChars();

    while (value > base) {
        --value;
        int remainder = static_cast<int>(value % base);
        value -= remainder;
        result.at(i++) = chars.at(remainder + 1);
        value /= base;
    }

    result.at(i++) = chars.at(value);
    return i;
}
