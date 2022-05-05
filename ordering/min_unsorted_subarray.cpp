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
    for (; left_last != right_begin and *left_last <= *std::next(left_last); ++left_last)
        ;

    if (left_last == right_begin) {
        return 0;
    }

    for (; right_begin != left_last and *std::prev(right_begin) <= *right_begin; --right_begin)
        ;

    const auto next_of_right_begin = std::next(right_begin);
    const auto [min_iter, max_iter] = std::minmax_element(left_last, next_of_right_begin);

    const auto mid_begin = std::upper_bound(elements.cbegin(), left_last, *min_iter);

    const auto mid_end = std::lower_bound(next_of_right_begin, elements.cend(), *max_iter);

    return std::distance(mid_begin, mid_end);
}


/**
 * @reference   Shortest Unsorted Continuous Subarray
 *              https://leetcode.com/problems/shortest-unsorted-continuous-subarray/
 *
 * Given an integer array nums, you need to find one continuous subarray that if you only
 * sort this subarray in ascending order, then the whole array will be sorted in ascending
 * order.
 * Return the shortest such subarray and output its length.
 * Follow up: Can you solve it in O(n) time complexity?
 */
auto MinUnsortedSubarray_MonotonicStack(const ArrayType &nums) {
    const int N = nums.size();
    std::stack<int> s;

    int left = N;
    for (int i = 0; i < N; ++i) {
        while (not s.empty() and nums[s.top()] > nums[i]) {
            left = std::min(left, s.top());
            s.pop();
        }
        s.push(i);
    }

    s = std::stack<int> {};
    int right = 0;
    for (int i = N - 1; i >= 0; --i) {
        while (not s.empty() and nums[s.top()] < nums[i]) {
            right = std::max(right, s.top());
            s.pop();
        }
        s.push(i);
    }

    return right - left > 0 ? right - left + 1 : 0;
}


auto MinUnsortedSubarray_MinMax(const ArrayType &nums) {
    int last = -2;
    int maximum = INT_MIN;
    for (std::size_t i = 0; i < nums.size(); ++i) {
        if (nums[i] >= maximum) {
            maximum = nums[i];
        } else {
            last = i;
        }
    }

    int first = -1;
    int minimum = INT_MAX;
    for (int i = nums.size() - 1; i >= 0; --i) {
        if (nums[i] <= minimum) {
            minimum = nums[i];
        } else {
            first = i;
        }
    }

    return last + 1 - first;
}


auto MinUnsortedSubarray_Sort(const ArrayType &nums) {
    auto copy = nums;
    std::sort(copy.begin(), copy.end());

    std::size_t left = 0;
    while (left < nums.size() and nums[left] == copy[left]) {
        ++left;
    }

    std::size_t right = nums.size() - 1;
    while (right > left and nums[right] == copy[right]) {
        --right;
    }

    return right + 1 - left;
}

} //namespace


const ArrayType SAMPLE1 = {10, 12, 20, 30, 25, 40, 32, 31, 35, 50, 60};
const ArrayType SAMPLE2 = {0, 1, 15, 25, 6, 7, 30, 40, 50};
const ArrayType SAMPLE3 = {0, 1};
const ArrayType SAMPLE4 = {0, 1, 6, 15, 7, 25, 30, 40, 50};
const ArrayType SAMPLE5 = {0, 1, 6, -1, 55, 25, 30, 40, 50};
const ArrayType SAMPLE6 = {2, 6, 4, 8, 10, 9, 15};


THE_BENCHMARK(MinUnsortedSubarray, SAMPLE1);

SIMPLE_TEST(MinUnsortedSubarray, TestSAMPLE1, 6, SAMPLE1);
SIMPLE_TEST(MinUnsortedSubarray, TestSAMPLE2, 4, SAMPLE2);
SIMPLE_TEST(MinUnsortedSubarray, TestSAMPLE3, 0, SAMPLE3);
SIMPLE_TEST(MinUnsortedSubarray, TestSAMPLE4, 2, SAMPLE4);
SIMPLE_TEST(MinUnsortedSubarray, TestSAMPLE5, SAMPLE5.size(), SAMPLE5);
SIMPLE_TEST(MinUnsortedSubarray, TestSAMPLE6, 5, SAMPLE6);


THE_BENCHMARK(MinUnsortedSubarray_MonotonicStack, SAMPLE1);

SIMPLE_TEST(MinUnsortedSubarray_MonotonicStack, TestSAMPLE1, 6, SAMPLE1);
SIMPLE_TEST(MinUnsortedSubarray_MonotonicStack, TestSAMPLE2, 4, SAMPLE2);
SIMPLE_TEST(MinUnsortedSubarray_MonotonicStack, TestSAMPLE3, 0, SAMPLE3);
SIMPLE_TEST(MinUnsortedSubarray_MonotonicStack, TestSAMPLE4, 2, SAMPLE4);
SIMPLE_TEST(MinUnsortedSubarray_MonotonicStack, TestSAMPLE5, SAMPLE5.size(), SAMPLE5);
SIMPLE_TEST(MinUnsortedSubarray_MonotonicStack, TestSAMPLE6, 5, SAMPLE6);


THE_BENCHMARK(MinUnsortedSubarray_MinMax, SAMPLE1);

SIMPLE_TEST(MinUnsortedSubarray_MinMax, TestSAMPLE1, 6, SAMPLE1);
SIMPLE_TEST(MinUnsortedSubarray_MinMax, TestSAMPLE2, 4, SAMPLE2);
SIMPLE_TEST(MinUnsortedSubarray_MinMax, TestSAMPLE3, 0, SAMPLE3);
SIMPLE_TEST(MinUnsortedSubarray_MinMax, TestSAMPLE4, 2, SAMPLE4);
SIMPLE_TEST(MinUnsortedSubarray_MinMax, TestSAMPLE5, SAMPLE5.size(), SAMPLE5);
SIMPLE_TEST(MinUnsortedSubarray_MinMax, TestSAMPLE6, 5, SAMPLE6);


THE_BENCHMARK(MinUnsortedSubarray_Sort, SAMPLE1);

SIMPLE_TEST(MinUnsortedSubarray_Sort, TestSAMPLE1, 6, SAMPLE1);
SIMPLE_TEST(MinUnsortedSubarray_Sort, TestSAMPLE2, 4, SAMPLE2);
SIMPLE_TEST(MinUnsortedSubarray_Sort, TestSAMPLE3, 0, SAMPLE3);
SIMPLE_TEST(MinUnsortedSubarray_Sort, TestSAMPLE4, 2, SAMPLE4);
SIMPLE_TEST(MinUnsortedSubarray_Sort, TestSAMPLE5, SAMPLE5.size(), SAMPLE5);
SIMPLE_TEST(MinUnsortedSubarray_Sort, TestSAMPLE6, 5, SAMPLE6);
