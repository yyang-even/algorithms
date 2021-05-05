#include "common_header.h"

#include "median.h"


namespace {

using ArrayType = std::vector<int>;
using OutputType = std::unordered_set<ArrayType::value_type>;

/** Find K closest elements to the median
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 9.3-7.
 *
 * Describe an O(n)-time algorithm that, given a set S of n distinct numbers and a positive
 * integer k <= n, determines the k numbers in S that are closest to the median of S.
 *
 * @note    Since in this problem, the terms median and closest is not well defined, so
 *  there could be different ways to interpret this problem.
 */
/**
 * @note    Here, closest means the elements that have nearest index when S is sorted.
 */
auto KClosestElementsToMedian_Index(ArrayType elements, const ArrayType::size_type K) {
    assert(K <= elements.size());

    const auto k_begin = elements.begin() + (elements.size() - K) / 2;
    std::nth_element(elements.begin(), k_begin, elements.end());
    const auto k_end = k_begin + K;
    std::nth_element(k_begin, k_end, elements.end());

    return OutputType(std::make_move_iterator(k_begin), std::make_move_iterator(k_end));
}


/**
 * @reference   Find K closest elements to the median
 *              https://knaidu.gitbooks.io/problem-solving/searching/k_closest_to_median.html
 *
 * @note    Here, closest means smallest absolute differences.
 */
auto KClosestElementsToMedian_Differences(ArrayType elements,
                                          const ArrayType::size_type K) {
    const auto median = Median_QuickSelect(elements);

    using DiffValuePair = std::pair<ArrayType::value_type, ArrayType::value_type>;
    std::vector<DiffValuePair> diff_array;
    for (const auto v : elements) {
        diff_array.emplace_back(std::abs(v - median), v);
    }

    const auto kth = diff_array.begin() + K;
    std::nth_element(diff_array.begin(), kth, diff_array.end());
    OutputType outputs;
    for (auto iter = diff_array.begin(); iter != kth; ++iter) {
        outputs.emplace(std::move(iter->second));
    }

    return outputs;
}

}//namespace


using InitializerType = std::initializer_list<ArrayType::value_type>;

constexpr InitializerType VALUES1 = {24, 8, 42, 75, 29, 77, 38, 57};
const OutputType EXPECTED1 = {38};
const OutputType EXPECTED2 = {38, 42};
const OutputType EXPECTED3 = {29, 38, 42};
constexpr InitializerType VALUES2 = {24, 8, 42, 75, 29, 38, 57};
const OutputType EXPECTED4 = {29, 38};


THE_BENCHMARK(KClosestElementsToMedian_Index, VALUES1, 3);

SIMPLE_TEST(KClosestElementsToMedian_Index, TestSAMPLE0, {}, VALUES1, 0);
SIMPLE_TEST(KClosestElementsToMedian_Index, TestSAMPLE1, EXPECTED1, VALUES1, 1);
SIMPLE_TEST(KClosestElementsToMedian_Index, TestSAMPLE2, EXPECTED2, VALUES1, 2);
SIMPLE_TEST(KClosestElementsToMedian_Index, TestSAMPLE3, EXPECTED3, VALUES1, 3);
SIMPLE_TEST(KClosestElementsToMedian_Index, TestSAMPLE4, VALUES1,
            VALUES1, VALUES1.size());
SIMPLE_TEST(KClosestElementsToMedian_Index, TestSAMPLE5, EXPECTED1, VALUES2, 1);
SIMPLE_TEST(KClosestElementsToMedian_Index, TestSAMPLE6, EXPECTED4, VALUES2, 2);
SIMPLE_TEST(KClosestElementsToMedian_Index, TestSAMPLE7, VALUES2,
            VALUES2, VALUES2.size());


const ArrayType VALUES3 = {1, 2, 3, 4, 9, 99, 999};
const OutputType EXPECTED5 = {2, 3, 4};


THE_BENCHMARK(KClosestElementsToMedian_Differences, VALUES1, 3);

SIMPLE_TEST(KClosestElementsToMedian_Differences, TestSAMPLE0, {}, VALUES1, 0);
SIMPLE_TEST(KClosestElementsToMedian_Differences, TestSAMPLE1, EXPECTED1, VALUES1, 1);
SIMPLE_TEST(KClosestElementsToMedian_Differences, TestSAMPLE2, EXPECTED2, VALUES1, 2);
SIMPLE_TEST(KClosestElementsToMedian_Differences, TestSAMPLE3, EXPECTED3, VALUES1, 3);
SIMPLE_TEST(KClosestElementsToMedian_Differences, TestSAMPLE4, VALUES1,
            VALUES1, VALUES1.size());
SIMPLE_TEST(KClosestElementsToMedian_Differences, TestSAMPLE5, EXPECTED1, VALUES2, 1);
SIMPLE_TEST(KClosestElementsToMedian_Differences, TestSAMPLE6, EXPECTED2, VALUES2, 2);
SIMPLE_TEST(KClosestElementsToMedian_Differences, TestSAMPLE7, VALUES2,
            VALUES2, VALUES2.size());
SIMPLE_TEST(KClosestElementsToMedian_Differences, TestSAMPLE8, EXPECTED5, VALUES3, 3);
