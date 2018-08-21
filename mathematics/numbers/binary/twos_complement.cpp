#include "common_header.h"

using InputType = unsigned;

/** Two’s complement of the number
 *
 * @reference   Bitwise Hacks for Competitive Programming
 *              https://www.geeksforgeeks.org/bitwise-hacks-for-competitive-programming/
 *
 * 2’s complement of a number is 1’s complement + 1.
 */
auto TwosComplementByOnesComplement(const InputType num) {
    return ~num + 1;
}

auto TwosComplementByMinusOperator(const InputType num) {
    return -num;
}


constexpr auto LOWER = std::numeric_limits<unsigned>::min();
constexpr auto UPPER = std::numeric_limits<unsigned>::max();

MUTUAL_RANDOM_TEST(TwosComplementByOnesComplement, TwosComplementByMinusOperator, LOWER, UPPER);
