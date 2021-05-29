#include "common_header.h"


namespace {

/** Two’s complement of the number
 *
 * @reference   Bitwise Hacks for Competitive Programming
 *              https://www.geeksforgeeks.org/bitwise-hacks-for-competitive-programming/
 *
 * 2’s complement of a number is 1’s complement + 1.
 */
inline auto TwosComplement_ByOnesComplement(const unsigned num) {
    return ~num + 1;
}

inline auto TwosComplement_ByMinusOperator(const unsigned num) {
    return -num;
}


/** 1’s and 2’s complement of a Binary Number
 *
 * @reference   https://www.geeksforgeeks.org/1s-2s-complement-binary-number/
 * @reference   Why are negative numbers stored as 2’s complement?
 *              https://www.geeksforgeeks.org/why-are-negative-numbers-stored-as-2s-complement/
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

/** Efficient method for 2’s complement of a binary string
 *
 * @reference   https://www.geeksforgeeks.org/efficient-method-2s-complement-binary-string/
 */
auto TwosComplement_Efficient(std::string binary_string) {
    auto riter = binary_string.rbegin();
    for (; riter != binary_string.rend() and * riter != '1'; ++riter) {
    }

    if (riter == binary_string.rend()) {
        binary_string.insert(binary_string.begin(), '1');
    } else {
        for (++riter; riter != binary_string.rend(); ++riter) {
            *riter = flip(*riter);
        }
    }

    return binary_string;
}

}//namespace


constexpr auto LOWER = std::numeric_limits<unsigned>::min();
constexpr auto UPPER = std::numeric_limits<unsigned>::max();


MUTUAL_RANDOM_TEST(TwosComplement_ByOnesComplement, TwosComplement_ByMinusOperator,
                   LOWER, UPPER);


SIMPLE_BENCHMARK(OnesComplement, Sample1, "0111");

SIMPLE_TEST(OnesComplement, TestSample1, "1000", "0111");
SIMPLE_TEST(OnesComplement, TestSample2, "0011", "1100");


SIMPLE_BENCHMARK(TwosComplement, Sample1, "0111");

SIMPLE_TEST(TwosComplement, TestSample1, "1001", "0111");
SIMPLE_TEST(TwosComplement, TestSample2, "0100", "1100");
SIMPLE_TEST(TwosComplement, TestSample3, "11000", "01000");
SIMPLE_TEST(TwosComplement, TestSample4, "1000", "000");
SIMPLE_TEST(TwosComplement, TestSample5, "0111100", "1000100");
SIMPLE_TEST(TwosComplement, TestSample6, "11111011", "00000101");


SIMPLE_BENCHMARK(TwosComplement_Efficient, Sample1, "0111");

SIMPLE_TEST(TwosComplement_Efficient, TestSample1, "1001", "0111");
SIMPLE_TEST(TwosComplement_Efficient, TestSample2, "0100", "1100");
SIMPLE_TEST(TwosComplement_Efficient, TestSample3, "11000", "01000");
SIMPLE_TEST(TwosComplement_Efficient, TestSample4, "1000", "000");
SIMPLE_TEST(TwosComplement_Efficient, TestSample5, "0111100", "1000100");
SIMPLE_TEST(TwosComplement_Efficient, TestSample6, "11111011", "00000101");
