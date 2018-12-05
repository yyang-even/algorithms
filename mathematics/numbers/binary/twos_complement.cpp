#include "common_header.h"

using InputType = unsigned;

/** Two’s complement of the number
 *
 * @reference   Bitwise Hacks for Competitive Programming
 *              https://www.geeksforgeeks.org/bitwise-hacks-for-competitive-programming/
 *
 * 2’s complement of a number is 1’s complement + 1.
 */
auto TwosComplementByOnesComplement(const InputType num) {
    return ~num + 1;
}

auto TwosComplementByMinusOperator(const InputType num) {
    return -num;
}


/** 1’s and 2’s complement of a Binary Number
 *
 * @reference   https://www.geeksforgeeks.org/1s-2s-complement-binary-number/
 *
 * Given a Binary Number as string, print its 1’s and 2’s complements.
 */
auto flip(const char bit) {
    return bit == '0' ? '1' : '0';
}
auto OnesComplement(std::string binary_string) {
    for (auto &bit : binary_string) {
        bit = flip(bit);
    }
    return binary_string;
}

auto TwosComplement(std::string binary_string) {
    binary_string = OnesComplement(binary_string);
    auto riter = binary_string.rbegin();
    for (; riter != binary_string.rend() and * riter == '1'; ++riter) {
        *riter = '0';
    }

    if (riter == binary_string.rend()) {
        binary_string.insert(binary_string.begin(), '1');
    } else {
        *riter = '1';
    }

    return binary_string;
}


constexpr auto LOWER = std::numeric_limits<unsigned>::min();
constexpr auto UPPER = std::numeric_limits<unsigned>::max();

MUTUAL_RANDOM_TEST(TwosComplementByOnesComplement, TwosComplementByMinusOperator, LOWER, UPPER);


SIMPLE_BENCHMARK(OnesComplement, std::string("0111"));

SIMPLE_TEST(OnesComplement, TestSample1, std::string("1000"), std::string("0111"));
SIMPLE_TEST(OnesComplement, TestSample2, std::string("0011"), std::string("1100"));


SIMPLE_BENCHMARK(TwosComplement, std::string("0111"));

SIMPLE_TEST(TwosComplement, TestSample1, std::string("1001"), std::string("0111"));
SIMPLE_TEST(TwosComplement, TestSample2, std::string("0100"), std::string("1100"));
SIMPLE_TEST(TwosComplement, TestSample3, std::string("11000"), std::string("01000"));
SIMPLE_TEST(TwosComplement, TestSample4, std::string("1000"), std::string("000"));
