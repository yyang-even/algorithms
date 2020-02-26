#include "common_header.h"

#include "mathematics/numbers/binary/are_opposite_signs.h"


namespace {

/** Divide two integers without using multiplication, division and mod operator
 *
 * @reference   https://www.geeksforgeeks.org/divide-two-integers-without-using-multiplication-division-mod-operator/
 */
auto Division_Subtract(int dividend, int divisor) {
    const auto sign = AreOppositeSigns(dividend, divisor) ? -1 : 1;

    dividend = std::abs(dividend);
    divisor = std::abs(divisor);

    auto quotient = 0;
    for (; dividend >= divisor; dividend -= divisor, ++quotient);

    return sign * quotient;
}


auto Division_Bit(int dividend, int divisor) {
    const auto sign = AreOppositeSigns(dividend, divisor) ? -1 : 1;

    dividend = std::abs(dividend);
    divisor = std::abs(divisor);

    auto quotient = 0;
    auto temp = 0;
    for (int i = BitsNumber<decltype(divisor)> - 1; i >= 0; --i) {
        const auto try_number = static_cast<long long>(divisor) << i;
        if (temp + try_number <= dividend) {
            temp += try_number;
            quotient |= 1 << i;
        }
    }

    return sign * quotient;
}

}//namespace


SIMPLE_BENCHMARK(Division_Subtract, 10, 3);

SIMPLE_TEST(Division_Subtract, TestSAMPLE1, 3, 10, 3);
SIMPLE_TEST(Division_Subtract, TestSAMPLE2, -5, 43, -8);


SIMPLE_BENCHMARK(Division_Bit, 10, 3);

SIMPLE_TEST(Division_Bit, TestSAMPLE1, 3, 10, 3);
SIMPLE_TEST(Division_Bit, TestSAMPLE2, -5, 43, -8);