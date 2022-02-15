#pragma once


/**
 * @reference   What is the strict aliasing rule?
 *              https://stackoverflow.com/questions/98650/what-is-the-strict-aliasing-rule
 */
union FloatUnsignedUnion {
    static_assert(sizeof(float) == sizeof(unsigned));

    float f;
    unsigned u;
};


constexpr char CASE_DIFF = 'a' - 'A';

static inline constexpr auto ToggleCase(const char c) {
    return c ^ CASE_DIFF;
}
