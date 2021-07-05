#include "common_header.h"

#include "clear_all_bits_except_the_last_set_bit.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Find the two non-repeating elements in an array of repeating elements
 *
 * @reference   https://www.geeksforgeeks.org/find-two-non-repeating-elements-in-an-array-of-repeating-elements/
 *
 * Given an array in which all numbers except two are repeated once. (i.e. we have 2n+2
 * numbers and n numbers are occurring twice and remaining two have occurred once). Find
 * those two numbers in the most efficient way.
 *
 * @reference   Single Number III
 *              https://leetcode.com/problems/single-number-iii/
 *
 * @complexity  O(n)
 */
/** Find the two numbers with odd occurrences in an unsorted array
 *
 * @reference   https://www.geeksforgeeks.org/find-the-two-numbers-with-odd-occurences-in-an-unsorted-array/
 * @reference   Two odd occurring elements in an array where all other occur even times
 *              https://www.geeksforgeeks.org/two-odd-occurring-elements-array-occur-even-times/
 *
 * Given an unsorted array that contains even number of occurrences for all numbers except
 * two numbers. Find the two numbers which have odd occurrences in O(n) time complexity
 * and O(1) extra space.
 */
/** Find Unique pair in an array with pairs of numbers
 *
 * @reference   https://www.geeksforgeeks.org/find-unique-pair-array-pairs-numbers/
 *
 * Given an array where every element appears twice except a pair (two elements). Find
 * the elements of this unique pair.
 */
auto FindTheTwoNonrepeatingElements(const ArrayType &elements) {
    unsigned xor_of_all = 0;
    ArrayType::value_type x = 0;
    ArrayType::value_type y = 0;

    for (const auto elem : elements) {
        xor_of_all ^= elem;
    }

    const auto last_set_bit = ClearAllBitsExceptTheLastSetBit(xor_of_all);

    for (const auto elem : elements) {
        if (elem & last_set_bit) {
            x ^= elem;
        } else {
            y ^= elem;
        }
    }

    return std::pair(x, y);
}

}//namespace


const ArrayType SAMPLE1 = {2, 4, 7, 9, 2, 4};
const ArrayType SAMPLE2 = {12, 23, 34, 12, 12, 23, 12, 45};
const ArrayType SAMPLE3 = {4, 4, 100, 5000, 4, 4, 4, 4, 100, 100};
const ArrayType SAMPLE4 = {10, 20};
const ArrayType SAMPLE5 = {6, 1, 3, 5, 1, 3, 7, 6};
const ArrayType SAMPLE6 = {2, 3, 3, 4, 4, 5};


THE_BENCHMARK(FindTheTwoNonrepeatingElements, SAMPLE1);

SIMPLE_TEST(FindTheTwoNonrepeatingElements, TestSample1, std::pair(7u, 9u), SAMPLE1);
SIMPLE_TEST(FindTheTwoNonrepeatingElements, TestSample2, std::pair(45u, 34u), SAMPLE2);
SIMPLE_TEST(FindTheTwoNonrepeatingElements, TestSample3, std::pair(100u, 5000u),
            SAMPLE3);
SIMPLE_TEST(FindTheTwoNonrepeatingElements, TestSample4, std::pair(10u, 20u), SAMPLE4);
SIMPLE_TEST(FindTheTwoNonrepeatingElements, TestSample5, std::pair(7u, 5u), SAMPLE5);
SIMPLE_TEST(FindTheTwoNonrepeatingElements, TestSample6, std::pair(5u, 2u), SAMPLE6);
