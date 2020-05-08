#include "common_header.h"

#include "number_convertion.h"


namespace {

auto ToDecimal(const std::string &number, const int base,
               const std::function<int(const char)> to_decimal_digit) {
    int power_of_base = 1;
    int decimal_result = 0;
    for (auto r_iter = number.crbegin(); r_iter != number.crend(); ++r_iter, power_of_base *= base) {
        decimal_result += to_decimal_digit(*r_iter) * power_of_base;
    }

    return decimal_result;
}


/** Program for Hexadecimal to Decimal
 *
 * @reference   https://www.geeksforgeeks.org/program-for-hexadecimal-to-decimal/
 */
auto HexToDecimal(const std::string &hex) {
    const auto hex_digit_to_decimal_map = CreateHexDigitToDecimalMap();
    return ToDecimal(hex, 16, [&hex_digit_to_decimal_map](const char digit) {
        return hex_digit_to_decimal_map.at(digit);
    });
}


/**
 * @reference   StringStream in C++ for Decimal to Hexadecimal and back
 *              https://www.geeksforgeeks.org/stringstream-c-decimal-hexadecimal-back/
 */
auto HexToDecimal_StringStream(const std::string &hex) {
    int decimal_result = 0;
    std::stringstream ss;
    ss << hex;
    ss >> std::hex >> decimal_result;

    return decimal_result;
}


/** Program for Octal to Decimal Conversion
 *
 * @reference   https://www.geeksforgeeks.org/program-octal-decimal-conversion/
 */
auto OctalToDecimal(const std::string &octal) {
    return ToDecimal(octal, 8, [](const char digit) {
        return digit - '0';
    });
}

}//namespace


SIMPLE_BENCHMARK(HexToDecimal, "1A");

SIMPLE_TEST(HexToDecimal, TestSAMPLE1, 26, "1A");
SIMPLE_TEST(HexToDecimal, TestSAMPLE2, 43, "2B");
SIMPLE_TEST(HexToDecimal, TestSAMPLE3, 103, "67");
SIMPLE_TEST(HexToDecimal, TestSAMPLE4, 1298, "512");
SIMPLE_TEST(HexToDecimal, TestSAMPLE5, 291, "123");


SIMPLE_BENCHMARK(HexToDecimal_StringStream, "1A");

SIMPLE_TEST(HexToDecimal_StringStream, TestSAMPLE1, 26, "1A");
SIMPLE_TEST(HexToDecimal_StringStream, TestSAMPLE2, 43, "2B");
SIMPLE_TEST(HexToDecimal_StringStream, TestSAMPLE3, 103, "67");
SIMPLE_TEST(HexToDecimal_StringStream, TestSAMPLE4, 1298, "512");
SIMPLE_TEST(HexToDecimal_StringStream, TestSAMPLE5, 291, "123");


SIMPLE_BENCHMARK(OctalToDecimal, "67");

SIMPLE_TEST(OctalToDecimal, TestSAMPLE1, 55, "67");
SIMPLE_TEST(OctalToDecimal, TestSAMPLE2, 330, "512");
SIMPLE_TEST(OctalToDecimal, TestSAMPLE3, 83, "123");
