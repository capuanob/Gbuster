//
// Created by bailey on 5/19/20.
//

#ifndef GBUSTER_CHARACTERSETS_H
#define GBUSTER_CHARACTERSETS_H

#endif //GBUSTER_CHARACTERSETS_H
#include <vector>


class CharacterSets {
    public:

        /**
         * Given the character sets to include, this function combines the respective lists
         * @param incLower Whether to include lowercase_alph
         * @param incUpper Whether to include uppercase_alph
         * @param incNum  Whether to include numbers
         * @param incSymb Whether to include symbols
         * @return a combined vector
         */
        static inline std::vector<char> getCharacterSet(bool incLower, bool incUpper, bool incNum, bool incSymb) {
            std::vector<char> combinationVector;
            combinationVector.reserve(lowercase_alph.size() + uppercase_alph.size() + numbers.size() + symbols.size());

            if (incLower)
                combinationVector.insert(combinationVector.end(), lowercase_alph.begin(), lowercase_alph.end());
            if (incUpper)
                combinationVector.insert(combinationVector.end(), uppercase_alph.begin(), uppercase_alph.end());
            if (incNum) combinationVector.insert(combinationVector.end(), numbers.begin(), numbers.end());
            if (incSymb) combinationVector.insert(combinationVector.end(), symbols.begin(), symbols.end());

            combinationVector.resize(combinationVector.size());
            return combinationVector;
        }

    private:
        static inline const std::vector<char> lowercase_alph = {
                'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
        };

        static inline const std::vector<char> uppercase_alph = {
                'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
        };

        static inline const std::vector<char> numbers = {
                '0', '1', '2', '3', '4',
                '5', '6', '7', '8', '9'
        };

        static inline const std::vector<char> symbols = {
                ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', ':',
                ';', '<', '=', '>', '?', '@', '[', '\\', ']', '^', '_', '`', '{', '|', '}', '~'
        };
    };


