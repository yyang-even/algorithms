#include "common_header.h"


namespace {

/** Compute the lexicographically next bit permutation
 *
 * @reference   Sean Eron Anderson. Bit Twiddling Hacks.
 *              Compute the lexicographically next bit permutation
 *              https://graphics.stanford.edu/~seander/bithacks.html
 *
 * Suppose we have a pattern of N bits set to 1 in an integer and we want the next
 * permutation of N 1 bits in a lexicographical sense. For example, if N is 3 and the
 * bit pattern is 00010011, the next patterns would be 00010101, 00010110, 00011001,
 * 00011010, 00011100, 00100011, and so forth.
 */
#ifdef __GNUC__
constexpr inline auto ClosestGreaterBitsPermutation_GNUC(const unsigned num) {
    const unsigned t = num | (num - 1); // t gets num's least significant 0 bits set to 1
    // Next set to 1 the most significant bit to change,
    // set to 0 the least significant ones, and add the necessary 1 bits.
    return (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(num) + 1)); //count trailing zeros
}
#endif


constexpr inline auto ClosestGreaterBitsPermutation_Division(const unsigned num) {
    const unsigned t = (num | (num - 1)) + 1;
    return t | ((((t & -t) / (num & -num)) >> 1) - 1);
}


/** Closest (or Next) smaller and greater numbers with same number of set bits
 *
 * @reference   https://www.geeksforgeeks.org/closest-next-smaller-greater-numbers-number-set-bits/
 *
 * Given a positive integer n, print the next smallest and the previous largest number
 * that have the same number of 1 bits in their binary representation.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 5.2.
 */
constexpr auto ClosestGreaterBitsPermutation(const int number) {
    assert(number > 0);

    unsigned temp = number;

    unsigned count_trailing_0s = 0;
    for (; temp and (temp & 1) == 0; temp >>= 1) {
        ++count_trailing_0s;
    }

    unsigned count_1s = 0;
    for (; (temp & 1) == 1; temp >>= 1) {
        ++count_1s;
    }

    const auto position_of_rightmost_nontrailing_0 = count_trailing_0s + count_1s;

    unsigned result = number;
    result |= (1 << position_of_rightmost_nontrailing_0);
    result &= ~((1 << position_of_rightmost_nontrailing_0) - 1);
    result |= (1 << (count_1s - 1)) - 1;

    return result;
}


constexpr auto ClosestGreaterBitsPermutation_Arithmetic(const int number) {
    assert(number > 0);

    unsigned temp = number;

    unsigned count_trailing_0s = 0;
    for (; temp and (temp & 1) == 0; temp >>= 1) {
        ++count_trailing_0s;
    }

    unsigned count_1s = 0;
    for (; (temp & 1) == 1; temp >>= 1) {
        ++count_1s;
    }

    return number + (1 << count_trailing_0s) + (1 << (count_1s - 1)) - 1;
}


constexpr auto ClosestSmallerBitsPermutation(const int number) {
    assert(number > 0);

    unsigned temp = number;

    unsigned count_trailing_1s = 0;
    for (; (temp & 1) == 1; temp >>= 1) {
        ++count_trailing_1s;
    }

    assert(temp);

    unsigned count_0s = 0;
    for (; temp and (temp & 1) == 0; temp >>= 1) {
        ++count_0s;
    }

    const auto position_of_rightmost_nontrailing_1 = count_trailing_1s + count_0s;

    unsigned result = number;
    result &= ((~0u) << (position_of_rightmost_nontrailing_1 + 1));
    const unsigned mask = (1 << (count_trailing_1s + 1)) - 1;
    result |= mask << (count_0s - 1);

    return result;
}


constexpr auto ClosestSmallerBitsPermutation_Arithmetic(const int number) {
    assert(number > 0);

    unsigned temp = number;

    unsigned count_trailing_1s = 0;
    for (; (temp & 1) == 1; temp >>= 1) {
        ++count_trailing_1s;
    }

    assert(temp);

    unsigned count_0s = 0;
    for (; temp and (temp & 1) == 0; temp >>= 1) {
        ++count_0s;
    }

    return number - (1 << count_trailing_1s) - (1 << (count_0s - 1)) + 1;
}


/**
 * @reference   Next higher number with same number of set bits
 *              https://www.geeksforgeeks.org/next-higher-number-with-same-number-of-set-bits/
 */
constexpr auto ClosestGreaterBitsPermutation_Snoob(const int number) {
    assert(number > 0);

    const unsigned unsigned_number = number;
    const unsigned right_most_1 = unsigned_number & -number;

    const auto next_higher_1 = unsigned_number + right_most_1;

    auto right_1s_pattern = unsigned_number ^ next_higher_1;
    right_1s_pattern /= right_most_1;
    right_1s_pattern >>= 2;

    return next_higher_1 | right_1s_pattern;
}

}//namespace


constexpr unsigned LOWER = 1;
constexpr auto UPPER = std::numeric_limits<unsigned>::max();


#ifdef __GNUC__
THE_BENCHMARK(ClosestGreaterBitsPermutation_GNUC, UPPER);

SIMPLE_TEST(ClosestGreaterBitsPermutation_GNUC, TestLOWER, 2, LOWER);
SIMPLE_TEST(ClosestGreaterBitsPermutation_GNUC, TestSAMPLE1, 0b00011001, 0b00010110);
SIMPLE_TEST(ClosestGreaterBitsPermutation_GNUC, TestSAMPLE2, 0b00011100, 0b00011010);
#endif


THE_BENCHMARK(ClosestGreaterBitsPermutation_Division, UPPER);

SIMPLE_TEST(ClosestGreaterBitsPermutation_Division, TestLOWER, 2, LOWER);
SIMPLE_TEST(ClosestGreaterBitsPermutation_Division, TestUPPER, UPPER, UPPER);
SIMPLE_TEST(ClosestGreaterBitsPermutation_Division, TestSAMPLE1,
            0b00011001, 0b00010110);
SIMPLE_TEST(ClosestGreaterBitsPermutation_Division, TestSAMPLE2,
            0b00011100, 0b00011010);


THE_BENCHMARK(ClosestGreaterBitsPermutation, 13948);

SIMPLE_TEST(ClosestGreaterBitsPermutation, TestSAMPLE1, 0b11011010001111, 13948);
SIMPLE_TEST(ClosestGreaterBitsPermutation, TestSAMPLE2, 6, 5);
SIMPLE_TEST(ClosestGreaterBitsPermutation, TestSAMPLE3, 13, 11);
SIMPLE_TEST(ClosestGreaterBitsPermutation, TestSAMPLE4, 16, 8);
SIMPLE_TEST(ClosestGreaterBitsPermutation, TestSAMPLE5, 17, 12);
SIMPLE_TEST(ClosestGreaterBitsPermutation, TestSAMPLE6, 163, 156);
SIMPLE_TEST(ClosestGreaterBitsPermutation, TestSAMPLE7, 0b00011001, 0b00010110);
SIMPLE_TEST(ClosestGreaterBitsPermutation, TestSAMPLE8, 0b00011100, 0b00011010);


THE_BENCHMARK(ClosestGreaterBitsPermutation_Snoob, 13948);

SIMPLE_TEST(ClosestGreaterBitsPermutation_Snoob, TestSAMPLE1, 0b11011010001111, 13948);
SIMPLE_TEST(ClosestGreaterBitsPermutation_Snoob, TestSAMPLE2, 6, 5);
SIMPLE_TEST(ClosestGreaterBitsPermutation_Snoob, TestSAMPLE3, 13, 11);
SIMPLE_TEST(ClosestGreaterBitsPermutation_Snoob, TestSAMPLE4, 16, 8);
SIMPLE_TEST(ClosestGreaterBitsPermutation_Snoob, TestSAMPLE5, 17, 12);
SIMPLE_TEST(ClosestGreaterBitsPermutation_Snoob, TestSAMPLE6, 163, 156);


THE_BENCHMARK(ClosestGreaterBitsPermutation_Arithmetic, 13948);

SIMPLE_TEST(ClosestGreaterBitsPermutation_Arithmetic, TestSAMPLE1,
            0b11011010001111, 13948);
SIMPLE_TEST(ClosestGreaterBitsPermutation_Arithmetic, TestSAMPLE2, 6, 5);
SIMPLE_TEST(ClosestGreaterBitsPermutation_Arithmetic, TestSAMPLE3, 13, 11);
SIMPLE_TEST(ClosestGreaterBitsPermutation_Arithmetic, TestSAMPLE4, 16, 8);


THE_BENCHMARK(ClosestSmallerBitsPermutation, 13948);

SIMPLE_TEST(ClosestSmallerBitsPermutation, TestSAMPLE2, 3, 5);
SIMPLE_TEST(ClosestSmallerBitsPermutation, TestSAMPLE3, 7, 11);
SIMPLE_TEST(ClosestSmallerBitsPermutation, TestSAMPLE4, 5, 6);
SIMPLE_TEST(ClosestSmallerBitsPermutation, TestSAMPLE5, 8, 16);


THE_BENCHMARK(ClosestSmallerBitsPermutation_Arithmetic, 13948);

SIMPLE_TEST(ClosestSmallerBitsPermutation_Arithmetic, TestSAMPLE2, 3, 5);
SIMPLE_TEST(ClosestSmallerBitsPermutation_Arithmetic, TestSAMPLE3, 7, 11);
SIMPLE_TEST(ClosestSmallerBitsPermutation_Arithmetic, TestSAMPLE4, 5, 6);
SIMPLE_TEST(ClosestSmallerBitsPermutation_Arithmetic, TestSAMPLE5, 8, 16);
