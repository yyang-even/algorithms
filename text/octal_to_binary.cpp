#include "common_header.h"


namespace {

/** Program to Convert Octal Number to Binary Number
 *
 * @reference   https://www.geeksforgeeks.org/program-to-convert-octal-number-to-binary-number/
 */
auto ToBinary(const std::string &octal) {
    std::stringstream ss_out;
    for (const auto octal_digit : octal) {
        ss_out << std::bitset<3>(octal_digit - '0');
    }

    return ss_out.str();
}

}//namespace


SIMPLE_BENCHMARK(ToBinary, "345");

SIMPLE_TEST(ToBinary, TestSAMPLE1, "011100101", "345");
SIMPLE_TEST(ToBinary, TestSAMPLE2, "001010000", "120");
