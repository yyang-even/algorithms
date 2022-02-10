#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Print squares of first n natural numbers without using *, / and –
 *
 * @reference   https://www.geeksforgeeks.org/print-squares-first-n-natural-numbers-without-using/
 *
 * Given a natural number 'n', print squares of first n natural numbers without using
 * *, / and -.
 */
auto SquaresOfFirstN_Prev(const ArrayType::value_type N) {
    ArrayType::value_type square = 0, previous_i = 0;
    ArrayType outputs;

    for (ArrayType::value_type i = 0; i < N; ++i) {
        square += (i + previous_i);
        outputs.push_back(square);
        previous_i = i;
    }

    return outputs;
}


auto SquaresOfFirstN_Odd(const ArrayType::value_type N) {
    ArrayType::value_type square = 0, odd = 1;
    ArrayType outputs;

    for (ArrayType::value_type i = 0; i < N; ++i) {
        outputs.push_back(square);
        square += odd;
        odd += 2;
    }

    return outputs;
}

}//namespace


const ArrayType EXPECTED1 = {0, 1, 4, 9, 16};
const ArrayType EXPECTED2 = {0, 1, 4, 9, 16, 25};


THE_BENCHMARK(SquaresOfFirstN_Prev, 51);

SIMPLE_TEST(SquaresOfFirstN_Prev, TestSample1, EXPECTED1, 5);
SIMPLE_TEST(SquaresOfFirstN_Prev, TestSample2, EXPECTED2, 6);


THE_BENCHMARK(SquaresOfFirstN_Odd, 51);

SIMPLE_TEST(SquaresOfFirstN_Odd, TestSample1, EXPECTED1, 5);
SIMPLE_TEST(SquaresOfFirstN_Odd, TestSample2, EXPECTED2, 6);
