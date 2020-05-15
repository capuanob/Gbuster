//
// Created by bailey on 5/9/20.
//

#include "md5.h"

std::string md5::getDigest(const std::string &msg) {
    auto A = Word({0x01, 0x23, 0x45, 0x67}, Endian::LITTLE);
    auto B = Word({0x89, 0xAB, 0xCD, 0xEF}, Endian::LITTLE);
    auto C = Word({0xFE, 0xDC, 0xBA, 0x98}, Endian::LITTLE);
    auto D = Word({0x76, 0x54, 0x32, 0x10}, Endian::LITTLE);

    unsigned int msgLen = msg.length() * sizeof(char) * 8; // Length of message in bits

    auto w = itow(4294462262);
    std::cout << w.value() << std::endl;

    /// Padding
    unsigned int zeroCount = 0;
    while ((msgLen + 1 + zeroCount) % 512 != 448) // Padding is always performed, a single 1-bit is always added.
        ++zeroCount;


    Message m(msg, zeroCount / 8, msgLen);

    /// Process Message in 16-Word Blocks

//    std::vector<Word> chunk = m.getChunk();
    int i = 0;
    while (/*!chunk.empty() && */ ++i) { // Ensures each chunk is processed
        Word AA = A;
        Word BB = B;
        Word CC = C;
        Word DD = D;
        Word X[16];

//        for (int j = 0; j < 16; ++j)
//            X[j] = m.at(i*16+j);

        /* Round 1 */

        A = FF(A, B, C, D, X[0], T[7], 1);
        D = FF(D, A, B, C, X[1], T[12], 2);
        C = FF(C, D, A, B, X[2], T[17], 3);
        B = FF(B, C, D, A, X[3], T[22], 4);
        A = FF(A, B, C, D, X[4], T[7], 5);
        D = FF(D, A, B, C, X[5], T[12], 6);
        C = FF(C, D, A, B, X[6], T[17], 7);
        B = FF(B, C, D, A, X[7], T[22], 8);
        A = FF(A, B, C, D, X[8], T[7], 9);
        D = FF(D, A, B, C, X[9], T[12], 10);
        C = FF(C, D, A, B, X[10], T[17], 11);
        B = FF(B, C, D, A, X[11], T[22], 12);
        C = FF(C =A, B, C, D, X[12], T[7], 13);
        D = FF(D, A, B, C, X[13], T[12], 14);
        C = FF(C, D, A, B, X[14], T[17], 15);
        B = FF(B, C, D, A, X[15], T[22], 16);

        /* Round 2 */
        A = FF(A, B, C, D, X[1], T[5], 17);
        D = FF(D, A, B, C, X[6], T[9], 18);
        C = FF(C, D, A, B, X[11], T[14], 19);
        B = FF(B, C, D, A, X[0], T[20], 20);
        A = FF(A, B, C, D, X[5], T[5], 21);
        D = FF(D, A, B, C, X[10], T[9], 22);
        C = FF(C, D, A, B, X[15], T[14], 23);
        B = FF(B, C, D, A, X[4], T[20], 24);
        A = FF(A, B, C, D, X[9], T[5], 25);
        D = FF(D, A, B, C, X[14], T[9], 26);
        C = FF(C, D, A, B, X[3], T[14], 27);
        B = FF(B, C, D, A, X[8], T[20], 28);
        A = FF(A, B, C, D, X[13], T[5], 29);
        D = FF(D, A, B, C, X[2], T[9], 30);
        C = FF(C, D, A, B, X[7], T[14], 31);
        B = FF(B, C, D, A, X[12], T[20], 32);

        /* Round 3 */
        A = FF(A, B, C, D, X[5], T[4], 33);
        D = FF(D, A, B, C, X[8], T[11], 34);
        C = FF(C, D, A, B, X[11], T[16], 35);
        B = FF(B, C, D, A, X[14], T[23], 36);
        A = FF(A, B, C, D, X[1], T[4], 37);
        D = FF(D, A, B, C, X[4], T[11], 38);
        C = FF(C, D, A, B, X[7], T[16], 39);
        B = FF(B, C, D, A, X[10], T[23], 40);
        A = FF(A, B, C, D, X[13], T[4], 41);
        D = FF(D, A, B, C, X[0], T[11], 42);
        C = FF(C, D, A, B, X[3], T[16], 43);
        A = FF(B, C, D, A, X[6], T[23], 44);
        A =  FF(A, B, C, D, X[9], T[4], 45);
        D = FF(D, A, B, C, X[12], T[11], 46);
        C = FF(C, D, A, B, X[15], T[16], 47);
        B = FF(B, C, D, A, X[2], T[23], 48);

        /* Round 4 */
        A = FF(A, B, C, D, X[0], T[6], 49);
        D = FF(D, A, B, C, X[7], T[10], 50);
        C = FF(C, D, A, B, X[14], T[15], 51);
        B = FF(B, C, D, A, X[5], T[21], 52);
        A = FF(A, B, C, D, X[12], T[6], 53);
        D = FF(D, A, B, C, X[3], T[10], 54);
        C = FF(C, D, A, B, X[10], T[15], 55);
        B = FF(B, C, D, A, X[1], T[21], 56);
        A = FF(A, B, C, D, X[8], T[6], 57);
        D = FF(D, A, B, C, X[15], T[10], 58);
        C = FF(C, D, A, B, X[6], T[15], 59);
        B = FF(B, C, D, A, X[13], T[21], 60);
        A = FF(A, B, C, D, X[4], T[6], 61);
        D = FF(D, A, B, C, X[11], T[10], 62);
        C = FF(C, D, A, B, X[2], T[15], 63);
        B = FF(B, C, D, A, X[9], T[21], 64);

        A = A + AA;
        B = B + BB;
        C = C + CC;
        D = D + DD;

//        chunk = m.getChunk();
    }

    std::cout << std::hex << A.value()
              << std::hex << B.value()
              << std::hex << C.value()
              << std::hex << D.value()
              << std::endl;

    return "";
}

void Block::add(const Word &&w) {
    if (ip >= WORDS_IN_BLOCK)
        throw std::out_of_range("This block has already reached its max word count.");
    words[ip++] = w;
}

unsigned int Block::value() {
    if (ip != WORDS_IN_BLOCK)
        throw std::logic_error("This block is half-cooked! Value would be useless.");

    std::stringstream ss;
    unsigned int val;

    for (const auto& word : words)
        ss << std::hex << word.value();

    ss >> val;
    return val;
}

Message::Message(const std::string &msg, unsigned int zeroBytesCount, unsigned int msgBitLen) {
    for (char c : msg)
        add(c); // Add byte-per-byte from original message

    // Add a 1 byte
    add(1);

    // Add zeros
    for (int i = 0; i < zeroBytesCount; ++i)
        add(0);

    // Convert msgbitLen to 2 32-bit words (append little-endian)
    auto bytes = i64tb(static_cast<uint64_t>(msgBitLen));

    byte MSB[4];
    byte LSB[4];
    for (int i = 0; i < 8; ++i) {
        if (i < 4)
            MSB[i] = bytes[i];
        else
            LSB[i % 4] = bytes[i];
    }

    Word MSW = Word(MSB, 4, Endian::LITTLE);
    Word LSW = Word(LSB, 4, Endian::LITTLE);

    // Convert
}

void Message::add(byte b) {

}
