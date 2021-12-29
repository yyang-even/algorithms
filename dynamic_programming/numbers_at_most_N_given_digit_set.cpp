#include "common_header.h"


namespace {

using ArrayType = std::vector<char>;

/** Numbers At Most N Given Digit Set
 *
 * @reference   https://leetcode.com/problems/numbers-at-most-n-given-digit-set/
 *
 * Given an array of digits which is sorted in non-decreasing order. You can write numbers
 * using each digits[i] as many times as we want. For example, if digits = ['1','3','5'],
 * we may write numbers such as '13', '551', and '1351315'. Return the number of positive
 * integers that can be generated that are less than or equal to a given integer n.
 * digits[i] is a digit from '1' to '9'.
 * All the values in digits are unique.
 */
auto NumbersAtMostNGivenDigitSet_DP(const ArrayType &digits, const int n) {
    const auto str_n = std::to_string(n);
    int dp[str_n.size() + 1] = {};
    dp[str_n.size()] = 1;

    for (int i = str_n.size() - 1; i >= 0; --i) {
        const auto c = str_n[i];
        for (const auto d : digits) {
            if (d < c) {
                dp[i] += std::pow(digits.size(), str_n.size() - i - 1);
            } else if (d == c) {
                dp[i] += dp[i + 1];
            }
        }
    }

    for (std::size_t i = 1; i < str_n.size(); ++i) {
        dp[0] += std::pow(digits.size(), i);
    }
    return dp[0];
}


auto NumbersAtMostNGivenDigitSet(const ArrayType &digits, const int n) {
    const auto str_n = std::to_string(n);
    const auto base = digits.size();
    int largest[str_n.size()] = {};
    std::size_t l = 0;

    for (const auto c : str_n) {
        int index = 0;
        bool match = false;
        for (std::size_t i = 0; i < base; ++i) {
            if (c >= digits[i]) {
                index = i + 1;
                if (c == digits[i]) {
                    match = true;
                }
            }
        }

        largest[l++] = index;
        if (match) {
            continue;
        }

        if (index == 0) {
            for (int j = l - 1; j > 0; --j) {
                if (largest[j] > 0) {
                    break;
                }
                largest[j] += base;
                --largest[j - 1];
            }
        }

        while (l < str_n.size()) {
            largest[l++] = base;
        }
        break;
    }

    int result = 0;
    for (const auto x : largest) {
        result = result * base + x;
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {'1', '3', '5', '7'};
const ArrayType SAMPLE2 = {'1', '4', '9'};
const ArrayType SAMPLE3 = {'7'};


THE_BENCHMARK(NumbersAtMostNGivenDigitSet_DP, SAMPLE1, 100);

SIMPLE_TEST(NumbersAtMostNGivenDigitSet_DP, TestSAMPLE1, 20, SAMPLE1, 100);
SIMPLE_TEST(NumbersAtMostNGivenDigitSet_DP, TestSAMPLE2, 29523, SAMPLE2, 1000000000);
SIMPLE_TEST(NumbersAtMostNGivenDigitSet_DP, TestSAMPLE3, 1, SAMPLE3, 8);


THE_BENCHMARK(NumbersAtMostNGivenDigitSet, SAMPLE1, 100);

SIMPLE_TEST(NumbersAtMostNGivenDigitSet, TestSAMPLE1, 20, SAMPLE1, 100);
SIMPLE_TEST(NumbersAtMostNGivenDigitSet, TestSAMPLE2, 29523, SAMPLE2, 1000000000);
SIMPLE_TEST(NumbersAtMostNGivenDigitSet, TestSAMPLE3, 1, SAMPLE3, 8);
