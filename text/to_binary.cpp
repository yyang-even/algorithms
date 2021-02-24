#include "common_header.h"

#include "number_convertion.h"
#include "to_binary.h"


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


/**
 * @reference   Decimal to Binary using recursion and without using power operator
 *              https://www.geeksforgeeks.org/decimal-to-binary-using-recursion-and-without-using-power-operator/
 */
void ToBinaryString_Recursive_Helper(const unsigned n,
                                     const unsigned i,
                                     std::string &output) {
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


/** Program to Convert Octal Number to Binary Number
 *
 * @reference   https://www.geeksforgeeks.org/program-to-convert-octal-number-to-binary-number/
 */
auto OctalToBinary(const std::string &octal) {
    return ToBinary<3>(octal, OctalDigitToDecimal);
}


/** Converting a Real Number (between 0 and 1) to Binary String
 *
 * @reference   https://www.geeksforgeeks.org/converting-a-real-number-between-0-and-1-to-binary-string/
 *
 * Given a real number between 0 and 1 (e.g., 0.72) that is passed in as a double, print
 * the binary representation. If the number cannot be represented accurately in binary
 * with at most 32 characters, print "ERROR."
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 5.2.
 */
const std::string ERROR_STR = "ERROR";

auto RealToBinary(double number) {
    assert(0 <= number and number <= 1);

    std::string result = "0.";
    while (number > 0) {
        if (result.size() >= 32) {
            return ERROR_STR;
        }

        number *= 2;
        if (number >= 1) {
            result.push_back('1');
            --number;
        } else {
            result.push_back('0');
        }
    }

    return result;
}

}//namespace


constexpr auto LOWER = std::numeric_limits<unsigned>::min();
constexpr auto UPPER = std::numeric_limits<unsigned>::max();


SIMPLE_BENCHMARK(ToBinaryString_Iterative, Sample1, UPPER);

SIMPLE_TEST(ToBinaryString_Iterative, TestSample1,
            std::string(BitsNumber<unsigned>, '0'), LOWER);
SIMPLE_TEST(ToBinaryString_Iterative, TestSample2,
            std::string(BitsNumber<unsigned>, '1'), UPPER);


SIMPLE_BENCHMARK(ToBinaryString_Recursive, Sample1, UPPER);

SIMPLE_TEST(ToBinaryString_Recursive, TestSample1,
            std::string(BitsNumber<unsigned>, '0'), LOWER);
SIMPLE_TEST(ToBinaryString_Recursive, TestSample2,
            std::string(BitsNumber<unsigned>, '1'), UPPER);


SIMPLE_BENCHMARK(ToBinaryString_Bitset, Sample1, UPPER);

MUTUAL_RANDOM_TEST(ToBinaryString_Bitset, ToBinaryString_Iterative, LOWER, UPPER);
MUTUAL_RANDOM_TEST(ToBinaryString_Bitset, ToBinaryString_Recursive, LOWER, UPPER);


SIMPLE_BENCHMARK(OctalToBinary, Sample1, "345");

SIMPLE_TEST(OctalToBinary, TestSAMPLE1, "011100101", "345");
SIMPLE_TEST(OctalToBinary, TestSAMPLE2, "001010000", "120");


SIMPLE_BENCHMARK(HexToBinary, Sample1, "1AC5");

SIMPLE_TEST(HexToBinary, TestSAMPLE1, "0001101011000101", "1AC5");
SIMPLE_TEST(HexToBinary, TestSAMPLE2, "0101110100011111", "5D1F");


SIMPLE_BENCHMARK(RealToBinary, Sample1, 0.625);

SIMPLE_TEST(RealToBinary, TestSAMPLE1, "0.101", 0.625);
SIMPLE_TEST(RealToBinary, TestSAMPLE2, ERROR_STR, 0.72);
