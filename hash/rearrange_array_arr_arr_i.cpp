#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Rearrange an array so that arr[i] becomes arr[arr[i]] with O(1) extra space
 *
 * @reference   https://www.geeksforgeeks.org/rearrange-given-array-place/
 *
 * Given an array arr[] of size n where every element is in range from 0 to n-1.
 * Rearrange the given array so that arr[i] becomes arr[arr[i]]. This should be done
 * with O(1) extra space.
 */
auto RearrangeArrayInPlace(ArrayType values) {
    std::transform(values.cbegin(), values.cend(),
    values.begin(), [&values](const auto v) {
        return v + values[v] % values.size() * values.size();
    });

    std::transform(values.cbegin(), values.cend(),
    values.begin(), [&values](const auto v) {
        return v / values.size();
    });

    return values;
}


/**
 * @reference   Shuffle String
 *              https://leetcode.com/problems/shuffle-string/
 *
 * You are given a string s and an integer array indices of the same length. The string s
 * will be shuffled such that the character at the ith position moves to indices[i] in the
 * shuffled string.
 * Return the shuffled string.
 */
auto ShuffleString_CyclicSort(std::string s, ArrayType indices) {
    for (std::size_t i = 0; i < indices.size(); ++i) {
        while (indices[i] != i) {
            std::swap(s[i], s[indices[i]]);
            std::swap(indices[i], indices[indices[i]]);

        }
    }

    return s;
}

}//namespace


const ArrayType SAMPLE1 = {3, 2, 0, 1};
const ArrayType EXPECTED1 = {1, 0, 3, 2};

const ArrayType SAMPLE2 = {4, 0, 2, 1, 3};
const ArrayType EXPECTED2 = {3, 4, 2, 0, 1};

const ArrayType SAMPLE3 = {0, 1, 2, 3};
const ArrayType EXPECTED3 = {0, 1, 2, 3};


THE_BENCHMARK(RearrangeArrayInPlace, SAMPLE1);

SIMPLE_TEST(RearrangeArrayInPlace, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(RearrangeArrayInPlace, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(RearrangeArrayInPlace, TestSAMPLE3, EXPECTED3, SAMPLE3);


const ArrayType SAMPLE1S = {4, 5, 6, 7, 0, 2, 1, 3};


THE_BENCHMARK(ShuffleString_CyclicSort, "codeleet", SAMPLE1S);

SIMPLE_TEST(ShuffleString_CyclicSort, TestSAMPLE1, "leetcode", "codeleet", SAMPLE1S);
SIMPLE_TEST(ShuffleString_CyclicSort, TestSAMPLE2, "abcd", "abcd", SAMPLE3);
