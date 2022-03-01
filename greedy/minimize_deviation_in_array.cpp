#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Minimize Deviation in Array
 *
 * @reference   https://leetcode.com/problems/minimize-deviation-in-array/
 *
 * You are given an array nums of n positive integers.
 * You can perform two types of operations on any element of the array any number of times:
 *  If the element is even, divide it by 2.
 *      For example, if the array is [1,2,3,4], then you can do this operation on the last
 *      element, and the array will be [1,2,3,2].
 *  If the element is odd, multiply it by 2.
 *      For example, if the array is [1,2,3,4], then you can do this operation on the first
 *      element, and the array will be [2,2,3,4].
 * The deviation of the array is the maximum difference between any two elements in the array.
 * Return the minimum deviation the array can have after performing some number of operations.
 */
auto MinimizeDeviation(const ArrayType &nums) {
    std::set<int> s;
    for (const auto n : nums) {
        s.insert(n % 2 ? n * 2 : n);
    }

    auto result = *s.crbegin() - *s.cbegin();
    while (*s.crbegin() % 2 == 0) {
        s.insert(*s.crbegin() / 2);
        s.erase(*s.crbegin());
        result = std::min(result, *s.crbegin() - *s.cbegin());
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {1, 2, 3, 4};
const ArrayType SAMPLE2 = {4, 1, 5, 20, 3};
const ArrayType SAMPLE3 = {2, 10, 8};
const ArrayType SAMPLE4 = {4, 9, 4, 5};


THE_BENCHMARK(MinimizeDeviation, SAMPLE1);

SIMPLE_TEST(MinimizeDeviation, TestSAMPLE1, 1, SAMPLE1);
SIMPLE_TEST(MinimizeDeviation, TestSAMPLE2, 3, SAMPLE2);
SIMPLE_TEST(MinimizeDeviation, TestSAMPLE3, 3, SAMPLE3);
SIMPLE_TEST(MinimizeDeviation, TestSAMPLE4, 5, SAMPLE4);
