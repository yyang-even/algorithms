#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Program for Mean and median of an unsorted array
 *
 * @reference   https://www.geeksforgeeks.org/program-for-mean-and-median-of-an-unsorted-array/
 *
 * Mean of an array = (sum of all elements) / (number of elements)
 */
auto Mean(const ArrayType &values) {
    assert(not values.empty());

    const double sum = std::accumulate(values.cbegin(), values.cend(), 0);
    return sum / values.size();
}

}//namespace


const ArrayType VALUES1 = {1};
const ArrayType VALUES2 = {1, 2};
const ArrayType VALUES3 = {2, 3, 1};
const ArrayType VALUES4 = {1, 3, 4, 2, 6, 5, 8, 7};
const ArrayType VALUES5 = {4, 4, 4, 4, 4};


SIMPLE_BENCHMARK(Mean, VALUES4);

SIMPLE_TEST(Mean, TestSAMPLE1, 1, VALUES1);
SIMPLE_TEST(Mean, TestSAMPLE2, 1.5, VALUES2);
SIMPLE_TEST(Mean, TestSAMPLE3, 2, VALUES3);
SIMPLE_TEST(Mean, TestSAMPLE4, 4.5, VALUES4);
SIMPLE_TEST(Mean, TestSAMPLE5, 4, VALUES5);
