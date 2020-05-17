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

    /// Padding
    unsigned int zeroCount = 0;
    while ((msgLen + 1 + zeroCount) % 512 != 448) // Padding is always performed, a single 1-bit is always added.
        ++zeroCount;


    Message m(msg, zeroCount / 8, msgLen);

    /// Process Message in 16-Word Blocks

    while (!m.empty()) { // Ensures each chunk is processed
        auto block = m.popBlock();

        Word AA = A;
        Word BB = B;
        Word CC = C;
        Word DD = D;
        Word X[16];

        // Create a duplicate of the current block's words
        for (int j = 0; j < 16; ++j)
            X[j] = block.at(j);

        /* Round 1 */
        int rndBase = 0;

        A = FF(A, B, C, D, X[0], S[rndBase+0], T[rndBase+0]);
        D = FF(D, A, B, C, X[1], S[rndBase+1], T[rndBase+1]);
        C = FF(C, D, A, B, X[2], S[rndBase+2], T[rndBase+2]);
        B = FF(B, C, D, A, X[3], S[rndBase+3], T[rndBase+3]);
        A = FF(A, B, C, D, X[4], S[rndBase+4], T[rndBase+4]);
        D = FF(D, A, B, C, X[5], S[rndBase+5], T[rndBase+5]);
        C = FF(C, D, A, B, X[6], S[rndBase+6], T[rndBase+6]);
        B = FF(B, C, D, A, X[7], S[rndBase+7], T[rndBase+7]);
        A = FF(A, B, C, D, X[8], S[rndBase+8], T[rndBase+8]);
        D = FF(D, A, B, C, X[9], S[rndBase+9], T[rndBase+9]);
        C = FF(C, D, A, B, X[10], S[rndBase+10], T[rndBase+10]);
        B = FF(B, C, D, A, X[11], S[rndBase+11], T[rndBase+11]);
        A = FF(A, B, C, D, X[12], S[rndBase+12], T[rndBase+12]);
        D = FF(D, A, B, C, X[13], S[rndBase+13], T[rndBase+13]);
        C = FF(C, D, A, B, X[14], S[rndBase+14], T[rndBase+14]);
        B = FF(B, C, D, A, X[15], S[rndBase+15], T[rndBase+15]);

        rndBase = 16;

        /* Round 2 */
        A = GG(A, B, C, D, X[1], S[rndBase+0], T[rndBase+0]);
        D = GG(D, A, B, C, X[6], S[rndBase+1], T[rndBase+1]);
        C = GG(C, D, A, B, X[11], S[rndBase+2], T[rndBase+2]);
        B = GG(B, C, D, A, X[0], S[rndBase+3], T[rndBase+3]);
        A = GG(A, B, C, D, X[5], S[rndBase+4], T[rndBase+4]);
        D = GG(D, A, B, C, X[10], S[rndBase+5], T[rndBase+5]);
        C = GG(C, D, A, B, X[15], S[rndBase+6], T[rndBase+6]);
        B = GG(B, C, D, A, X[4], S[rndBase+7], T[rndBase+7]);
        A = GG(A, B, C, D, X[9], S[rndBase+8], T[rndBase+8]);
        D = GG(D, A, B, C, X[14], S[rndBase+9], T[rndBase+9]);
        C = GG(C, D, A, B, X[3], S[rndBase+10], T[rndBase+10]);
        B = GG(B, C, D, A, X[8], S[rndBase+11], T[rndBase+11]);
        A = GG(A, B, C, D, X[13], S[rndBase+12], T[rndBase+12]);
        D = GG(D, A, B, C, X[2], S[rndBase+13], T[rndBase+13]);
        C = GG(C, D, A, B, X[7], S[rndBase+14], T[rndBase+14]);
        B = GG(B, C, D, A, X[12], S[rndBase+15], T[rndBase+15]);

        rndBase = 32;
        /* Round 3 */
        A = HH(A, B, C, D, X[5], S[rndBase+0], T[rndBase+0]);
        D = HH(D, A, B, C, X[8], S[rndBase+1], T[rndBase+1]);
        C = HH(C, D, A, B, X[11], S[rndBase+2], T[rndBase+2]);
        B = HH(B, C, D, A, X[14], S[rndBase+3], T[rndBase+3]);
        A = HH(A, B, C, D, X[1], S[rndBase+4], T[rndBase+4]);
        D = HH(D, A, B, C, X[4], S[rndBase+5], T[rndBase+5]);
        C = HH(C, D, A, B, X[7], S[rndBase+6], T[rndBase+6]);
        B = HH(B, C, D, A, X[10], S[rndBase+7], T[rndBase+7]);
        A = HH(A, B, C, D, X[13], S[rndBase+8], T[rndBase+8]);
        D = HH(D, A, B, C, X[0], S[rndBase+9], T[rndBase+9]);
        C = HH(C, D, A, B, X[3], S[rndBase+10], T[rndBase+10]);
        B = HH(B, C, D, A, X[6], S[rndBase+11], T[rndBase+11]);
        A = HH(A, B, C, D, X[9], S[rndBase+12], T[rndBase+12]);
        D = HH(D, A, B, C, X[12], S[rndBase+13], T[rndBase+13]);
        C = HH(C, D, A, B, X[15], S[rndBase+14], T[rndBase+14]);
        B = HH(B, C, D, A, X[2], S[rndBase+15], T[rndBase+15]);

        rndBase = 48;
        /* Round 4 */
        A = II(A, B, C, D, X[0], S[rndBase+0], T[rndBase+0]);
        D = II(D, A, B, C, X[7], S[rndBase+1], T[rndBase+1]);
        C = II(C, D, A, B, X[14], S[rndBase+2], T[rndBase+2]);
        B = II(B, C, D, A, X[5], S[rndBase+3], T[rndBase+3]);
        A = II(A, B, C, D, X[12], S[rndBase+4], T[rndBase+4]);
        D = II(D, A, B, C, X[3], S[rndBase+5], T[rndBase+5]);
        C = II(C, D, A, B, X[10], S[rndBase+6], T[rndBase+6]);
        B = II(B, C, D, A, X[1], S[rndBase+7], T[rndBase+7]);
        A = II(A, B, C, D, X[8], S[rndBase+8], T[rndBase+8]);
        D = II(D, A, B, C, X[15], S[rndBase+9], T[rndBase+9]);
        C = II(C, D, A, B, X[6], S[rndBase+10], T[rndBase+10]);
        B = II(B, C, D, A, X[13], S[rndBase+11], T[rndBase+11]);
        A = II(A, B, C, D, X[4], S[rndBase+12], T[rndBase+12]);
        D = II(D, A, B, C, X[11], S[rndBase+13], T[rndBase+13]);
        C = II(C, D, A, B, X[2], S[rndBase+14], T[rndBase+14]);
        B = II(B, C, D, A, X[9], S[rndBase+15], T[rndBase+15]);

        A = A + AA;
        B = B + BB;
        C = C + CC;
        D = D + DD;
    }

    // Get output of MD5 algorithm

    std::stringstream ss;
    byte buffer[16];

    std::copy(std::begin(A.bytes), std::end(A.bytes), std::begin(buffer));
    std::copy(std::begin(B.bytes), std::end(B.bytes), std::begin(buffer) + 4);
    std::copy(std::begin(C.bytes), std::end(C.bytes), std::begin(buffer) + 8);
    std::copy(std::begin(D.bytes), std::end(D.bytes), std::begin(buffer) + 12);

    for (int i = 0; i < 16; ++i)
        ss << std::hex << std::setfill('0') << std::setw(2) << static_cast<unsigned int>(buffer[i]);

    return std::string(ss.str());
}

void Block::add(const Word& w) {
    if (ip >= WORDS_IN_BLOCK)
        throw std::out_of_range("This block has already reached its max word count.");
    words[ip++] = w;
}

unsigned int Block::value() const {
    if (ip != WORDS_IN_BLOCK)
        throw std::logic_error("This block is half-cooked! Value would be useless.");

    std::stringstream ss;
    unsigned int val;

    for (const auto& word : words)
        ss << std::hex << word.value();

    ss >> val;
    return val;
}

void Block::add(byte b) {
    if (back().isFull()) {
        Word w({});
        w.add(b);
        words[ip++] = w;
    } else
        back().add(b);
}

inline bool Block::isFull() const {
    return (ip > WORDS_IN_BLOCK) || (ip == WORDS_IN_BLOCK && words[ip - 1].isFull());
}

void Block::printDebug() {
    for (int i = 0; i < 16; ++i)
        std::cout << "\t[" << i << "] " << words[i].value() << std::endl;
    std::cout << std::endl;
}

Block::Block() {
    words[0] = Word({});
}

Word &Block::back() {
    return words[ip - 1];
}

Message::Message(const std::string &msg, unsigned int zeroBytesCount, unsigned int msgBitLen) {
    for (char c : msg)
        add(c); // Add byte-per-byte from original message

    // Add a 1 byte (1000 0000) = 128, base 10
    add(128);

    // Add zeros
    for (int i = 0; i < zeroBytesCount; ++i)
        add(0);

    // Convert msgbitLen to 2 32-bit words
    auto words = i64tw(static_cast<uint64_t>(msgBitLen));


    // Add both words little-endian
    add(words[0]);
    add(words[1]);
}

void Message::add(byte b) {
    if (chunks.empty() || chunks.back().isFull()) {
        Block newBlock;
        newBlock.add(b);
        chunks.push_back(newBlock);
    }
    else
        chunks.back().add(b);
}

Block Message::popBlock() {
    auto frontBlock = chunks.front();
    chunks.erase(chunks.begin());
    return frontBlock;
}

void Message::add(const Word& w) {
    if (chunks.back().isFull()) {
        Block new_block;
        new_block.add(w);
    } else
        chunks.back().add(w);
}

void Message::printDebug() {
    for (int i = 0; i < chunks.size(); ++i) {
        std::cout << "Block" << "[" << i << "] contains:" << std::endl;
        chunks[i].printDebug();
    }
}
