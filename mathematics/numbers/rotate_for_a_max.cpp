#include "common_header.h"

namespace {

/** Rotate for a Max
 *
 * @reference   Rotate for a Max
 *              https://www.codewars.com/kata/rotate-for-a-max/cpp
 *
 * Take a number: 56789. Rotate left, you get 67895.
 * Keep the first digit in place and rotate left the other digits: 68957.
 * Keep the first two digits in place and rotate the other ones: 68579.
 * Keep the first three digits and rotate left the rest: 68597.
 * Now it is over since keeping the first four it remains only one digit which rotated
 * is itself.
 * You have the following sequence of numbers:
 *  56789 -> 67895 -> 68957 -> 68579 -> 68597
 * and you must return the greatest: 68957.
 */
auto RotateForMax(long long n) {
    auto str_n = std::to_string(n);
    for (auto iter = str_n.begin(); iter != str_n.end(); ++iter) {
        std::rotate(iter, iter + 1, str_n.end());
        n = std::max(stoll(str_n), n);
    }
    return n;
}

}//namespace


THE_BENCHMARK(RotateForMax, 56789);

SIMPLE_TEST(RotateForMax, TestSample1, 68957, 56789);
SIMPLE_TEST(RotateForMax, TestSample2, 85821534, 38458215);
SIMPLE_TEST(RotateForMax, TestSample3, 988103115, 195881031);
SIMPLE_TEST(RotateForMax, TestSample4, 962193428, 896219342);
SIMPLE_TEST(RotateForMax, TestSample5, 94183076, 69418307);
