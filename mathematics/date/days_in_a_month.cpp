#include "common_header.h"

#include "text/number_convertion.h"


namespace {

/** Number of Days in a Month
 *
 * @reference   https://leetcode.ca/2018-12-22-1118-Number-of-Days-in-a-Month/
 *
 * Given a year Y and a month M, return how many days there are in that month.
 */
inline constexpr auto
isLeapYear(const int year) {
    return (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0);
}

constexpr int DAYS[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

constexpr auto DaysInMonth(const int year, const int month) {
    if (month == 2 and isLeapYear(year)) {
        return 29;
    }

    return DAYS[month - 1];
}


/**
 * @reference   Day of the Year
 *              https://leetcode.com/problems/day-of-the-year/
 *
 * Given a string date representing a Gregorian calendar date formatted as YYYY-MM-DD,
 * return the day number of the year.
 */
auto DaysOfYear(const std::string_view date) {
    const auto year = from_string_view(date.substr(0, 4));
    int month = from_string_view(date.substr(5, 2));
    int day = from_string_view(date.substr(8));

    if (month > 2 and isLeapYear(year)) {
        ++day;
    }

    while (month-- > 1) {
        day += DAYS[month - 1];
    }

    return day;
}

}//namespace


THE_BENCHMARK(DaysInMonth, 1992, 7);

SIMPLE_TEST(DaysInMonth, TestSAMPLE1, 31, 1992, 7);
SIMPLE_TEST(DaysInMonth, TestSAMPLE2, 29, 2000, 2);
SIMPLE_TEST(DaysInMonth, TestSAMPLE3, 28, 1900, 2);


THE_BENCHMARK(DaysOfYear, "2019-01-09");

SIMPLE_TEST(DaysOfYear, TestSAMPLE1, 9, "2019-01-09");
SIMPLE_TEST(DaysOfYear, TestSAMPLE2, 41, "2019-02-10");
SIMPLE_TEST(DaysOfYear, TestSAMPLE3, 60, "2003-03-01");
SIMPLE_TEST(DaysOfYear, TestSAMPLE4, 61, "2004-03-01");
