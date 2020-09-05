#include "common_header.h"

#include "number_convertion.h"


namespace {

auto ToDecimal(const std::string &number, const int base,
               const std::function<int(const char)> to_decimal) {
    int power_of_base = 1;
    int decimal_result = 0;
    for (auto r_iter = number.crbegin(); r_iter != number.crend(); ++r_iter, power_of_base *= base) {
        decimal_result += to_decimal(*r_iter) * power_of_base;
    }

    return decimal_result;
}


/** Program for Hexadecimal to Decimal
 *
 * @reference   https://www.geeksforgeeks.org/program-for-hexadecimal-to-decimal/
 */
auto HexToDecimal(const std::string &hex) {
    return ToDecimal(hex, 16, HexDigitToDecimal);
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
    return ToDecimal(octal, 8, OctalDigitToDecimal);
}


/** Program for Binary To Decimal Conversion
 *
 * @reference   https://www.geeksforgeeks.org/program-binary-decimal-conversion/
 */
auto BinaryToDecimal(const std::string &binary) {
    return ToDecimal(binary, 2, BinaryDigitToDecimal);
}


/**
 * @reference   Recursive Program for Binary to Decimal
 *              https://www.geeksforgeeks.org/recursive-program-for-binary-to-decimal/
 */
int BinaryToDecimal_Recursive(const std::string &binary, const std::string::size_type i = 0) {
    if (i == binary.size()) {
        return 0;
    }

    return (BinaryDigitToDecimal(binary[i]) << (binary.size() - i - 1)) +
           BinaryToDecimal_Recursive(binary, i + 1);
}

}//namespace


SIMPLE_BENCHMARK(HexToDecimal, Sample1, "1A");

SIMPLE_TEST(HexToDecimal, TestSAMPLE1, 26, "1A");
SIMPLE_TEST(HexToDecimal, TestSAMPLE2, 43, "2B");
SIMPLE_TEST(HexToDecimal, TestSAMPLE3, 103, "67");
SIMPLE_TEST(HexToDecimal, TestSAMPLE4, 1298, "512");
SIMPLE_TEST(HexToDecimal, TestSAMPLE5, 291, "123");


SIMPLE_BENCHMARK(HexToDecimal_StringStream, Sample1, "1A");

SIMPLE_TEST(HexToDecimal_StringStream, TestSAMPLE1, 26, "1A");
SIMPLE_TEST(HexToDecimal_StringStream, TestSAMPLE2, 43, "2B");
SIMPLE_TEST(HexToDecimal_StringStream, TestSAMPLE3, 103, "67");
SIMPLE_TEST(HexToDecimal_StringStream, TestSAMPLE4, 1298, "512");
SIMPLE_TEST(HexToDecimal_StringStream, TestSAMPLE5, 291, "123");


SIMPLE_BENCHMARK(OctalToDecimal, Sample1, "67");

SIMPLE_TEST(OctalToDecimal, TestSAMPLE1, 55, "67");
SIMPLE_TEST(OctalToDecimal, TestSAMPLE2, 330, "512");
SIMPLE_TEST(OctalToDecimal, TestSAMPLE3, 83, "123");


SIMPLE_BENCHMARK(BinaryToDecimal, Sample1, "111");

SIMPLE_TEST(BinaryToDecimal, TestSAMPLE1, 7, "111");
SIMPLE_TEST(BinaryToDecimal, TestSAMPLE2, 10, "1010");
SIMPLE_TEST(BinaryToDecimal, TestSAMPLE3, 33, "100001");
SIMPLE_TEST(BinaryToDecimal, TestSAMPLE4, 169, "10101001");
SIMPLE_TEST(BinaryToDecimal, TestSAMPLE5, 9, "1001");


SIMPLE_BENCHMARK(BinaryToDecimal_Recursive, Sample1, "111");

SIMPLE_TEST(BinaryToDecimal_Recursive, TestSAMPLE1, 7, "111");
SIMPLE_TEST(BinaryToDecimal_Recursive, TestSAMPLE2, 10, "1010");
SIMPLE_TEST(BinaryToDecimal_Recursive, TestSAMPLE3, 33, "100001");
SIMPLE_TEST(BinaryToDecimal_Recursive, TestSAMPLE4, 169, "10101001");
SIMPLE_TEST(BinaryToDecimal_Recursive, TestSAMPLE5, 9, "1001");
