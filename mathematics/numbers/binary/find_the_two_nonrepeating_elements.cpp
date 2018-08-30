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


const ArraryType SAMPLE = {2, 4, 7, 9, 2, 4};


SIMPLE_BENCHMARK(FindTheTwoNonrepeatingElements, SAMPLE);

SIMPLE_TEST(FindTheTwoNonrepeatingElements, TestSample1, std::make_pair(7u, 9u), SAMPLE);
