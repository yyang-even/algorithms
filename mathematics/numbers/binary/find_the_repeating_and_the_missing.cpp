#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

#include "clear_all_bits_except_the_last_set_bit.h"

using ArraryType = std::vector<unsigned>;

/** Find the repeating and the missing | Added 3 new methods
 *
 * @reference   https://www.geeksforgeeks.org/find-a-repeating-and-a-missing-number/
 *
 * Given an unsorted array of size n. Array elements are in range from 1 to n.
 * One number from set {1, 2, …n} is missing and one number occurs twice in array.
 * Find these two numbers.
 */
auto FindTheRepeatingAndMissing(const ArraryType &elements, const ArraryType::value_type n) {
    assert(not integers.empty());
    assert(elements.size() == n);
    
    ArraryType::value_type xor_of_all = elements[0];
    ArraryType::value_type x = 0u;
    ArraryType::value_type y = 0u;

    for (ArraryType::size_type i = 1ul; i < n; ++i) {
        xor_of_all ^= (i ^ integers[i]);
    }

    const auto last_set_bit = ClearAllBitsExceptTheLastSetBit(xor_of_all);
