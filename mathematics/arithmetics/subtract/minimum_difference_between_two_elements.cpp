#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;
using PairArrayType =
    std::vector<std::pair<ArrayType::value_type, ArrayType::value_type>>;

/** Find minimum difference between any two elements
 *
 * @reference   https://www.geeksforgeeks.org/find-minimum-difference-pair/
 *
 * Given an unsorted array, find the minimum difference between any pair in given array.
 */
auto FindMinDifferenceBetweenTwoElements(ArrayType elements,
                                         PairArrayType *const closest_pairs = nullptr) {
    const auto N = elements.size();
    assert(N > 1);

    std::sort(elements.begin(), elements.end());

    auto min_diff = std::numeric_limits<ArrayType::value_type>::max();
    for (ArrayType::size_type i = 1; i < N; ++i) {
        const auto diff = elements[i] - elements[i - 1];
        if (diff < min_diff) {
            min_diff = diff;
        }
    }

    if (closest_pairs) {
        for (ArrayType::size_type i = 1; i < N; ++i) {
            if (elements[i] - elements[i - 1] == min_diff) {
                closest_pairs->emplace_back(elements[i - 1], elements[i]);
            }
        }
    }

    return min_diff;
}


/**
 * @reference   Closest numbers from a list of unsorted integers
 *              https://www.geeksforgeeks.org/closest-numbers-list-unsorted-integers/
 *
 * Given a list of distinct unsorted integers, find the pair of elements that have the
 * smallest absolute difference between them? If there are multiple pairs, find them all.
 */
inline auto AllClosestNumbers(const ArrayType &elements) {
    PairArrayType closest_pairs;
    FindMinDifferenceBetweenTwoElements(elements, &closest_pairs);
    return closest_pairs;
}

}//namespace


const ArrayType SAMPLE1 = {1, 5, 3, 19, 18, 25};
const ArrayType SAMPLE2 = {30, 5, 20, 9};
const ArrayType SAMPLE3 = {1, 19, -4, 31, 38, 25, 100};
const ArrayType SAMPLE4 = {10, 50, 12, 100};
const ArrayType SAMPLE5 = {5, 4, 3, 2};


THE_BENCHMARK(FindMinDifferenceBetweenTwoElements, SAMPLE1);

SIMPLE_TEST(FindMinDifferenceBetweenTwoElements, TestSample1, 1, SAMPLE1);
SIMPLE_TEST(FindMinDifferenceBetweenTwoElements, TestSample2, 4, SAMPLE2);
SIMPLE_TEST(FindMinDifferenceBetweenTwoElements, TestSample3, 5, SAMPLE3);
SIMPLE_TEST(FindMinDifferenceBetweenTwoElements, TestSample4, 2, SAMPLE4);
SIMPLE_TEST(FindMinDifferenceBetweenTwoElements, TestSample5, 1, SAMPLE5);


const PairArrayType EXPECTED4 = {{10, 12}};
const PairArrayType EXPECTED5 = {{2, 3}, {3, 4}, {4, 5}};


THE_BENCHMARK(AllClosestNumbers, SAMPLE1);

SIMPLE_TEST(AllClosestNumbers, TestSample4, EXPECTED4, SAMPLE4);
SIMPLE_TEST(AllClosestNumbers, TestSample5, EXPECTED5, SAMPLE5);
