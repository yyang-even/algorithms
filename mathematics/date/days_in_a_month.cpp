#include "common_header.h"


namespace {

/** Number of Days in a Month
 *
 * @reference   https://leetcode.ca/2018-12-22-1118-Number-of-Days-in-a-Month/
 *
 * Given a year Y and a month M, return how many days there are in that month.
 */
constexpr auto isLeapYear(const int year) {
    return (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0);
}

constexpr auto DaysInMonth(const int year, const int month) {
    constexpr int DAYS[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2 and isLeapYear(year)) {
        return 29;
    }

    return DAYS[month - 1];
}

}//namespace


THE_BENCHMARK(DaysInMonth, 1992, 7);

SIMPLE_TEST(DaysInMonth, TestSAMPLE1, 31, 1992, 7);
SIMPLE_TEST(DaysInMonth, TestSAMPLE2, 29, 2000, 2);
SIMPLE_TEST(DaysInMonth, TestSAMPLE3, 28, 1900, 2);
