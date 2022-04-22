#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Program to check if an array is sorted or not (Iterative and Recursive)
 *
 * @reference   https://www.geeksforgeeks.org/program-check-array-sorted-not-iterative-recursive/
 */
inline auto isSortedRecursive(const ArrayType::const_iterator cbegin,
                              const ArrayType::const_iterator cend) {
    if (cbegin == cend) {
        return true;
    }
    return *(cbegin - 1) > *cbegin ? false : isSortedRecursive(cbegin + 1, cend);
}

inline bool isSortedRecursive(const ArrayType &values) {
    return values.size() > 1 ? isSortedRecursive(values.cbegin() + 1, values.cend()) : true;
}


auto isSortedIterative(const ArrayType &values) {
    if (values.size() > 1) {
        for (auto iter = values.cbegin() + 1; iter != values.cend(); ++iter) {
            if (*(iter - 1) > *iter) {
                return false;
            }
        }
    }
    return true;
}


/**
 * @reference   Monotonic Array
 *              https://leetcode.com/problems/monotonic-array/
 *
 * An array is monotonic if it is either monotone increasing or monotone decreasing. An
 * array nums is monotone increasing if for all i <= j, nums[i] <= nums[j]. An array nums
 * is monotone decreasing if for all i <= j, nums[i] >= nums[j]. Given an integer array
 * nums, return true if the given array is monotonic, or false otherwise.
 */
auto isMonotonic(const ArrayType &nums) {
    assert(not nums.empty());

    auto increasing = true;
    auto decreasing = true;
    for (std::size_t i = 0; i < nums.size() - 1; ++i) {
        if (nums[i] > nums[i + 1]) {
            increasing = false;
        }
        if (nums[i] < nums[i + 1]) {
            decreasing = false;
        }
    }

    return increasing or decreasing;
}


/**
 * @reference   Verifying an Alien Dictionary
 *              https://leetcode.com/problems/verifying-an-alien-dictionary/
 *
 * In an alien language, surprisingly, they also use English lowercase letters, but
 * possibly in a different order. The order of the alphabet is some permutation of
 * lowercase letters. Given a sequence of words written in the alien language, and the
 * order of the alphabet, return true if and only if the given words are sorted
 * lexicographically in this alien language.
 */
auto isAlienSorted(const std::vector<std::string_view> &words,
                   const std::string_view order) {
    std::unordered_map<char, int> order_map;
    for (std::size_t i = 0; i < order.size(); ++i) {
        order_map[order[i]] = i;
    }

    return std::is_sorted(words.cbegin(), words.cend(),
    [&order_map](const auto one, const auto another) {
        const auto size = std::min(one.size(), another.size());
        std::size_t i = 0;
        for (; i < size and one[i] == another[i]; ++i);
        if (i < size) {
            return order_map[one[i]] < order_map[another[i]];
        }
        return one.size() < another.size();
    });
}


/**
 * @reference   Longest Turbulent Subarray
 *              https://leetcode.com/problems/longest-turbulent-subarray/
 *
 * Given an integer array arr, return the length of a maximum size turbulent subarray of
 * arr. A subarray is turbulent if the comparison sign flips between each adjacent pair
 * of elements in the subarray. More formally, a subarray [arr[i], arr[i + 1], ..., arr[j]]
 * of arr is said to be turbulent if and only if:
 *  For i <= k < j:
 *      arr[k] > arr[k + 1] when k is odd, and
 *      arr[k] < arr[k + 1] when k is even.
 *  Or, for i <= k < j:
 *      arr[k] > arr[k + 1] when k is even, and
 *      arr[k] < arr[k + 1] when k is odd.
 */
auto LongestTurbulentSubarray(const ArrayType &nums) {
    int length_smaller = 1;
    int length_greater = 1;

    int result = 1;
    for (std::size_t i = 1; i < nums.size(); ++i) {
        if (nums[i - 1] == nums[i]) {
            length_greater = 1;
            length_smaller = 1;
        } else if (nums[i - 1] < nums[i]) {
            length_greater = length_smaller + 1;
            length_smaller = 1;
        } else {
            length_smaller = length_greater + 1;
            length_greater = 1;
        }

        result = std::max({result, length_smaller, length_greater});
    }

    return result;
}


inline constexpr int threeWayCompare(const int x, const int y) {
    if (x < y) {
        return -1;
    }
    return x > y;
}

auto LongestTurbulentSubarray_SlidingWindow(const ArrayType &nums) {
    assert(not nums.empty());

    std::size_t result = 1;
    std::size_t anchor = 0;
    for (std::size_t i = 1; i < nums.size(); ++i) {
        const auto c = threeWayCompare(nums[i - 1], nums[i]);
        if (c == 0) {
            anchor = i;
        } else if (i == nums.size() - 1 or c * threeWayCompare(nums[i], nums[i + 1]) != -1) {
            result = std::max(result, i - anchor + 1);
            anchor = i;
        }
    }

    return result;
}


/**
 * @reference   Check if All A's Appears Before All B's
 *              https://leetcode.com/problems/check-if-all-as-appears-before-all-bs/
 *
 * Given a string s consisting of only the characters 'a' and 'b', return true if every
 * 'a' appears before every 'b' in the string. Otherwise, return false.
 */
inline constexpr auto isABSorted(const std::string_view s) {
    return s.find("ba") == std::string_view::npos;
}

}//namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {1};
const ArrayType VALUES3 = {1, 2};
const ArrayType VALUES4 = {2, 3, 1};
const ArrayType VALUES5 = {4, 3, 2, 1};


THE_BENCHMARK(isSortedRecursive, VALUES5);

SIMPLE_TEST(isSortedRecursive, TestSAMPLE1, true, VALUES1);
SIMPLE_TEST(isSortedRecursive, TestSAMPLE2, true, VALUES2);
SIMPLE_TEST(isSortedRecursive, TestSAMPLE3, true, VALUES3);
SIMPLE_TEST(isSortedRecursive, TestSAMPLE4, false, VALUES4);
SIMPLE_TEST(isSortedRecursive, TestSAMPLE5, false, VALUES5);


THE_BENCHMARK(isSortedIterative, VALUES5);

SIMPLE_TEST(isSortedIterative, TestSAMPLE1, true, VALUES1);
SIMPLE_TEST(isSortedIterative, TestSAMPLE2, true, VALUES2);
SIMPLE_TEST(isSortedIterative, TestSAMPLE3, true, VALUES3);
SIMPLE_TEST(isSortedIterative, TestSAMPLE4, false, VALUES4);
SIMPLE_TEST(isSortedIterative, TestSAMPLE5, false, VALUES5);


THE_BENCHMARK(isMonotonic, VALUES5);

SIMPLE_TEST(isMonotonic, TestSAMPLE2, true, VALUES2);
SIMPLE_TEST(isMonotonic, TestSAMPLE3, true, VALUES3);
SIMPLE_TEST(isMonotonic, TestSAMPLE4, false, VALUES4);
SIMPLE_TEST(isMonotonic, TestSAMPLE5, true, VALUES5);


const std::vector<std::string_view> SAMPLE1 = {"hello", "leetcode"};
const std::vector<std::string_view> SAMPLE2 = {"word", "world", "row"};
const std::vector<std::string_view> SAMPLE3 = {"apple", "app"};


THE_BENCHMARK(isAlienSorted, SAMPLE1, "hlabcdefgijkmnopqrstuvwxyz");

SIMPLE_TEST(isAlienSorted, TestSAMPLE1, true, SAMPLE1, "hlabcdefgijkmnopqrstuvwxyz");
SIMPLE_TEST(isAlienSorted, TestSAMPLE2, false, SAMPLE2, "worldabcefghijkmnpqstuvxyz");
SIMPLE_TEST(isAlienSorted, TestSAMPLE3, false, SAMPLE3, "abcdefghijklmnopqrstuvwxyz");


const ArrayType SAMPLE1T = {9, 4, 2, 10, 7, 8, 8, 1, 9};
const ArrayType SAMPLE2T = {4, 8, 12, 16};
const ArrayType SAMPLE3T = {4};
const ArrayType SAMPLE4T = {4, 4};


THE_BENCHMARK(LongestTurbulentSubarray, SAMPLE1T);

SIMPLE_TEST(LongestTurbulentSubarray, TestSAMPLE1, 5, SAMPLE1T);
SIMPLE_TEST(LongestTurbulentSubarray, TestSAMPLE2, 2, SAMPLE2T);
SIMPLE_TEST(LongestTurbulentSubarray, TestSAMPLE3, 1, SAMPLE3T);
SIMPLE_TEST(LongestTurbulentSubarray, TestSAMPLE4, 1, SAMPLE4T);


THE_BENCHMARK(LongestTurbulentSubarray_SlidingWindow, SAMPLE1T);

SIMPLE_TEST(LongestTurbulentSubarray_SlidingWindow, TestSAMPLE1, 5, SAMPLE1T);
SIMPLE_TEST(LongestTurbulentSubarray_SlidingWindow, TestSAMPLE2, 2, SAMPLE2T);
SIMPLE_TEST(LongestTurbulentSubarray_SlidingWindow, TestSAMPLE3, 1, SAMPLE3T);
SIMPLE_TEST(LongestTurbulentSubarray_SlidingWindow, TestSAMPLE4, 1, SAMPLE4T);


THE_BENCHMARK(isABSorted, "aaabbb");

SIMPLE_TEST(isABSorted, TestSAMPLE1, true, "aaabbb");
SIMPLE_TEST(isABSorted, TestSAMPLE2, true, "bbb");
SIMPLE_TEST(isABSorted, TestSAMPLE3, false, "abab");
