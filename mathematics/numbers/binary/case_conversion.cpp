#include "common_header.h"

#include "conditionally_set_or_clear.h"


namespace {

/** Case conversion
 *
 * @reference   Case conversion (Lower to Upper and Vice Versa) of a string using BitWise operators in C/C++
 *              https://www.geeksforgeeks.org/case-conversion-lower-upper-vice-versa-string-using-bitwise-operators-cc/
 * @reference   Bit Tricks for Competitive Programming
 *              https://www.geeksforgeeks.org/bit-tricks-competitive-programming/
 * @reference   Lower case to upper case – An interesting fact
 *              https://www.geeksforgeeks.org/lower-case-upper-case-interesting-fact/
 *
 * Given a string, write a function that converts it either from lower to upper case or from upper
 * to lower case using the bitwise operators &(AND), |(OR), ~(NOT) in place and returns the string.
 */
constexpr char CASE_DIFF = 'a' - 'A';
auto ToLowerCase(const char c) {
    static constexpr bool IS_SET = true;
    return SetOrClear_Superscalar(IS_SET, CASE_DIFF, c);
}

auto ToUpperCase(const char c) {
    static constexpr bool IS_SET = false;
    return SetOrClear_Superscalar(IS_SET, CASE_DIFF, c);
}

/** Toggle case of a string using Bitwise Operators
 *
 * @reference   https://www.geeksforgeeks.org/toggle-case-string-using-bitwise-operators/
 * @reference   Convert characters of a string to opposite case
 *              https://www.geeksforgeeks.org/convert-alternate-characters-string-upper-case/
 * @reference   Program to toggle all characters in a string
 *              https://www.geeksforgeeks.org/program-toggle-characters-string/
 *
 * Given a string, write a function that returns toggle case of a string using the bitwise operators in place.
 */
auto ToggleCase(const char c) {
    return c ^ CASE_DIFF;
}

auto TransformString(std::string str, std::function<char(const char)> change_case) {
    std::transform(str.cbegin(), str.cend(), str.begin(), change_case);
    return str;
}

}//namespace


const std::string SAMPLE = "SanjaYKannA";
const std::string EXPECTED_UPPER = "SANJAYKANNA";
const std::string EXPECTED_LOWER = "sanjaykanna";
const std::string EXPECTED_TOGGLE = "sANJAykANNa";


SIMPLE_BENCHMARK(TransformString, Sample1, SAMPLE, ToLowerCase);

SIMPLE_TEST(TransformString, TestSampleLower, EXPECTED_LOWER, SAMPLE, ToLowerCase);


SIMPLE_BENCHMARK(TransformString, Sample2, SAMPLE, ToUpperCase);

SIMPLE_TEST(TransformString, TestSampleUpper, EXPECTED_UPPER, SAMPLE, ToUpperCase);


SIMPLE_BENCHMARK(TransformString, Sample3, SAMPLE, ToggleCase);

SIMPLE_TEST(TransformString, TestSampleToggle, EXPECTED_TOGGLE, SAMPLE, ToggleCase);
