#include "common_header.h"

#include "counting_sort.h"


namespace {

using ArrayType = std::vector<int>;
using Query = std::pair<ArrayType::value_type, ArrayType::value_type>;

/**
 * @reference   Queries for counts of array elements with values in given range
 *              https://www.geeksforgeeks.org/queries-counts-array-elements-values-given-range/
 *
 * Given an unsorted array of size n, find no of elements between two elements i and j (both inclusive).
 *
 * @tags    #sorting #binary-search
 */
auto QueriesForCountsInRange_Sort(ArrayType values, const std::vector<Query> &queries) {
    std::sort(values.begin(), values.end());

    std::vector<ArrayType::difference_type> output;
    for (const auto &[i, j] : queries) {
        const auto lower = std::lower_bound(values.cbegin(), values.cend(), i);
        const auto upper = std::upper_bound(values.cbegin(), values.cend(), j);
        output.push_back(upper - lower);
    }

    return output;
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 8.2-4.
 *
 * @tags    #sorting #counting-sort #min-max-element
 */
auto QueriesForCountsInRange_CountingSort(const ArrayType &values,
                                          const std::vector<Query> &queries) {
    std::vector<ArrayType::difference_type> output;

    if (values.empty()) {
        return output;
    }

    const auto [min_iter, max_iter] = std::minmax_element(values.cbegin(), values.cend());
    const auto RANGE = *max_iter - *min_iter + 1;
    const auto ToIndex = [min = *min_iter](const auto v) {
        return v - min;
    };

    const auto counter = ToCountingArray(values, RANGE, ToIndex);

    for (const auto &[left, right] : queries) {
        const auto lower = counter[ToIndex(std::max(left, *min_iter))];
        const auto upper = counter[ToIndex(std::min(right, *max_iter))];
        output.push_back(upper - lower + 1);
    }

    return output;
}


/**
 * @reference   Plates Between Candles
 *              https://leetcode.com/problems/plates-between-candles/
 *
 * There is a long table with a line of plates and candles arranged on top of it. You are given a
 * 0-indexed string s consisting of characters '*' and '|' only, where a '*' represents a plate and a
 * '|' represents a candle.
 * You are also given a 0-indexed 2D integer array queries where queries[i] = [lefti, righti] denotes
 * the substring s[lefti...righti] (inclusive). For each query, you need to find the number of plates
 * between candles that are in the substring. A plate is considered between candles if there is at least
 * one candle to its left and at least one candle to its right in the substring.
 *  For example, s = "||**||**|*", and a query [3, 8] denotes the substring "*||**|". The number of
 *  plates between candles in this substring is 2, as each of the two plates has at least one candle in
 *  the substring to its left and right.
 * Return an integer array answer where answer[i] is the answer to the ith query.
 *
 * @tags    #binary-search
 */
auto PlatesBetweenCandles(const std::string_view s, const std::vector<ArrayType> &queries) {
    std::vector<int> candles;
    for (std::size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '|') {
            candles.push_back(i);
        }
    }

    std::vector<int> result;
    for (const auto &q : queries) {
        const int i = std::lower_bound(candles.cbegin(), candles.cend(), q[0]) - candles.cbegin();
        const int j =
            std::upper_bound(candles.cbegin(), candles.cend(), q[1]) - candles.cbegin() - 1;
        if (i < j) {
            const auto plates = candles[j] - candles[i] - (j - i);
            result.push_back(plates);
        } else {
            result.push_back(0);
        }
    }

    return result;
}

} //namespace


const ArrayType VALUES = {1, 3, 4, 9, 10, 3};
const std::vector<Query> QUERIES = {{1, 4}, {9, 12}};
const std::vector<ArrayType::difference_type> EXPECTED = {4, 2};


THE_BENCHMARK(QueriesForCountsInRange_Sort, VALUES, QUERIES);

SIMPLE_TEST(QueriesForCountsInRange_Sort, TestSAMPLE1, EXPECTED, VALUES, QUERIES);


THE_BENCHMARK(QueriesForCountsInRange_CountingSort, VALUES, QUERIES);

SIMPLE_TEST(QueriesForCountsInRange_CountingSort, TestSAMPLE1, EXPECTED, VALUES, QUERIES);


const std::vector<ArrayType> QUERIES_CPQ1 = {{2, 5}, {5, 9}};
const std::vector EXPECTED_CPQ1 = {2, 3};

const std::vector<ArrayType> QUERIES_CPQ2 = {{1, 17}, {4, 5}, {14, 17}, {5, 11}, {15, 16}};
const std::vector EXPECTED_CPQ2 = {9, 0, 0, 0, 0};

const std::vector<ArrayType> QUERIES_CPQ3 = {{2, 2}};
const std::vector EXPECTED_CPQ3 = {0};

const std::vector<ArrayType> QUERIES_CPQ4 = {{0, 0}, {1, 3}};
const std::vector EXPECTED_CPQ4 = {0, 1};


THE_BENCHMARK(PlatesBetweenCandles, "**|**|***|", QUERIES_CPQ1);

SIMPLE_TEST(PlatesBetweenCandles, TestSAMPLE1, EXPECTED_CPQ1, "**|**|***|", QUERIES_CPQ1);
SIMPLE_TEST(
    PlatesBetweenCandles, TestSAMPLE2, EXPECTED_CPQ2, "***|**|*****|**||**|*", QUERIES_CPQ2);
SIMPLE_TEST(PlatesBetweenCandles, TestSAMPLE3, EXPECTED_CPQ3, "***", QUERIES_CPQ3);
SIMPLE_TEST(PlatesBetweenCandles, TestSAMPLE4, EXPECTED_CPQ4, "*|*|||", QUERIES_CPQ4);
