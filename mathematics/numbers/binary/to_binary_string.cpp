#include "common_header.h"

#include <bitset>

typedef unsigned InputType;

/** Binary representation of a given number
 *
 * @reference   https://www.geeksforgeeks.org/binary-representation-of-a-given-number/
 *
 * Write a program to print Binary representation of a given number.
 */
auto ToBinaryStringIterative(const InputType n) {
    std::string output;
    for (InputType i = 1 << (Bits_Number<decltype(n)>() - 1); i; i >>= 1) {
        output.push_back(static_cast<bool>(n & i) + '0');
    }
    return output;
}


void ToBinaryStringRecursiveHelper(const InputType n, const unsigned i, std::string &output) {
    if (i > 1u) {
        ToBinaryStringRecursiveHelper(n / 2u, i - 1, output);
    }

    output.push_back(static_cast<bool>(n & 1) + '0');
}
auto ToBinaryStringRecursive(const InputType n) {
    std::string output;
    ToBinaryStringRecursiveHelper(n, Bits_Number<decltype(n)>(), output);
    return output;
}


auto ToBinaryStringBitset(const InputType n) {
    return std::bitset<Bits_Number<decltype(n)>()>(n).to_string();
}


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr auto UPPER = std::numeric_limits<InputType>::max();

SIMPLE_BENCHMARK(ToBinaryStringIterative, UPPER);
SIMPLE_BENCHMARK(ToBinaryStringRecursive, UPPER);
SIMPLE_BENCHMARK(ToBinaryStringBitset, UPPER);

SIMPLE_TEST(ToBinaryStringIterative, TestSample1, std::string(Bits_Number<InputType>(), '0'),
            LOWER);
SIMPLE_TEST(ToBinaryStringIterative, TestSample2, std::string(Bits_Number<InputType>(), '1'),
            UPPER);

SIMPLE_TEST(ToBinaryStringRecursive, TestSample1, std::string(Bits_Number<InputType>(), '0'),
            LOWER);
SIMPLE_TEST(ToBinaryStringRecursive, TestSample2, std::string(Bits_Number<InputType>(), '1'),
            UPPER);

MUTUAL_RANDOM_TEST(ToBinaryStringBitset, ToBinaryStringIterative, LOWER, UPPER);
MUTUAL_RANDOM_TEST(ToBinaryStringBitset, ToBinaryStringRecursive, LOWER, UPPER);
