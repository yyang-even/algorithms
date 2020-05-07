#include "common_header.h"

#include "number_convertion.h"


namespace {

/** Program to Convert Hexadecimal Number to Binary
 *
 * @reference   https://www.geeksforgeeks.org/program-to-convert-hexadecimal-number-to-binary/
 */
auto ToBinary(const std::string &hex) {
    const auto hex_digit_to_decimal_map = CreateHexDigitToDecimalMap();
    std::stringstream ss_out;
    for (const auto hex_digit : hex) {
        ss_out << std::bitset<4>(hex_digit_to_decimal_map.at(hex_digit));
    }

    return ss_out.str();
}

}//namespace


SIMPLE_BENCHMARK(ToBinary, "1AC5");

SIMPLE_TEST(ToBinary, TestSAMPLE1, "0001101011000101", "1AC5");
SIMPLE_TEST(ToBinary, TestSAMPLE2, "0101110100011111", "5D1F");
