//
// Created by bailey on 5/26/20.
//
#include "numberSystem.h"

unsigned int NumberSystem::toBase(ull value, std::array<unsigned char, Constants::MAX_PASSWORD_LEN>& result) noexcept {
    unsigned int i = 0;
    const auto& chars = CharacterSet::getChars();
    const auto& front = chars[1];
    do {
        int remainder = static_cast<int>(value % base);
        result.at(i++) = (remainder == 0) ? front : chars.at(remainder);
        value /= base;
    } while (value > 0);

    return i;
}
