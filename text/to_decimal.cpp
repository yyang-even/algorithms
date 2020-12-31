#include "common_header.h"

#include "number_convertion.h"


namespace {

auto ToDecimal(const std::string &number, const int base,
               const std::function<int(const char)> to_decimal) {
    int result = 0;
    int sign = 1;

    if (not number.empty()) {
        auto cbegin = number.cbegin();
        if (*cbegin == '-') {
            sign = -1;
            ++cbegin;
        }

        while (cbegin != number.cend()) {
            result = result * base + to_decimal(*(cbegin++));
        }
    }

    return sign * result;
}


/** Write your own atoi()
 *
 * @reference   https://www.geeksforgeeks.org/write-your-own-atoi/
 * @reference   C++ Program to Convert String to Integer
 *              https://www.geeksforgeeks.org/c-program-to-convert-string-to-integer/
 * @reference   Convert string to integer without using any in-built functions
 *              https://www.geeksforgeeks.org/convert-string-to-integer-without-using-any-in-built-functions/
 * @reference   Converting string to number and vice-versa in C++
 *              https://www.geeksforgeeks.org/converting-string-to-number-and-vice-versa-in-c/
 * @reference   Converting Strings to Numbers in C/C++
 *              https://www.geeksforgeeks.org/converting-strings-numbers-cc/
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 6.
 */
auto DecToDecimal(const std::string &dec) {
    return ToDecimal(dec, 10, HexDigitToDecimal);
}


/**
 * @reference   Recursive Implementation of atoi()
 *              https://www.geeksforgeeks.org/recursive-implementation-of-atoi/
 */
auto DecToDecimal_Recursive(const std::string::const_reverse_iterator crbegin,
                            const std::string::size_type n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return *crbegin - '0';
    }

    return DecToDecimal_Recursive(std::next(crbegin), n - 1) * 10 + *crbegin - '0';
}

auto DecToDecimal_Recursive(const std::string &dec) {
    return DecToDecimal_Recursive(dec.crbegin(), dec.size());
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
int BinaryToDecimal_Recursive(const std::string &binary,
                              const std::string::size_type i = 0) {
    if (i == binary.size()) {
        return 0;
    }

    return (BinaryDigitToDecimal(binary[i]) << (binary.size() - i - 1)) +
           BinaryToDecimal_Recursive(binary, i + 1);
}

}//namespace


THE_BENCHMARK(HexToDecimal, "1A");

SIMPLE_TEST(HexToDecimal, TestSAMPLE1, 26, "1A");
SIMPLE_TEST(HexToDecimal, TestSAMPLE2, 43, "2B");
SIMPLE_TEST(HexToDecimal, TestSAMPLE3, 103, "67");
SIMPLE_TEST(HexToDecimal, TestSAMPLE4, 1298, "512");
SIMPLE_TEST(HexToDecimal, TestSAMPLE5, 291, "123");


THE_BENCHMARK(HexToDecimal_StringStream, "1A");

SIMPLE_TEST(HexToDecimal_StringStream, TestSAMPLE1, 26, "1A");
SIMPLE_TEST(HexToDecimal_StringStream, TestSAMPLE2, 43, "2B");
SIMPLE_TEST(HexToDecimal_StringStream, TestSAMPLE3, 103, "67");
SIMPLE_TEST(HexToDecimal_StringStream, TestSAMPLE4, 1298, "512");
SIMPLE_TEST(HexToDecimal_StringStream, TestSAMPLE5, 291, "123");


THE_BENCHMARK(OctalToDecimal, "67");

SIMPLE_TEST(OctalToDecimal, TestSAMPLE1, 55, "67");
SIMPLE_TEST(OctalToDecimal, TestSAMPLE2, 330, "512");
SIMPLE_TEST(OctalToDecimal, TestSAMPLE3, 83, "123");


THE_BENCHMARK(BinaryToDecimal, "111");

SIMPLE_TEST(BinaryToDecimal, TestSAMPLE1, 7, "111");
SIMPLE_TEST(BinaryToDecimal, TestSAMPLE2, 10, "1010");
SIMPLE_TEST(BinaryToDecimal, TestSAMPLE3, 33, "100001");
SIMPLE_TEST(BinaryToDecimal, TestSAMPLE4, 169, "10101001");
SIMPLE_TEST(BinaryToDecimal, TestSAMPLE5, 9, "1001");


THE_BENCHMARK(BinaryToDecimal_Recursive, "111");

SIMPLE_TEST(BinaryToDecimal_Recursive, TestSAMPLE1, 7, "111");
SIMPLE_TEST(BinaryToDecimal_Recursive, TestSAMPLE2, 10, "1010");
SIMPLE_TEST(BinaryToDecimal_Recursive, TestSAMPLE3, 33, "100001");
SIMPLE_TEST(BinaryToDecimal_Recursive, TestSAMPLE4, 169, "10101001");
SIMPLE_TEST(BinaryToDecimal_Recursive, TestSAMPLE5, 9, "1001");


THE_BENCHMARK(DecToDecimal, "111");

SIMPLE_TEST(DecToDecimal, TestSAMPLE1, 1, "1");
SIMPLE_TEST(DecToDecimal, TestSAMPLE2, 0, "0");
SIMPLE_TEST(DecToDecimal, TestSAMPLE3, -1, "-1");
SIMPLE_TEST(DecToDecimal, TestSAMPLE4, 4562, "4562");


THE_BENCHMARK(DecToDecimal_Recursive, "111");

SIMPLE_TEST(DecToDecimal_Recursive, TestSAMPLE1, 1, "1");
SIMPLE_TEST(DecToDecimal_Recursive, TestSAMPLE2, 0, "0");
SIMPLE_TEST(DecToDecimal_Recursive, TestSAMPLE4, 4562, "4562");
