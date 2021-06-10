#include "common_header.h"


namespace {

/** Check if two numbers are equal without using comparison operators
 *
 * @reference   https://www.geeksforgeeks.org/check-two-numbers-equal-without-using-comparison-operators/
 * @reference   https://www.geeksforgeeks.org/check-if-two-numbers-are-equal-without-using-arithmetic-and-comparison-operators/
 * @reference   Compare two integers without using any Comparison operator
 *              https://www.geeksforgeeks.org/compare-two-integers-without-using-comparison-operator/
 *
 * Following are not allowed to use
 *  1) Comparison Operators
 *  2) String functions
 */
constexpr inline auto Equal_Xor(const unsigned lhs, const unsigned rhs) {
    return not(lhs ^ rhs);
}


constexpr inline auto Equal_Subtract(const unsigned lhs, const unsigned rhs) {
    return not(lhs - rhs);
}


constexpr inline auto Equal_Complement(const unsigned lhs, const unsigned rhs) {
    return not((lhs & ~rhs));
}

}//namespace


THE_BENCHMARK(Equal_Xor, 0, 4);

SIMPLE_TEST(Equal_Xor, TestSample1, true, 1233, 1233);
SIMPLE_TEST(Equal_Xor, TestSample2, false, 123, 321);


THE_BENCHMARK(Equal_Subtract, 0, 4);

SIMPLE_TEST(Equal_Subtract, TestSample1, true, 1233, 1233);
SIMPLE_TEST(Equal_Subtract, TestSample2, false, 123, 321);


THE_BENCHMARK(Equal_Complement, 0, 4);

SIMPLE_TEST(Equal_Complement, TestSample1, true, 1233, 1233);
SIMPLE_TEST(Equal_Complement, TestSample2, false, 123, 321);
