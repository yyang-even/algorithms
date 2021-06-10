#pragma once


/** Conditionally set or clear bits without branching
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Conditionally set or clear bits without branching
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 * @param is_set    if (is_set) bits |= mask; else bits &= ~mask;
 */
static inline constexpr unsigned
SetOrClear(const bool is_set, const unsigned mask, const unsigned bits) {
    return bits ^ ((-is_set ^ bits) & mask);
}

static inline constexpr unsigned
SetOrClear_Superscalar(const bool is_set, const unsigned mask, const unsigned bits) {
    return (bits & ~mask) | (-is_set & mask);
}
