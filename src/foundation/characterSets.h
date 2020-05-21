//
// Created by bailey on 5/19/20.
//

#ifndef GBUSTER_CHARACTERSETS_H
#define GBUSTER_CHARACTERSETS_H

#endif //GBUSTER_CHARACTERSETS_H
#include <vector>


class CharacterSet {
    public:
        std::vector<char> char_set; // Ordered container of characters used in this instantiation

        // The following are -1 if not present
        int loOffset; // Starting index of lowercase letters
        int hiOffset; // Starting index of uppercase letters
        int numOffset; // Starting index of numbers
        int symbOffset; // Starting index of symbols

        CharacterSet(bool incLower, bool incUpper, bool incNum, bool incSymb); // Default constructor
private:
        /**
         * Given the character sets to include, this function combines the respective lists
         * @param incLower Whether to include lowercase_alph
         * @param incUpper Whether to include uppercase_alph
         * @param incNum  Whether to include numbers
         * @param incSymb Whether to include symbols
         * @return a combined vector
         */
        std::vector<char> getCharacterSet(bool incLower, bool incUpper, bool incNum, bool incSymb);

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

