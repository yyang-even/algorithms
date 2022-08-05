#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** 1-bit and 2-bit Characters
 *
 * @reference   https://leetcode.com/problems/1-bit-and-2-bit-characters/
 *
 * We have two special characters:
 *  The first character can be represented by one bit 0.
 *  The second character can be represented by two bits (10 or 11).
 * Given a binary array bits that ends with 0, return true if the last character must be a one-bit
 * character.
 */
auto BitChars(const ArrayType &bits) {
    const int N = bits.size();

    int count_1 = 0;
    for (int i = N - 2; i >= 0 and bits[i] == 1; --i) {
        ++count_1;
    }

    return (count_1 % 2 == 0);
}

} //namespace


const ArrayType SAMPLE1 = {1, 0, 0};
const ArrayType SAMPLE2 = {1, 1, 1, 0};


THE_BENCHMARK(BitChars, SAMPLE1);

SIMPLE_TEST(BitChars, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(BitChars, TestSAMPLE2, false, SAMPLE2);
