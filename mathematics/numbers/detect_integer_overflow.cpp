#include "common_header.h"


namespace {

/** Check for Integer Overflow
 *
 * @reference   https://www.geeksforgeeks.org/check-for-integer-overflow/
 *
 * Write a “C” function, int addOvf(int* result, int a, int b) If there is no overflow,
 * the function places the resultant = sum a+b in “result” and returns 0. Otherwise it
 * returns -1. The solution of casting to long and adding to find detecting the overflow
 * is not allowed.
 */
const auto INVALID = std::make_pair(true, 0);

auto SafeAdd_Sign(const int lhs, const int rhs) {
    const auto sum = lhs + rhs;
    if ((lhs > 0 and rhs > 0 and sum < 0) or    //overflow
        (lhs < 0 and rhs < 0 and sum > 0)) {    //underflow
        return INVALID;
    }
    return std::make_pair(false, sum);
}


/**
 * @reference   Agner Fog. NAN propagation versus fault trapping in floating point code.
 */
auto SafeAdd_Limits(const int lhs, const int rhs) {
    if ((rhs > 0 and lhs > std::numeric_limits<int>::max() - rhs) or    //overflow
        (rhs < 0 and lhs < std::numeric_limits<int>::min() - rhs)) {    //underflow
        return INVALID;
    }
    return std::make_pair(false, lhs + rhs);
}


auto SafeAdd_Unsigned(const unsigned lhs, const unsigned rhs) {
    const auto sum = lhs + rhs;
    if (sum < lhs) {
        return INVALID;
    }
    return decltype(INVALID)(false, sum);
}

}//namespace


const auto EXPECTED1 = std::make_pair(false, 9);
const auto EXPECTED2 = std::make_pair(false, -9);
const auto EXPECTED3 = std::make_pair(false, -1);


SIMPLE_BENCHMARK(SafeAdd_Sign, Sample1, 4, 5);

SIMPLE_TEST(SafeAdd_Sign, TestSAMPLE1, EXPECTED1, 4, 5);
SIMPLE_TEST(SafeAdd_Sign, TestSAMPLE2, EXPECTED2, -4, -5);
SIMPLE_TEST(SafeAdd_Sign, TestSAMPLE3, EXPECTED3, 4, -5);
SIMPLE_TEST(SafeAdd_Sign, TestOverflow, INVALID, std::numeric_limits<int>::max(), 5);
SIMPLE_TEST(SafeAdd_Sign, TestUnderflow, INVALID, -5, std::numeric_limits<int>::min());


SIMPLE_BENCHMARK(SafeAdd_Limits, Sample1, 4, 5);

SIMPLE_TEST(SafeAdd_Limits, TestSAMPLE1, EXPECTED1, 4, 5);
SIMPLE_TEST(SafeAdd_Limits, TestSAMPLE2, EXPECTED2, -4, -5);
SIMPLE_TEST(SafeAdd_Limits, TestSAMPLE3, EXPECTED3, 4, -5);
SIMPLE_TEST(SafeAdd_Limits, TestOverflow, INVALID, std::numeric_limits<int>::max(), 5);
SIMPLE_TEST(SafeAdd_Limits, TestUnderflow, INVALID, -5, std::numeric_limits<int>::min());


SIMPLE_BENCHMARK(SafeAdd_Unsigned, Sample1, 4, 5);

SIMPLE_TEST(SafeAdd_Unsigned, TestSAMPLE1, EXPECTED1, 4, 5);
SIMPLE_TEST(SafeAdd_Unsigned, TestOverflow, INVALID, std::numeric_limits<unsigned>::max(), 5);
