#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Minimum Moves to Equal Array Elements
 *
 * @reference   https://leetcode.com/problems/minimum-moves-to-equal-array-elements/
 *
 * Given an integer array nums of size n, return the minimum number of moves required to make all
 * array elements equal.
 * In one move, you can increment n - 1 elements of the array by 1.
 *
 * @reference   Minimum number of increment-other operations to make all array elements equal.
 *              https://www.geeksforgeeks.org/minimum-number-increment-operations-make-array-elements-equal/
 */
auto MinMovesToEqualElements_IncOthers(const ArrayType &elements) {
    int sum = 0;
    int min = INT_MAX;
    for (const auto n : elements) {
        sum += n;
        min = std::min(min, n);
    }

    return sum - (elements.size() * min);
}


/**
 * @reference   Minimum Moves to Equal Array Elements II
 *              https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/
 *
 * Given an integer array nums of size n, return the minimum number of moves required to make all
 * array elements equal.
 * In one move, you can increment or decrement an element of the array by 1.
 * Test cases are designed so that the answer will fit in a 32-bit integer.
 */
auto MinMovesToEqualElements_IncDec(ArrayType elements) {
    const auto mid = elements.begin() + elements.size() / 2;
    std::nth_element(elements.begin(), mid, elements.end());

    int result = 0;
    for (const auto n : elements) {
        result += std::abs(*mid - n);
    }

    return result;
}


auto MinMovesToEqualElements_IncDec_Sort(ArrayType elements) {
    std::sort(elements.begin(), elements.end());

    int result = 0;
    for (int i = 0, j = elements.size() - 1; i < j;) {
        result += elements[j--] - elements[i++];
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {1, 2, 3};
const ArrayType SAMPLE2 = {1, 1, 1};
const ArrayType SAMPLE3 = {4, 3, 4};


THE_BENCHMARK(MinMovesToEqualElements_IncOthers, SAMPLE1);

SIMPLE_TEST(MinMovesToEqualElements_IncOthers, TestSAMPLE1, 3, SAMPLE1);
SIMPLE_TEST(MinMovesToEqualElements_IncOthers, TestSAMPLE2, 0, SAMPLE2);
SIMPLE_TEST(MinMovesToEqualElements_IncOthers, TestSAMPLE3, 2, SAMPLE3);


const ArrayType SAMPLE4 = {1, 10, 2, 9};


THE_BENCHMARK(MinMovesToEqualElements_IncDec, SAMPLE1);

SIMPLE_TEST(MinMovesToEqualElements_IncDec, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(MinMovesToEqualElements_IncDec, TestSAMPLE2, 0, SAMPLE2);
SIMPLE_TEST(MinMovesToEqualElements_IncDec, TestSAMPLE3, 1, SAMPLE3);
SIMPLE_TEST(MinMovesToEqualElements_IncDec, TestSAMPLE4, 16, SAMPLE4);


THE_BENCHMARK(MinMovesToEqualElements_IncDec_Sort, SAMPLE1);

SIMPLE_TEST(MinMovesToEqualElements_IncDec_Sort, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(MinMovesToEqualElements_IncDec_Sort, TestSAMPLE2, 0, SAMPLE2);
SIMPLE_TEST(MinMovesToEqualElements_IncDec_Sort, TestSAMPLE3, 1, SAMPLE3);
SIMPLE_TEST(MinMovesToEqualElements_IncDec_Sort, TestSAMPLE4, 16, SAMPLE4);
