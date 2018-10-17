#include "common_header.h"

using ArrayType = std::vector<int>;
/** Find minimum difference between any two elements
 *
 * @reference   https://www.geeksforgeeks.org/find-minimum-difference-pair/
 *
 * Given an unsorted array, find the minimum difference between any pair in given array.
 */
auto FindMinDifferenceBetweenTwoElements(ArrayType elements) {
    assert(elements.size() > 1);

    std::sort(elements.begin(), elements.end());

    auto min_diff = std::numeric_limits<ArrayType::value_type>::max();
    for (ArrayType::size_type i = 1; i < elements.size(); ++i) {
        const auto diff = elements[i] - elements[i - 1];
        if (diff < min_diff) {
            min_diff = diff;
        }
    }

    return min_diff;
}


const ArrayType SAMPLE1 = {1, 5, 3, 19, 18, 25};
const ArrayType SAMPLE2 = {30, 5, 20, 9};
const ArrayType SAMPLE3 = {1, 19, -4, 31, 38, 25, 100};


SIMPLE_BENCHMARK(FindMinDifferenceBetweenTwoElements, SAMPLE1);

SIMPLE_TEST(FindMinDifferenceBetweenTwoElements, TestSample1, 1, SAMPLE1);
SIMPLE_TEST(FindMinDifferenceBetweenTwoElements, TestSample2, 4, SAMPLE2);
SIMPLE_TEST(FindMinDifferenceBetweenTwoElements, TestSample3, 5, SAMPLE3);
