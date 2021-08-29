#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Patching Array
 *
 * @reference   https://leetcode.com/problems/patching-array/
 *
 * Given a sorted integer array nums and an integer n, add/patch elements to the array
 * such that any number in the range [1, n] inclusive can be formed by the sum of some
 * elements in the array. Return the minimum number of patches required.
 */
auto PatchingArray(const ArrayType &nums, const int n) {
    assert(std::is_sorted(nums.cbegin(), nums.cend()));

    long miss = 1, result = 0;
    std::size_t i = 0;
    while (miss <= n) {
        if (i < nums.size() and nums[i] <= miss) {
            miss += nums[i++];
        } else {
            miss += miss;
            ++result;
        }
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {1, 3};
const ArrayType SAMPLE2 = {1, 5, 10};
const ArrayType SAMPLE3 = {1, 2, 2};


THE_BENCHMARK(PatchingArray, SAMPLE1, 6);

SIMPLE_TEST(PatchingArray, TestSAMPLE1, 1, SAMPLE1, 6);
SIMPLE_TEST(PatchingArray, TestSAMPLE2, 2, SAMPLE2, 20);
SIMPLE_TEST(PatchingArray, TestSAMPLE3, 0, SAMPLE3, 5);
