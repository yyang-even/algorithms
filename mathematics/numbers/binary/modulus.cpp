#include "common_header.h"

typedef unsigned InputType;

/** Compute modulus division by 1 << s without a division operator
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Compute modulus division by 1 << s without a division operator
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 * Swap two values without using a temporary variable.
 */
InputType Modulus2Power(const unsigned num, const unsigned s) {
    return num & ((1U << s) - 1);
}


const InputType LOWER = 0;
constexpr InputType UPPER = (sizeof(InputType) * CHAR_BIT) - 1;

SIMPLE_BENCHMARK(Modulus2Power, 1, UPPER);

SIMPLE_TEST(Modulus2Power, TestLOWER, LOWER, LOWER, LOWER);
SIMPLE_TEST(Modulus2Power, TestUPPER, UPPER, UPPER, UPPER);
SIMPLE_TEST(Modulus2Power, TestSAMPLE1, 51, 179, 7);
SIMPLE_TEST(Modulus2Power, TestSAMPLE2, 0, 708, 2);
