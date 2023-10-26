#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Sliding Window Maximum (Maximum of all subarrays of size k)
 *
 * @reference   https://www.geeksforgeeks.org/sliding-window-maximum-maximum-of-all-subarrays-of-size-k/
 * @reference   Maximum of all Subarrays of size k using set in C++ STL
 *              https://www.geeksforgeeks.org/maximum-of-all-subarrays-of-size-k-using-set-in-cpp-stl/
 *
 * @reference   Minimum and Maximum of all subarrays of size K using Map
 *              https://www.geeksforgeeks.org/minimum-and-maximum-of-all-subarrays-of-size-k-using-map/
 *
 * @reference   Sum of minimum and maximum elements of all subarrays of size k.
 *              https://www.geeksforgeeks.org/sum-minimum-maximum-elements-subarrays-size-k/
 *
 * @reference   Sliding Window Maximum : Set 2
 *              https://www.geeksforgeeks.org/sliding-window-maximum-set-2/
 *
 * @note    Same as the naive solution in Set 1.
 *
 * @reference   Sliding Window Maximum (Maximum of all subarrays of size k) using stack in O(n) time
 *              https://www.geeksforgeeks.org/sliding-window-maximum-maximum-of-all-subarrays-of-size-k-using-stack-in-on-time/
 *
 * @reference   Sliding Window Maximum
 *              https://leetcode.com/problems/sliding-window-maximum/
 *
 * You are given an array of integers nums, there is a sliding window of size k which is moving from the
 * very left of the array to the very right. You can only see the k numbers in the window. Each time the
 * sliding window moves right by one position.
 * Return the max sliding window.
 */
auto MaxOfAllSubarraysOfSizeK_Multiset(const ArrayType &elements, const ArrayType::size_type K) {
    assert(K);
    assert(elements.size() >= K);

    std::multiset subarray_set(elements.cbegin(), elements.cbegin() + K);
    ArrayType result = {*subarray_set.crbegin()};
    for (auto i = K; i < elements.size(); ++i) {
        subarray_set.erase(subarray_set.find(elements[i - K]));
        subarray_set.insert(elements[i]);
        result.push_back(*subarray_set.crbegin());
    }

    return result;
}


auto MaxOfAllSubarraysOfSizeK_MonotonicQueue(const ArrayType &nums,
                                             const ArrayType::size_type K) {
    assert(K);
    assert(nums.size() >= K);

    std::deque<ArrayType::size_type> monotonic_queue;
    ArrayType result;

    for (std::size_t i = 0; i < nums.size(); ++i) {
        while (not monotonic_queue.empty() and monotonic_queue.front() + K <= i) {
            monotonic_queue.pop_front();
        }

        while (not monotonic_queue.empty() and nums[monotonic_queue.back()] < nums[i]) {
            monotonic_queue.pop_back();
        }

        monotonic_queue.push_back(i);

        if (i >= K - 1) {
            result.push_back(nums[monotonic_queue.front()]);
        }
    }

    return result;
}


/**
 * @reference   Maximum of all subarrays of size K using Segment Tree
 *              https://www.geeksforgeeks.org/maximum-of-all-subarrays-of-size-k-using-segment-tree/
 *
 * Given an array arr[] and an integer K, the task is to find the maximum for each and every contiguous
 * subarray of size K.
 * The idea is to use the Segment tree to answer the maximum of all subarrays of size K.
 */


/**
 * @reference   Maximum Number of Vowels in a Substring of Given Length
 *              https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/
 *
 * Given a string s and an integer k, return the maximum number of vowel letters in any substring of s
 * with length k.
 * Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.
 */


/**
 * @reference   Continuous Subarrays
 *              https://leetcode.com/problems/continuous-subarrays/
 *
 * You are given a 0-indexed integer array nums. A subarray of nums is called continuous if:
 *  Let i, i + 1, ..., j be the indices in the subarray. Then, for each pair of indices i <= i1, i2 <= j,
 *  0 <= |nums[i1] - nums[i2]| <= 2.
 * Return the total number of continuous subarrays.
 * A subarray is a contiguous non-empty sequence of elements within an array.
 */
auto ContinuousSubarrays(const ArrayType &nums) {
    long long result = 1;

    auto minimum = nums.front() - 2;
    auto maximum = nums.front() + 2;
    std::size_t left = 0;
    for (std::size_t right = 1; right < nums.size(); ++right) {
        if (nums[right] >= minimum and nums[right] <= maximum) {
            minimum = std::max(minimum, nums[right] - 2);
            maximum = std::min(maximum, nums[right] + 2);
        } else {
            minimum = nums[right] - 2;
            maximum = nums[right] + 2;

            for (left = right - 1;
                 nums[left] >= nums[right] - 2 and nums[left] <= nums[right] + 2;
                 --left) {
                minimum = std::max(minimum, nums[left] - 2);
                maximum = std::min(maximum, nums[left] + 2);
            }
            ++left;
        }

        result += (right - left + 1);
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {1, 2, 3, 1, 4, 5, 2, 3, 6};
const ArrayType EXPECTED1 = {3, 3, 4, 5, 5, 5, 6};

const ArrayType SAMPLE2 = {8, 5, 10, 7, 9, 4, 15, 12, 90, 13};
const ArrayType EXPECTED2 = {10, 10, 10, 15, 15, 90, 90};

const ArrayType SAMPLE3 = {1, 3, -1, -3, 5, 3, 6, 7};
const ArrayType EXPECTED3 = {3, 3, 5, 5, 6, 7};

const ArrayType SAMPLE4 = {1};

const ArrayType SAMPLE5 = {7, 2, 4};
const ArrayType EXPECTED5 = {7, 4};

const ArrayType SAMPLE6 = {1, 3, 1, 2, 0, 5};
const ArrayType EXPECTED6 = {3, 3, 2, 5};


THE_BENCHMARK(MaxOfAllSubarraysOfSizeK_Multiset, SAMPLE1, 3);

SIMPLE_TEST(MaxOfAllSubarraysOfSizeK_Multiset, TestSAMPLE1, EXPECTED1, SAMPLE1, 3);
SIMPLE_TEST(MaxOfAllSubarraysOfSizeK_Multiset, TestSAMPLE2, EXPECTED2, SAMPLE2, 4);
SIMPLE_TEST(MaxOfAllSubarraysOfSizeK_Multiset, TestSAMPLE3, EXPECTED3, SAMPLE3, 3);
SIMPLE_TEST(MaxOfAllSubarraysOfSizeK_Multiset, TestSAMPLE4, SAMPLE4, SAMPLE4, 1);
SIMPLE_TEST(MaxOfAllSubarraysOfSizeK_Multiset, TestSAMPLE5, EXPECTED5, SAMPLE5, 2);
SIMPLE_TEST(MaxOfAllSubarraysOfSizeK_Multiset, TestSAMPLE6, EXPECTED6, SAMPLE6, 3);


THE_BENCHMARK(MaxOfAllSubarraysOfSizeK_MonotonicQueue, SAMPLE1, 3);

SIMPLE_TEST(MaxOfAllSubarraysOfSizeK_MonotonicQueue, TestSAMPLE1, EXPECTED1, SAMPLE1, 3);
SIMPLE_TEST(MaxOfAllSubarraysOfSizeK_MonotonicQueue, TestSAMPLE2, EXPECTED2, SAMPLE2, 4);
SIMPLE_TEST(MaxOfAllSubarraysOfSizeK_MonotonicQueue, TestSAMPLE3, EXPECTED3, SAMPLE3, 3);
SIMPLE_TEST(MaxOfAllSubarraysOfSizeK_MonotonicQueue, TestSAMPLE4, SAMPLE4, SAMPLE4, 1);
SIMPLE_TEST(MaxOfAllSubarraysOfSizeK_MonotonicQueue, TestSAMPLE5, EXPECTED5, SAMPLE5, 2);
SIMPLE_TEST(MaxOfAllSubarraysOfSizeK_MonotonicQueue, TestSAMPLE6, EXPECTED6, SAMPLE6, 3);


const ArrayType SAMPLE1C = {5, 4, 2, 4};
const ArrayType SAMPLE2C = {1, 2, 3};
const ArrayType SAMPLE3C = {65, 66, 67, 66, 66, 65, 64, 65, 65, 64};
const ArrayType SAMPLE4C = {50, 49, 48, 49, 48, 47, 46};


THE_BENCHMARK(ContinuousSubarrays, SAMPLE1C);

SIMPLE_TEST(ContinuousSubarrays, TestSAMPLE1, 8, SAMPLE1C);
SIMPLE_TEST(ContinuousSubarrays, TestSAMPLE2, 6, SAMPLE2C);
SIMPLE_TEST(ContinuousSubarrays, TestSAMPLE3, 43, SAMPLE3C);
SIMPLE_TEST(ContinuousSubarrays, TestSAMPLE4, 23, SAMPLE4C);
