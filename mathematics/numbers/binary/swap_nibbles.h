#pragma once


/** Swap two nibbles in a byte
 *
 * @reference   https://www.geeksforgeeks.org/swap-two-nibbles-byte/
 *
 * A nibble is a four-bit aggregation, or half an octet. There are two nibbles in a byte.
 * Given a byte, swap the two nibbles in it.
 */
static inline constexpr auto SwapNibbles(const uint32_t num) {
    return ((num >> 4) & 0x0F0F0F0F) | ((num & 0x0F0F0F0F) << 4);
}
