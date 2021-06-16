#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Number of local extrema in an array
 *
 * @reference   https://www.geeksforgeeks.org/maximum-number-local-extrema/
 *
 * You are given an array on n-elements. An extrema is an elements which is either
 * greater than its both of neighbors or less than its both neighbors. You have to
 * calculate the number of local extrema in given array.
 * Note: 1st and last elements are not extrema.
 */
auto CountLocalExtrema(const ArrayType &elements) {
    assert(elements.size() > 2);

    auto count = 0;
    auto prev = elements.cbegin();
    auto iter = std::next(prev);
    for (auto next = std::next(iter); next != elements.cend(); ++prev, ++iter, ++next)
        count += (*prev < *iter and *iter > *next) or
                 (*prev > *iter and * iter < *next);

    return count;
}

}//namespace


const ArrayType SAMPLE1 = {1, 5, 2, 5};
const ArrayType SAMPLE2 = {1, 2, 3};
const ArrayType SAMPLE3 = {1, 0, 2, 1};


THE_BENCHMARK(CountLocalExtrema, SAMPLE1);

SIMPLE_TEST(CountLocalExtrema, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(CountLocalExtrema, TestSAMPLE2, 0, SAMPLE2);
SIMPLE_TEST(CountLocalExtrema, TestSAMPLE3, 2, SAMPLE3);
