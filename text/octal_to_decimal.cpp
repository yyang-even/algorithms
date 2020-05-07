#include "common_header.h"


namespace {

/** Program for Octal to Decimal Conversion
 *
 * @reference   https://www.geeksforgeeks.org/program-octal-decimal-conversion/
 */
auto ToDecimal(const std::string &octal) {
    int base = 1;
    int decimal_result = 0;
    for (auto r_iter = octal.crbegin(); r_iter != octal.crend(); ++r_iter, base *= 8) {
        decimal_result += (*r_iter - '0') * base;
    }

    return decimal_result;
}

}//namespace


SIMPLE_BENCHMARK(ToDecimal, "67");

SIMPLE_TEST(ToDecimal, TestSAMPLE1, 55, "67");
SIMPLE_TEST(ToDecimal, TestSAMPLE2, 330, "512");
SIMPLE_TEST(ToDecimal, TestSAMPLE3, 83, "123");
