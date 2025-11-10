#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Minimum Operations to Convert All Elements to Zero
 *              https://leetcode.com/problems/minimum-operations-to-convert-all-elements-to-zero/
 *
 * You are given an array nums of size n, consisting of non-negative integers. Your task is to apply
 * some (possibly zero) operations on the array so that all elements become 0.
 * In one operation, you can select a subarray [i, j] (where 0 <= i <= j < n) and set all occurrences of
 * the minimum non-negative integer in that subarray to 0.
 * Return the minimum number of operations required to make all elements in the array 0.
 *
 * @tags    #greedy #monotonic-stack
 */
auto MinOperationsToConvertAllToZero(const ArrayType &nums) {
    int result = 0;

    std::stack<int> s;
    for (const auto n : nums) {
        while (not s.empty() and s.top() > n) {
            s.pop();
            ++result;
        }

        if (n) {
            if (s.empty() or s.top() != n) {
                s.push(n);
            }
        }
    }

    return result + s.size();
}

} //namespace


const ArrayType SAMPLE1 = {0, 2};
const ArrayType SAMPLE2 = {3, 1, 2, 1};
const ArrayType SAMPLE3 = {1, 2, 1, 2, 1, 2};


THE_BENCHMARK(MinOperationsToConvertAllToZero, SAMPLE1);

SIMPLE_TEST(MinOperationsToConvertAllToZero, TestSAMPLE1, 1, SAMPLE1);
SIMPLE_TEST(MinOperationsToConvertAllToZero, TestSAMPLE2, 3, SAMPLE2);
SIMPLE_TEST(MinOperationsToConvertAllToZero, TestSAMPLE3, 4, SAMPLE3);
