#include "common_header.h"

#include "mathematics/numbers/binary/are_opposite_signs.h"


namespace {

/** Divide two integers without using multiplication, division and mod operator
 *
 * @reference   https://www.geeksforgeeks.org/divide-two-integers-without-using-multiplication-division-mod-operator/
 * @reference   Division without using ‘/’ operator
 *              https://www.geeksforgeeks.org/division-without-using-operator/
 */
auto Division_Subtract(int dividend, int divisor) {
    assert(divisor);

    const auto sign = AreOppositeSigns(dividend, divisor) ? -1 : 1;

    dividend = std::abs(dividend);
    divisor = std::abs(divisor);

    auto quotient = 0;
    for (; dividend >= divisor; dividend -= divisor, ++quotient);

    return sign * quotient;
}


auto Division_Bit(int dividend, int divisor) {
    assert(divisor);

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


/**
 * @reference   Divide two integers without using multiplication, division and mod operator | Set2
 *              https://www.geeksforgeeks.org/divide-two-integers-without-using-multiplication-division-and-mod-operator-set2/
 */
int Division_Log(int dividend, int divisor) {
    assert(divisor);

    const auto sign = AreOppositeSigns(dividend, divisor) ? -1 : 1;

    dividend = std::abs(dividend);
    divisor = std::abs(divisor);

    return sign * std::exp(std::log(dividend) - std::log(divisor));
}

}//namespace


SIMPLE_BENCHMARK(Division_Subtract, Sample1, 10, 3);

SIMPLE_TEST(Division_Subtract, TestSAMPLE1, 3, 10, 3);
SIMPLE_TEST(Division_Subtract, TestSAMPLE2, -5, 43, -8);
SIMPLE_TEST(Division_Subtract, TestSAMPLE3, 0, 0, -8);
SIMPLE_TEST(Division_Subtract, TestSAMPLE4, 3, 3, 1);


SIMPLE_BENCHMARK(Division_Bit, Sample1, 10, 3);

SIMPLE_TEST(Division_Bit, TestSAMPLE1, 3, 10, 3);
SIMPLE_TEST(Division_Bit, TestSAMPLE2, -5, 43, -8);
SIMPLE_TEST(Division_Bit, TestSAMPLE3, 0, 0, -8);
SIMPLE_TEST(Division_Bit, TestSAMPLE4, 3, 3, 1);


SIMPLE_BENCHMARK(Division_Log, Sample1, 10, 3);

SIMPLE_TEST(Division_Log, TestSAMPLE1, 3, 10, 3);
SIMPLE_TEST(Division_Log, TestSAMPLE2, -5, 43, -8);
SIMPLE_TEST(Division_Log, TestSAMPLE3, 0, 0, -8);
SIMPLE_TEST(Division_Log, TestSAMPLE4, 3, 3, 1);
