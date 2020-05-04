#include "common_header.h"


namespace {

/** Program to Convert Hexadecimal Number to Binary
 *
 * @reference   https://www.geeksforgeeks.org/program-to-convert-hexadecimal-number-to-binary/
 */
auto CreateHexToDecimalMap() {
    std::unordered_map<char, int> hex_to_decimal_map;
    for (int i = 0; i < 10; ++i) {
        hex_to_decimal_map['0' + i] = i;
    }

    for (int i = 0; i < 6; ++i) {
        hex_to_decimal_map['a' + i] = 10 + i;
        hex_to_decimal_map['A' + i] = 10 + i;
    }

    return hex_to_decimal_map;
}

auto ToBinary(const std::string &hex) {
    const auto hex_to_decimal_map = CreateHexToDecimalMap();
    std::stringstream ss_out;
    for (const auto hex_digit : hex) {
        ss_out << std::bitset<4>(hex_to_decimal_map.at(hex_digit));
    }

    return ss_out.str();
}

}//namespace


SIMPLE_BENCHMARK(ToBinary, "1AC5");

SIMPLE_TEST(ToBinary, TestSAMPLE1, "0001101011000101", "1AC5");
SIMPLE_TEST(ToBinary, TestSAMPLE2, "0101110100011111", "5D1F");
