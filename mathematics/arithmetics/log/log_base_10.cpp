#include "common_header.h"

#include "mathematics/numbers/binary/binary.h"

typedef unsigned InputType;

/** Find integer log base 10 of an integer
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Find integer log base 10 of an integer
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
InputType LogBase10(const InputType num) {
    static_assert(sizeof(InputType) * CHAR_BIT == 32, "InputType is not 32 bits.");

    static InputType constexpr PowersOf10[] = {
        1, 10, 100, 1000, 10000, 100000,
        1000000, 10000000, 100000000, 1000000000
    };

    const auto t = (LogBase2LookupTable(num) + 1) * 1233 >> 12; //log10(v) = log2(v) / log2(10)
    return t - (num < PowersOf10[t]);
}


/** Find integer log base 10 of an integer the obvious way
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Find integer log base 10 of an integer the obvious way
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
inline InputType LogBase10Enum(const InputType num) {
    static_assert(sizeof(InputType) * CHAR_BIT == 32, "InputType is not 32 bits.");

    return (num >= 1000000000) ? 9 : (num >= 100000000) ? 8 : (num >= 10000000) ? 7 :
           (num >= 1000000) ? 6 : (num >= 100000) ? 5 : (num >= 10000) ? 4 :
           (num >= 1000) ? 3 : (num >= 100) ? 2 : (num >= 10) ? 1 : 0;
}



constexpr InputType LOWER = 1;
constexpr InputType UPPER = std::numeric_limits<InputType>::max();

SIMPLE_BENCHMARK(LogBase10, UPPER);

SIMPLE_TEST(LogBase10, TestLOWER, 0, LOWER);
SIMPLE_TEST(LogBase10, TestUPPER, 9, UPPER);
SIMPLE_TEST(LogBase10, TestSAMPLE1, 2, 100);
SIMPLE_TEST(LogBase10, TestSAMPLE2, 4, 87000);

SIMPLE_BENCHMARK(LogBase10Enum, UPPER);

SIMPLE_TEST(LogBase10Enum, TestLOWER, 0, LOWER);
SIMPLE_TEST(LogBase10Enum, TestUPPER, 9, UPPER);
SIMPLE_TEST(LogBase10Enum, TestSAMPLE1, 2, 100);
SIMPLE_TEST(LogBase10Enum, TestSAMPLE2, 4, 87000);

MUTUAL_RANDOM_TEST(LogBase10, LogBase10Enum, LOWER, UPPER);
