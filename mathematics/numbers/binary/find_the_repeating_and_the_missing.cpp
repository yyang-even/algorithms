#include "common_header.h"

#include "find_the_element_helper.h"

#include "clear_all_bits_except_the_last_set_bit.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Find the repeating and the missing | Added 3 new methods
 *
 * @reference   https://www.geeksforgeeks.org/find-a-repeating-and-a-missing-number/
 *
 * Given an unsorted array of size n. Array elements are in range from 1 to n. One number
 * from set {1, 2, ..., n} is missing and one number occurs twice in array. Find these
 * two numbers.
 */
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
        divideElement<ArrayType::value_type>(i, last_set_bit, x, y);
        divideElement<ArrayType::value_type>(elements[i], last_set_bit, x, y);
    }
    divideElement<ArrayType::value_type>(N, last_set_bit, x, y);

    return std::pair(x, y);
}

}//namespace


const ArrayType SAMPLE1 = {3, 1, 3};
const ArrayType SAMPLE2 = {4, 3, 6, 2, 1, 1};


THE_BENCHMARK(FindTheRepeatingAndMissing, SAMPLE1);

SIMPLE_TEST(FindTheRepeatingAndMissing, TestSample1, std::pair(3u, 2u), SAMPLE1);
SIMPLE_TEST(FindTheRepeatingAndMissing, TestSample2, std::pair(5u, 1u), SAMPLE2);
