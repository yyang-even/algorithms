#include "common_header.h"

using ArrayType = std::vector<int>;
using QueryListType = std::vector<std::pair<ArrayType::size_type, ArrayType::size_type>>;
/** Print modified array after multiple array range increment operations
 *
 * @reference   https://www.geeksforgeeks.org/print-modified-array-multiple-array-range-increment-operations/
 *
 * Given an array containing n integers and a value d. m queries are given.
 * Each query has two values start and end. For each query, the problem is
 * to increment the values from the start to end index in the given array
 * by the given value d. A linear time efficient solution is required for
 * handling such multiple queries.
 */
auto MultipleArrayRangeIncrementOperations(ArrayType integers, const ArrayType::value_type d,
        const  QueryListType &queries) {
    ArrayType sum(integers.size(), 0);

    for (const auto query : queries) {
        sum[query.first] += d;
        const auto end = query.second + 1;
        if (end < sum.size()) {
            sum[end] -= d;
        }
    }

    for (auto iter = sum.begin() + 1; iter != sum.end(); ++iter) {
        *iter += *(iter - 1);
    }

    std::transform(integers.cbegin(), integers.cend(), sum.cbegin(), integers.begin(),
                   std::plus<ArrayType::value_type> {});

    return integers;
}


const ArrayType SAMPLE1 = {3, 5, 4, 8, 6, 1};
const QueryListType QUERIES1 = {{0, 3}, {4, 5}, {1, 4}, {0, 1}, {2, 5}};
const ArrayType EXPECTED1 = {7, 11, 10, 14, 12, 5};

SIMPLE_BENCHMARK(MultipleArrayRangeIncrementOperations, SAMPLE1, 2, QUERIES1);

SIMPLE_TEST(MultipleArrayRangeIncrementOperations, TestSAMPLE1, EXPECTED1, SAMPLE1, 2, QUERIES1);
