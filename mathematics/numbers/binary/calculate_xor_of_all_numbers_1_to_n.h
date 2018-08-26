#pragma once

/** Calculate XOR from 1 to n.
 *
 * @reference   https://www.geeksforgeeks.org/calculate-xor-1-n/
 * @reference   Bits manipulation (Important tactics)
 *              https://www.geeksforgeeks.org/bits-manipulation-important-tactics/
 *
 * Given a number n, the task is to find the XOR from 1 to n.
 */
unsigned XorOfAllFrom1toN(const unsigned n) {
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
