#include "common_header.h"


namespace {

/** Multiplying a variable with a constant without using multiplication operator
 *
 * @reference   Multiplying a variable with a constant without using multiplication operator
 *              https://www.geeksforgeeks.org/multiplying-variable-constant-without-using-multiplication-operator/
 * @reference   Multiply a number with 10 without using multiplication operator
 *              https://www.geeksforgeeks.org/multiply-number-10-without-using-multiplication-operator/
 * @reference   Multiply a number by 15 without using * and / operators
 *              https://www.geeksforgeeks.org/multiply-a-number-by-15-without-using-and-operators/
 *
 * @reference   Efficient way to multiply with 7
 *              https://www.geeksforgeeks.org/efficient-way-to-multiply-with-7/
 *
 * We can multiply a number by 7 using bitwise operator. First left shift the number by
 * 3 bits (you will get 8n) then subtract the original number from the shifted number
 * and return the difference (8n – n).
 */
constexpr inline auto Multiply7(const unsigned n) {
    return (n << 3) - n;
}


constexpr inline auto Multiply10(const unsigned n) {
    return (n << 1) + (n << 3);
}


constexpr inline auto Multiply12(const unsigned n) {
    return (n << 3) + (n << 2);
}


constexpr inline auto Multiply15(const unsigned n) {
    return (n << 4) - n;
}

}//namespace


THE_BENCHMARK(Multiply7, 4);

SIMPLE_TEST(Multiply7, TestSAMPLE1, 28, 4);


THE_BENCHMARK(Multiply10, 5);

SIMPLE_TEST(Multiply10, TestSAMPLE1, 50, 5);


THE_BENCHMARK(Multiply12, 5);

SIMPLE_TEST(Multiply12, TestSAMPLE1, 60, 5);


THE_BENCHMARK(Multiply15, 7);

SIMPLE_TEST(Multiply15, TestSAMPLE1, 105, 7);
