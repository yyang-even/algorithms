#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Rearrange an array so that arr[i] becomes arr[arr[i]] with O(1) extra space
 *
 * @reference   https://www.geeksforgeeks.org/rearrange-given-array-place/
 *
 * Given an array arr[] of size n where every element is in range from 0 to n-1.
 * Rearrange the given array so that arr[i] becomes arr[arr[i]]. This should be done
 * with O(1) extra space.
 */
auto RearrangeArrayInPlace(ArrayType values) {
    std::transform(values.cbegin(), values.cend(),
    values.begin(), [&values](const auto v) {
        return v + values[v] % values.size() * values.size();
    });

    std::transform(values.cbegin(), values.cend(),
    values.begin(), [&values](const auto v) {
        return v / values.size();
    });

    return values;
}

}//namespace


const ArrayType SAMPLE1 = {3, 2, 0, 1};
const ArrayType EXPECTED1 = {1, 0, 3, 2};

const ArrayType SAMPLE2 = {4, 0, 2, 1, 3};
const ArrayType EXPECTED2 = {3, 4, 2, 0, 1};

const ArrayType SAMPLE3 = {0, 1, 2, 3};
const ArrayType EXPECTED3 = {0, 1, 2, 3};


THE_BENCHMARK(RearrangeArrayInPlace, SAMPLE1);

SIMPLE_TEST(RearrangeArrayInPlace, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(RearrangeArrayInPlace, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(RearrangeArrayInPlace, TestSAMPLE3, EXPECTED3, SAMPLE3);
