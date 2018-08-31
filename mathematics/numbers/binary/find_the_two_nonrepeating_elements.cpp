#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

#include "clear_all_bits_except_the_last_set_bit.h"

using ArraryType = std::vector<unsigned>;

/** Find the two non-repeating elements in an array of repeating elements
 *
 * @reference   https://www.geeksforgeeks.org/?p=2457
 *
 * Given an array in which all numbers except two are repeated once. (i.e. we
 * have 2n+2 numbers and n numbers are occurring twice and remaining two have
 * occurred once). Find those two numbers in the most efficient way.
 *
 * @complexity  O(n)
 */
/** Find the two numbers with odd occurrences in an unsorted array
 *
 * @reference   https://www.geeksforgeeks.org/find-the-two-numbers-with-odd-occurences-in-an-unsorted-array/
 *
 * Given an unsorted array that contains even number of occurrences for all
 * numbers except two numbers. Find the two numbers which have odd occurrences
 * in O(n) time complexity and O(1) extra space.
 */
auto FindTheTwoNonrepeatingElements(const ArraryType &elements) {
    ArraryType::value_type xor_of_all = 0u;
    ArraryType::value_type x = 0u;
    ArraryType::value_type y = 0u;

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

    return std::make_pair(x, y);
}


const ArraryType SAMPLE1 = {2, 4, 7, 9, 2, 4};
const ArraryType SAMPLE2 = {12, 23, 34, 12, 12, 23, 12, 45};
const ArraryType SAMPLE3 = {4, 4, 100, 5000, 4, 4, 4, 4, 100, 100};
const ArraryType SAMPLE4 = {10, 20};


SIMPLE_BENCHMARK(FindTheTwoNonrepeatingElements, SAMPLE1);

SIMPLE_TEST(FindTheTwoNonrepeatingElements, TestSample1, std::make_pair(7u, 9u), SAMPLE1);
SIMPLE_TEST(FindTheTwoNonrepeatingElements, TestSample2, std::make_pair(45u, 34u), SAMPLE2);
SIMPLE_TEST(FindTheTwoNonrepeatingElements, TestSample3, std::make_pair(100u, 5000u), SAMPLE3);
SIMPLE_TEST(FindTheTwoNonrepeatingElements, TestSample4, std::make_pair(10u, 20u), SAMPLE4);
