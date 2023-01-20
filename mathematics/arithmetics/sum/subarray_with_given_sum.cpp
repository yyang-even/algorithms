#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

using ArrayType = std::vector<int>;

/** Find subarray with given sum | Set 1 (Nonnegative Numbers)
 *
 * @reference   https://www.geeksforgeeks.org/find-subarray-with-given-sum/
 *
 * Given an unsorted array of nonnegative integers, find a continuous subarray which adds to a given
 * number.
 */
constexpr auto NOT_FOUND = std::pair(-1, -1);

std::pair<int, int> FindSubarrayWithGivenSum(const ArrayType &integers,
                                             const ArrayType::value_type SUM) {
    assert(not integers.empty());

    auto start = integers.cbegin();
    auto current_sum = *start;
    for (auto i = start + 1; i != integers.cend(); ++i) {
        while (current_sum > SUM and start < i - 1) {
            current_sum -= *start++;
        }

        if (current_sum == SUM) {
            return std::pair(start - integers.cbegin(), i - integers.cbegin() - 1);
        }

        current_sum += *i;
    }

    return NOT_FOUND;
}


/** Find subarray with given sum | Set 2 (Handles Negative Numbers)
 *
 * @reference   https://www.geeksforgeeks.org/find-subarray-with-given-sum-in-array-of-integers/
 */
auto AllSubarraysWithGivenSum(const ArrayType &integers, const ArrayType::value_type SUM) {
    std::unordered_multimap<ArrayType::value_type, ArrayType::size_type> sum_index_map;
    ArrayType::value_type current_sum = 0;
    std::vector<std::pair<int, int>> outputs;

    for (ArrayType::size_type i = 0; i < integers.size(); ++i) {
        current_sum += integers[i];

        if (current_sum == SUM) {
            outputs.emplace_back(0, i);
        }

        const auto expected_subarray_sum = current_sum - SUM;
        const auto [lower, upper] = sum_index_map.equal_range(expected_subarray_sum);
        if (lower != sum_index_map.cend()) {
            for (auto iter = lower; iter != upper; ++iter) {
                outputs.emplace_back(iter->second + 1, i);
            }
        }

        sum_index_map.emplace(current_sum, i);
    }

    return outputs;
}

inline auto FindSubarrayWithGivenSum_Map(const ArrayType &integers,
                                         const ArrayType::value_type SUM) {
    const auto all_such_arrays = AllSubarraysWithGivenSum(integers, SUM);

    if (all_such_arrays.empty()) {
        return NOT_FOUND;
    } else {
        return all_such_arrays.front();
    }
}


/** Find if there is a subarray with 0 sum
 *
 * @reference   https://www.geeksforgeeks.org/find-if-there-is-a-subarray-with-0-sum/
 *
 * Given an array of positive and negative numbers, find if there is a subarray (of size at-least one)
 * with 0 sum.
 */
inline bool FindSubarrayWith0Sum(const ArrayType &integers) {
    return not AllSubarraysWithGivenSum(integers, 0).empty();
}


/**
 * @reference   Number of subarrays having sum exactly equal to k
 *              https://www.geeksforgeeks.org/number-subarrays-sum-exactly-equal-k/
 *
 * Given an unsorted array of integers, find number of subarrays having sum exactly equal to a given
 * number k.
 *
 * @reference   Subarray Sum Equals K
 *              https://leetcode.com/problems/subarray-sum-equals-k/
 *
 * Given an array of integers nums and an integer k, return the total number of subarrays whose sum
 * equals to k.
 * A subarray is a contiguous non-empty sequence of elements within an array.
 * -1000 <= nums[i] <= 1000
 */
auto NumberOfSubarraysWithGivenSum(const ArrayType &nums, const ArrayType::value_type k) {
    std::unordered_map<int, int> counts = {{0, 1}};
    int sum = 0;
    int result = 0;
    for (const auto n : nums) {
        sum += n;
        const auto iter = counts.find(sum - k);
        if (iter != counts.cend()) {
            result += iter->second;
        }
        ++counts[sum];
    }

    return result;
}


/**
 * @reference   Subarray Sums Divisible by K
 *              https://leetcode.com/problems/subarray-sums-divisible-by-k/
 *
 * Given an integer array nums and an integer k, return the number of non-empty subarrays that have a
 * sum divisible by k.
 * A subarray is a contiguous part of an array.
 */
auto SubarraysDivisibleByK(const ArrayType &nums, const int k) {
    std::unordered_map<int, int> counts {{0, 1}};

    int sum = 0;
    int result = 0;
    for (const auto n : nums) {
        sum = (sum + n % k + k) % k;
        result += counts[sum]++;
    }

    return result;
}


/**
 * @reference   Maximum Size Subarray Sum Equals k
 *              https://cheonhyangzhang.gitbooks.io/leetcode-solutions/content/325-maximum-size-subarray-sum-equals-k.html
 *
 * Given an array nums and a target value k, find the maximum length of a subarray that sums to k.  If
 * there isn't one, return 0 instead.
 * Note: The sum of the entire nums array is guaranteed to fit within the 32-bit signed integer range.
 * Follow Up: Can you do it in O(n) time?
 */
auto MaxLengthSubarraySumAs(const ArrayType &nums, const int k) {
    std::unordered_map<int, int> hash = {{0, -1}};

    const int N = nums.size();
    int result = 0;
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += nums[i];

        const auto expected = sum - k;
        const auto iter = hash.find(expected);
        if (iter != hash.cend()) {
            result = std::max(result, i - iter->second);
        }

        hash.emplace(sum, i);
    }

    return result;
}


/**
 * @reference   Minimum Operations to Reduce X to Zero
 *              https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/
 *
 * You are given an integer array nums and an integer x. In one operation, you can either remove the
 * leftmost or the rightmost element from the array nums and subtract its value from x. Note that this
 * modifies the array for future operations.
 * Return the minimum number of operations to reduce x to exactly 0 if it is possible, otherwise, return
 * -1.
 */
int MinOperationsReduceXto0(const ArrayType &nums, const int x) {
    const auto sum = std::accumulate(nums.cbegin(), nums.cend(), 0);
    if (sum == x) {
        return nums.size();
    }

    const auto result = MaxLengthSubarraySumAs(nums, sum - x);
    return result ? nums.size() - result : -1;
}


/** Find the length of largest subarray with 0 sum
 *
 * @reference   https://www.geeksforgeeks.org/find-the-largest-subarray-with-0-sum/
 *
 * Given an array of integers, find length of the largest subarray with sum equals to 0.
 */
inline auto LengthOfLargestSubarrayWith0Sum(const ArrayType &integers) {
    return MaxLengthSubarraySumAs(integers, 0);
}


/**
 * @reference   Largest subarray with equal number of 0s and 1s
 *              https://www.geeksforgeeks.org/largest-subarray-with-equal-number-of-0s-and-1s/
 *
 * @reference   Length of longest Subarray with equal number of odd and even elements
 *              https://www.geeksforgeeks.org/length-of-longest-subarray-with-equal-number-of-odd-and-even-elements/
 *
 * @reference   Contiguous Array
 *              https://leetcode.com/problems/contiguous-array/
 *
 * Given a binary array nums, return the maximum length of a contiguous subarray with an equal number of
 * 0 and 1.
 */
auto MaxLengthSubarrayWithEqual0sAnd1s(const ArrayType &nums) {
    std::unordered_map<int, int> hash = {{0, -1}};

    const int N = nums.size();
    int result = 0;
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += nums[i] ? 1 : -1;
        const auto [iter, inserted] = hash.emplace(sum, i);
        if (not inserted) {
            result = std::max(result, i - iter->second);
        }
    }

    return result;
}


/**
 * @reference   Number of Submatrices That Sum to Target
 *              https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/
 *
 * Given a matrix and a target, return the number of non-empty submatrices that sum to target.  A
 * submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <= x <= x2 and y1 <= y <= y2.
 * Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different if they have some coordinate
 * that is different: for example, if x1 != x1'.
 */
auto NumSubmatrixSumAsTarget(MatrixType a_matrix, const int target) {
    const auto M = a_matrix.size();
    const auto N = a_matrix.front().size();

    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 1; j < N; ++j) {
            a_matrix[i][j] += a_matrix[i][j - 1];
        }
    }

    int result = 0;
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = i; j < N; ++j) {
            std::unordered_map<int, int> counter {{0, 1}};
            int submatrix_sum = 0;

            for (std::size_t k = 0; k < M; k++) {
                submatrix_sum += a_matrix[k][j] - (i > 0 ? a_matrix[k][i - 1] : 0);
                if (const auto iter = counter.find(submatrix_sum - target);
                    iter != counter.cend()) {
                    result += iter->second;
                }
                ++counter[submatrix_sum];
            }
        }
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {1, 4, 20, 3, 10, 5};
const ArrayType SAMPLE2 = {1, 4, 0, 0, 3, 10, 5};
const ArrayType SAMPLE3 = {1, 4};
const ArrayType SAMPLE4 = {15, 2, 4, 8, 9, 5, 10};


THE_BENCHMARK(FindSubarrayWithGivenSum, SAMPLE1, 33);

SIMPLE_TEST(FindSubarrayWithGivenSum, TestSample1, std::pair(2, 4), SAMPLE1, 33);
SIMPLE_TEST(FindSubarrayWithGivenSum, TestSample2, std::pair(1, 4), SAMPLE2, 7);
SIMPLE_TEST(FindSubarrayWithGivenSum, TestSample3, NOT_FOUND, SAMPLE3, 0);
SIMPLE_TEST(FindSubarrayWithGivenSum, TestSample4, std::pair(1, 4), SAMPLE4, 23);
SIMPLE_TEST(FindSubarrayWithGivenSum, TestSample5, std::pair(3, 3), SAMPLE4, 8);


const ArrayType SAMPLE6 = {10, 2, -2, -20, 10};
const ArrayType SAMPLE7 = {-10, 0, 2, -2, -20, 10};


THE_BENCHMARK(FindSubarrayWithGivenSum_Map, SAMPLE6, 33);

SIMPLE_TEST(FindSubarrayWithGivenSum_Map, TestSample1, std::pair(2, 4), SAMPLE1, 33);
SIMPLE_TEST(FindSubarrayWithGivenSum_Map, TestSample2, std::pair(1, 4), SAMPLE2, 7);
SIMPLE_TEST(FindSubarrayWithGivenSum_Map, TestSample3, NOT_FOUND, SAMPLE3, 0);
SIMPLE_TEST(FindSubarrayWithGivenSum_Map, TestSample4, std::pair(1, 4), SAMPLE4, 23);
SIMPLE_TEST(FindSubarrayWithGivenSum_Map, TestSample5, std::pair(3, 3), SAMPLE4, 8);
SIMPLE_TEST(FindSubarrayWithGivenSum_Map, TestSample6, std::pair(0, 3), SAMPLE6, -10);
SIMPLE_TEST(FindSubarrayWithGivenSum_Map, TestSample7, NOT_FOUND, SAMPLE7, 20);


const ArrayType SAMPLE8 = {4, 2, -3, 1, 6};
const ArrayType SAMPLE9 = {4, 2, 0, 1, 6};
const ArrayType SAMPLE10 = {-3, 2, 3, 1, 6};


THE_BENCHMARK(FindSubarrayWith0Sum, SAMPLE8);

SIMPLE_TEST(FindSubarrayWith0Sum, TestSample8, true, SAMPLE8);
SIMPLE_TEST(FindSubarrayWith0Sum, TestSample9, true, SAMPLE9);
SIMPLE_TEST(FindSubarrayWith0Sum, TestSample10, false, SAMPLE10);


const ArrayType SAMPLE11 = {9, 4, 20, 3, 10, 5};


THE_BENCHMARK(NumberOfSubarraysWithGivenSum, SAMPLE6, -10);

SIMPLE_TEST(NumberOfSubarraysWithGivenSum, TestSample6, 3, SAMPLE6, -10);
SIMPLE_TEST(NumberOfSubarraysWithGivenSum, TestSample7, 0, SAMPLE7, 20);
SIMPLE_TEST(NumberOfSubarraysWithGivenSum, TestSample11, 2, SAMPLE11, 33);


const ArrayType SAMPLE12 = {15, -2, 2, -8, 1, 7, 10, 23};
const ArrayType SAMPLE13 = {1, 2, 3};
const ArrayType SAMPLE14 = {1, 0, 3};


THE_BENCHMARK(LengthOfLargestSubarrayWith0Sum, SAMPLE12);

SIMPLE_TEST(LengthOfLargestSubarrayWith0Sum, TestSample12, 5, SAMPLE12);
SIMPLE_TEST(LengthOfLargestSubarrayWith0Sum, TestSample13, 0, SAMPLE13);
SIMPLE_TEST(LengthOfLargestSubarrayWith0Sum, TestSample14, 1, SAMPLE14);


const ArrayType SAMPLE15 = {1, 0, 1, 1, 1, 0, 0};
const ArrayType SAMPLE16 = {1, 1, 1, 1};
const ArrayType SAMPLE17 = {0, 0, 1, 1, 0};


THE_BENCHMARK(MaxLengthSubarrayWithEqual0sAnd1s, SAMPLE15);

SIMPLE_TEST(MaxLengthSubarrayWithEqual0sAnd1s, TestSample15, 6, SAMPLE15);
SIMPLE_TEST(MaxLengthSubarrayWithEqual0sAnd1s, TestSample16, 0, SAMPLE16);
SIMPLE_TEST(MaxLengthSubarrayWithEqual0sAnd1s, TestSample17, 4, SAMPLE17);


const ArrayType SAMPLE1K = {1, -1, 5, -2, 3};
const ArrayType SAMPLE2K = {-2, -1, 2, 1};


THE_BENCHMARK(MaxLengthSubarraySumAs, SAMPLE1K, 3);

SIMPLE_TEST(MaxLengthSubarraySumAs, TestSample1, 4, SAMPLE1K, 3);
SIMPLE_TEST(MaxLengthSubarraySumAs, TestSample2, 2, SAMPLE2K, 1);


const ArrayType SAMPLE1O = {1, 1, 4, 2, 3};
const ArrayType SAMPLE2O = {5, 6, 7, 8, 9};
const ArrayType SAMPLE3O = {3, 2, 20, 1, 1, 3};


THE_BENCHMARK(MinOperationsReduceXto0, SAMPLE1O, 5);

SIMPLE_TEST(MinOperationsReduceXto0, TestSample0, SAMPLE1O.size(), SAMPLE1O, 11);
SIMPLE_TEST(MinOperationsReduceXto0, TestSample1, 2, SAMPLE1O, 5);
SIMPLE_TEST(MinOperationsReduceXto0, TestSample2, -1, SAMPLE2O, 4);
SIMPLE_TEST(MinOperationsReduceXto0, TestSample3, 5, SAMPLE3O, 10);


// clang-format off
const MatrixType SAMPLE1M = {
    {0, 1, 0},
    {1, 1, 1},
    {0, 1, 0}
};

const MatrixType SAMPLE2M = {
    {1, -1},
    {-1, 1}
};

const MatrixType SAMPLE3M = {{904}};
// clang-format on


THE_BENCHMARK(NumSubmatrixSumAsTarget, SAMPLE1M, 0);

SIMPLE_TEST(NumSubmatrixSumAsTarget, TestSample1, 4, SAMPLE1M, 0);
SIMPLE_TEST(NumSubmatrixSumAsTarget, TestSample2, 5, SAMPLE2M, 0);
SIMPLE_TEST(NumSubmatrixSumAsTarget, TestSample3, 0, SAMPLE3M, 0);


const ArrayType SAMPLE1D = {4, 5, 0, -2, -3, 1};
const ArrayType SAMPLE2D = {5};


THE_BENCHMARK(SubarraysDivisibleByK, SAMPLE1D, 5);

SIMPLE_TEST(SubarraysDivisibleByK, TestSample1, 7, SAMPLE1D, 5);
SIMPLE_TEST(SubarraysDivisibleByK, TestSample2, 0, SAMPLE2D, 9);
