#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** 132 Pattern
 *
 * @reference   https://leetcode.com/problems/132-pattern/
 *
 * Given an array of n integers nums, a 132 pattern is a subsequence of three integers nums[i], nums[j]
 * and nums[k] such that i < j < k and nums[i] < nums[k] < nums[j].
 * Return true if there is a 132 pattern in nums, otherwise, return false.
 */
auto has132Pattern(const ArrayType &nums) {
    int p2 = INT_MIN;
    std::stack<int> s;

    for (int i = nums.size() - 1; i >= 0; --i) {
        if (nums[i] < p2) {
            return true;
        } else {
            while (not s.empty() and nums[i] > s.top()) {
                p2 = s.top();
                s.pop();
            }
        }

        s.push(nums[i]);
    }

    return false;
}

} //namespace


const ArrayType SAMPLE1 = {1, 2, 3, 4};
const ArrayType SAMPLE2 = {3, 1, 4, 2};
const ArrayType SAMPLE3 = {-1, 3, 2, 0};
const ArrayType SAMPLE4 = {1, 0, 1, -4, -3};
const ArrayType SAMPLE5 = {3, 5, 0, 3, 4};


THE_BENCHMARK(has132Pattern, SAMPLE1);

SIMPLE_TEST(has132Pattern, TestSAMPLE1, false, SAMPLE1);
SIMPLE_TEST(has132Pattern, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(has132Pattern, TestSAMPLE3, true, SAMPLE3);
SIMPLE_TEST(has132Pattern, TestSAMPLE4, false, SAMPLE4);
SIMPLE_TEST(has132Pattern, TestSAMPLE5, true, SAMPLE5);
