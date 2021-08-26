#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Self Dividing Numbers
 *
 * @reference   https://leetcode.com/problems/self-dividing-numbers/
 *
 * A self-dividing number is a number that is divisible by every digit it contains. For
 * example, 128 is a self-dividing number because 128 % 1 == 0, 128 % 2 == 0, and
 * 128 % 8 == 0. A self-dividing number is not allowed to contain the digit zero. Given
 * two integers left and right, return a list of all the self-dividing numbers in the
 * range [left, right].
 */
constexpr auto isSelfDividing(const int n) {
    for (auto i = n; i > 0; i /= 10) {
        const auto digit = i % 10;
        if (digit == 0 or n % digit != 0) {
            return false;
        }
    }

    return true;
}

auto SelfDividingNumbers(const int left, const int right) {
    ArrayType results;
    for (auto i = left; i <= right; ++i) {
        if (isSelfDividing(i)) {
            results.push_back(i);
        }
    }

    return results;
}

}//namespace


const ArrayType EXPECTED1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 15, 22};
const ArrayType EXPECTED2 = {48, 55, 66, 77};


THE_BENCHMARK(SelfDividingNumbers, 1, 22);

SIMPLE_TEST(SelfDividingNumbers, TestSAMPLE1, EXPECTED1, 1, 22);
SIMPLE_TEST(SelfDividingNumbers, TestSAMPLE2, EXPECTED2, 47, 85);

