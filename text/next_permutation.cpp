#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Next Permutation
 *
 * @reference   https://leetcode.com/problems/next-permutation/
 *
 * Implement next permutation, which rearranges numbers into the lexicographically next
 * greater permutation of numbers. If such an arrangement is not possible, it must
 * rearrange it as the lowest possible order (i.e., sorted in ascending order). The
 * replacement must be in place and use only constant extra memory.
 */
auto NextPermutation(ArrayType nums) {
    int i = nums.size() - 2;
    while (i >= 0 and nums[i + 1] <= nums[i]) {
        --i;
    }

    if (i >= 0) {
        int j = nums.size() - 1;
        while (nums[j] <= nums[i]) {
            --j;
        }
        std::swap(nums[i], nums[j]);
    }

    std::reverse(nums.begin() + i + 1, nums.end());
    return nums;
}


auto NextPermutation_Stack(ArrayType nums) {
    std::stack<std::pair<int, int>> s;
    int tmp = -1;
    for (int i = nums.size() - 1; i >= 0; --i) {
        while (not s.empty() and nums[i] < s.top().first) {
            tmp = s.top().second;
            s.pop();
        }

        if (tmp != -1) {
            std::swap(nums[i], nums[tmp]);
            break;
        }

        if (s.empty() or nums[i] > s.top().first) {
            s.emplace(nums[i], i);
        }
    }

    std::reverse(nums.begin() + tmp + 1, nums.end());
    return nums;
}

}//namespace


const ArrayType SAMPLE1 = {1, 2, 3};
const ArrayType EXPECTED1 = {1, 3, 2};

const ArrayType SAMPLE2 = {3, 2, 1};
const ArrayType EXPECTED2 = {1, 2, 3};

const ArrayType SAMPLE3 = {1, 1, 5};
const ArrayType EXPECTED3 = {1, 5, 1};


THE_BENCHMARK(NextPermutation, SAMPLE1);

SIMPLE_TEST(NextPermutation, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(NextPermutation, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(NextPermutation, TestSAMPLE3, EXPECTED3, SAMPLE3);


THE_BENCHMARK(NextPermutation_Stack, SAMPLE1);

SIMPLE_TEST(NextPermutation_Stack, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(NextPermutation_Stack, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(NextPermutation_Stack, TestSAMPLE3, EXPECTED3, SAMPLE3);
