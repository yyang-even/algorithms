#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Program for Mean and median of an unsorted array
 *
 * @reference   https://www.geeksforgeeks.org/program-for-mean-and-median-of-an-unsorted-array/
 *
 * Median of a sorted array of size n is defined as below:
 * It is middle element when n is odd and average of middle two elements when n is even.
 */
double Median(const ArrayType &sorted_array) {
    assert(not sorted_array.empty());
    assert(std::is_sorted(sorted_array.cbegin(), sorted_array.cend()));

    if (sorted_array.size() % 2 == 0) {
        return (sorted_array[(sorted_array.size() - 1) / 2] + sorted_array[sorted_array.size() / 2]) / 2.0;
    } else {
        return sorted_array[sorted_array.size() / 2];
    }
}


auto Median_Unsorted(ArrayType values) {
    std::sort(values.begin(), values.end());
    return Median(values);
}

}//namespace


const ArrayType VALUES1 = {1};
const ArrayType VALUES2 = {1, 2};
const ArrayType VALUES3 = {2, 3, 1};
const ArrayType VALUES4 = {1, 3, 4, 2, 6, 5, 8, 7};
const ArrayType VALUES5 = {4, 4, 4, 4, 4};


SIMPLE_BENCHMARK(Median_Unsorted, VALUES4);

SIMPLE_TEST(Median_Unsorted, TestSAMPLE1, 1, VALUES1);
SIMPLE_TEST(Median_Unsorted, TestSAMPLE2, 1.5, VALUES2);
SIMPLE_TEST(Median_Unsorted, TestSAMPLE3, 2, VALUES3);
SIMPLE_TEST(Median_Unsorted, TestSAMPLE4, 4.5, VALUES4);
SIMPLE_TEST(Median_Unsorted, TestSAMPLE5, 4, VALUES5);
