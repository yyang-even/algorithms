#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Find the Minimum length Unsorted Subarray, sorting which makes the complete array sorted
 *
 * @reference   https://www.geeksforgeeks.org/minimum-length-unsorted-subarray-sorting-which-makes-the-complete-array-sorted/
 *
 * Given an unsorted array arr[0..n-1] of size n, find the minimum length subarray
 * arr[s..e] such that sorting this subarray makes the whole array sorted.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 17.6.
 */
int MinUnsortedSubarray(const ArrayType &elements) {
    assert(not elements.empty());

    auto left_last = elements.cbegin();
    auto right_begin = std::prev(elements.cend());
    for (; left_last != right_begin and
         * left_last <= *std::next(left_last); ++left_last);

    if (left_last == right_begin) {
        return 0;
    }

    for (; right_begin != left_last and
         * std::prev(right_begin) <= *right_begin; --right_begin);

    const auto next_of_right_begin = std::next(right_begin);
    const auto [min_iter, max_iter] =
        std::minmax_element(left_last, next_of_right_begin);

    const auto mid_begin = std::upper_bound(elements.cbegin(), left_last, *min_iter);

    const auto mid_end =
        std::lower_bound(next_of_right_begin, elements.cend(), *max_iter);

    return std::distance(mid_begin, mid_end);
}

}//namespace


const ArrayType SAMPLE1 = {10, 12, 20, 30, 25, 40, 32, 31, 35, 50, 60};
const ArrayType SAMPLE2 = {0, 1, 15, 25, 6, 7, 30, 40, 50};
const ArrayType SAMPLE3 = {0, 1};
const ArrayType SAMPLE4 = {0, 1, 6, 15, 7, 25, 30, 40, 50};
const ArrayType SAMPLE5 = {0, 1, 6, -1, 55, 25, 30, 40, 50};


THE_BENCHMARK(MinUnsortedSubarray, SAMPLE1);

SIMPLE_TEST(MinUnsortedSubarray, TestSAMPLE1, 6, SAMPLE1);
SIMPLE_TEST(MinUnsortedSubarray, TestSAMPLE2, 4, SAMPLE2);
SIMPLE_TEST(MinUnsortedSubarray, TestSAMPLE3, 0, SAMPLE3);
SIMPLE_TEST(MinUnsortedSubarray, TestSAMPLE4, 2, SAMPLE4);
SIMPLE_TEST(MinUnsortedSubarray, TestSAMPLE5, SAMPLE5.size(), SAMPLE5);
