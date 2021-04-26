#pragma once

#include "count_set_bits.h"


/** Count the consecutive zero bits (trailing) on the right linearly
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Count the consecutive zero bits (trailing) on the right linearly
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 * Count num's trailing zero bits, so if v is 1101000 (base 2), then the output will be 3
 */
static constexpr inline unsigned CountTrailingZeros_Linear(unsigned num) {
    if (num) {
        num = (num ^ (num - 1)) >> 1;  // Set num's trailing 0s to 1s and zero rest
        return CountSetBits_BrianKernighan(num);

    } else {
        return BitsNumber<decltype(num)>;
    }
}
