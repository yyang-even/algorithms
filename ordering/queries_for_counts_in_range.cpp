#include "common_header.h"

#include "counting_sort.h"


namespace {

using ArrayType = std::vector<int>;
using Query = std::pair<ArrayType::size_type, ArrayType::size_type>;

/** Queries for counts of array elements with values in given range
 *
 * @reference   https://www.geeksforgeeks.org/queries-counts-array-elements-values-given-range/
 *
 * Given an unsorted array of size n, find no of elements between two elements i and j (both inclusive).
 */
auto QueriesForCountsInRange_Sort(ArrayType values, const std::vector<Query> &queries) {
    std::sort(values.begin(), values.end());

    std::vector<ArrayType::difference_type> output;
    for (const auto &range_pair : queries) {
        const auto lower = std::lower_bound(values.cbegin(), values.cend(), range_pair.first);
        const auto upper = std::upper_bound(values.cbegin(), values.cend(), range_pair.second);
        output.push_back(upper - lower);
    }

    return output;
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 8.2-4.
 */
auto QueriesForCountsInRange_CountingSort(const ArrayType &values,
                                          const std::vector<Query> &queries) {
    std::vector<ArrayType::difference_type> output;

    if (values.empty()) {
        return output;
    }

    const auto min_max_pair = std::minmax_element(values.cbegin(), values.cend());
    const auto RANGE = *min_max_pair.second - *min_max_pair.first + 1;
    const auto ToIndex = [min = *min_max_pair.first](const auto v) {
        return v - min;
    };

    const auto counter = ToCountingArray(values, RANGE, ToIndex);

    for (const auto &range_pair : queries) {
        const auto lower = counter[ToIndex(
                                       std::max<ArrayType::size_type>(range_pair.first, *min_max_pair.first))];
        const auto upper = counter[ToIndex(
                                       std::min<ArrayType::size_type>(range_pair.second, *min_max_pair.second))];
        output.push_back(upper - lower + 1);
    }

    return output;
}

}//namespace


const ArrayType VALUES = {1, 3, 4, 9, 10, 3};
const std::vector<Query> QUERIES = {{1, 4}, {9, 12}};
const std::vector<ArrayType::difference_type> EXPECTED = {4, 2};


SIMPLE_BENCHMARK(QueriesForCountsInRange_Sort, Sample1, VALUES, QUERIES);

SIMPLE_TEST(QueriesForCountsInRange_Sort, TestSAMPLE1, EXPECTED, VALUES, QUERIES);


SIMPLE_BENCHMARK(QueriesForCountsInRange_CountingSort, Sample1, VALUES, QUERIES);

SIMPLE_TEST(QueriesForCountsInRange_CountingSort, TestSAMPLE1, EXPECTED,
            VALUES, QUERIES);
