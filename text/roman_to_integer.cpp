#include "common_header.h"


namespace {

/** Roman to Integer
 *
 * @reference   https://leetcode.com/problems/roman-to-integer/
 *
 * Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.
 *  Symbol       Value
 *  I             1
 *  V             5
 *  X             10
 *  L             50
 *  C             100
 *  D             500
 *  M             1000
 * For example, 2 is written as II in Roman numeral, just two one's added together. 12 is written
 * as XII, which is simply X + II. The number 27 is written as XXVII, which is XX + V + II.
 * Roman numerals are usually written largest to smallest from left to right. However, the numeral
 * for four is not IIII. Instead, the number four is written as IV. Because the one is before the
 * five we subtract it making four. The same principle applies to the number nine, which is written
 * as IX. There are six instances where subtraction is used:
 *  I can be placed before V (5) and X (10) to make 4 and 9.
 *  X can be placed before L (50) and C (100) to make 40 and 90.
 *  C can be placed before D (500) and M (1000) to make 400 and 900.
 * Given a roman numeral, convert it to an integer.
 * It is guaranteed that s is a valid roman numeral in the range [1, 3999].
 */
auto RomanToInt(const std::string_view roman) {
    static const std::unordered_map<char, int> SYMBOLS = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000},
    };

    char prev = 0;
    int result = 0;
    for (const auto c : roman) {
        if ((prev == 'I' and (c == 'V' or c == 'X')) or
            (prev == 'X' and (c == 'L' or c == 'C')) or
            (prev == 'C' and (c == 'D' or c == 'M'))) {
            result -= 2 * SYMBOLS.at(prev);
        }
        result += SYMBOLS.at(c);
        prev = c;
    }

    return result;
}


/**
 * @reference   Integer to Roman
 *              https://leetcode.com/problems/integer-to-roman/
 *
 * Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.
 *  Symbol       Value
 *  I             1
 *  V             5
 *  X             10
 *  L             50
 *  C             100
 *  D             500
 *  M             1000
 * For example, 2 is written as II in Roman numeral, just two one's added together. 12 is written
 * as XII, which is simply X + II. The number 27 is written as XXVII, which is XX + V + II.
 * Roman numerals are usually written largest to smallest from left to right. However, the numeral
 * for four is not IIII. Instead, the number four is written as IV. Because the one is before the
 * five we subtract it making four. The same principle applies to the number nine, which is written
 * as IX. There are six instances where subtraction is used:
 *  I can be placed before V (5) and X (10) to make 4 and 9.
 *  X can be placed before L (50) and C (100) to make 40 and 90.
 *  C can be placed before D (500) and M (1000) to make 400 and 900.
 * Given an integer, convert it to a roman numeral.
 */
auto IntToRoman(int num) {
    static const std::vector<std::pair<int, std::string>> SYMBOLS = {
        {1000, "M"},
        {900, "CM"},
        {500, "D"},
        {400, "CD"},
        {100, "C"},
        {90, "XC"},
        {50, "L"},
        {40, "XL"},
        {10, "X"},
        {9, "IX"},
        {5, "V"},
        {4, "IV"},
        {1, "I"},
    };

    std::string result;
    for (const auto &[v, s] : SYMBOLS) {
        while (num >= v) {
            num -= v;
            result += s;
        }
    }

    return result;
}

} //namespace


THE_BENCHMARK(RomanToInt, "III");

SIMPLE_TEST(RomanToInt, TestSAMPLE1, 3, "III");
SIMPLE_TEST(RomanToInt, TestSAMPLE2, 4, "IV");
SIMPLE_TEST(RomanToInt, TestSAMPLE3, 12, "XII");
SIMPLE_TEST(RomanToInt, TestSAMPLE4, 27, "XXVII");
SIMPLE_TEST(RomanToInt, TestSAMPLE5, 9, "IX");
SIMPLE_TEST(RomanToInt, TestSAMPLE6, 40, "XL");
SIMPLE_TEST(RomanToInt, TestSAMPLE7, 90, "XC");
SIMPLE_TEST(RomanToInt, TestSAMPLE8, 400, "CD");
SIMPLE_TEST(RomanToInt, TestSAMPLE9, 900, "CM");


THE_BENCHMARK(IntToRoman, 27);

SIMPLE_TEST(IntToRoman, TestSAMPLE1, "III", 3);
SIMPLE_TEST(IntToRoman, TestSAMPLE2, "IV", 4);
SIMPLE_TEST(IntToRoman, TestSAMPLE3, "XII", 12);
SIMPLE_TEST(IntToRoman, TestSAMPLE4, "XXVII", 27);
SIMPLE_TEST(IntToRoman, TestSAMPLE5, "IX", 9);
SIMPLE_TEST(IntToRoman, TestSAMPLE6, "XL", 40);
SIMPLE_TEST(IntToRoman, TestSAMPLE7, "XC", 90);
SIMPLE_TEST(IntToRoman, TestSAMPLE8, "CD", 400);
SIMPLE_TEST(IntToRoman, TestSAMPLE9, "CM", 900);
SIMPLE_TEST(IntToRoman, TestSAMPLE10, "LVIII", 58);
SIMPLE_TEST(IntToRoman, TestSAMPLE11, "MCMXCIV", 1994);
