#include "common_header.h"


namespace {

/** Increment a number without using ++ or +
 *
 * @reference   https://www.geeksforgeeks.org/increment-a-number-without-using-or/
 *
 * The task is to Increment a number without using ++ and + operators.
 */
auto Increment(const unsigned num) {
    return -(~num);
}

}//namespace


SIMPLE_BENCHMARK(Increment, Sample1, 4);

SIMPLE_TEST(Increment, TestSample1, 4u, 3);
SIMPLE_TEST(Increment, TestSample2, 10u, 9);
