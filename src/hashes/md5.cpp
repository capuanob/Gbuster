//
// Created by bailey on 5/25/20.
//

#include "md5.h"

md5::Context::Context() {
    count = {0, 0};
    state = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 }; // Magic initialization constants
}

std::array<byte, md5::DOUBLE_WORD> PADDING {
        0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void md5::transform(std::array<uint32_t, BYTES_IN_WORD> &state, std::array<byte, DOUBLE_WORD> &block) {
    auto A = state[0];
    auto B = state[1];
    auto C = state[2];
    auto D = state[3];
    std::array<uint32_t, WORDS_IN_BLOCK> X{};
    decode(X, block);

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

    state[0] += A;
    state[1] += B;
    state[2] += C;
    state[3] += D;

    // Zeroize sensitive information
    std::memset(&X, 0, sizeof(X));
}

void md5::final(std::array<byte, 16> &digest, md5::Context &context) {
    std::array<byte, 8> bits{};
    encode(bits, context.count);

    // Pad out to 56 mod 64
    auto index = static_cast<unsigned int>((context.count[0] >> 3U) & 0x3fU);
    unsigned int padLen = (index < 56) ? (56 - index) : (120 - index);
    update(context, PADDING, padLen);

    // Append length (before padding)
    update(context, bits);

    // Store state in digest
    encode(digest, context.state);

    // Zeroize sensitive information
    std::memset(&context, 0, sizeof(context));
}