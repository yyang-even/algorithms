#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Given a sorted array and a number x, find the pair in array whose sum is closest to x
 *
 * @reference   https://www.geeksforgeeks.org/given-sorted-array-number-x-find-pair-array-whose-sum-closest-x/
 *
 * Given a sorted array and a number x, find a pair in array whose sum is closest to x.
 *
 * @reference   2 Sum Closest
 *              https://aaronice.gitbook.io/lintcode/high_frequency/2sum_closest
 *
 * Given an array nums of n integers, find two integers in nums such that the sum is
 * closest to a given number, target. Return the difference between the sum of the two
 * integers and the target.
 *
 * @reference   Two elements whose sum is closest to zero
 *              https://www.geeksforgeeks.org/two-elements-whose-sum-is-closest-to-zero/
 */
auto ClosestSumPair_Sorted_TwoPointer(const ArrayType &elements,
                                      const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));

    auto diff = std::numeric_limits<ArrayType::value_type>::max();
    std::pair<ArrayType::value_type, ArrayType::value_type> output;
    if (not elements.empty()) {
        auto left = elements.cbegin();
        auto right = std::prev(elements.cend());

        while (left != right and diff) {
            const auto sum = *left + *right;
            const auto new_diff = std::abs(sum - x);
            if (new_diff < diff) {
                diff = new_diff;
                output = std::pair(*left, *right);
            }

            if (sum < x) {
                ++left;
            } else {
                --right;
            }
        }
    }

    return output;
}

inline auto
ClosestSumPair_Sort(ArrayType elements, const ArrayType::value_type x) {
    std::sort(elements.begin(), elements.end());
    return ClosestSumPair_Sorted_TwoPointer(elements, x);
}


/**
 * @reference   3Sum Closest
 *              https://leetcode.com/problems/3sum-closest/
 *
 * Given an array nums of n integers and an integer target, find three integers in nums
 * such that the sum is closest to target. Return the sum of the three integers. You may
 * assume that each input would have exactly one solution.
 */
auto ThreeSum(ArrayType nums, const int target) {
    std::sort(nums.begin(), nums.end());

    int min_diff = INT_MAX;
    int result = 0;
    for (std::size_t i = 0; i < nums.size() and min_diff; ++i) {
        int left = i + 1;
        int right = nums.size() - 1;
        while (left < right) {
            const int sum = nums[i] + nums[left] + nums[right];
            if (std::abs(target - sum) < min_diff) {
                min_diff = std::abs(target - sum);
                result = sum;
            }
            if (sum < target) {
                ++left;
            } else {
                --right;
            }
        }
    }

    return result;
}


/**
 * @reference   Two Sum Less Than K
 *              https://wentao-shao.gitbook.io/leetcode/two-pointers/1099.two-sum-less-than-k
 *
 * Given an array A of integers and integer K, return the maximum S such that there
 * exists i < j with A[i] + A[j] = S and S < K. If no i, j exist satisfying this
 * equation, return -1.
 */
auto TwoSumLessThan(ArrayType nums, const int K) {
    std::sort(nums.begin(), nums.end());

    int left = 0;
    int right = nums.size() - 1;
    int result = -1;
    while (left < right) {
        const auto sum = nums[left] + nums[right];
        if (sum >= K) {
            --right;
        } else {
            result = std::max(result, sum);
            ++left;
        }
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {10, 22, 28, 29, 30, 40};
const ArrayType SAMPLE2 = {1, 3, 4, 7, 10};
const ArrayType SAMPLE3 = {1, 60, -10, 70, -80, 85};


THE_BENCHMARK(ClosestSumPair_Sorted_TwoPointer, SAMPLE1, 54);

SIMPLE_TEST(ClosestSumPair_Sorted_TwoPointer, TestSample1, std::pair(22, 30),
            SAMPLE1, 54);
SIMPLE_TEST(ClosestSumPair_Sorted_TwoPointer, TestSample2, std::pair(4, 10),
            SAMPLE2, 15);
SIMPLE_TEST(ClosestSumPair_Sort, TestSample3, std::pair(-80, 85), SAMPLE3, 0);


const ArrayType SAMPLE4 = {-1, 2, 1, -4};


THE_BENCHMARK(ThreeSum, SAMPLE4, 1);

SIMPLE_TEST(ThreeSum, TestSample4, 2, SAMPLE4, 1);


const ArrayType SAMPLE1L = {34, 23, 1, 24, 75, 33, 54, 8};
const ArrayType SAMPLE2L = {10, 20, 30};


THE_BENCHMARK(TwoSumLessThan, SAMPLE1L, 60);

SIMPLE_TEST(TwoSumLessThan, TestSample1, 58, SAMPLE1L, 60);
SIMPLE_TEST(TwoSumLessThan, TestSample2, -1, SAMPLE2L, 15);
