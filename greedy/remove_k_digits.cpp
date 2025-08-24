#include "common_header.h"


namespace {

/**
 * @reference   Remove K Digits
 *              https://leetcode.com/problems/remove-k-digits/
 *
 * Given string num representing a non-negative integer num, and an integer k, return the smallest
 * possible integer after removing k digits from num.
 *
 * @tags    #greedy #monotonic-stack
 */
std::string RemoveKDigits(const std::string_view num, std::size_t k) {
    std::string result;
    for (const auto c : num) {
        while (not result.empty() and k and c < result.back()) {
            result.pop_back();
            --k;
        }

        if (not result.empty() or c != '0') {
            result.push_back(c);
        }
    }

    return result.size() <= k ? "0" : result.substr(0, result.size() - k);
}


/**
 * @reference   Remove Digit From Number to Maximize Result
 *              https://leetcode.com/problems/remove-digit-from-number-to-maximize-result/
 *
 * You are given a string number representing a positive integer and a character digit.
 * Return the resulting string after removing exactly one occurrence of digit from number such that the
 * value of the resulting string in decimal form is maximized. The test cases are generated such that
 * digit occurs at least once in number.
 *
 * @tags    #greedy
 */
auto RemoveOneDigit(const std::string &number, const char digit) {
    int last_seen = -1;
    for (std::size_t i = 0; i < number.size(); ++i) {
        if (number[i] == digit) {
            last_seen = i;
            if ((i + 1 < number.size()) and number[i + 1] > digit) {
                break;
            }
        }
    }

    return number.substr(0, last_seen) + number.substr(last_seen + 1);
}

} //namespace


THE_BENCHMARK(RemoveKDigits, "1432219", 3);

SIMPLE_TEST(RemoveKDigits, TestSAMPLE1, "1219", "1432219", 3);
SIMPLE_TEST(RemoveKDigits, TestSAMPLE2, "200", "10200", 1);
SIMPLE_TEST(RemoveKDigits, TestSAMPLE3, "0", "10", 2);
SIMPLE_TEST(RemoveKDigits, TestSAMPLE4, "12", "1234", 2);
SIMPLE_TEST(RemoveKDigits, TestSAMPLE5, "107", "1107", 1);
SIMPLE_TEST(RemoveKDigits, TestSAMPLE6, "11", "112", 1);
SIMPLE_TEST(RemoveKDigits, TestSAMPLE7, "0", "1234567890", 9);


THE_BENCHMARK(RemoveOneDigit, "123", '3');

SIMPLE_TEST(RemoveOneDigit, TestSAMPLE1, "12", "123", '3');
SIMPLE_TEST(RemoveOneDigit, TestSAMPLE2, "231", "1231", '1');
SIMPLE_TEST(RemoveOneDigit, TestSAMPLE3, "51", "551", '5');
SIMPLE_TEST(RemoveOneDigit, TestSAMPLE4, "312", "3123", '3');
