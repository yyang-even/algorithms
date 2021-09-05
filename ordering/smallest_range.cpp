#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Smallest Range I
 *
 * @reference   https://leetcode.com/problems/smallest-range-i/
 *
 * You are given an integer array nums and an integer k. In one operation, you can choose
 * any index i where 0 <= i < nums.length and change nums[i] to nums[i] + x where x is an
 * integer from the range [-k, k]. You can apply this operation at most once for each
 * index i. The score of nums is the difference between the maximum and minimum elements
 * in nums. Return the minimum score of nums after applying the mentioned operation at
 * most once for each index in it.
 */
inline auto SmallestRangeKRange(const ArrayType &nums, const int k) {
    assert(not nums.empty());

    const auto [min_iter, max_iter] = std::minmax_element(nums.cbegin(), nums.cend());
    return std::max(*max_iter - *min_iter - k * 2, 0);
}


/**
 * @reference   Smallest Range II
 *              https://leetcode.com/problems/smallest-range-ii/
 *
 * You are given an integer array nums and an integer k. For each index i where
 * 0 <= i < nums.length, change nums[i] to be either nums[i] + k or nums[i] - k. The
 * score of nums is the difference between the maximum and minimum elements in nums.
 * Return the minimum score of nums after changing the values at each index.
 */
auto SmallestRangeK(ArrayType nums, const int k) {
    const auto N = nums.size();
    std::sort(nums.begin(), nums.end());

    auto result = nums.back() - nums.front();
    for (std::size_t i = 0; i + 1 < N; ++i) {
        const auto high = std::max(nums.back() - k, nums[i] + k);
        const auto low = std::min(nums.front() + k, nums[i + 1] - k);
        result = std::min(result, high - low);
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {1};
const ArrayType SAMPLE2 = {0, 10};
const ArrayType SAMPLE3 = {1, 3, 6};


THE_BENCHMARK(SmallestRangeKRange, SAMPLE1, 0);

SIMPLE_TEST(SmallestRangeKRange, TestSAMPLE1, 0, SAMPLE1, 0);
SIMPLE_TEST(SmallestRangeKRange, TestSAMPLE2, 6, SAMPLE2, 2);
SIMPLE_TEST(SmallestRangeKRange, TestSAMPLE3, 0, SAMPLE3, 3);


THE_BENCHMARK(SmallestRangeK, SAMPLE1, 0);

SIMPLE_TEST(SmallestRangeK, TestSAMPLE1, 0, SAMPLE1, 0);
SIMPLE_TEST(SmallestRangeK, TestSAMPLE2, 6, SAMPLE2, 2);
SIMPLE_TEST(SmallestRangeK, TestSAMPLE3, 3, SAMPLE3, 3);
