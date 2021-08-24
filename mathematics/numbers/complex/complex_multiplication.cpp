#include "common_header.h"

#include "complex.h"


namespace {

/** Complex Number Multiplication
 *
 * @reference   https://leetcode.com/problems/complex-number-multiplication/
 *
 * A complex number can be represented as a string on the form "real+imaginaryi" where:
 *  real is the real part and is an integer in the range [-100, 100].
 *  imaginary is the imaginary part and is an integer in the range [-100, 100].
 *  i^2 == -1.
 * Given two complex numbers num1 and num2 as strings, return a string of the complex
 * number that represents their multiplications.
 */
inline auto ComplexMultiplication(const std::string_view num1,
                                  const std::string_view num2) {
    return ToStr(Complex(num1) * Complex(num2));
}

}//namespace


THE_BENCHMARK(ComplexMultiplication, "1+1i", "1+1i");

SIMPLE_TEST(ComplexMultiplication, TestSAMPLE1, "0+2i", "1+1i", "1+1i");
SIMPLE_TEST(ComplexMultiplication, TestSAMPLE2, "0+-2i", "1+-1i", "1+-1i");
SIMPLE_TEST(ComplexMultiplication, TestSAMPLE3, "-1236+12152i", "78+-76i", "-86+72i");

