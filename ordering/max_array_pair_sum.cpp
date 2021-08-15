#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Array Partition I
 *
 * @reference   https://leetcode.com/problems/array-partition-i/
 *
 * Given an integer array nums of 2n integers, group these integers into n pairs
 * (a1, b1), (a2, b2), ..., (an, bn) such that the sum of min(ai, bi) for all i is
 * maximized. Return the maximized sum.
 * -10^4 <= nums[i] <= 10^4
 */
auto MaxArrayPairSum(ArrayType nums) {
    std::sort(nums.begin(), nums.end());

    const auto N = nums.size();
    int sum = 0;
    for (std::size_t i = 0; i < N; i += 2) {
        sum += nums[i];
    }

    return sum;
}


auto MaxArrayPairSum_CountingSort(const ArrayType &nums) {
    int buckets[20001] = {};

    for (const auto x : nums) {
        ++buckets[x + 10000];
    }

    int sum = 0;
    std::size_t i = 0;
    for (int x = 0; i < nums.size();) {
        if (buckets[x] == 0) {
            ++x;
        } else {
            if (i++ % 2 == 0) {
                sum += x - 10000;
            }

            --buckets[x];
        }
    }

    return sum;
}

}//namespace


const ArrayType SAMPLE1 = {1, 4, 3, 2};
const ArrayType SAMPLE2 = {6, 2, 6, 5, 1, 2};


THE_BENCHMARK(MaxArrayPairSum, SAMPLE1);

SIMPLE_TEST(MaxArrayPairSum, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(MaxArrayPairSum, TestSAMPLE2, 9, SAMPLE2);


THE_BENCHMARK(MaxArrayPairSum_CountingSort, SAMPLE1);

SIMPLE_TEST(MaxArrayPairSum_CountingSort, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(MaxArrayPairSum_CountingSort, TestSAMPLE2, 9, SAMPLE2);
