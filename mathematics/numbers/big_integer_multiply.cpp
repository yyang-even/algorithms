#include "common_header.h"


namespace {

/** Multiply Strings
 *
 * @reference   https://leetcode.com/problems/multiply-strings/
 *
 * Given two non-negative integers num1 and num2 represented as strings, return the product of num1
 * and num2, also represented as a string.
 * Note: You must not use any built-in BigInteger library or convert the inputs to integer directly.
 */
std::string MultiplyStrs(const std::string_view num1, const std::string_view num2) {
    if (num1 == "0" or num2 == "0") {
        return "0";
    }

    std::vector<int> result(num1.size() + num2.size(), 0);
    for (int i = num1.size() - 1; i >= 0; --i) {
        for (int j = num2.size() - 1; j >= 0; --j) {
            result[i + j + 1] += (num1[i] - '0') * (num2[j] - '0');
            result[i + j] += result[i + j + 1] / 10;
            result[i + j + 1] %= 10;
        }
    }

    std::size_t i = 0;
    for (; result[i] == 0; ++i)
        ;
    std::string str_result;
    while (i < result.size()) {
        str_result.push_back(result[i++] + '0');
    }

    return str_result;
}

} //namespace


THE_BENCHMARK(MultiplyStrs, "2", "3");

SIMPLE_TEST(MultiplyStrs, TestSAMPLE1, "6", "2", "3");
SIMPLE_TEST(MultiplyStrs, TestSAMPLE2, "56088", "123", "456");
