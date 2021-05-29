#include "common_header.h"


namespace {

/** Multiply large integers under large modulo
 *
 * @reference   https://www.geeksforgeeks.org/multiply-large-integers-under-large-modulo/
 *
 * Given an integer a, b, m. Find (a * b) mod m, where a, b may be large and their direct
 * multiplication may cause overflow. However they are smaller than half of the maximum
 * allowed long long int value.
 */
constexpr auto
ModularMultiplication(long long a, long long b, const long long mod) {
    long long result = 0;
    a %= mod;

    for (a %= mod; b; b >>= 1) {
        if (b & 1) {
            result = (result + a) % mod;
        }
        a = (2 * a) % mod;
    }

    return result;
}

}//namespace


THE_BENCHMARK(ModularMultiplication, 426, 964, 235);

SIMPLE_TEST(ModularMultiplication, TestSample1, 119, 426, 964, 235);
SIMPLE_TEST(ModularMultiplication, TestSample2, 4652135769797794,
            10123465234878998, 65746311545646431, 10005412336548794);
