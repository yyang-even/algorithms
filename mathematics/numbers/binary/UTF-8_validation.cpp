#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** UTF-8 Validation
 *
 * @reference   https://leetcode.com/problems/utf-8-validation/
 *
 * Given an integer array data representing the data, return whether it is a valid UTF-8 encoding (i.e.
 * it translates to a sequence of valid UTF-8 encoded characters).
 * A character in UTF8 can be from 1 to 4 bytes long, subjected to the following rules:
 *  For a 1-byte character, the first bit is a 0, followed by its Unicode code.
 *  For an n-bytes character, the first n bits are all one's, the n + 1 bit is 0, followed by n - 1
 *      bytes with the most significant 2 bits being 10.
 * This is how the UTF-8 encoding would work:
 *
 *  Number of Bytes    |        UTF-8 Octet Sequence (binary)
 *  -------------------+-----------------------------------------
 *          1          |   0xxxxxxx
 *          2          |   110xxxxx 10xxxxxx
 *          3          |   1110xxxx 10xxxxxx 10xxxxxx
 *          4          |   11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 *
 * x denotes a bit in the binary form of a byte that may be either 0 or 1.
 * Note: The input is an array of integers. Only the least significant 8 bits of each integer is used to
 * store the data. This means each integer represents only 1 byte of data.
 */
auto UTF8Validation(const ArrayType &data) {
    int count = 0;
    for (const auto d : data) {
        const unsigned b = d & 0xFF;
        if (count == 0) {
            if ((b >> 5) == 0b110) {
                count = 1;
            } else if ((b >> 4) == 0b1110) {
                count = 2;
            } else if ((b >> 3) == 0b11110) {
                count = 3;
            } else if ((b >> 7)) {
                return false;
            }
        } else {
            if ((b >> 6) != 0b10) {
                return false;
            }
            --count;
        }
    }

    return count == 0;
}

} //namespace


const ArrayType SAMPLE1 = {197, 130, 1};
const ArrayType SAMPLE2 = {235, 140, 4};
const ArrayType SAMPLE3 = {255};


THE_BENCHMARK(UTF8Validation, SAMPLE1);

SIMPLE_TEST(UTF8Validation, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(UTF8Validation, TestSAMPLE2, false, SAMPLE2);
SIMPLE_TEST(UTF8Validation, TestSAMPLE3, false, SAMPLE3);
