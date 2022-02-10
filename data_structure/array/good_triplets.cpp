#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Count Good Triplets
 *
 * @reference   https://leetcode.com/problems/count-good-triplets/
 *
 * Given an array of integers arr, and three integers a, b and c. You need to find the
 * number of good triplets.
 * A triplet (arr[i], arr[j], arr[k]) is good if the following conditions are true:
 *  0 <= i < j < k < arr.length
 *  |arr[i] - arr[j]| <= a
 *  |arr[j] - arr[k]| <= b
 *  |arr[i] - arr[k]| <= c
 * Where |x| denotes the absolute value of x.
 * Return the number of good triplets.
 */
auto GoodTriplets(const ArrayType &nums, const int a, const int b, const int c) {
    int result = 0;
    const int N = nums.size();
    for (int i = 0; i < N - 2; ++i) {
        for (auto j = i + 1; j < N - 1; ++j) {
            if (std::abs(nums[i] - nums[j]) <= a) {
                for (auto k = j + 1; k < N; ++k) {
                    if (std::abs(nums[j] - nums[k]) <= b and
                        std::abs(nums[k] - nums[i]) <= c) {
                        ++result;
                    }
                }
            }
        }
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {3, 0, 1, 1, 9, 7};
const ArrayType SAMPLE2 = {1, 1, 2, 2, 3};


THE_BENCHMARK(GoodTriplets, SAMPLE1, 7, 2, 3);

SIMPLE_TEST(GoodTriplets, TestSAMPLE1, 4, SAMPLE1, 7, 2, 3);
SIMPLE_TEST(GoodTriplets, TestSAMPLE2, 0, SAMPLE2, 0, 0, 1);
