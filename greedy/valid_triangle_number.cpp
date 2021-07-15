#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Valid Triangle Number
 *
 * @reference   https://leetcode.com/problems/valid-triangle-number/
 *
 * Given an integer array nums, return the number of triplets chosen from the array that
 * can make triangles if we take them as side lengths of a triangle.
 */
auto ValidTriangleNumber(ArrayType nums) {
    std::sort(nums.begin(), nums.end());

    const int SIZE = nums.size();
    int total = 0;
    for (int i = 0; i < SIZE - 2; ++i) {
        auto k = i + 2;
        for (auto j = i + 1; j < SIZE - 1 and nums[i]; ++j) {
            while (k < SIZE and (nums[i] + nums[j] > nums[k])) {
                ++k;
            }
            total += k - j - 1;
        }
    }

    return total;
}


auto ValidTriangleNumber_BinarySearch(ArrayType nums) {
    std::sort(nums.begin(), nums.end());

    const int SIZE = nums.size();
    int total = 0;
    for (int i = 0; i < SIZE - 2; ++i) {
        auto k = i + 2;
        for (auto j = i + 1; j < SIZE - 1 and nums[i]; ++j) {
            const auto lower = std::lower_bound(nums.cbegin() + k, nums.cend(), nums[i] + nums[j]);
            std::cout << k << std::endl;
            k = lower - nums.cbegin();
            total += k - j - 1;
        }
    }

    return total;
}


auto ValidTriangleNumber_TwoPointers(ArrayType nums) {
    std::sort(nums.begin(), nums.end());
    int count = 0;
    for (int k = nums.size() - 1; k >= 1; --k) {
        int low = 0, high = k - 1;
        while (low < high) {
            if (nums[low] + nums[high] > nums[k]) {
                count += (high--) - low;
            } else {
                ++low;
            }
        }

    }
    return count;
}

}//namespace


const ArrayType SAMPLE1 = {0, 0, 0};
const ArrayType SAMPLE2 = {2, 2, 3, 4};
const ArrayType SAMPLE3 = {4, 2, 3, 4};


THE_BENCHMARK(ValidTriangleNumber, SAMPLE1);

SIMPLE_TEST(ValidTriangleNumber, TestSAMPLE1, 0, SAMPLE1);
SIMPLE_TEST(ValidTriangleNumber, TestSAMPLE2, 3, SAMPLE2);
SIMPLE_TEST(ValidTriangleNumber, TestSAMPLE3, 4, SAMPLE3);


THE_BENCHMARK(ValidTriangleNumber_BinarySearch, SAMPLE1);

SIMPLE_TEST(ValidTriangleNumber_BinarySearch, TestSAMPLE1, 0, SAMPLE1);
SIMPLE_TEST(ValidTriangleNumber_BinarySearch, TestSAMPLE2, 3, SAMPLE2);
SIMPLE_TEST(ValidTriangleNumber_BinarySearch, TestSAMPLE3, 4, SAMPLE3);


THE_BENCHMARK(ValidTriangleNumber_TwoPointers, SAMPLE1);

SIMPLE_TEST(ValidTriangleNumber_TwoPointers, TestSAMPLE1, 0, SAMPLE1);
SIMPLE_TEST(ValidTriangleNumber_TwoPointers, TestSAMPLE2, 3, SAMPLE2);
SIMPLE_TEST(ValidTriangleNumber_TwoPointers, TestSAMPLE3, 4, SAMPLE3);
