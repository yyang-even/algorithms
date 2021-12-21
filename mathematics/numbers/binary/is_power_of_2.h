#pragma once


/** Compute the sign of an integer
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Determining if an integer is a power of 2
 *              https://graphics.stanford.edu/~seander/bithacks.html
 * @reference   Program to find whether a no is power of two
 *              https://www.geeksforgeeks.org/program-to-find-whether-a-no-is-power-of-two/
 * @reference   C Program to find whether a no is power of two
 *              https://www.geeksforgeeks.org/c-program-to-find-whether-a-no-is-power-of-two/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 5.4.
 *
 * @reference   Power of Two
 *              https://leetcode.com/problems/power-of-two/
 *
 * Given an integer n, return true if it is a power of two. Otherwise, return false. An
 * integer n is a power of two, if there exists an integer x such that n == 2x.
 * Follow up: Could you solve it without loops/recursion?
 */
static inline constexpr auto IsPowerOf2(const unsigned num) {
    return num and !(num & (num - 1));
}
