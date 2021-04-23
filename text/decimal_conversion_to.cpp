#include "common_header.h"


namespace {

/**
 * @reference   Implement your own itoa()
 *              https://www.geeksforgeeks.org/implement-itoa/
 */
auto DecimalTo(int number, const int base,
               const std::function<char(const int)> to_digit) {
    std::string result;
    for (; number; number /= base) {
        result.push_back(to_digit(number % base));
    }

    std::reverse(result.begin(), result.end());
    return result;
}


/** Program for Decimal to Octal Conversion
 *
 * @reference   https://www.geeksforgeeks.org/program-decimal-octal-conversion/
 * @reference   Decimal to octal conversion with minimum use of arithmetic operators
 *              https://www.geeksforgeeks.org/decimal-octal-conversion-minimum-use-arithmetic-operators/
 */
inline auto ToOctal(const int number) {
    return DecimalTo(number, 8, [](const int digit) {
        return '0' + digit;
    });
}


/** Program for decimal to hexadecimal conversion
 *
 * @reference   https://www.geeksforgeeks.org/program-decimal-hexadecimal-conversion/
 * @reference   Convert Decimal To Hexa-Decimal including negative numbers
 *              https://www.geeksforgeeks.org/convert-decimal-to-hexa-decimal-including-negative-numbers/
 */
inline auto ToHex(const int number) {
    return DecimalTo(number, 16, [](const int digit) {
        if (digit < 10) {
            return '0' + digit;
        } else {
            return 'A' + digit - 10;
        }
    });
}

}//namespace


THE_BENCHMARK(ToOctal, 16);

SIMPLE_TEST(ToOctal, TestSAMPLE1, "20", 16);
SIMPLE_TEST(ToOctal, TestSAMPLE2, "12", 10);
SIMPLE_TEST(ToOctal, TestSAMPLE3, "41", 33);


THE_BENCHMARK(ToHex, 942);

SIMPLE_TEST(ToHex, TestSAMPLE1, "3AE", 942);
SIMPLE_TEST(ToHex, TestSAMPLE2, "74", 116);
SIMPLE_TEST(ToHex, TestSAMPLE3, "A", 10);
SIMPLE_TEST(ToHex, TestSAMPLE4, "21", 33);
SIMPLE_TEST(ToHex, TestSAMPLE5, "9F1", 2545);
