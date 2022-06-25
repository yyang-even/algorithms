#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Construct Target Array With Multiple Sums
 *
 * @reference   https://leetcode.com/problems/construct-target-array-with-multiple-sums/
 *
 * You are given an array target of n integers. From a starting array arr consisting of n 1's,
 * you may perform the following procedure :
 *  let x be the sum of all elements currently in your array.
 *  choose index i, such that 0 <= i < n and set the value of arr at index i to x.
 *  You may repeat this procedure as many times as needed.
 * Return true if it is possible to construct the target array from arr, otherwise, return false.
 */
auto ConstructTargetArray(const ArrayType &target) {
    std::priority_queue<int> max_heap(target.cbegin(), target.cend());
    auto total = std::accumulate(target.cbegin(), target.cend(), 0l);

    while (true) {
        const auto maximum = max_heap.top();
        max_heap.pop();

        total -= maximum;
        if (maximum == 1 or total == 1) {
            return true;
        }

        if (maximum < total or total == 0 or maximum % total == 0) {
            return false;
        }

        const auto new_element = maximum % total;
        total += new_element;
        max_heap.push(new_element);
    }
}

} //namespace


const ArrayType SAMPLE1 = {9, 3, 5};
const ArrayType SAMPLE2 = {1, 1, 1, 2};
const ArrayType SAMPLE3 = {8, 5};
const ArrayType SAMPLE4 = {5};
const ArrayType SAMPLE5 = {1};
const ArrayType SAMPLE6 = {1, 1000000000};


THE_BENCHMARK(ConstructTargetArray, SAMPLE1);

SIMPLE_TEST(ConstructTargetArray, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(ConstructTargetArray, TestSAMPLE2, false, SAMPLE2);
SIMPLE_TEST(ConstructTargetArray, TestSAMPLE3, true, SAMPLE3);
SIMPLE_TEST(ConstructTargetArray, TestSAMPLE4, false, SAMPLE4);
SIMPLE_TEST(ConstructTargetArray, TestSAMPLE5, true, SAMPLE5);
SIMPLE_TEST(ConstructTargetArray, TestSAMPLE6, true, SAMPLE6);
