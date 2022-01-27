#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Kth Missing Positive Number
 *
 * @reference   https://leetcode.com/problems/kth-missing-positive-number/
 *
 * Given an array arr of positive integers sorted in a strictly increasing order, and an
 * integer k.
 * Find the kth positive integer that is missing from this array.
 */
auto KthMissing(const ArrayType &nums, const int k) {
    int l = 0, r = nums.size();
    while (l < r) {
        const auto m = (l + r) / 2;
        if (nums[m] - 1 - m < k) {
            l = m + 1;
        } else {
            r = m;
        }
    }

    return l + k;
}

}//namespace


const ArrayType SAMPLE1 = {2, 3, 4, 7, 11};
const ArrayType SAMPLE2 = {1, 2, 3, 4};


THE_BENCHMARK(KthMissing, SAMPLE1, 5);

SIMPLE_TEST(KthMissing, TestSAMPLE1, 9, SAMPLE1, 5);
SIMPLE_TEST(KthMissing, TestSAMPLE2, 6, SAMPLE2, 2);
