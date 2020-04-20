#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Prefix Sum Array – Implementation and Applications in Competitive Programming
 *
 * @reference   https://www.geeksforgeeks.org/prefix-sum-array-implementation-applications-competitive-programming/
 *
 * Given an array arr[] of size n, its prefix sum array is another array prefixSum[] of
 * same size such that the value of prefixSum[i] is arr[0] + arr[1] + arr[2] … arr[i].
 */
auto PrefixSumArray(ArrayType elements) {
    for (ArrayType::size_type i = 1; i < elements.size(); ++i) {
        elements[i] += elements[i - 1];
    }

    return elements;
}


/**
 * @reference   Prefix Sum Array – Implementation and Applications in Competitive Programming
 *              https://www.geeksforgeeks.org/prefix-sum-array-implementation-applications-competitive-programming/
 *
 * Consider an array of size n with all initial values as 0. Perform given ‘m’ add
 * operations from index ‘a’ to ‘b’ and evaluate highest element in array. An add
 * operation adds 100 to all elements from a to b (both inclusive).
 */
using RangeType = std::pair<ArrayType::size_type, ArrayType::size_type>;
using RangeArray = std::vector<RangeType>;

auto MaxAfterRangesOfAdditions(const ArrayType::size_type size, const RangeArray &ranges) {
    ArrayType elements(size, 0);

    for (const auto &a_range : ranges) {
        elements[a_range.first] += 100;
        if (a_range.second < size) {
            elements[a_range.second + 1] -= 100;
        }
    }

    const auto prefix_sums = PrefixSumArray(std::move(elements));

    return *std::max_element(prefix_sums.cbegin(), prefix_sums.cend());
}

}//namespace


const ArrayType SAMPLE1 = {10, 20, 10, 5, 15};
const ArrayType EXPECTED1 = {10, 30, 40, 45, 60};

const ArrayType SAMPLE2 = {10, 4, 16, 20};
const ArrayType EXPECTED2 = {10, 14, 30, 50};


SIMPLE_BENCHMARK(PrefixSumArray, SAMPLE1);

SIMPLE_TEST(PrefixSumArray, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(PrefixSumArray, TestSAMPLE2, EXPECTED2, SAMPLE2);


const RangeArray SAMPLE_RANGES1 = {{2, 4}, {1, 3}, {1, 2}};


SIMPLE_BENCHMARK(MaxAfterRangesOfAdditions, 5, SAMPLE_RANGES1);

SIMPLE_TEST(MaxAfterRangesOfAdditions, TestSAMPLE1, 300, 5, SAMPLE_RANGES1);
