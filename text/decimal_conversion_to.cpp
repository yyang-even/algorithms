#include "common_header.h"

#include "number_convertion.h"


namespace {

/**
 * @reference   Implement your own itoa()
 *              https://www.geeksforgeeks.org/implement-itoa/
 */
auto DecimalTo(unsigned number, const int base,
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
    return DecimalTo(number, 8, [](const auto digit) {
        return '0' + digit;
    });
}


/** Program for decimal to hexadecimal conversion
 *
 * @reference   https://www.geeksforgeeks.org/program-decimal-hexadecimal-conversion/
 * @reference   Convert Decimal To Hexa-Decimal including negative numbers
 *              https://www.geeksforgeeks.org/convert-decimal-to-hexa-decimal-including-negative-numbers/
 *
 * @reference   Convert a Number to Hexadecimal
 *              https://leetcode.com/problems/convert-a-number-to-hexadecimal/
 *
 * Given an integer num, return a string representing its hexadecimal representation.
 * For negative integers, two's complement method is used. All the letters in the answer
 * string should be lowercase characters, and there should not be any leading zeros in
 * the answer except for the zero itself. Note: You are not allowed to use any built-in
 * library method to directly solve this problem.
 */
inline auto ToHex(const int number) {
    return DecimalTo(number, 16, ToHexDigit);
}


/**
 * @reference   Hexspeak
 *              https://www.cnblogs.com/seyjs/p/11967411.html
 *
 * A decimal number can be converted to its Hexspeak representation by first converting
 * it to an uppercase hexadecimal string, then replacing all occurrences of the digit 0
 * with the letter O, and the digit 1 with the letter I.  Such a representation is valid
 * if and only if it consists only of the letters in the set
 * {"A", "B", "C", "D", "E", "F", "I", "O"}. Given a string num representing a decimal
 * integer N, return the Hexspeak representation of N if it is valid, otherwise return
 * "ERROR".
 * All answers must be in uppercase letters.
 */


/**
 * @reference   Base 7
 *              https://leetcode.com/problems/base-7/
 *
 * Given an integer num, return a string of its base 7 representation.
 */


/**
 * @reference   Excel Sheet Column Title
 *              https://leetcode.com/problems/excel-sheet-column-title/
 *
 * Given an integer columnNumber, return its corresponding column title as it appears
 * in an Excel sheet.
 */
auto ToColumnTitle(int number) {
    std::string result;
    while (number--) {
        result.push_back('A' + (number % 26));
        number /= 26;
    }

    std::reverse(result.begin(), result.end());
    return result;
}


/**
 * @reference   Excel Sheet Column Number
 *              https://leetcode.com/problems/excel-sheet-column-number/
 *
 * Given a string columnTitle that represents the column title as appear in an Excel
 * sheet, return its corresponding column number.
 */
constexpr auto ToColumnNumber(const std::string_view column_title) {
    int result = 0;
    for (const auto c : column_title) {
        result *= 26;
        result += c - 'A' + 1;
    }

    return result;
}


/**
 * @reference   Cells in a Range on an Excel Sheet
 *              https://leetcode.com/problems/cells-in-a-range-on-an-excel-sheet/
 *
 * A cell (r, c) of an excel sheet is represented as a string "<col><row>" where:
 *  <col> denotes the column number c of the cell. It is represented by alphabetical letters.
 *      For example, the 1st column is denoted by 'A', the 2nd by 'B', the 3rd by 'C',
 *      and so on.
 *  <row> is the row number r of the cell. The rth row is represented by the integer r.
 * You are given a string s in the format "<col1><row1>:<col2><row2>", where <col1>
 * represents the column c1, <row1> represents the row r1, <col2> represents the column
 * c2, and <row2> represents the row r2, such that r1 <= r2 and c1 <= c2.
 * Return the list of cells (x, y) such that r1 <= x <= r2 and c1 <= y <= c2. The cells
 * should be represented as strings in the format mentioned above and be sorted in
 * non-decreasing order first by columns and then by rows.
 */


/**
 * @reference   Thousand Separator
 *              https://leetcode.com/problems/thousand-separator/
 *
 * Given an integer n, add a dot (".") as the thousands separator and return it in string
 * format.
 */

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
SIMPLE_TEST(ToHex, TestSAMPLE6, "FFFFFFFF", -1);


THE_BENCHMARK(ToColumnTitle, 2147483647);

SIMPLE_TEST(ToColumnTitle, TestSAMPLE1, "A", 1);
SIMPLE_TEST(ToColumnTitle, TestSAMPLE2, "B", 2);
SIMPLE_TEST(ToColumnTitle, TestSAMPLE3, "C", 3);
SIMPLE_TEST(ToColumnTitle, TestSAMPLE4, "Z", 26);
SIMPLE_TEST(ToColumnTitle, TestSAMPLE5, "AA", 27);
SIMPLE_TEST(ToColumnTitle, TestSAMPLE6, "AB", 28);
SIMPLE_TEST(ToColumnTitle, TestSAMPLE7, "ZY", 701);
SIMPLE_TEST(ToColumnTitle, TestSAMPLE8, "FXSHRXW", 2147483647);


THE_BENCHMARK(ToColumnNumber, "FXSHRXW");

SIMPLE_TEST(ToColumnNumber, TestSAMPLE1, 1, "A");
SIMPLE_TEST(ToColumnNumber, TestSAMPLE2, 2, "B");
SIMPLE_TEST(ToColumnNumber, TestSAMPLE3, 3, "C");
SIMPLE_TEST(ToColumnNumber, TestSAMPLE4, 26, "Z");
SIMPLE_TEST(ToColumnNumber, TestSAMPLE5, 27, "AA");
SIMPLE_TEST(ToColumnNumber, TestSAMPLE6, 28, "AB");
SIMPLE_TEST(ToColumnNumber, TestSAMPLE7, 701, "ZY");
SIMPLE_TEST(ToColumnNumber, TestSAMPLE8, 2147483647, "FXSHRXW");
