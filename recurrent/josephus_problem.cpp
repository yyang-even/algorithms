#include "common_header.h"

typedef unsigned long InputType;
/** Josephus Problem
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 1.3.
 *
 * A variant of Josephus Problem. Start with n people numbered 1 to n around a circle,
 * and we eliminate every second remaining person until only one survives. For n = 10,
 * the elimination order is 2, 4, 6, 8, 10, 3, 7, 1, 9, so 5 survives.
 * The problem: Determine the survivor’s number, J(n).
 */

/**
 * J(1) = 1;
 * J(2n) = 2J(n) - 1,      for n >= 1;
 * J(2n + 1) = 2J(n) + 1,  for n >= 1.
 */
InputType JosephusProblem2Recursive(const InputType n) {
    if (n == 1) {
        return 1;
    } else if ((n & 1) == 1) {  //odd
        return (JosephusProblem2Recursive(n / 2) << 1) + 1;
    } else { //even
        return (JosephusProblem2Recursive(n / 2) << 1) - 1;
    }
}

/**
 * J(2^m + l) = 2l + 1, for m >= 0 and 0 <= l < 2^m.
 */
InputType JosephusProblem2Closedform(const InputType n) {
    const auto bit_length = sizeof(n) * CHAR_BIT;
    InputType m = InputType(1) << (bit_length - 1);

    while (m and !(m & n)) {
        m /= 2;
    }
    return ((m ^ n) << 1) + 1;
}

const InputType LOWER = 1;
constexpr InputType UPPER = ~InputType(0);
const InputType SAMPLE = 15;
std::uniform_int_distribution<InputType> distribution(LOWER, UPPER);

BENCHMARK_SUIT(JosephusProblem2Recursive);
BENCHMARK_SUIT(JosephusProblem2Closedform);

SIMPLE_TEST_SUIT(JosephusProblem2Recursive, 1, UPPER, 15);
SIMPLE_TEST_SUIT(JosephusProblem2Closedform, 1, UPPER, 15);
MUTUAL_TEST(JosephusProblem2Recursive, JosephusProblem2Closedform);
