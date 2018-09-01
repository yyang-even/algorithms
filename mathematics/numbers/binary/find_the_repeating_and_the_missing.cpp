#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

#include "clear_all_bits_except_the_last_set_bit.h"

using ArrayType = std::vector<unsigned>;

/** Find the repeating and the missing | Added 3 new methods
 *
 * @reference   https://www.geeksforgeeks.org/find-a-repeating-and-a-missing-number/
 *
 * Given an unsorted array of size n. Array elements are in range from 1 to n.
 * One number from set {1, 2, …n} is missing and one number occurs twice in array.
 * Find these two numbers.
 */
inline void divideElement(const ArrayType::value_type elem, const ArrayType::value_type lsb,
                          ArrayType::value_type &x, ArrayType::value_type &y) {
    if (elem & lsb) {
        x ^= elem;
    } else {
        y ^= elem;
    }
}
auto FindTheRepeatingAndMissing(const ArrayType &elements) {
    assert(not elements.empty());

    const auto N = elements.size();
    ArrayType::value_type xor_of_all = elements[0];
    ArrayType::value_type x = 0u;
    ArrayType::value_type y = 0u;

    for (ArrayType::size_type i = 1ul; i < N; ++i) {
        xor_of_all ^= (i ^ elements[i]);
    }

    const auto last_set_bit = ClearAllBitsExceptTheLastSetBit(xor_of_all ^ N);

    for (ArrayType::size_type i = 0ul; i < N; ++i) {
        divideElement(i, last_set_bit, x, y);
        divideElement(elements[i], last_set_bit, x, y);
    }
    divideElement(N, last_set_bit, x, y);

    return std::make_pair(x, y);
}


const ArrayType SAMPLE1 = {3, 1, 3};
const ArrayType SAMPLE2 = {4, 3, 6, 2, 1, 1};


SIMPLE_BENCHMARK(FindTheRepeatingAndMissing, SAMPLE1);

SIMPLE_TEST(FindTheRepeatingAndMissing, TestSample1, std::make_pair(3u, 2u), SAMPLE1);
SIMPLE_TEST(FindTheRepeatingAndMissing, TestSample2, std::make_pair(5u, 1u), SAMPLE2);
