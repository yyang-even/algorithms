#include "common_header.h"

typedef unsigned InputType;

/** Determine if a word has a zero byte
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Determine if a word has a zero byte
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
#define haszero(v) (((v) - 0x01010101UL) & ~(v) & 0x80808080UL)
INT_BOOL HasByteZero(const InputType num) {
    static_assert(Bits_Number<decltype(num)>() == 32, "InputType is not 32 bits.");

    return haszero(num) ? TRUE : FALSE;
}
/** Determine if a word has a zero byte
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Determine if a word has a zero byte
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
INT_BOOL HasByteZeroPointer(const InputType num) {
    const auto *p = (const unsigned char *)&num;
    const auto *end = p + sizeof(num);
    for (; p < end; ++p) {
        if ((*p) == 0) {
            return TRUE;
        }
    }
    return FALSE;
}

/** Determine if a word has a byte equal to n
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Determine if a word has a byte equal to n
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
#define hasvalue(x,n) (haszero((x) ^ (~0UL/255 * (n))))
INT_BOOL HasByteN(const InputType x, const unsigned char n) {
    static_assert(Bits_Number<decltype(x)>() == 32, "InputType is not 32 bits.");

    return hasvalue(x, n) ? TRUE : FALSE;
}


/** Determine if a word has a byte less than n
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Determine if a word has a byte less than n
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 * Requirements: x>=0; 0<=n<=128
 */
#define hasless(x,n) (((x)-~0UL/255*(n))&~(x)&~0UL/255*128)
#define countless(x,n) \
(((~0UL/255*(127+(n))-((x)&~0UL/255*127))&~(x)&~0UL/255*128)/128%255)



/** Determine if a word has a byte greater than n
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Determine if a word has a byte greater than n
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 * Requirements: x>=0; 0<=n<=127
 */
#define hasmore(x,n) (((x)+~0UL/255*(127-(n))|(x))&~0UL/255*128)
#define countmore(x,n) \
(((((x)&~0UL/255*127)+~0UL/255*(127-(n))|(x))&~0UL/255*128)/128%255)


/** Determine if a word has a byte between m and n
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Determine if a word has a byte between m and n
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 * Requirements: x>=0; 0<=m<=127; 0<=n<=128
 */
#define hasbetween(x,m,n) \
((~0UL/255*(127+(n))-((x)&~0UL/255*127)&~(x)&((x)&~0UL/255*127)+~0UL/255*(127-(m)))&~0UL/255*128)
#define countbetween(x,m,n) (hasbetween(x,m,n)/128%255)


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr auto UPPER = std::numeric_limits<InputType>::max();

SIMPLE_BENCHMARK(HasByteZero, UPPER);

SIMPLE_TEST(HasByteZero, TestLOWER, TRUE, LOWER);
SIMPLE_TEST(HasByteZero, TestUPPER, FALSE, UPPER);
SIMPLE_TEST(HasByteZero, TestSAMPLE1, TRUE, 8);
SIMPLE_TEST(HasByteZero, TestSAMPLE2, FALSE, 0x88888888U);

SIMPLE_BENCHMARK(HasByteZeroPointer, UPPER);

SIMPLE_TEST(HasByteZeroPointer, TestLOWER, TRUE, LOWER);
SIMPLE_TEST(HasByteZeroPointer, TestUPPER, FALSE, UPPER);
SIMPLE_TEST(HasByteZeroPointer, TestSAMPLE1, TRUE, 8);
SIMPLE_TEST(HasByteZeroPointer, TestSAMPLE2, FALSE, 0x88888888U);

SIMPLE_BENCHMARK(HasByteN, UPPER, 0xF);

SIMPLE_TEST(HasByteN, TestLOWER, TRUE, LOWER, 0);
SIMPLE_TEST(HasByteN, TestUPPER, TRUE, UPPER, 0xFF);
SIMPLE_TEST(HasByteN, TestSAMPLE1, FALSE, 8, 0xFF);
SIMPLE_TEST(HasByteN, TestSAMPLE2, TRUE, 0x88888888U, 0x88);
