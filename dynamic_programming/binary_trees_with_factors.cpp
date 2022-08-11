#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Binary Trees With Factors
 *
 * @reference   https://leetcode.com/problems/binary-trees-with-factors/
 *
 * Given an array of unique integers, arr, where each integer arr[i] is strictly greater than 1.
 * We make a binary tree using these integers, and each number may be used for any number of times. Each
 * non-leaf node's value should be equal to the product of the values of its children.
 * Return the number of binary trees we can make. The answer may be too large so return the answer
 * modulo 10^9 + 7.
 */
int NumFactoredBinaryTrees(ArrayType arr) {
    std::sort(arr.begin(), arr.end());

    std::unordered_map<int, long> m;
    long result = 0;
    for (const auto n : arr) {
        long temp = 1;
        for (const auto [i, c] : m) {
            if (n % i == 0) {
                const auto other = n / i;
                const auto iter = m.find(other);
                if (iter != m.cend()) {
                    temp += (c * iter->second);
                }
            }
        }

        temp %= LARGE_PRIME;
        result += temp;
        m[n] = temp;
    }

    return result % LARGE_PRIME;
}

} //namespace


const ArrayType SAMPLE1 = {2, 4};
const ArrayType SAMPLE2 = {2, 4, 5, 10};


THE_BENCHMARK(NumFactoredBinaryTrees, SAMPLE1);

SIMPLE_TEST(NumFactoredBinaryTrees, TestSAMPLE1, 3, SAMPLE1);
SIMPLE_TEST(NumFactoredBinaryTrees, TestSAMPLE2, 7, SAMPLE2);
