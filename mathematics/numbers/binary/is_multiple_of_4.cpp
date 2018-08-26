#include "common_header.h"

#include "calculate_xor_of_all_numbers_1_to_n.h"

using InputType = unsigned;

/** Multiples of 4 (An Interesting Method)
 *
 * @reference   https://www.geeksforgeeks.org/multiples-4-interesting-method/
 *
 * Given a number n, the task is to check whether this number is a multiple
 * of 4 or not without using +, -, * ,/ and % operators.
 */
INT_BOOL IsMultipleOf4Xor(const InputType num) {
    if (num == 1) {
        return false;
    }
    return XorOfAllFrom1toN(num) == num;
}

INT_BOOL IsMultipleOf4Shift(const InputType num) {
    return ((num >> 2) << 2) == num;
}

/** Efficiently check whether n is a multiple of 4 or not
 *
 * @reference   https://www.geeksforgeeks.org/efficiently-check-whether-n-multiple-4-not/
 *
 * Given a number n. The problem is to efficiently check whether n is a
 * multiple of 4 or not without using arithmetic operators.
 */
INT_BOOL IsMultipleOf4Mask(const InputType num) {
    return not(num & (4 - 1));
}


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr auto UPPER = std::numeric_limits<InputType>::max();

SIMPLE_BENCHMARK(IsMultipleOf4Xor, 4);

SIMPLE_TEST(IsMultipleOf4Xor, TestSample1, TRUE, 0);
SIMPLE_TEST(IsMultipleOf4Xor, TestSample2, FALSE, 1);
SIMPLE_TEST(IsMultipleOf4Xor, TestSample3, TRUE, 16);
SIMPLE_TEST(IsMultipleOf4Xor, TestSample4, FALSE, 14);

SIMPLE_BENCHMARK(IsMultipleOf4Mask, 4);

SIMPLE_TEST(IsMultipleOf4Mask, TestSample1, TRUE, 0);
SIMPLE_TEST(IsMultipleOf4Mask, TestSample2, FALSE, 1);
SIMPLE_TEST(IsMultipleOf4Mask, TestSample3, TRUE, 16);
SIMPLE_TEST(IsMultipleOf4Mask, TestSample4, FALSE, 14);

SIMPLE_BENCHMARK(IsMultipleOf4Shift, 4);

SIMPLE_TEST(IsMultipleOf4Shift, TestSample1, TRUE, 0);
SIMPLE_TEST(IsMultipleOf4Shift, TestSample2, FALSE, 1);
SIMPLE_TEST(IsMultipleOf4Shift, TestSample3, TRUE, 16);
SIMPLE_TEST(IsMultipleOf4Shift, TestSample4, FALSE, 14);

MUTUAL_RANDOM_TEST(IsMultipleOf4Xor, IsMultipleOf4Mask, LOWER, UPPER);
MUTUAL_RANDOM_TEST(IsMultipleOf4Shift, IsMultipleOf4Mask, LOWER, UPPER);
