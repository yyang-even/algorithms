#include "common_header.h"

#include "hash/hash.h"


namespace {

using ArrayType = std::vector<int>;

/** Sort elements by frequency | Set 1
 *
 * @reference   https://www.geeksforgeeks.org/sort-elements-by-frequency/
 * @reference   Sort elements by frequency | Set 2
 *              https://www.geeksforgeeks.org/sort-elements-by-frequency-set-2/
 * @reference   Sorting Array Elements By Frequency | Set 3 (Using STL)
 *              https://www.geeksforgeeks.org/sorting-array-elements-frequency-set-3-using-stl/
 * @reference   Sort elements by frequency | Set 4 (Efficient approach using hash)
 *              https://www.geeksforgeeks.org/sort-elements-frequency-set-4-efficient-approach-using-hash/
 * @reference   Sort elements by frequency | Set 5 (using Java Map)
 *              https://www.geeksforgeeks.org/sort-elements-by-frequency-set-5-using-java-map/
 *
 * Print the elements of an array in the decreasing frequency if 2 numbers have same
 * frequency then print the one which came first.
 *
 * @reference   Sort a string according to the frequency of characters
 *              https://www.geeksforgeeks.org/sort-a-string-according-to-the-frequency-of-characters/
 */
auto SortByFrequency(ArrayType elements) {
    using MinIndex_Count_Pair = std::pair<ArrayType::size_type, ArrayType::size_type>;
    std::unordered_map<ArrayType::value_type, MinIndex_Count_Pair> counter;

    for (ArrayType::size_type i = 0; i < elements.size(); ++i) {
        const auto elem = elements[i];
        if (const auto iter = counter.find(elem); iter == counter.end()) {
            counter.emplace(elem, MinIndex_Count_Pair{i, 1});
        } else {
            ++(iter->second.second);
        }
    }

    std::sort(elements.begin(), elements.end(),
    [&counter](const auto & lhs, const auto & rhs) {
        const auto [lhs_index, lhs_count] = counter.at(lhs);
        const auto [rhs_index, rhs_count] = counter.at(rhs);
        if (lhs_count == rhs_count) {
            return lhs_index < rhs_index;
        } else {
            return lhs_count > rhs_count;
        }
    });

    return elements;
}


/**
 * Print the elements of an array in the decreasing frequency if 2 numbers have same
 * frequency then keeps their relative order.
 */
inline auto SortByFrequency_Stable(ArrayType elements) {
    const auto counter = ToFrequencyHashTable(elements);
    std::stable_sort(elements.begin(), elements.end(),
    [&counter](const auto & lhs, const auto & rhs) {
        return counter.at(lhs) > counter.at(rhs);
    });

    return elements;
}

}//namespace


const ArrayType SAMPLE1 = {2, 5, 2, 8, 5, 6, 8, 8};
const ArrayType EXPECTED1 = {8, 8, 8, 2, 2, 5, 5, 6};
const ArrayType EXPECTED_STABLE1 = {8, 8, 8, 2, 5, 2, 5, 6};

const ArrayType SAMPLE2 = {2, 5, 2, 6, -1, 9999999, 5, 8, 8, 8};
const ArrayType EXPECTED2 = {8, 8, 8, 2, 2, 5, 5, 6, -1, 9999999};
const ArrayType EXPECTED_STABLE2 = {8, 8, 8, 2, 5, 2, 5, 6, -1, 9999999};

const ArrayType SAMPLE3 = {2, 3, 2, 4, 5, 12, 2, 3, 3, 3, 12};
const ArrayType EXPECTED3 = {3, 3, 3, 3, 2, 2, 2, 12, 12, 4, 5};


THE_BENCHMARK(SortByFrequency, SAMPLE1);

SIMPLE_TEST(SortByFrequency, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(SortByFrequency, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(SortByFrequency, TestSAMPLE3, EXPECTED3, SAMPLE3);


THE_BENCHMARK(SortByFrequency_Stable, SAMPLE1);

SIMPLE_TEST(SortByFrequency_Stable, TestSAMPLE1, EXPECTED_STABLE1, SAMPLE1);
SIMPLE_TEST(SortByFrequency_Stable, TestSAMPLE2, EXPECTED_STABLE2, SAMPLE2);
SIMPLE_TEST(SortByFrequency_Stable, TestSAMPLE3, EXPECTED3, SAMPLE3);
