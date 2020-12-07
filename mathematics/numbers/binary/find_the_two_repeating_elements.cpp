#include "common_header.h"

#include "find_the_element_helper.h"

#include "clear_all_bits_except_the_last_set_bit.h"

using ArrayType = std::vector<int>;

/** Find the two repeating elements in a given array
 *
 * @reference   https://www.geeksforgeeks.org/find-the-two-repeating-elements-in-a-given-array/
 *
 * You are given an array of n+2 elements. All elements of the array are in range 1 to n.
 * And all elements occur once except two numbers which occur twice. Find the two repeating numbers.
 * For example, array = {4, 2, 4, 5, 2, 3, 1} and n = 5
 * The above array has n + 2 = 7 elements with all elements occurring once except 2 and 4
 * which occur twice. So the output should be 4 2.
 */
auto FindTheTwoRepeatingElementsXor(const ArrayType &elements) {
    assert(elements.size() >= 4ul);

    const auto N = elements.size() - 2ul;
    ArrayType::value_type xor_of_all = elements[0];
    ArrayType::value_type x = 0;
    ArrayType::value_type y = 0;

    for (ArrayType::size_type i = 1ul; i <= N; ++i) {
        xor_of_all ^= (i ^ elements[i]);
    }

    const auto last_set_bit =
        ClearAllBitsExceptTheLastSetBit(xor_of_all ^ elements[N + 1ul]);

    for (ArrayType::size_type i = 0ul; i <= N; ++i) {
        divideElement<ArrayType::value_type>(i, last_set_bit, x, y);
        divideElement<ArrayType::value_type>(elements[i], last_set_bit, x, y);
    }
    divideElement<ArrayType::value_type>(elements[N + 1ul], last_set_bit, x, y);

    return std::make_pair(x, y);
}


auto FindTheTwoRepeatingElementsInplace(ArrayType elements) {
    assert(elements.size() >= 4ul);

    ArrayType repeating_elments;
    for (const auto elem : elements) {
        auto &counter = elements[abs(elem)];
        if (counter > 0) {
            counter = -counter;
        } else {
            repeating_elments.push_back(abs(elem));
        }
    }

    return std::make_pair(repeating_elments[0], repeating_elments[1]);
}


const ArrayType SAMPLE1 = {4, 2, 4, 5, 2, 3, 1};

SIMPLE_BENCHMARK(FindTheTwoRepeatingElementsXor, Sample1, SAMPLE1);

SIMPLE_TEST(FindTheTwoRepeatingElementsXor, TestSample1, std::make_pair(2, 4), SAMPLE1);


SIMPLE_BENCHMARK(FindTheTwoRepeatingElementsInplace, Sample1, SAMPLE1);

SIMPLE_TEST(FindTheTwoRepeatingElementsInplace, TestSample1, std::make_pair(4, 2),
            SAMPLE1);
