#include "common_header.h"


namespace {

/** Increment a number without using ++ or +
 *
 * @reference   https://www.geeksforgeeks.org/increment-a-number-without-using-or/
 *
 * The task is to Increment a number without using ++ and + operators.
 */
inline constexpr auto Increment(const unsigned num) {
    return -(~num);
}

}//namespace


THE_BENCHMARK(Increment, 4);

SIMPLE_TEST(Increment, TestSample1, 4, 3);
SIMPLE_TEST(Increment, TestSample2, 10, 9);
