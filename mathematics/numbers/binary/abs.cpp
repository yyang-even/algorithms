#include "common_header.h"

namespace {

typedef int InputType;

/** Compute the integer absolute value (abs) without branching
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Compute the integer absolute value (abs) without branching
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   Compute the integer absolute value (abs) without branching
 *              https://www.geeksforgeeks.org/compute-the-integer-absolute-value-abs-without-branching/
 */
unsigned Absolute(const InputType num) {
    const InputType mask = num >> (Bits_Number<decltype(num)>() - 1);
    return (num + mask) ^ mask;
}


unsigned Abs_Patented(const InputType num) {
    const InputType mask = num >> (Bits_Number<decltype(num)>() - 1);
    return (num ^ mask) - mask;
}

}//namespace


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr auto UPPER = std::numeric_limits<InputType>::max();


SIMPLE_BENCHMARK(Absolute, -1);
SIMPLE_BENCHMARK(Absolute, 0);
SIMPLE_BENCHMARK(Absolute, LOWER);
SIMPLE_BENCHMARK(Absolute, UPPER);

SIMPLE_TEST(Absolute, TestSample1, 1u, -1);
SIMPLE_TEST(Absolute, TestSample2, 1u, -1);
SIMPLE_TEST(Absolute, TestSample3, 0u, 0);
SIMPLE_TEST(Absolute, TestSample4, static_cast<unsigned>(UPPER) + 1, LOWER);
SIMPLE_TEST(Absolute, TestSample5, static_cast<unsigned>(UPPER), UPPER);


SIMPLE_BENCHMARK(Abs_Patented, -1);
SIMPLE_BENCHMARK(Abs_Patented, 0);
SIMPLE_BENCHMARK(Abs_Patented, LOWER);
SIMPLE_BENCHMARK(Abs_Patented, UPPER);

SIMPLE_TEST(Abs_Patented, TestSample1, 1u, -1);
SIMPLE_TEST(Abs_Patented, TestSample2, 1u, -1);
SIMPLE_TEST(Abs_Patented, TestSample3, 0u, 0);
SIMPLE_TEST(Abs_Patented, TestSample4, static_cast<unsigned>(UPPER) + 1, LOWER);
SIMPLE_TEST(Abs_Patented, TestSample5, static_cast<unsigned>(UPPER), UPPER);

MUTUAL_RANDOM_TEST(Absolute, Abs_Patented, LOWER, UPPER);
