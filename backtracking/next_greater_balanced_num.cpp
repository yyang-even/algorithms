#include "common_header.h"


namespace {

/**
 * @reference   Next Greater Numerically Balanced Number
 *              https://leetcode.com/problems/next-greater-numerically-balanced-number/
 *
 * An integer x is numerically balanced if for every digit d in the number x, there are exactly d
 * occurrences of that digit in x.
 * Given an integer n, return the smallest numerically balanced number strictly greater than n.
 * 0 <= n <= 10^6
 *
 * @tags    #backtracking #hash-table #sorting #binary-search
 */
auto isBalanced(const std::vector<int> &counts) {
    const int SIZE = counts.size();
    for (int d = 1; d < SIZE; ++d) {
        if (counts[d] and counts[d] != d) {
            return false;
        }
    }
    return true;
}

void generateBalancedNums(const int n,
                          std::vector<int> &counts,
                          std::vector<int> &balanced_nums) {
    if (n and isBalanced(counts)) {
        balanced_nums.push_back(n);
    }

    if (n > 1224444) {
        return;
    }

    const int SIZE = counts.size();
    for (int d = 1; d < SIZE; ++d) {
        if (counts[d] < d) {
            ++counts[d];
            generateBalancedNums(n * 10 + d, counts, balanced_nums);
            --counts[d];
        }
    }
}

auto NextGreaterBalancedNum(const int n) {
    static const auto balanced_nums = []() {
        std::vector<int> balanced_nums;
        std::vector<int> counts(7, 0);
        generateBalancedNums(0, counts, balanced_nums);

        std::sort(balanced_nums.begin(), balanced_nums.end());

        return balanced_nums;
    }();

    return *std::upper_bound(balanced_nums.cbegin(), balanced_nums.cend(), n);
}

} //namespace


THE_BENCHMARK(NextGreaterBalancedNum, 1);

SIMPLE_TEST(NextGreaterBalancedNum, TestSAMPLE1, 22, 1);
SIMPLE_TEST(NextGreaterBalancedNum, TestSAMPLE2, 1333, 1000);
SIMPLE_TEST(NextGreaterBalancedNum, TestSAMPLE3, 3133, 3000);
SIMPLE_TEST(NextGreaterBalancedNum, TestSAMPLE4, 221, 212);
SIMPLE_TEST(NextGreaterBalancedNum, TestSAMPLE5, 4444, 3632);
