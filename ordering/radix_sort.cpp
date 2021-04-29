#include "common_header.h"

#include "radix_sort.h"


namespace {

using ArrayType = std::vector<int>;

/** Radix Sort
 *
 * @reference   https://www.geeksforgeeks.org/radix-sort/
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 8.3.
 * @reference   Radix Sort
 *              http://users.monash.edu/~lloyd/tildeAlgDS/Sort/Radix/
 * @reference   C Program for Radix Sort
 *              https://www.geeksforgeeks.org/c-program-for-radix-sort/
 *
 * The idea of Radix Sort is to do digit by digit sort starting from least significant
 * digit to most significant digit. Radix sort uses counting sort as a subroutine to sort.
 */


/**
 * @reference   Sort n numbers in range from 0 to n^2 – 1 in linear time
 *              https://www.geeksforgeeks.org/sort-n-numbers-range-0-n2-1-linear-time/
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 8.3-4.
 */
inline auto RadixSort_BaseN(ArrayType values) {
    return RadixSort(std::move(values), values.size());
}

}//namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {1};
const ArrayType VALUES3 = {1, 2};
const ArrayType VALUES4 = {2, 3, 1};
const ArrayType EXPECTED4 = {1, 2, 3};
const ArrayType VALUES5 = {4, 3, 2, 1};
const ArrayType EXPECTED5 = {1, 2, 3, 4};
const ArrayType VALUES6 = {170, 45, 75, 90, 802, 24, 2, 66};
const ArrayType EXPECTED6 = {2, 24, 45, 66, 75, 90, 170, 802};


THE_BENCHMARK(RadixSort, VALUES6);

SIMPLE_TEST(RadixSort, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(RadixSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(RadixSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(RadixSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(RadixSort, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(RadixSort, TestSAMPLE6, EXPECTED6, VALUES6);


const ArrayType VALUES7 = {0, 23, 14, 12, 9};
const ArrayType EXPECTED7 = {0, 9, 12, 14, 23};
const ArrayType VALUES8 = {7, 0, 2};
const ArrayType EXPECTED8 = {0, 2, 7};


THE_BENCHMARK(RadixSort_BaseN, VALUES7);

SIMPLE_TEST(RadixSort_BaseN, TestSAMPLE7, EXPECTED7, VALUES7);
SIMPLE_TEST(RadixSort_BaseN, TestSAMPLE8, EXPECTED8, VALUES8);
