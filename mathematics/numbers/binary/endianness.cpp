#include "common_header.h"


namespace {

/** Is Little Endian
 *
 * @reference   Little and Big Endian Mystery
 *              https://www.geeksforgeeks.org/little-and-big-endian-mystery/
 *
 * Is there a quick way to determine endianness of your machine?
 */
inline constexpr bool IsLittleEndian_Pointer() {
    const auto one = 1;
    const auto *byte_ptr = reinterpret_cast<const char *>(&one);
    return *byte_ptr;
}


/**
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 13.
 */
union EndiannessUnion {
    int i;
    char c;
};

inline constexpr bool IsLittleEndian_Union() {
    EndiannessUnion endianness{};
    endianness.i = 1;
    return endianness.c;
}

}//namespace


#ifdef __GNUC__
constexpr bool EXPECTED = __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__;
SIMPLE_TEST0(IsLittleEndian_Pointer, Test, EXPECTED);
SIMPLE_TEST0(IsLittleEndian_Union, Test, EXPECTED);
#endif
