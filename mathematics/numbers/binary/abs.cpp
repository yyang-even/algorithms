#include "common_header.h"


namespace {

/** Compute the integer absolute value (abs) without branching
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Compute the integer absolute value (abs) without branching
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   Compute the integer absolute value (abs) without branching
 *              https://www.geeksforgeeks.org/compute-the-integer-absolute-value-abs-without-branching/
 */
inline constexpr unsigned Absolute(const int num) {
    const auto mask = num >> (BitsNumber<decltype(num)> - 1);
    return (num + mask) ^ mask;
}


inline constexpr unsigned Abs_Patented(const int num) {
    const auto mask = num >> (BitsNumber<decltype(num)> - 1);
    return (num ^ mask) - mask;
}

}//namespace


constexpr auto LOWER = std::numeric_limits<int>::min();
constexpr auto UPPER = std::numeric_limits<int>::max();


SIMPLE_BENCHMARK(Absolute, Sample1, -1);
SIMPLE_BENCHMARK(Absolute, Sample2, 0);

SIMPLE_TEST(Absolute, TestSample1, 1, -1);
SIMPLE_TEST(Absolute, TestSample2, 1, -1);
SIMPLE_TEST(Absolute, TestSample3, 0, 0);
SIMPLE_TEST(Absolute, TestSample5, UPPER, UPPER);


SIMPLE_BENCHMARK(Abs_Patented, Sample1, -1);
SIMPLE_BENCHMARK(Abs_Patented, Sample2, 0);

SIMPLE_TEST(Abs_Patented, TestSample1, 1, -1);
SIMPLE_TEST(Abs_Patented, TestSample2, 1, -1);
SIMPLE_TEST(Abs_Patented, TestSample3, 0, 0);
SIMPLE_TEST(Abs_Patented, TestSample5, UPPER, UPPER);
