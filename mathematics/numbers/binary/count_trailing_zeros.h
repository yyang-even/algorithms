#pragma once


/** Count the consecutive zero bits (trailing) on the right linearly
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Count the consecutive zero bits (trailing) on the right linearly
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 * Count num's trailing zero bits, so if v is 1101000 (base 2), then the output will be 3
 */
auto CountTrailingZerosLinear(unsigned num) {
    unsigned result = 0;
    if (num) {
        num = (num ^ (num - 1)) >> 1;  // Set num's trailing 0s to 1s and zero rest
        for (; num; ++result) {
            num >>= 1;
        }
    } else {
        result = Bits_Number<decltype(num)>();
    }
    return result;
}
