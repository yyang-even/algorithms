#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

using ArrayType = std::vector<int>;
/** Array elements that appear more than once
 *
 * @reference   https://www.geeksforgeeks.org/array-elements-that-appear-more-than-once/
 *
 * Given an integer array, print all repeating elements (Elements that appear
 * more than once) in array. The output should contain elements according to
 * their first occurrences.
 *
 * @complexity  O(n)
 */
auto FindRepeatedElements(const ArrayType &values) {
    std::unordered_map<ArrayType::value_type, ArrayType::size_type> counters;
    for (const auto elem : values) {
        ++counters[elem];
    }

    ArrayType output;
    for (const auto elem : values) {
        auto iter = counters.find(elem);
        if (iter->second > 1) {
            iter->second = 0;
            output.push_back(elem);
        }
    }

    return output;
}


const ArrayType SAMPLE1 = {12, 10, 9, 45, 2, 10, 10, 45};
const ArrayType EXPECTED1 = {10, 45};
const ArrayType SAMPLE2 = {1, 1, 1, 1, 1};
const ArrayType EXPECTED2 = {1};

SIMPLE_BENCHMARK(FindRepeatedElements, SAMPLE1);

SIMPLE_TEST(FindRepeatedElements, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(FindRepeatedElements, TestSAMPLE2, EXPECTED2, SAMPLE2);
