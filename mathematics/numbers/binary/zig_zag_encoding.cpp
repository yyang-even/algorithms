#include "common_header.h"


namespace {

/** Zig Zag Encoding
 *
 * @reference   Protocol Buffers: Encoding
 *              https://developers.google.com/protocol-buffers/docs/encoding
 *
 * @reference   Zig Zag Decoding
 *              https://stackoverflow.com/questions/2210923/zig-zag-decoding
 *
 * ZigZag encoding maps signed integers to unsigned integers so that numbers with a small
 * absolute value (for instance, -1) have a small varint encoded value too. It does this
 * in a way that "zig-zags" back and forth through the positive and negative integers, so
 * that -1 is encoded as 1, 1 is encoded as 2, -2 is encoded as 3, and so on.
 */
inline constexpr unsigned ZigZagEncoding(const int num) {
    return (num << 1) ^ (num >> (BitsNumber<decltype(num)> - 1));
}


inline constexpr int ZigZagDecoding(const unsigned num) {
    return (num >> 1) ^ (-(num & 1));
}

}//namespace


SIMPLE_BENCHMARK(ZigZagEncoding, Sample1, 0);
SIMPLE_BENCHMARK(ZigZagEncoding, Sample2, 1);
SIMPLE_BENCHMARK(ZigZagEncoding, Sample3, -1);

SIMPLE_TEST(ZigZagEncoding, TestSample1, 0, 0);
SIMPLE_TEST(ZigZagEncoding, TestSample2, 1, -1);
SIMPLE_TEST(ZigZagEncoding, TestSample3, 2, 1);
SIMPLE_TEST(ZigZagEncoding, TestSample4, 3, -2);
SIMPLE_TEST(ZigZagEncoding, TestSample5, 4294967294, 2147483647);
SIMPLE_TEST(ZigZagEncoding, TestSample6, 4294967295, -2147483648);


SIMPLE_BENCHMARK(ZigZagDecoding, Sample1, 0);
SIMPLE_BENCHMARK(ZigZagDecoding, Sample2, 1);
SIMPLE_BENCHMARK(ZigZagDecoding, Sample3, -1);

SIMPLE_TEST(ZigZagDecoding, TestSample1, 0, 0);
SIMPLE_TEST(ZigZagDecoding, TestSample2, -1, 1);
SIMPLE_TEST(ZigZagDecoding, TestSample3, 1, 2);
SIMPLE_TEST(ZigZagDecoding, TestSample4, -2, 3);
SIMPLE_TEST(ZigZagDecoding, TestSample5, 2147483647, 4294967294);
SIMPLE_TEST(ZigZagDecoding, TestSample6, -2147483648, 4294967295);
