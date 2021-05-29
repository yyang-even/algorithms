#pragma once


/** Find the log base 2 of an integer with a lookup table
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Find the log base 2 of an integer with a lookup table
 *              https://graphics.stanford.edu/~seander/bithacks.html
 */
static constexpr char LogTable256[256] = {
#define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n
    -1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
        LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6),
        LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7)
    };
#undef LT

static constexpr inline unsigned
LogBase2_LookupTable(const uint32_t num) {
    unsigned t{}, tt{}; // temporaries

    if ((tt = num >> 16)) {
        return (t = tt >> 8) ? 24 + LogTable256[t] : 16 + LogTable256[tt];
    } else {
        return (t = num >> 8) ? 8 + LogTable256[t] : LogTable256[num];
    }
}
