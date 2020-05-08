#include "common_header.h"


namespace {

auto DecimalTo(int number, const int base, const std::function<char(const int)> to_digit) {
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
 */
auto ToOctal(const int number) {
    return DecimalTo(number, 8, [](const int digit) {
        return '0' + digit;
    });
}


auto ToHex(const int number) {
    return DecimalTo(number, 16, [](const int digit) {
        if (digit < 10) {
            return '0' + digit;
        } else {
            return 'A' + digit - 10;
        }
    });
}

}//namespace


SIMPLE_BENCHMARK(ToOctal, 16);

SIMPLE_TEST(ToOctal, TestSAMPLE1, "20", 16);
SIMPLE_TEST(ToOctal, TestSAMPLE2, "12", 10);
SIMPLE_TEST(ToOctal, TestSAMPLE3, "41", 33);


SIMPLE_BENCHMARK(ToHex, 942);

SIMPLE_TEST(ToHex, TestSAMPLE1, "3AE", 942);
