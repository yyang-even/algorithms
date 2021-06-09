#include "common_header.h"


namespace {

/** Length of the Longest Consecutive 1s in Binary Representation
 *
 * @reference   https://www.geeksforgeeks.org/length-longest-consecutive-1s-binary-representation/
 *
 * The idea is based on the concept that if we AND a bit sequence with a shifted version
 * of itself, we're effectively removing the trailing 1 from every sequence of
 * consecutive 1s.
 */
constexpr auto LengthOfLongestConsecutive1s(unsigned number) {
    unsigned length = 0;
    while (number) {
        number &= (number << 1);
        ++length;
    }

    return length;
}


/** Length of longest consecutive zeroes in the binary representation of a number.
 *
 * @reference   https://www.geeksforgeeks.org/length-of-longest-consecutive-zeroes-in-the-binary-representation-of-a-number/
 */

}//namespace


THE_BENCHMARK(LengthOfLongestConsecutive1s, 14);

SIMPLE_TEST(LengthOfLongestConsecutive1s, TestSAMPLE1, 3, 14);
SIMPLE_TEST(LengthOfLongestConsecutive1s, TestSAMPLE2, 4, 222);
