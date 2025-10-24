#include "common_header.h"

#include "prefix_sum_array.h"


namespace {

using ArrayType = std::vector<int>;
using RangeType = std::pair<ArrayType::size_type, ArrayType::size_type>;
using RangeArray = std::vector<RangeType>;
using UpdateType = std::tuple<std::size_t, std::size_t, int>;
using UpdateArray = std::vector<UpdateType>;

void update(ArrayType &elements,
            const std::size_t left,
            const std::size_t right,
            const int increment) {
    elements[left] += increment;
    if (right + 1 < elements.size()) {
        elements[right + 1] -= increment;
    }
}

/**
 * @reference   Constant time range add operation on an array
 *              https://www.geeksforgeeks.org/constant-time-range-add-operation-array/
 *
 * Given an array of size N which is initialized with all zeros. We are given many range add queries,
 * which should be applied to this array. We need to print final updated array as our result.
 *
 * @tags    #prefix-sum
 */
auto RangesOfAdditions(const ArrayType::size_type size,
                       const ArrayType::value_type d,
                       const RangeArray &ranges) {
    ArrayType elements(size, 0);

    for (const auto &[left, right] : ranges) {
        update(elements, left, right, d);
    }

    return PrefixSumArray(std::move(elements));
}


/**
 * @reference   Range Addition
 *              https://xiaoguan.gitbooks.io/leetcode/content/LeetCode/370-range-addition-medium.html
 *
 * Assume you have an array of length n initialized with all 0's and are given k update operations.
 * Each operation is represented as a triplet: [startIndex, endIndex, inc] which increments each element
 * of subarray A[startIndex ... endIndex] (startIndex and endIndex inclusive) with inc.
 * Return the modified array after all k operations were executed.
 *
 * @tags    #prefix-sum
 */
auto RangeAddition(const std::size_t N, const UpdateArray &updates) {
    ArrayType elements(N, 0);

    for (const auto &[left, right, inc] : updates) {
        update(elements, left, right, inc);
    }

    return PrefixSumArray(std::move(elements));
}


/**
 * reference    Print modified array after multiple array range increment operations
 *              https://www.geeksforgeeks.org/print-modified-array-multiple-array-range-increment-operations/
 *
 * Given an array containing n integers and a value d. m queries are given. Each query has two values
 * start and end. For each query, the problem is to increment the values from the start to end index in
 * the given array by the given value d. A linear time efficient solution is required for handling such
 * multiple queries.
 *
 * @tags    #prefix-sum
 */
inline auto RangesOfAdditions(const ArrayType &elements,
                              const ArrayType::value_type d,
                              const RangeArray &ranges) {
    auto sums = RangesOfAdditions(elements.size(), d, ranges);

    std::transform(sums.cbegin(),
                   sums.cend(),
                   elements.cbegin(),
                   sums.begin(),
                   std::plus<ArrayType::value_type> {});

    return sums;
}


/**
 * @reference   Prefix Sum Array – Implementation and Applications in Competitive Programming
 *              https://www.geeksforgeeks.org/prefix-sum-array-implementation-applications-competitive-programming/
 *
 * Consider an array of size n with all initial values as 0. Perform given 'm' add operations from index
 * 'a' to 'b' and evaluate highest element in array. An add operation adds 100 to all elements from a to
 * b (both inclusive).
 *
 * @reference   Maximum occurred integer in n ranges
 *              https://www.geeksforgeeks.org/maximum-occurred-integer-n-ranges/
 * @reference   Maximum occurred integer in n ranges | Set-2
 *              https://www.geeksforgeeks.org/maximum-occurred-integer-in-n-ranges-set-2/
 *
 * Given n ranges of the form L and R, the task is to find the maximum occurred integer in all the
 * ranges. If more than one such integer exists, print the smallest one.
 * Note: 1 <= L <= R <= 10^6
 *
 * @reference   Maximum value in an array after m range increment operations
 *              https://www.geeksforgeeks.org/maximum-value-array-m-range-increment-operations/
 *
 * Consider an array of size n with all initial values as 0, we need to perform following m range
 * increment operations.
 *  increment(a, b, k) : Increment values from 'a' to 'b' by 'k'.
 * After m operations, we need to calculate the maximum of the values in the array.
 *
 * @tags    #prefix-sum #min-max-element
 */
inline auto MaxAfterRangesOfAdditions(const ArrayType::size_type size, const RangeArray &ranges) {
    const auto prefix_sums = RangesOfAdditions(size, 100, ranges);
    return *std::max_element(prefix_sums.cbegin(), prefix_sums.cend());
}


/**
 * @reference   Range Addition II
 *              https://leetcode.com/problems/range-addition-ii/
 *
 * You are given an m x n matrix M initialized with all 0's and an array of operations ops, where ops[i]
 * = [ai, bi] means M[x][y] should be incremented by one for all 0 <= x < ai and 0 <= y < bi.
 * Count and return the number of maximum integers in the matrix after performing all the operations.
 *
 * @tags    #matrix #min-max-element
 */
auto CountMaxAfterRangeAddition(std::size_t m, std::size_t n, const RangeArray &operations) {
    for (const auto &[i, j] : operations) {
        m = std::min(m, i);
        n = std::min(n, j);
    }

    return m * n;
}


/**
 * @reference   Minimum Value to Get Positive Step by Step Sum
 *              https://leetcode.com/problems/minimum-value-to-get-positive-step-by-step-sum/
 *
 * Given an array of integers nums, you start with an initial positive value startValue.
 * In each iteration, you calculate the step by step sum of startValue plus elements in nums (from left
 * to right).
 * Return the minimum positive value of startValue such that the step by step sum is never less than 1.
 */


/**
 * @reference   Find the Highest Altitude
 *              https://leetcode.com/problems/find-the-highest-altitude/
 *
 * There is a biker going on a road trip. The road trip consists of n + 1 points at different altitudes.
 * The biker starts his trip on point 0 with altitude equal 0.
 * You are given an integer array gain of length n where gain[i] is the net gain in altitude between
 * points i and i + 1 for all (0 <= i < n). Return the highest altitude of a point.
 */


/**
 * @reference   Maximum Population Year
 *              https://leetcode.com/problems/maximum-population-year/
 *
 * You are given a 2D integer array logs where each logs[i] = [birthi, deathi] indicates the birth and
 * death years of the ith person.
 * The population of some year x is the number of people alive during that year. The ith person is
 * counted in year x's population if x is in the inclusive range [birthi, deathi - 1]. Note that the
 * person is not counted in the year that they die.
 * Return the earliest year with the maximum population.
 * 1950 <= birthi < deathi <= 2050
 */


/**
 * @reference   Check if All the Integers in a Range Are Covered
 *              https://leetcode.com/problems/check-if-all-the-integers-in-a-range-are-covered/
 *
 * You are given a 2D integer array ranges and two integers left and right. Each ranges[i] = [starti,
 * endi] represents an inclusive interval between starti and endi.
 * Return true if each integer in the inclusive range [left, right] is covered by at least one interval
 * in ranges. Return false otherwise.
 * An integer x is covered by an interval ranges[i] = [starti, endi] if starti <= x <= endi.
 * 1 <= starti <= endi <= 50
 * 1 <= left <= right <= 50
 */


/**
 * @reference   Minimum Average Difference
 *              https://leetcode.com/problems/minimum-average-difference/
 *
 * You are given a 0-indexed integer array nums of length n.
 * The average difference of the index i is the absolute difference between the average of the first i + 1
 * elements of nums and the average of the last n - i - 1 elements. Both averages should be rounded down
 * to the nearest integer.
 * Return the index with the minimum average difference. If there are multiple such indices, return the
 * smallest one.
 * Note:
 *  The absolute difference of two numbers is the absolute value of their difference.
 *  The average of n elements is the sum of the n elements divided (integer division) by n.
 *  The average of 0 elements is considered to be 0.
 */
auto MinAverageDiff(const ArrayType &nums) {
    const auto total_sum = std::accumulate(nums.cbegin(), nums.cend(), 0ll);

    const int N = nums.size();
    long long prefix_sum = 0;
    long long minimum = INT_MAX;
    int minimum_index = 0;
    for (int i = 0; i < N; ++i) {
        prefix_sum += nums[i];
        const auto suffix_sum = total_sum - prefix_sum;
        const auto prefix_average = prefix_sum / (i + 1);
        const auto suffix_average = (i == N - 1) ? 0 : (suffix_sum / (N - i - 1));

        const auto diff = std::abs(prefix_average - suffix_average);
        if (diff < minimum) {
            minimum = diff;
            minimum_index = i;
        }
    }

    return minimum_index;
}


/**
 * @reference   Sum of Absolute Differences in a Sorted Array
 *              https://leetcode.com/problems/sum-of-absolute-differences-in-a-sorted-array/
 *
 * You are given an integer array nums sorted in non-decreasing order.
 * Build and return an integer array result with the same length as nums such that result[i] is equal to
 * the summation of absolute differences between nums[i] and all the other elements in the array.
 * In other words, result[i] is equal to sum(|nums[i]-nums[j]|) where 0 <= j < nums.length and j != i
 * (0-indexed).
 */


/**
 * @reference   Unique Length-3 Palindromic Subsequences
 *              https://leetcode.com/problems/unique-length-3-palindromic-subsequences/
 *
 * Given a string s, return the number of unique palindromes of length three that are a subsequence of
 * s.
 * Note that even if there are multiple ways to obtain the same subsequence, it is still only counted
 * once.
 * A palindrome is a string that reads the same forwards and backwards.
 * A subsequence of a string is a new string generated from the original string with some characters
 * (can be none) deleted without changing the relative order of the remaining characters.
 *  For example, "ace" is a subsequence of "abcde".
 */
auto CountPalindromicSubsequence(const std::string_view s) {
    std::vector prefix_sums(26, std::vector(s.size() + 1, 0));
    std::vector lasts(26, 0);

    for (std::size_t i = 0; i < s.size(); ++i) {
        const int c_index = s[i] - 'a';

        lasts[c_index] = i;

        for (auto &sums : prefix_sums) {
            sums[i + 1] = sums[i];
        }
        ++(prefix_sums[c_index][i + 1]);
    }

    int result = 0;
    for (std::size_t i = 0; i < s.size(); ++i) {
        const int c_index = s[i] - 'a';

        const size_t l = lasts[c_index];
        if (l > i) {
            for (const auto &sums : prefix_sums) {
                const auto diff = sums[l] - sums[i + 1];
                if (diff > 0) {
                    ++result;
                }
            }
        }
        lasts[c_index] = 0;
    }

    return result;
}


/**
 * @reference   Minimum Amount of Time to Collect Garbage
 *              https://leetcode.com/problems/minimum-amount-of-time-to-collect-garbage/
 *
 * You are given a 0-indexed array of strings garbage where garbage[i] represents the assortment of
 * garbage at the ith house. garbage[i] consists only of the characters 'M', 'P' and 'G' representing
 * one unit of metal, paper and glass garbage respectively. Picking up one unit of any type of garbage
 * takes 1 minute.
 * You are also given a 0-indexed integer array travel where travel[i] is the number of minutes needed
 * to go from house i to house i + 1.
 * There are three garbage trucks in the city, each responsible for picking up one type of garbage. Each
 * garbage truck starts at house 0 and must visit each house in order; however, they do not need to
 * visit every house.
 * Only one garbage truck may be used at any given moment. While one truck is driving or picking up
 * garbage, the other two trucks cannot do anything.
 * Return the minimum number of minutes needed to pick up all the garbage.
 */
auto MinTimeToCollectGarbage(const std::vector<std::string> &garbage, ArrayType travel) {
    std::unordered_map<char, int> lasts;
    int result = 0;
    for (std::size_t i = 0; i < garbage.size(); ++i) {
        result += garbage[i].size();
        for (const auto c : garbage[i]) {
            lasts[c] = i;
        }
    }

    for (std::size_t i = 1; i < travel.size(); ++i) {
        travel[i] += travel[i - 1];
    }

    for (const auto c : "MPG") {
        if (lasts[c]) {
            result += travel[lasts[c] - 1];
        }
    }

    return result;
}


/**
 * @reference   Find the Student that Will Replace the Chalk
 *              https://leetcode.com/problems/find-the-student-that-will-replace-the-chalk/
 *
 * There are n students in a class numbered from 0 to n - 1. The teacher will give each student a
 * problem starting with the student number 0, then the student number 1, and so on until the teacher
 * reaches the student number n - 1. After that, the teacher will restart the process, starting with the
 * student number 0 again.
 * You are given a 0-indexed integer array chalk and an integer k. There are initially k pieces of
 * chalk. When the student number i is given a problem to solve, they will use chalk[i] pieces of chalk
 * to solve that problem. However, if the current number of chalk pieces is strictly less than chalk[i],
 * then the student number i will be asked to replace the chalk.
 * Return the index of the student that will replace the chalk pieces.
 *
 * @tags    #prefix-sum #binary-search
 */
int ChalkReplacer(const ArrayType &chalk, int k) {
    std::vector<long> prefix_sum_array = {chalk.front()};

    for (std::size_t i = 1; i < chalk.size(); ++i) {
        prefix_sum_array.push_back(prefix_sum_array.back() + chalk[i]);
    }

    k %= prefix_sum_array.back();

    return std::upper_bound(prefix_sum_array.cbegin(), prefix_sum_array.cend(), k) -
           prefix_sum_array.cbegin();
}


/**
 * @reference   Maximum Frequency of an Element After Performing Operations I
 *              https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-i/
 *
 * You are given an integer array nums and two integers k and numOperations.
 * You must perform an operation numOperations times on nums, where in each operation you:
 *  Select an index i that was not selected in any previous operations.
 *  Add an integer in the range [-k, k] to nums[i].
 * Return the maximum possible frequency of any element in nums after performing the operations.
 * 1 <= nums[i] <= 10^5
 *
 * @tags    #hash-table #prefix-sum #min-max-element
 */
auto MaxFrequencyAfterOperations_Ranges(const ArrayType &nums,
                                        const int k,
                                        const int numOperations) {
    const auto maximum = *std::max_element(nums.cbegin(), nums.cend());

    const int SIZE = maximum + k + 2;
    std::vector frequencies(SIZE, 0);
    std::vector counts(SIZE, 0);

    for (const auto n : nums) {
        ++frequencies[std::max(0, n - k)];
        --frequencies[n + k + 1];
        ++counts[n];
    }

    int result = 1;
    for (std::size_t i = 1; i < frequencies.size(); ++i) {
        frequencies[i] += frequencies[i - 1];
        const auto actual = std::min(frequencies[i], counts[i] + numOperations);
        result = std::max(result, actual);
    }

    return result;
}


auto MaxFrequencyAfterOperations(const ArrayType &nums, const int k, const int numOperations) {
    const auto maximum = *std::max_element(nums.cbegin(), nums.cend());

    const int SIZE = maximum + k + 2;
    std::vector count(SIZE, 0);

    for (const auto v : nums) {
        ++count[v];
    }

    for (int i = 1; i < SIZE; ++i) {
        count[i] += count[i - 1];
    }

    int result = 1;
    for (int i = 1; i <= maximum; ++i) {
        const auto left = std::max(1, i - k) - 1;
        const auto right = i + k;
        const auto total = count[right] - count[left];
        const auto frequency = count[i] - count[i - 1];
        const auto actual = std::min(numOperations + frequency, total);
        result = std::max(result, actual);
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {10, 20, 10, 5, 15};
const ArrayType EXPECTED1 = {10, 30, 40, 45, 60};

const ArrayType SAMPLE2 = {10, 4, 16, 20};
const ArrayType EXPECTED2 = {10, 14, 30, 50};


THE_BENCHMARK(PrefixSumArray, SAMPLE1);

SIMPLE_TEST(PrefixSumArray, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(PrefixSumArray, TestSAMPLE2, EXPECTED2, SAMPLE2);


const ArrayType SAMPLE3 = {3, 5, 4, 8, 6, 1};
const RangeArray SAMPLE_RANGES3 = {{0, 3}, {4, 5}, {1, 4}, {0, 1}, {2, 5}};
const ArrayType EXPECTED3 = {7, 11, 10, 14, 12, 5};

const RangeArray SAMPLE_RANGES4 = {{0, 2}, {1, 5}, {2, 3}};
const ArrayType EXPECTED4 = {100, 200, 300, 200, 100, 100};

const RangeArray SAMPLE_RANGES5 = {{2, 4}, {1, 3}, {1, 2}};


SIMPLE_BENCHMARK(RangesOfAdditions, Sample1, SAMPLE3, 2, SAMPLE_RANGES3);

SIMPLE_TEST(RangesOfAdditions, TestSAMPLE3, EXPECTED3, SAMPLE3, 2, SAMPLE_RANGES3);


SIMPLE_BENCHMARK(RangesOfAdditions, Sample2, 6, 100, SAMPLE_RANGES4);

SIMPLE_TEST(RangesOfAdditions, TestSAMPLE4, EXPECTED4, 6, 100, SAMPLE_RANGES4);


THE_BENCHMARK(MaxAfterRangesOfAdditions, 5, SAMPLE_RANGES5);

SIMPLE_TEST(MaxAfterRangesOfAdditions, TestSAMPLE5, 300, 5, SAMPLE_RANGES5);


const UpdateArray SAMPLE1U = {{1, 3, 2}, {2, 4, 3}, {0, 2, -2}};
const ArrayType EXPECTED1U = {-2, 0, 3, 5, 3};


THE_BENCHMARK(RangeAddition, 5, SAMPLE1U);

SIMPLE_TEST(RangeAddition, TestSAMPLE1, EXPECTED1U, 5, SAMPLE1U);


const RangeArray SAMPLE1o = {{2, 2}, {3, 3}};
const RangeArray SAMPLE2o = {};


THE_BENCHMARK(CountMaxAfterRangeAddition, 3, 3, SAMPLE1o);

SIMPLE_TEST(CountMaxAfterRangeAddition, TestSAMPLE1, 4, 3, 3, SAMPLE1o);
SIMPLE_TEST(CountMaxAfterRangeAddition, TestSAMPLE2, 9, 3, 3, SAMPLE2o);


const ArrayType SAMPLE1M = {2, 5, 3, 9, 5, 3};
const ArrayType SAMPLE2M = {0};


THE_BENCHMARK(MinAverageDiff, SAMPLE1M);

SIMPLE_TEST(MinAverageDiff, TestSAMPLE1, 3, SAMPLE1M);
SIMPLE_TEST(MinAverageDiff, TestSAMPLE2, 0, SAMPLE2M);


THE_BENCHMARK(CountPalindromicSubsequence, "aabca");

SIMPLE_TEST(CountPalindromicSubsequence, TestSAMPLE1, 3, "aabca");
SIMPLE_TEST(CountPalindromicSubsequence, TestSAMPLE2, 0, "adc");
SIMPLE_TEST(CountPalindromicSubsequence, TestSAMPLE3, 4, "bbcbaba");


const std::vector<std::string> SAMPLE1G = {"G", "P", "GP", "GG"};
const ArrayType SAMPLE1T = {2, 4, 3};

const std::vector<std::string> SAMPLE2G = {"MMM", "PGM", "GP"};
const ArrayType SAMPLE2T = {3, 10};


THE_BENCHMARK(MinTimeToCollectGarbage, SAMPLE1G, SAMPLE1T);

SIMPLE_TEST(MinTimeToCollectGarbage, TestSAMPLE1, 21, SAMPLE1G, SAMPLE1T);
SIMPLE_TEST(MinTimeToCollectGarbage, TestSAMPLE2, 37, SAMPLE2G, SAMPLE2T);


const ArrayType SAMPLE1CR = {5, 1, 5};
const ArrayType SAMPLE2CR = {3, 4, 1, 2};


THE_BENCHMARK(ChalkReplacer, SAMPLE2CR, 25);

SIMPLE_TEST(ChalkReplacer, TestSAMPLE1, 0, SAMPLE1CR, 22);
SIMPLE_TEST(ChalkReplacer, TestSAMPLE2, 1, SAMPLE2CR, 25);


const ArrayType SAMPLE1MF = {1, 4, 5};
const ArrayType SAMPLE2MF = {5, 11, 20, 20};
const ArrayType SAMPLE3MF = {2, 49};
const ArrayType SAMPLE4MF = {88, 53};
const ArrayType SAMPLE5MF = {100000, 100000};


THE_BENCHMARK(MaxFrequencyAfterOperations, SAMPLE1MF, 1, 2);

SIMPLE_TEST(MaxFrequencyAfterOperations, TestSAMPLE1, 2, SAMPLE1MF, 1, 2);
SIMPLE_TEST(MaxFrequencyAfterOperations, TestSAMPLE2, 2, SAMPLE2MF, 5, 1);
SIMPLE_TEST(MaxFrequencyAfterOperations, TestSAMPLE3, 1, SAMPLE3MF, 97, 0);
SIMPLE_TEST(MaxFrequencyAfterOperations, TestSAMPLE4, 2, SAMPLE4MF, 27, 2);
SIMPLE_TEST(MaxFrequencyAfterOperations, TestSAMPLE5, 2, SAMPLE5MF, 1, 1);


THE_BENCHMARK(MaxFrequencyAfterOperations_Ranges, SAMPLE1MF, 1, 2);

SIMPLE_TEST(MaxFrequencyAfterOperations_Ranges, TestSAMPLE1, 2, SAMPLE1MF, 1, 2);
SIMPLE_TEST(MaxFrequencyAfterOperations_Ranges, TestSAMPLE2, 2, SAMPLE2MF, 5, 1);
SIMPLE_TEST(MaxFrequencyAfterOperations_Ranges, TestSAMPLE3, 1, SAMPLE3MF, 97, 0);
SIMPLE_TEST(MaxFrequencyAfterOperations_Ranges, TestSAMPLE4, 2, SAMPLE4MF, 27, 2);
SIMPLE_TEST(MaxFrequencyAfterOperations_Ranges, TestSAMPLE5, 2, SAMPLE5MF, 1, 1);
