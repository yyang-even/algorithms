#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Gray Code
 *
 * @reference   https://leetcode.com/problems/gray-code/
 *
 * An n-bit gray code sequence is a sequence of 2^n integers where:
 *  Every integer is in the inclusive range [0, 2^n - 1],
 *  The first integer is 0,
 *  An integer appears no more than once in the sequence,
 *  The binary representation of every pair of adjacent integers differs by exactly one bit, and
 *  The binary representation of the first and last integers differs by exactly one bit.
 * Given an integer n, return any valid n-bit gray code sequence.
 *
 * @reference   Generate n-bit Gray Codes
 *              https://www.geeksforgeeks.org/generate-n-bit-gray-codes/
 * @reference   Generate n-bit Gray Codes | Set 2
 *              https://www.geeksforgeeks.org/generate-n-bit-gray-codes-set-2/
 * @reference   A backtracking approach to generate n bit Gray Codes
 *              https://www.geeksforgeeks.org/backtracking-approach-generate-n-bit-gray-codes/
 */
void GrayCode_Recursive(const unsigned n, ArrayType &results) {
    if (n == 0) {
        results.push_back(0);
        return;
    }

    GrayCode_Recursive(n - 1, results);
    const auto mask = 1u << (n - 1);
    for (int i = results.size() - 1; i >= 0; --i) {
        results.push_back(results[i] | mask);
    }
}

inline auto GrayCode_Recursive(const unsigned n) {
    assert(1 <= n and n <= 16);

    ArrayType results;
    GrayCode_Recursive(n, results);

    return results;
}


auto GrayCode_Iterative(const unsigned n) {
    assert(1 <= n and n <= 16);

    ArrayType results{0};

    for (unsigned i = 1; i <= n; ++i) {
        const auto mask = 1u << (i - 1);
        for (int j = results.size() - 1; j >= 0; --j) {
            results.push_back(mask + results[j]);
        }
    }

    return results;
}


inline auto GrayCode(const unsigned n) {
    assert(1 <= n and n <= 16);

    ArrayType results;
    for (unsigned i = 0; i < (1u << n); ++i) {
        results.push_back(i ^ (i >> 1));
    }

    return results;
}

}//namespace


const ArrayType EXPECTED1 = {0, 1};
const ArrayType EXPECTED2 = {0, 1, 0b11, 0b10};
const ArrayType EXPECTED3 = {0b000, 0b001, 0b011, 0b010, 0b110, 0b111, 0b101, 0b100};


THE_BENCHMARK(GrayCode_Recursive, 3);

SIMPLE_TEST(GrayCode_Recursive, TestSAMPLE1, EXPECTED1, 1);
SIMPLE_TEST(GrayCode_Recursive, TestSAMPLE2, EXPECTED2, 2);
SIMPLE_TEST(GrayCode_Recursive, TestSAMPLE3, EXPECTED3, 3);


THE_BENCHMARK(GrayCode_Iterative, 3);

SIMPLE_TEST(GrayCode_Iterative, TestSAMPLE1, EXPECTED1, 1);
SIMPLE_TEST(GrayCode_Iterative, TestSAMPLE2, EXPECTED2, 2);
SIMPLE_TEST(GrayCode_Iterative, TestSAMPLE3, EXPECTED3, 3);


THE_BENCHMARK(GrayCode, 3);

SIMPLE_TEST(GrayCode, TestSAMPLE1, EXPECTED1, 1);
SIMPLE_TEST(GrayCode, TestSAMPLE2, EXPECTED2, 2);
SIMPLE_TEST(GrayCode, TestSAMPLE3, EXPECTED3, 3);
