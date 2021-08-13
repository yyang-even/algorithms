#include "common_header.h"

#include "hash/hash.h"


namespace {

using ArrayType = std::vector<int>;

/** Array of Doubled Pairs
 *
 * @reference   https://leetcode.com/problems/array-of-doubled-pairs/
 *
 * Given an array of integers arr of even length, return true if and only if it is
 * possible to reorder it such that arr[2 * i + 1] = 2 * arr[2 * i] for every
 * 0 <= i < len(arr) / 2.
 */
auto ArrayDoubledPairs(const ArrayType &elements) {
    auto counts = ToFrequencyHashTable(elements);

    ArrayType keys;
    for (const auto [value, _] : counts) {
        keys.push_back(value);
    }

    std::sort(keys.begin(), keys.end(), [](const auto lhs, const auto rhs) {
        return std::abs(lhs) < std::abs(rhs);
    });

    for (const auto one : keys) {
        const auto the_other = 2 * one;
        if (counts[the_other] < counts[one]) {
            return false;
        }
        counts[the_other] -= counts[one];
    }

    return true;
}

}//namespace


const ArrayType SAMPLE1 = {3, 1, 3, 6};
const ArrayType SAMPLE2 = {2, 1, 2, 6};
const ArrayType SAMPLE3 = {4, -2, 2, -4};
const ArrayType SAMPLE4 = {1, 2, 4, 16, 8, 4};
const ArrayType SAMPLE5 = {-5, -2};


THE_BENCHMARK(ArrayDoubledPairs, SAMPLE1);

SIMPLE_TEST(ArrayDoubledPairs, TestSAMPLE1, false, SAMPLE1);
SIMPLE_TEST(ArrayDoubledPairs, TestSAMPLE2, false, SAMPLE2);
SIMPLE_TEST(ArrayDoubledPairs, TestSAMPLE3, true, SAMPLE3);
SIMPLE_TEST(ArrayDoubledPairs, TestSAMPLE4, false, SAMPLE4);
SIMPLE_TEST(ArrayDoubledPairs, TestSAMPLE5, false, SAMPLE5);
