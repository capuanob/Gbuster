//
// Created by bailey on 5/25/20.
//

/**
 * An adaptation of RFC-1321 Message-Digest-Algorithm-5 by Ronald Rivest @ RSA Data Security
 */
#ifndef HASHIMPL_MD5_H
#define HASHIMPL_MD5_H

#include <array>
#include <memory>
#include <cstring>
#include <vector>
#include <string>

using byte = uint8_t ;

namespace md5 {
/// CONSTANTS ///
    constexpr int BYTES_IN_WORD = 4;
    constexpr int WORDS_IN_BLOCK = 16;
    constexpr int DOUBLE_WORD = 64;
    constexpr int DIGEST_LEN = 32;

    constexpr const std::array<uint32_t, DOUBLE_WORD> T = {
            0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
            0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
            0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
            0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
            0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
            0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
            0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
            0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
            0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
            0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
            0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
            0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
            0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
            0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
            0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
            0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
    };

    constexpr const std::array<byte, DOUBLE_WORD> S = {
            7, 12, 17, 22, 7, 12, 17, 22,
            7, 12, 17, 22, 7, 12, 17, 22,
            5, 9, 14, 20, 5, 9, 14, 20,
            5, 9, 14, 20, 5, 9, 14, 20,
            4, 11, 16, 23, 4, 11, 16, 23,
            4, 11, 16, 23, 4, 11, 16, 23,
            6, 10, 15, 21, 6, 10, 15, 21,
            6, 10, 15, 21, 6, 10, 15, 21
    };

/// AUXILIARY FUNCTIONS ///
    inline constexpr auto lrotate(uint32_t value, byte amt) -> uint32_t {
        return (value << amt) | (value >> static_cast<byte>(32u - amt));
    }

    inline constexpr auto F(uint32_t x, uint32_t y, uint32_t z) -> uint32_t {
        return (x & y) | (~x & z);
    }

    inline constexpr auto G(uint32_t x, uint32_t y, uint32_t z) -> uint32_t {
        return (x & z) | (y & ~z);
    }

    inline constexpr auto H(uint32_t x, uint32_t y, uint32_t z) -> uint32_t {
        return x ^ y ^ z;
    }

    inline constexpr auto I(uint32_t x, uint32_t y, uint32_t z) -> uint32_t {
        return y ^ (x | ~z);
    }

    inline constexpr auto
    FF(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t blk, byte shiftAmt, uint32_t tableVal) -> uint32_t {
        return b + lrotate(a + F(b, c, d) + blk + tableVal, shiftAmt);
    }

    inline constexpr auto
    GG(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t blk, byte shiftAmt, uint32_t tableVal) -> uint32_t {
        return b + lrotate(a + G(b, c, d) + blk + tableVal, shiftAmt);
    }

    inline constexpr auto
    HH(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t blk, byte shiftAmt, uint32_t tableVal) -> uint32_t {
        return b + lrotate(a + H(b, c, d) + blk + tableVal, shiftAmt);
    }

    inline constexpr uint32_t
    II(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t blk, byte shiftAmt, uint32_t tableVal) {
        return b + lrotate(a + I(b, c, d) + blk + tableVal, shiftAmt);
    }

/// MD5 Implementation

    // Serves as storage for initialization constants and counts
    struct Context {
        std::array<uint32_t, BYTES_IN_WORD> state{}; // State variables (A, B, C, D)
        std::array<uint32_t, 2> count{}; // Number of bits, modulo 2^64 (lsb first)
        std::array<byte, DOUBLE_WORD> buffer{}; // Input buffer

        Context();
    };


    /**
     * @brief MD5 Finalization
     *
     * @details Ends an MD5 operation, writing the message digest out and cleaning up the context
     * @param digest Output of MD5 algorithm to be converted to hexadecimal output
     * @param context State of algorithm at end of operation
     */
    void final(std::array<byte, WORDS_IN_BLOCK>& digest, Context& context);

    /**
     * @brief MD5 basic transformation, transforms state based on block
     *
     * @param state State of MD5 algorithm at time of processing
     * @param block Collection of 16 words (64 bytes)
     */
    void transform(std::array<uint32_t, BYTES_IN_WORD>& state, std::array<byte, DOUBLE_WORD>& block);

    /**
     *  @brief MD5 block update operation
     *
     *  @details Continues an MD5 message-digest operation by processing a new block and updating the context
     *  @param context MD5 context containing state of algorithm at time of input
     *  @param input Cleartext input to be processed
     *  @param inputLen Length of input
     */
    template <size_t in_size>
    void update(Context& context, std::array<byte, in_size>& input, unsigned int inputLen = in_size) {
        // Compute number of bytes (mod 64)
        auto index = static_cast<unsigned int>((context.count[0] >> 3u) & 0x3Fu);

        // Update number of bits
        if ((context.count[0] += static_cast<uint32_t>(inputLen << 3u)) < static_cast<uint32_t>(inputLen << 3u))
            context.count[1]++;
        context.count[1] += static_cast<uint32_t>(inputLen >> 29u);
        unsigned int partialLength = DOUBLE_WORD - index;

        // Transform as many times as possible
        unsigned int i = 0;
        if (inputLen >= partialLength) {
            std::memcpy(&context.buffer.at(index), &input, partialLength);
            md5::transform(context.state, context.buffer);

            for (i = partialLength; i + 63 < inputLen; i += 64) {
                md5::transform(context.state, reinterpret_cast<std::array<byte, DOUBLE_WORD>&>(input[i]));
            }
            index = 0;
        } else {
            i = 0;
        }

        // Buffer remaining input
        std::memcpy(&context.buffer.at(index), &input[i], inputLen-i);
    }

    /**
     * @brief Encodes uint32_t input into readable output, assuming length is a multiple of 4
     *
     * @param output string output (hex)
     * @param input uint32_t input
     */
    template <size_t out_size, size_t in_size>
    void encode(std::array<byte, out_size>& output, std::array<uint32_t, in_size>& input) {
        static_assert(out_size % 4 == 0); // Pre-req to usage of this function
        unsigned int i = 0;
        unsigned int j = 0;
        for (; j < out_size; i++, j+= 4) {
            output[j] = static_cast<byte>(input[i] & 0xFFU);
            output[j+1] = static_cast<byte>((input[i] >> 8U) & 0xFFU);
            output[j+2] = static_cast<byte>((input[i] >> 16U) & 0xFFU);
            output[j+3] = static_cast<byte>((input[i] >> 24U) & 0xFFU);
        }
    }

    /**
     * @brief Decodes string input into uint32_t output
     *
     * @param output uint32_t output
     * @param input string input
     */
    template <size_t out_size, size_t in_size>
    void decode(std::array<uint32_t, out_size>& output, std::array<byte, in_size>& input) {
        static_assert(in_size % 4 == 0); // Pre-req to usage of this function
        unsigned int i = 0;
        unsigned int j = 0;
        for (; j < in_size; i++, j += 4) {
            output[i] = static_cast<uint32_t>(input[j]) | static_cast<uint32_t>(input[j+1] << 8U) |
                        static_cast<uint32_t>(input[j+2] << 16U) | static_cast<uint32_t>(input[j+3] << 24U);
        }
    }

    /**
     * @brief Shortcut function for updating and producing MD5 digest
     *
     * @param Input: Array of characters containing cleartext to be hashes
     * @param Digest: Where to store resulting digest
     * @param inputLen Actual length of input, not necessarily the same as max_len
     * @return 16 bytes of digest output
     */
    template <size_t max_len>
    void getDigest(std::array<unsigned char, max_len>& input, std::array<unsigned char, WORDS_IN_BLOCK>& digest, unsigned int inputLen = max_len) {
        Context context;
        update(context, input, inputLen);
        final(digest, context);
    }

    template <size_t n>
    auto digestStr(const std::array<unsigned char, n>& digest) -> std::string {
        std::string temp;
        temp.resize(DIGEST_LEN);

        unsigned int i = 0;
        unsigned int j = 0;
        for (; i < DIGEST_LEN; i += 2, j++) {
            sprintf(&temp[i], "%02x", digest[j]);
        }

        return temp;
    }
} // namespace md5

#endif //HASHIMPL_MD5_H