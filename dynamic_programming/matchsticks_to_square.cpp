#include "common_header.h"

#include "hash/hash.h"


namespace {

using ArrayType = std::vector<int>;
using MemoType = std::unordered_map<std::pair<unsigned, unsigned>, bool, PairHash>;

/** Partition of a set into K subsets with equal sum
 *
 * @reference   https://www.geeksforgeeks.org/partition-set-k-subsets-equal-sum/
 *
 * Given an integer array of N elements, the task is to divide this array into K non-empty subsets such
 * that the sum of elements in every subset is same. All elements of this array should be part of
 * exactly one partition.
 *
 * @reference   Partition to K Equal Sum Subsets
 *              https://leetcode.com/problems/partition-to-k-equal-sum-subsets/
 */
auto SubsetsOfEqualSum(const ArrayType &elements,
                       const ArrayType::value_type edge_length,
                       const ArrayType::size_type index,
                       ArrayType &sums) {
    if (index == elements.size()) {
        for (const auto a_sum : sums) {
            if (a_sum != edge_length) {
                return false;
            }
        }
        return true;
    }

    const auto an_element = elements[index];

    for (auto &a_sum : sums) {
        if (a_sum + an_element <= edge_length) {
            a_sum += an_element;
            if (SubsetsOfEqualSum(elements, edge_length, index + 1, sums)) {
                return true;
            }
            a_sum -= an_element;
        }
    }

    return false;
}

auto SubsetsOfEqualSum(ArrayType elements, const unsigned K) {
    if (K == 1) {
        return true;
    }

    if (elements.size() < K) {
        return false;
    }

    const auto total = std::accumulate(elements.cbegin(), elements.cend(), 0ul);
    const auto average = total / K;
    if (average * K != total) {
        return false;
    }

    std::sort(elements.begin(), elements.end(), std::greater<ArrayType::value_type> {});
    ArrayType sums(K, 0);
    return SubsetsOfEqualSum(elements, average, 0, sums);
}

/** Matchsticks to Square
 *
 * @reference   https://leetcode.com/problems/matchsticks-to-square/
 *
 * You are given an integer array matchsticks where matchsticks[i] is the length of the ith matchstick.
 * You want to use all the matchsticks to make one square. You should not break any stick, but you can
 * link them up, and each matchstick must be used exactly one time.
 * Return true if you can make this square and false otherwise.
 * 1 <= matchsticks.length <= 15
 * 1 <= matchsticks[i] <= 10^8
 */
inline auto MatchsticksToSquare_Recursive(ArrayType elements) {
    return SubsetsOfEqualSum(std::move(elements), 4);
}


auto MatchsticksToSquare_DP(const ArrayType &elements,
                            const ArrayType::value_type edge_length,
                            const unsigned mask,
                            unsigned sides_done,
                            MemoType &memo) {
    const auto key = std::pair(mask, sides_done);
    ArrayType::value_type total_length = 0;
    for (ArrayType::size_type i = 0; i < elements.size(); ++i) {
        if ((mask & (1u << i)) == 0) {
            total_length += elements[i];
        }
    }

    if (total_length > 0 and total_length % edge_length == 0) {
        ++sides_done;
    }

    if (sides_done == 3) {
        return true;
    }

    if (const auto iter = memo.find(key); iter != memo.cend()) {
        return iter->second;
    }

    bool result = false;
    const auto remaining_edge_length =
        edge_length * (total_length / edge_length + 1) - total_length;
    for (ArrayType::size_type i = 0; i < elements.size(); ++i) {
        if (elements[i] <= remaining_edge_length and (mask & (1u << i))) {
            if (MatchsticksToSquare_DP(
                    elements, edge_length, mask ^ (1u << i), sides_done, memo)) {
                result = true;
                break;
            }
        }
    }

    memo[key] = result;
    return result;
}

auto MatchsticksToSquare_DP(ArrayType elements) {
    assert(elements.size() < 15);

    if (elements.size() < 4) {
        return false;
    }

    const auto perimeter = std::accumulate(elements.cbegin(), elements.cend(), 0);
    const auto edge_length = perimeter / 4;
    if (edge_length * 4 != perimeter) {
        return false;
    }

    std::sort(elements.begin(), elements.end(), std::greater<ArrayType::value_type> {});
    MemoType memo;
    return MatchsticksToSquare_DP(elements, edge_length, (1u << elements.size()) - 1, 0, memo);
}


/**
 * @reference   Partition Array Into Three Parts With Equal Sum
 *              https://leetcode.com/problems/partition-array-into-three-parts-with-equal-sum/
 *
 * Given an array of integers arr, return true if we can partition the array into three non-empty parts
 * with equal sums.
 * Formally, we can partition the array if we can find indexes i + 1 < j with (arr[0] + arr[1] + ... +
 * arr[i] == arr[i + 1] + arr[i + 2] + ... + arr[j - 1] == arr[j] + arr[j + 1] + ... + arr[arr.length -
 * 1])
 */
auto SubarraysOfEqualSum(const ArrayType &nums) {
    const auto total = std::accumulate(nums.cbegin(), nums.cend(), 0);
    const auto average = total / 3;
    if (average * 3 != total) {
        return false;
    }

    int sum = 0;
    int count = 0;
    for (const auto n : nums) {
        sum += n;
        if (sum == average) {
            if (++count == 3) {
                return true;
            }
            sum = 0;
        }
    }

    return false;
}


/**
 * @reference   Partition Equal Subset Sum
 *              https://leetcode.com/problems/partition-equal-subset-sum/
 *
 * Given a non-empty array nums containing only positive integers, find if the array can be partitioned
 * into two subsets such that the sum of elements in both subsets is equal.
 */
auto EqualSumSubset(const ArrayType &nums) {
    if (nums.size() < 2) {
        return false;
    }

    const auto sum = std::accumulate(nums.cbegin(), nums.cend(), 0);
    const auto average = sum / 2;
    if (average * 2 != sum) {
        return false;
    }

    bool dp[average + 1] = {true};
    for (const auto n : nums) {
        for (int i = average; i > 0; --i) {
            if (i >= n) {
                dp[i] = dp[i] or dp[i - n];
            }
        }
    }

    return dp[average];
}


/**
 * @reference   Fair Distribution of Cookies
 *              https://leetcode.com/problems/fair-distribution-of-cookies/
 *
 * You are given an integer array cookies, where cookies[i] denotes the number of cookies in the ith
 * bag. You are also given an integer k that denotes the number of children to distribute all the bags
 * of cookies to. All the cookies in the same bag must go to the same child and cannot be split up.
 * The unfairness of a distribution is defined as the maximum total cookies obtained by a single child
 * in the distribution.
 * Return the minimum unfairness of all distributions.
 * 2 <= cookies.length <= 8
 */
int DistributeCookies(std::size_t i,
                      const ArrayType &cookies,
                      const int k,
                      const std::size_t empty_bag_count,
                      ArrayType &distribution) {
    if (cookies.size() - i < empty_bag_count) {
        return INT_MAX;
    }

    if (i == cookies.size()) {
        return *std::max_element(distribution.cbegin(), distribution.cend());
    }

    int result = INT_MAX;
    for (int j = 0; j < k; ++j) {
        const auto is_empty_bag = not distribution[j];
        distribution[j] += cookies[i];

        result = std::min(
            result,
            DistributeCookies(i + 1, cookies, k, empty_bag_count - is_empty_bag, distribution));

        distribution[j] -= cookies[i];
    }

    return result;
}

auto DistributeCookies(const ArrayType &cookies, const int k) {
    ArrayType distribution(k, 0);

    return DistributeCookies(0, cookies, k, k, distribution);
}

} //namespace


const ArrayType SAMPLE1 = {1, 1, 2, 2, 2};
const ArrayType SAMPLE2 = {3, 3, 3, 3, 4};
const ArrayType SAMPLE3 = {1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3};


THE_BENCHMARK(MatchsticksToSquare_Recursive, SAMPLE1);

SIMPLE_TEST(MatchsticksToSquare_Recursive, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(MatchsticksToSquare_Recursive, TestSAMPLE2, false, SAMPLE2);
SIMPLE_TEST(MatchsticksToSquare_Recursive, TestSAMPLE3, true, SAMPLE3);


THE_BENCHMARK(MatchsticksToSquare_DP, SAMPLE1);

SIMPLE_TEST(MatchsticksToSquare_DP, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(MatchsticksToSquare_DP, TestSAMPLE2, false, SAMPLE2);
SIMPLE_TEST(MatchsticksToSquare_DP, TestSAMPLE3, true, SAMPLE3);


const ArrayType SAMPLE4 = {2, 1, 4, 5, 6};
const ArrayType SAMPLE5 = {2, 1, 5, 5, 6};
const ArrayType SAMPLE6 = {2, 1, 4, 5, 3, 3};
const ArrayType SAMPLE7 = {4, 3, 2, 3, 5, 2, 1};


THE_BENCHMARK(SubsetsOfEqualSum, SAMPLE1, 4);

SIMPLE_TEST(SubsetsOfEqualSum, TestSAMPLE1, true, SAMPLE1, 4);
SIMPLE_TEST(SubsetsOfEqualSum, TestSAMPLE2, false, SAMPLE2, 4);
SIMPLE_TEST(SubsetsOfEqualSum, TestSAMPLE3, true, SAMPLE3, 4);
SIMPLE_TEST(SubsetsOfEqualSum, TestSAMPLE4, true, SAMPLE4, 3);
SIMPLE_TEST(SubsetsOfEqualSum, TestSAMPLE5, false, SAMPLE5, 3);
SIMPLE_TEST(SubsetsOfEqualSum, TestSAMPLE6, true, SAMPLE6, 3);
SIMPLE_TEST(SubsetsOfEqualSum, TestSAMPLE7, true, SAMPLE7, 4);


const ArrayType SAMPLE1A = {0, 2, 1, -6, 6, -7, 9, 1, 2, 0, 1};
const ArrayType SAMPLE2A = {0, 2, 1, -6, 6, 7, 9, -1, 2, 0, 1};
const ArrayType SAMPLE3A = {3, 3, 6, 5, -2, 2, 5, 1, -9, 4};
const ArrayType SAMPLE4A = {1, -1, 1, -1};


THE_BENCHMARK(SubarraysOfEqualSum, SAMPLE1A);

SIMPLE_TEST(SubarraysOfEqualSum, TestSAMPLE1, true, SAMPLE1A);
SIMPLE_TEST(SubarraysOfEqualSum, TestSAMPLE2, false, SAMPLE2A);
SIMPLE_TEST(SubarraysOfEqualSum, TestSAMPLE3, true, SAMPLE3A);
SIMPLE_TEST(SubarraysOfEqualSum, TestSAMPLE4, false, SAMPLE4A);


const ArrayType SAMPLE1T = {1, 5, 11, 5};
const ArrayType SAMPLE2T = {1, 2, 3, 5};


THE_BENCHMARK(EqualSumSubset, SAMPLE1T);

SIMPLE_TEST(EqualSumSubset, TestSAMPLE1, true, SAMPLE1T);
SIMPLE_TEST(EqualSumSubset, TestSAMPLE2, false, SAMPLE2T);


const ArrayType SAMPLE1C = {8, 15, 10, 20, 8};
const ArrayType SAMPLE2C = {6, 1, 3, 2, 2, 4, 1, 2};


THE_BENCHMARK(DistributeCookies, SAMPLE1C, 2);

SIMPLE_TEST(DistributeCookies, TestSAMPLE1, 31, SAMPLE1C, 2);
SIMPLE_TEST(DistributeCookies, TestSAMPLE2, 7, SAMPLE2C, 3);
