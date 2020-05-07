#include "common_header.h"

#include "number_convertion.h"


namespace {

/** Program for Hexadecimal to Decimal
 *
 * @reference   https://www.geeksforgeeks.org/program-for-hexadecimal-to-decimal/
 */
auto ToDecimal(const std::string &hex) {
    const auto hex_digit_to_decimal_map = CreateHexDigitToDecimalMap();

    int base = 1;
    int decimal_result = 0;
    for (auto r_iter = hex.crbegin(); r_iter != hex.crend(); ++r_iter, base *= 16) {
        decimal_result += hex_digit_to_decimal_map.at(*r_iter) * base;
    }

    return decimal_result;
}

}//namespace


SIMPLE_BENCHMARK(ToDecimal, "1A");

SIMPLE_TEST(ToDecimal, TestSAMPLE1, 26, "1A");
SIMPLE_TEST(ToDecimal, TestSAMPLE2, 43, "2B");
SIMPLE_TEST(ToDecimal, TestSAMPLE3, 103, "67");
SIMPLE_TEST(ToDecimal, TestSAMPLE4, 1298, "512");
SIMPLE_TEST(ToDecimal, TestSAMPLE5, 291, "123");
