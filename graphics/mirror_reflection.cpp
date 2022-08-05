#include "common_header.h"


namespace {

/** Mirror Reflection
 *
 * @reference   https://leetcode.com/problems/mirror-reflection/
 *
 * There is a special square room with mirrors on each of the four walls. Except for the southwest
 * corner, there are receptors on each of the remaining corners, numbered 0, 1, and 2.
 * The square room has walls of length p and a laser ray from the southwest corner first meets the east
 * wall at a distance q from the 0th receptor.
 * Given the two integers p and q, return the number of the receptor that the ray meets first.
 * The test cases are guaranteed so that the ray will meet a receptor eventually.
 */
inline constexpr auto MirrorReflection(int p, int q) {
    while (p % 2 == 0 and q % 2 == 0) {
        p >>= 1;
        q >>= 1;
    }

    return 1 - p % 2 + q % 2;
}

} //namespace


THE_BENCHMARK(MirrorReflection, 2, 1);

SIMPLE_TEST(MirrorReflection, TestSAMPLE1, 2, 2, 1);
SIMPLE_TEST(MirrorReflection, TestSAMPLE2, 1, 3, 1);
