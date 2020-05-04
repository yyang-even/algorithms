#include "common_header.h"


namespace {

/** Binary representation of a given number
 *
 * @reference   https://www.geeksforgeeks.org/binary-representation-of-a-given-number/
 * @reference   Decimal to binary conversion without using arithmetic operators
 *              https://www.geeksforgeeks.org/decimal-binary-conversion-without-using-arithmetic-operators/
 * @reference   Program for Decimal to Binary Conversion
 *              https://www.geeksforgeeks.org/program-decimal-binary-conversion/
 * @reference   Decimal to binary number using recursion
 *              https://www.geeksforgeeks.org/decimal-binary-number-using-recursion/
 *
 * Write a program to print Binary representation of a given number.
 */
auto ToBinaryString_Iterative(const unsigned n) {
    std::string output;
    for (unsigned i = 1 << (BitsNumber<decltype(n)> - 1); i; i >>= 1) {
        output.push_back(static_cast<bool>(n & i) + '0');
    }
    return output;
}


void ToBinaryString_Recursive_Helper(const unsigned n, const unsigned i, std::string &output) {
    if (i > 1u) {
        ToBinaryString_Recursive_Helper(n / 2u, i - 1, output);
    }

    output.push_back(static_cast<bool>(n & 1) + '0');
}

auto ToBinaryString_Recursive(const unsigned n) {
    std::string output;
    ToBinaryString_Recursive_Helper(n, BitsNumber<decltype(n)>, output);
    return output;
}


auto ToBinaryString_Bitset(const unsigned n) {
    return std::bitset<BitsNumber<decltype(n)>>(n).to_string();
}

}//namespace


constexpr auto LOWER = std::numeric_limits<unsigned>::min();
constexpr auto UPPER = std::numeric_limits<unsigned>::max();


SIMPLE_BENCHMARK(ToBinaryString_Iterative, UPPER);

SIMPLE_TEST(ToBinaryString_Iterative, TestSample1, std::string(BitsNumber<unsigned>, '0'),
            LOWER);
SIMPLE_TEST(ToBinaryString_Iterative, TestSample2, std::string(BitsNumber<unsigned>, '1'),
            UPPER);


SIMPLE_BENCHMARK(ToBinaryString_Recursive, UPPER);

SIMPLE_TEST(ToBinaryString_Recursive, TestSample1, std::string(BitsNumber<unsigned>, '0'),
            LOWER);
SIMPLE_TEST(ToBinaryString_Recursive, TestSample2, std::string(BitsNumber<unsigned>, '1'),
            UPPER);


SIMPLE_BENCHMARK(ToBinaryString_Bitset, UPPER);

MUTUAL_RANDOM_TEST(ToBinaryString_Bitset, ToBinaryString_Iterative, LOWER, UPPER);
MUTUAL_RANDOM_TEST(ToBinaryString_Bitset, ToBinaryString_Recursive, LOWER, UPPER);
