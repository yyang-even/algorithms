#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;
using OutputType = std::vector<std::pair<ArrayType::value_type, ArrayType::value_type>>;

/** Given two unsorted arrays, find all pairs whose sum is x
 *
 * @reference   https://www.geeksforgeeks.org/given-two-unsorted-arrays-find-pairs-whose-sum-x/
 *
 * Given two unsorted arrays of distinct elements, the task is to find all pairs from
 * both arrays whose sum is equal to x.
 */
auto FindAllPairsSumAsN_Hash(const ArrayType &arr1, const ArrayType &arr2,
                             const ArrayType::value_type SUM) {
    std::unordered_set array1_set(arr1.cbegin(), arr1.cend());
    OutputType outputs;

    for (const auto elem : arr2) {
        const auto pair = SUM - elem;
        if (array1_set.find(pair) != array1_set.cend()) {
            outputs.emplace_back(pair, elem);
        }
    }

    return outputs;
}


/**
 * @reference   Count pairs from two sorted arrays whose sum is equal to a given value x
 *              https://www.geeksforgeeks.org/count-pairs-two-sorted-arrays-whose-sum-equal-given-value-x/
 *
 * Given two sorted arrays of size m and n of distinct elements. Given a value x. The
 * problem is to count all pairs from both arrays whose sum is equal to x. Note: The
 * pair has an element from each array.
 */
auto FindAllPairsSumAsN_TwoPointers(const ArrayType &arr1, const ArrayType &arr2,
                                    const ArrayType::value_type SUM) {
    assert(std::is_sorted(arr1.cbegin(), arr1.cend()));
    assert(std::is_sorted(arr2.cbegin(), arr2.cend()));

    OutputType outputs;
    auto l = arr1.cbegin();
    auto r = arr2.crbegin();

    while (l != arr1.cend() and r != arr2.crend()) {
        const auto new_sum = *l + *r;
        if (new_sum == SUM) {
            outputs.emplace_back(*l, *r);
            ++l;
            ++r;
        } else if (new_sum < SUM) {
            ++l;
        } else {
            ++r;
        }
    }

    return outputs;
}

inline auto
FindAllPairsSumAsN_Sort_TwoPointers(ArrayType arr1, ArrayType arr2,
                                    const ArrayType::value_type SUM) {
    std::sort(arr1.begin(), arr1.end());
    std::sort(arr2.begin(), arr2.end());

    return FindAllPairsSumAsN_TwoPointers(arr1, arr2, SUM);
}

}//namespace


const ArrayType SAMPLE1L = { -1, -2, 4, -6, 5, 7};
const ArrayType SAMPLE1R = {6, 3, 4, 0};
const OutputType EXPECTED1 = {{5, 3}, {4, 4}};

const ArrayType SAMPLE2L = {1, 2, 4, 5, 7};
const ArrayType SAMPLE2R = {5, 6, 3, 4, 8};
const OutputType EXPECTED2 = {{4, 5}, {5, 4}, {1, 8}};

const ArrayType SAMPLE3L = {1, 2, 3, 7, 5, 4};
const ArrayType SAMPLE3R = {0, 7, 4, 3, 2, 1};
const OutputType EXPECTED3 = {{1, 7}, {4, 4}, {5, 3}, {7, 1}};

const ArrayType SAMPLE4L = {1, 0, -4, 7, 6, 4};
const ArrayType SAMPLE4R = {0, 2, 4, -3, 2, 1};
const OutputType EXPECTED4 = {{6, 2}, {4, 4}, {6, 2}, {7, 1}};


THE_BENCHMARK(FindAllPairsSumAsN_Hash, SAMPLE1L, SAMPLE1R, 8);

SIMPLE_TEST(FindAllPairsSumAsN_Hash, TestSample1, EXPECTED1, SAMPLE1L, SAMPLE1R, 8);
SIMPLE_TEST(FindAllPairsSumAsN_Hash, TestSample2, EXPECTED2, SAMPLE2L, SAMPLE2R, 9);
SIMPLE_TEST(FindAllPairsSumAsN_Hash, TestSample3, EXPECTED3, SAMPLE3L, SAMPLE3R, 8);
SIMPLE_TEST(FindAllPairsSumAsN_Hash, TestSample4, EXPECTED4, SAMPLE4L, SAMPLE4R, 8);


const OutputType EXPECTED_SORTED1 = {{4, 4}, {5, 3}};
const OutputType EXPECTED_SORTED2 = {{1, 8}, {4, 5}, {5, 4}};


THE_BENCHMARK(FindAllPairsSumAsN_Sort_TwoPointers, SAMPLE1L, SAMPLE1R, 8);

SIMPLE_TEST(FindAllPairsSumAsN_Sort_TwoPointers, TestSample1, EXPECTED_SORTED1,
            SAMPLE1L, SAMPLE1R, 8);
SIMPLE_TEST(FindAllPairsSumAsN_Sort_TwoPointers, TestSample2, EXPECTED_SORTED2,
            SAMPLE2L, SAMPLE2R, 9);
SIMPLE_TEST(FindAllPairsSumAsN_Sort_TwoPointers, TestSample3, EXPECTED3,
            SAMPLE3L, SAMPLE3R, 8);
