#include "common_header.h"


namespace {

/** Is Little Endian
 *
 * @reference   Little and Big Endian Mystery
 *              https://www.geeksforgeeks.org/little-and-big-endian-mystery/
 *
 * Is there a quick way to determine endianness of your machine?
 */
inline INT_BOOL IsLittleEndian() {
    const auto one = 1;
    const auto *byte_ptr = reinterpret_cast<const char *>(&one);
    return *byte_ptr ? TRUE : FALSE;
}

}//namespace


#ifdef __GNUC__
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
SIMPLE_TEST0(IsLittleEndian, Test, TRUE);
#else
SIMPLE_TEST0(IsLittleEndian, Test, FALSE);
#endif
#endif
