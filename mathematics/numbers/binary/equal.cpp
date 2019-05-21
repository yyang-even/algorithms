#include "common_header.h"

namespace {

using InputType = int;

/** Check if two numbers are equal without using comparison operators
 *
 * @reference   https://www.geeksforgeeks.org/check-two-numbers-equal-without-using-comparison-operators/
 * @reference   https://www.geeksforgeeks.org/check-if-two-numbers-are-equal-without-using-arithmetic-and-comparison-operators/
 *
 * Following are not allowed to use
 * 1) Comparison Operators
 * 2) String functions
 */
auto Equal_Xor(const InputType lhs, const InputType rhs) {
    return not(lhs ^ rhs);
}


auto Equal_Subtract(const InputType lhs, const InputType rhs) {
    return not(lhs - rhs);
}


auto Equal_Complement(const InputType lhs, const InputType rhs) {
    return not((lhs & ~rhs));
}

}//namespace


SIMPLE_BENCHMARK(Equal_Xor, 0, 4);

SIMPLE_TEST(Equal_Xor, TestSample1, TRUE, 1233, 1233);
SIMPLE_TEST(Equal_Xor, TestSample2, FALSE, 123, 321);


SIMPLE_BENCHMARK(Equal_Subtract, 0, 4);

SIMPLE_TEST(Equal_Subtract, TestSample1, TRUE, 1233, 1233);
SIMPLE_TEST(Equal_Subtract, TestSample2, FALSE, 123, 321);


SIMPLE_BENCHMARK(Equal_Complement, 0, 4);

SIMPLE_TEST(Equal_Complement, TestSample1, TRUE, 1233, 1233);
SIMPLE_TEST(Equal_Complement, TestSample2, FALSE, 123, 321);
