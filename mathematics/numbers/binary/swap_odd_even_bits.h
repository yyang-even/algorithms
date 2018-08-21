/** Swap all odd and even bits
 *
 * @reference   https://www.geeksforgeeks.org/swap-all-odd-and-even-bits/
 *
 * Given an unsigned integer, swap all odd bits with even bits. For example,
 * if the given number is 23 (00010111), it should be converted to 43 (00101011).
 * Every even position bit is swapped with adjacent bit on right side (even
 * position bits are highlighted in binary representation of 23), and every
 * odd position bit is swapped with adjacent on left side.
 */
inline constexpr auto SwapOddAndEvenBits(const unsigned num) {
    return ((num >> 1) & 0x55555555) | ((num & 0x55555555) << 1);
}
