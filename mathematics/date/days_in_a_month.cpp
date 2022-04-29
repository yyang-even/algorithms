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
constexpr auto DaysOfYear(const int year, int month, int day) {
    if (month > 2 and isLeapYear(year)) {
        ++day;
    }

    while (month-- > 1) {
        day += DAYS[month - 1];
    }

    return day;
}

inline auto DaysOfYear(const std::string_view date) {
    const auto year = from_string_view(date.substr(0, 4));
    const int month = from_string_view(date.substr(5, 2));
    const int day = from_string_view(date.substr(8));

    return DaysOfYear(year, month, day);
}


/**
 * @reference   Number of Days Between Two Dates
 *              https://leetcode.com/problems/number-of-days-between-two-dates/
 *
 * Write a program to count the number of days between two dates. The two dates are given
 * as strings, their format is YYYY-MM-DD as shown in the examples.
 * The given dates are valid dates between the years 1971 and 2100.
 */
auto DaysSince1971(const std::string_view date) {
    const auto year = from_string_view(date.substr(0, 4));
    const int month = from_string_view(date.substr(5, 2));
    const int day = from_string_view(date.substr(8));

    auto result = DaysOfYear(year, month, day);
    for (int i = 1971; i < year; ++i) {
        result += isLeapYear(i) ? 366 : 365;
    }

    return result;
}

inline auto
DaysBetween(const std::string_view one_date, const std::string_view another) {
    return std::abs(DaysSince1971(one_date) - DaysSince1971(another));
}


/**
 * @reference   Minimum Number of Operations to Convert Time
 *              https://leetcode.com/problems/minimum-number-of-operations-to-convert-time/
 *
 * You are given two strings current and correct representing two 24-hour times.
 * 24-hour times are formatted as "HH:MM", where HH is between 00 and 23, and MM is
 * between 00 and 59. The earliest 24-hour time is 00:00, and the latest is 23:59.
 * In one operation you can increase the time current by 1, 5, 15, or 60 minutes. You
 * can perform this operation any number of times.
 * Return the minimum number of operations needed to convert current to correct.
 * current <= correct
 */

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


THE_BENCHMARK(DaysBetween, "2019-06-29", "2019-06-30");

SIMPLE_TEST(DaysBetween, TestSAMPLE1, 1, "2019-06-29", "2019-06-30");
SIMPLE_TEST(DaysBetween, TestSAMPLE2, 15, "2020-01-15", "2019-12-31");
