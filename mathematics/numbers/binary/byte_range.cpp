#include "common_header.h"


namespace {

/** Determine if a word has a zero byte
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Determine if a word has a zero byte
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
#define haszero(v) (((v) - 0x01010101) & ~(v) & 0x80808080)
inline constexpr bool HasByteZero(const uint32_t num) {
    return haszero(num);
}


/** Determine if a word has a zero byte
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Determine if a word has a zero byte
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
inline constexpr auto HasByteZero_Pointer(const unsigned num) {
    const auto *p = (const unsigned char *)&num;
    const auto *end = p + sizeof(num);
    for (; p < end; ++p) {
        if ((*p) == 0) {
            return true;
        }
    }
    return false;
}


/** Determine if a word has a byte equal to n
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Determine if a word has a byte equal to n
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
#define hasvalue(x,n) (haszero((x) ^ (~0UL/255 * (n))))
inline constexpr bool HasByteN(const uint32_t x, const unsigned char n) {
    return hasvalue(x, n);
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

}//namespace


constexpr auto LOWER = std::numeric_limits<uint32_t>::min();
constexpr auto UPPER = std::numeric_limits<uint32_t>::max();


THE_BENCHMARK(HasByteZero, UPPER);

SIMPLE_TEST(HasByteZero, TestLOWER, true, LOWER);
SIMPLE_TEST(HasByteZero, TestUPPER, false, UPPER);
SIMPLE_TEST(HasByteZero, TestSAMPLE1, true, 8);
SIMPLE_TEST(HasByteZero, TestSAMPLE2, false, 0x88888888);


THE_BENCHMARK(HasByteZero_Pointer, UPPER);

SIMPLE_TEST(HasByteZero_Pointer, TestLOWER, true, LOWER);
SIMPLE_TEST(HasByteZero_Pointer, TestUPPER, false, UPPER);
SIMPLE_TEST(HasByteZero_Pointer, TestSAMPLE1, true, 8);
SIMPLE_TEST(HasByteZero_Pointer, TestSAMPLE2, false, 0x88888888);


THE_BENCHMARK(HasByteN, UPPER, 0xF);

SIMPLE_TEST(HasByteN, TestLOWER, true, LOWER, 0);
SIMPLE_TEST(HasByteN, TestUPPER, true, UPPER, 0xFF);
SIMPLE_TEST(HasByteN, TestSAMPLE1, false, 8, 0xFF);
SIMPLE_TEST(HasByteN, TestSAMPLE2, true, 0x88888888U, 0x88);
