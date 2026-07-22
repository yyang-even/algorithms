#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Minimum Pair Removal to Sort Array I
 *              https://leetcode.com/problems/minimum-pair-removal-to-sort-array-i/
 * @reference   Minimum Pair Removal to Sort Array II
 *              https://leetcode.com/problems/minimum-pair-removal-to-sort-array-ii/
 *
 * Given an array nums, you can perform the following operation any number of times:
 *  Select the adjacent pair with the minimum sum in nums. If multiple such pairs exist, choose the
 *  leftmost one.
 *  Replace the pair with their sum.
 * Return the minimum number of operations needed to make the array non-decreasing.
 * An array is said to be non-decreasing if each element is greater than or equal to its previous
 * element (if it exists).
 *
 * @tags    #singly-linked-list #doubly-linked-list #linked-list-array #ordered-set #priority-queue
 */
auto MinPairRemovalToSortArray(const ArrayType &nums) {
    int result = 0;

    std::list copy(nums.cbegin(), nums.cend());

    while (copy.size() > 1) {
        auto min_sum_iter = copy.begin();
        auto min_sum = *min_sum_iter + *(std::next(min_sum_iter));
        bool is_ordered = *min_sum_iter <= *std::next(min_sum_iter);

        for (auto iter = std::next(std::next(copy.begin())); iter != copy.end(); ++iter) {
            const auto prev_iter = std::prev(iter);
            const auto sum = *prev_iter + *iter;
            if (sum < min_sum) {
                min_sum = sum;
                min_sum_iter = prev_iter;
            }

            if (*prev_iter > *iter) {
                is_ordered = false;
            }
        }

        if (is_ordered) {
            break;
        }

        ++result;
        *min_sum_iter = min_sum;
        copy.erase(std::next(min_sum_iter));
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {5, 2, 3, 1};
const ArrayType SAMPLE2 = {1, 2, 2};


THE_BENCHMARK(MinPairRemovalToSortArray, SAMPLE1);

SIMPLE_TEST(MinPairRemovalToSortArray, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(MinPairRemovalToSortArray, TestSAMPLE2, 0, SAMPLE2);
