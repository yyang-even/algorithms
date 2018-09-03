#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

#include "clear_all_bits_except_the_last_set_bit.h"

using ArrayType = std::vector<unsigned>;

/** Find Two Missing Numbers
 *
 * @reference   Find Two Missing Numbers | Set 1 (An Interesting Linear Time Solution)
 *              https://www.geeksforgeeks.org/find-two-missing-numbers-set-1-an-interesting-linear-time-solution/
 * @reference   Find Two Missing Numbers | Set 2 (XOR based solution)
 *              https://www.geeksforgeeks.org/find-two-missing-numbers-set-2-xor-based-solution/
 *
 * Given an array of n unique integers where each element in the array is in range [1, n].
 * The array has all distinct elements and size of array is (n-2). Hence Two numbers from
 * the range are missing from this array. Find the two missing numbers.
 */
auto FindTheTwoMissingNumbersSum(const ArrayType &elements) {
    assert(not elements.empty());

    const auto N = elements.size() + 2ul;
    const auto total_sum = (N * (N + 1)) / 2;
    const ArrayType::value_type x_plus_y = total_sum -
                                           std::accumulate(elements.cbegin(), elements.cend(), 0ul);
    const auto average = x_plus_y / 2u;

    ArrayType::value_type sum_of_smallers = 0u;
    ArrayType::value_type sum_of_greaters = 0u;
    for (const auto elem : elements) {
        if (elem <= average) {
            sum_of_smallers += elem;
        } else {
            sum_of_greaters += elem;
        }
    }

    const auto total_smallers_sum = average * (average + 1) / 2;
    return std::make_pair<ArrayType::value_type, ArrayType::value_type>(
               total_smallers_sum - sum_of_smallers,
               total_sum - total_smallers_sum - sum_of_greaters);
}

inline void divideElement(const ArrayType::value_type elem, const ArrayType::value_type lsb,
                          ArrayType::value_type &x, ArrayType::value_type &y) {
    if (elem & lsb) {
        x ^= elem;
    } else {
        y ^= elem;
    }
}
auto FindTheTwoMissingNumbersXor(const ArrayType &elements) {
    assert(not elements.empty());

    const auto N = elements.size() + 2ul;
    ArrayType::value_type xor_of_all = elements[0];
    ArrayType::value_type x = 0u;
    ArrayType::value_type y = 0u;

    for (ArrayType::size_type i = 1ul; i < elements.size(); ++i) {
        xor_of_all ^= (i ^ elements[i]);
    }

    const auto last_set_bit = ClearAllBitsExceptTheLastSetBit(
                                  xor_of_all ^ elements.size() ^ (N - 1) ^ N);

    for (ArrayType::size_type i = 0ul; i < elements.size(); ++i) {
        divideElement(i, last_set_bit, x, y);
        divideElement(elements[i], last_set_bit, x, y);
    }
    divideElement(elements.size(), last_set_bit, x, y);
    divideElement(N - 1, last_set_bit, x, y);
    divideElement(N, last_set_bit, x, y);

    return std::make_pair(x, y);
}


const ArrayType SAMPLE1 = {1, 3, 5, 6};
const ArrayType SAMPLE2 = {1, 2, 4};
const ArrayType SAMPLE3 = {1, 2};


SIMPLE_BENCHMARK(FindTheTwoMissingNumbersSum, SAMPLE1);

SIMPLE_TEST(FindTheTwoMissingNumbersSum, TestSample1, std::make_pair(2u, 4u), SAMPLE1);
SIMPLE_TEST(FindTheTwoMissingNumbersSum, TestSample2, std::make_pair(3u, 5u), SAMPLE2);
SIMPLE_TEST(FindTheTwoMissingNumbersSum, TestSample3, std::make_pair(3u, 4u), SAMPLE3);


SIMPLE_BENCHMARK(FindTheTwoMissingNumbersXor, SAMPLE1);

SIMPLE_TEST(FindTheTwoMissingNumbersXor, TestSample1, std::make_pair(2u, 4u), SAMPLE1);
SIMPLE_TEST(FindTheTwoMissingNumbersXor, TestSample2, std::make_pair(3u, 5u), SAMPLE2);
SIMPLE_TEST(FindTheTwoMissingNumbersXor, TestSample3, std::make_pair(3u, 4u), SAMPLE3);
