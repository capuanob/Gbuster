//
// Created by bailey on 5/20/20.
//

#include "characterSets.h"

void CharacterSet::buildCharacterSet(bool lo, bool up, bool num, bool symbol) noexcept {
    // Copy in desired character-sets and increment insertion index to ensure ordered insert(char...char_n\0\0\0)
    std::size_t insertionIdx = 1;

    if (lo) {
        std::copy(loAlpha.begin(), loAlpha.end(), combinedSet.begin() + insertionIdx);
        insertionIdx += Constants::ALPHA_COUNT;
    }
    if (up) {
        std::copy(upAlpha.begin(), upAlpha.end(), combinedSet.begin() + insertionIdx);
        insertionIdx += Constants::ALPHA_COUNT;
    }
    if (num) {
        std::copy(numbers.begin(), numbers.end(), combinedSet.begin() + insertionIdx);
        insertionIdx += Constants::NUM_COUNT;
    }
    if (symbol) {
        std::copy(symbols.begin(), symbols.end(), combinedSet.begin() + insertionIdx);
        insertionIdx += Constants::SYMBOL_COUNT;
    }

    for (; insertionIdx != Constants::MAX_CHARS; ++insertionIdx) {
        combinedSet.at(insertionIdx) = '\0';
    }
}

