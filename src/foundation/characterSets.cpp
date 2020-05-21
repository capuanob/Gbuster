//
// Created by bailey on 5/20/20.
//

#include "characterSets.h"

CharacterSet::CharacterSet(bool incLower, bool incUpper, bool incNum, bool incSymb) {
    loOffset = hiOffset = numOffset = symbOffset = -1;
    char_set = getCharacterSet(incLower, incUpper, incNum, incSymb); // Sets up offsets as well
}

std::vector<char> CharacterSet::getCharacterSet(bool incLower, bool incUpper, bool incNum, bool incSymb) {
    std::vector<char> combinationVector;
    combinationVector.reserve(lowercase_alph.size() + uppercase_alph.size() + numbers.size() + symbols.size());

    if (incLower) {
        loOffset = combinationVector.size();
        combinationVector.insert(combinationVector.end(), lowercase_alph.begin(), lowercase_alph.end());
    }
    if (incUpper) {
        hiOffset = combinationVector.size();
        combinationVector.insert(combinationVector.end(), uppercase_alph.begin(), uppercase_alph.end());
    }
    if (incNum) {
        numOffset = combinationVector.size();
        combinationVector.insert(combinationVector.end(), numbers.begin(), numbers.end());
    }
    if (incSymb) {
        symbOffset = combinationVector.size();
        combinationVector.insert(combinationVector.end(), symbols.begin(), symbols.end());
    }

    combinationVector.resize(combinationVector.size());
    return combinationVector;
}
