#include "common_header.h"


namespace {

/** Broken Calculator
 *
 * @reference   https://leetcode.com/problems/broken-calculator/
 *
 * There is a broken calculator that has the integer startValue on its display initially.
 * In one operation, you can:
 *  multiply the number on display by 2, or
 *  subtract 1 from the number on display.
 * Given two integers startValue and target, return the minimum number of operations needed
 * to display target on the calculator.
 */
constexpr auto BrokenCalculator(const int start, int target) {
    int result = 0;
    while (target > start) {
        ++result;
        if (target % 2 == 1) {
            ++target;
        } else {
            target /= 2;
        }
    }

    return result + start - target;
}

}//namespace


THE_BENCHMARK(BrokenCalculator, 2, 3);

SIMPLE_TEST(BrokenCalculator, TestSAMPLE1, 2, 2, 3);
SIMPLE_TEST(BrokenCalculator, TestSAMPLE2, 2, 5, 8);
SIMPLE_TEST(BrokenCalculator, TestSAMPLE3, 3, 3, 10);
