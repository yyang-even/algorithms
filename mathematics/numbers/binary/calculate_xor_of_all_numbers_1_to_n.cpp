#include "common_header.h"

using InputType = unsigned;

/** Calculate XOR from 1 to n.
 *
 * @reference   https://www.geeksforgeeks.org/calculate-xor-1-n/
 * @reference   Bits manipulation (Important tactics)
 *              https://www.geeksforgeeks.org/bits-manipulation-important-tactics/
 *
 * Given a number n, the task is to find the XOR from 1 to n.
 */
auto XorOfAllFrom1toN(const InputType n) {
    switch (n % 4) {
        case 0:
            return n;
        case 1:
            return 1u;
        case 2:
            return n + 1u;
        case 3:
        default:
            return 0u;
    }
}


SIMPLE_BENCHMARK(XorOfAllFrom1toN, 4);

SIMPLE_TEST(XorOfAllFrom1toN, TestLOWER, 0, 0);
SIMPLE_TEST(XorOfAllFrom1toN, TestSample1, 1, 1);
SIMPLE_TEST(XorOfAllFrom1toN, TestSample2, 3, 2);
SIMPLE_TEST(XorOfAllFrom1toN, TestSample3, 3, 2);
SIMPLE_TEST(XorOfAllFrom1toN, TestSample4, 0, 3);
SIMPLE_TEST(XorOfAllFrom1toN, TestSample5, 1, 5);
