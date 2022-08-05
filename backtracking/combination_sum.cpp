#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;
using ResultType = std::multiset<ArrayType>;

/** Combination Sum
 *
 * @reference   https://leetcode.com/problems/combination-sum/
 *
 * Given an array of distinct integers candidates and a target integer target, return a list of
 * all unique combinations of candidates where the chosen numbers sum to target. You may return
 * the combinations in any order.
 * The same number may be chosen from candidates an unlimited number of times. Two combinations
 * are unique if the frequency of at least one of the chosen numbers is different.
 * It is guaranteed that the number of unique combinations that sum up to target is less than 150
 * combinations for the given input.
 */
void CombinationSum(const ArrayType &candidates,
                    const int target,
                    const std::size_t index,
                    ArrayType &current,
                    ResultType &results) {
    if (target == 0) {
        results.insert(current);
        return;
    }

    if (index == candidates.size() or target < 0) {
        return;
    }

    current.push_back(candidates[index]);
    CombinationSum(candidates, target - candidates[index], index, current, results);
    current.pop_back();

    CombinationSum(candidates, target, index + 1, current, results);
}

inline auto CombinationSum(const ArrayType &candidates, const int target) {
    ResultType results;
    ArrayType current;
    CombinationSum(candidates, target, 0, current, results);
    return results;
}


/**
 * @reference   Combination Sum II
 *              https://leetcode.com/problems/combination-sum-ii/
 *
 * Given a collection of candidate numbers (candidates) and a target number (target), find all
 * unique combinations in candidates where the candidate numbers sum to target.
 * Each number in candidates may only be used once in the combination.
 * Note: The solution set must not contain duplicate combinations.
 */
void CombinationSumWithDuplicates(const ArrayType &candidates,
                                  const int target,
                                  std::size_t i,
                                  ArrayType &one_combination,
                                  ResultType &results) {
    if (target == 0) {
        results.insert(one_combination);
        return;
    }

    if (i == candidates.size() or target < 0) {
        return;
    }

    one_combination.push_back(candidates[i]);
    CombinationSumWithDuplicates(
        candidates, target - candidates[i], i + 1, one_combination, results);
    one_combination.pop_back();

    ++i;
    while (i < candidates.size() and candidates[i] == candidates[i - 1]) {
        ++i;
    }
    CombinationSumWithDuplicates(candidates, target, i, one_combination, results);
}

inline auto CombinationSumWithDuplicates(ArrayType candidates, const int target) {
    std::sort(candidates.begin(), candidates.end());

    ResultType results;
    ArrayType one_combination;
    CombinationSumWithDuplicates(candidates, target, 0, one_combination, results);

    return results;
}


/**
 * @reference   Combination Sum III
 *              https://leetcode.com/problems/combination-sum-iii/
 *
 * Find all valid combinations of k numbers that sum up to n such that the following conditions
 * are true:
 *  Only numbers 1 through 9 are used.
 *  Each number is used at most once.
 * Return a list of all possible valid combinations. The list must not contain the same combination
 * twice, and the combinations may be returned in any order.
 */
auto AllCombinationsOfLength_Iterative(const char k, const int n) {
    ResultType result;
    int i = 0;
    ArrayType one_combination(k, 0);
    while (i >= 0) {
        if (++one_combination[i] > 9) {
            --i;
        } else if (i == k - 1) {
            const auto sum = std::accumulate(one_combination.cbegin(), one_combination.cend(), 0);
            if (sum == n) {
                result.insert(one_combination);
            }
        } else {
            ++i;
            one_combination[i] = one_combination[i - 1];
        }
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {2, 3, 6, 7};
const ResultType EXPECTED1 = {{2, 2, 3}, {7}};

const ArrayType SAMPLE2 = {2, 3, 5};
const ResultType EXPECTED2 = {{2, 2, 2, 2}, {2, 3, 3}, {3, 5}};

const ArrayType SAMPLE3 = {2};
const ResultType EXPECTED3 = {};


THE_BENCHMARK(CombinationSum, SAMPLE1, 7);

SIMPLE_TEST(CombinationSum, TestSAMPLE1, EXPECTED1, SAMPLE1, 7);
SIMPLE_TEST(CombinationSum, TestSAMPLE2, EXPECTED2, SAMPLE2, 8);
SIMPLE_TEST(CombinationSum, TestSAMPLE3, EXPECTED3, SAMPLE3, 1);


const ArrayType SAMPLE1D = {10, 1, 2, 7, 6, 1, 5};
const ResultType EXPECTED1D = {{1, 1, 6}, {1, 2, 5}, {1, 7}, {2, 6}};

const ArrayType SAMPLE2D = {2, 5, 2, 1, 2};
const ResultType EXPECTED2D = {{1, 2, 2}, {5}};


THE_BENCHMARK(CombinationSumWithDuplicates, SAMPLE1D, 8);

SIMPLE_TEST(CombinationSumWithDuplicates, TestSAMPLE1, EXPECTED1D, SAMPLE1D, 8);
SIMPLE_TEST(CombinationSumWithDuplicates, TestSAMPLE2, EXPECTED2D, SAMPLE2D, 5);


const ResultType EXPECTED1L = {{1, 2, 4}};
const ResultType EXPECTED2L = {{1, 2, 6}, {1, 3, 5}, {2, 3, 4}};


THE_BENCHMARK(AllCombinationsOfLength_Iterative, 3, 7);

SIMPLE_TEST(AllCombinationsOfLength_Iterative, TestSAMPLE1, EXPECTED1L, 3, 7);
SIMPLE_TEST(AllCombinationsOfLength_Iterative, TestSAMPLE2, EXPECTED2L, 3, 9);
SIMPLE_TEST(AllCombinationsOfLength_Iterative, TestSAMPLE3, EXPECTED3, 4, 1);
