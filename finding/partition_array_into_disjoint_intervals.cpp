#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Partition Array into Disjoint Intervals
 *
 * @reference   https://leetcode.com/problems/partition-array-into-disjoint-intervals/
 *
 * Given an array nums, partition it into two (contiguous) subarrays left and right so
 * that:
 *  Every element in left is less than or equal to every element in right.
 *  left and right are non-empty.
 *  left has the smallest possible size.
 * Return the length of left after such a partitioning.  It is guaranteed that such a
 * partitioning exists.
 */
int PartitionArrayIntoDisjointIntervals(const ArrayType &nums) {
    int mins_till_end[nums.size()] = {};
    int current_min = INT_MAX;
    for (int i = nums.size() - 1; i >= 0; --i) {
        current_min = std::min(current_min, nums[i]);
        mins_till_end[i] = current_min;
    }

    int max = INT_MIN;
    for (std::size_t i = 0; i < nums.size(); ++i) {
        max = std::max(max, nums[i]);
        if (max <= mins_till_end[i + 1]) {
            return i + 1;
        }
    }

    return -1;
}


int PartitionArrayIntoDisjointIntervals_O1Space(const ArrayType &nums) {
    auto current_max = nums.front();
    auto all_time_max = current_max;
    int result = 1;

    for (std::size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] < current_max) {
            result = i + 1;
            current_max = all_time_max;
        } else {
            all_time_max = std::max(all_time_max, nums[i]);
        }
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {5, 0, 3, 8, 6};
const ArrayType SAMPLE2 = {1, 1, 1, 0, 6, 12};


THE_BENCHMARK(PartitionArrayIntoDisjointIntervals, SAMPLE1);

SIMPLE_TEST(PartitionArrayIntoDisjointIntervals, TestSAMPLE1, 3, SAMPLE1);
SIMPLE_TEST(PartitionArrayIntoDisjointIntervals, TestSAMPLE2, 4, SAMPLE2);


THE_BENCHMARK(PartitionArrayIntoDisjointIntervals_O1Space, SAMPLE1);

SIMPLE_TEST(PartitionArrayIntoDisjointIntervals_O1Space, TestSAMPLE1, 3, SAMPLE1);
SIMPLE_TEST(PartitionArrayIntoDisjointIntervals_O1Space, TestSAMPLE2, 4, SAMPLE2);
