#include "common_header.h"


namespace {

/** Day of the Week
 *
 * @reference   https://leetcode.com/problems/day-of-the-week/
 *
 * Given a date, return the corresponding day of the week for that date. The input is
 * given as three integers representing the day, month and year respectively. Return
 * the answer as one of the following values {"Sunday", "Monday", "Tuesday", "Wednesday",
 * "Thursday", "Friday", "Saturday"}.
 * The given dates are valid dates between the years 1971 and 2100.
 */
constexpr std::string_view days_in_week[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

constexpr auto DayOfWeek_Zeller(const int day, int month, int year) {
    if (month < 3) {
        month += 12;
        year -= 1;
    }

    const auto century = year / 100;
    year %= 100;

    const auto week =
        (century / 4 - 2 * century + year + year / 4 + 13 * (month + 1) / 5 + day - 1) % 7;
    return days_in_week[(week + 7) % 7];
}


constexpr auto DayOfWeek_Sakamoto(const int day, const int month, int year) {
    constexpr int days_by_month_mod7[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};

    if (month < 3) {
        year -= 1;
    }

    const auto week =
        (year + (year / 4 - year / 100 + year / 400) + days_by_month_mod7[month - 1] + day) % 7;
    return days_in_week[week];
}

}//namespace


THE_BENCHMARK(DayOfWeek_Zeller, 31, 8, 2019);

SIMPLE_TEST(DayOfWeek_Zeller, TestSAMPLE1, "Saturday", 31, 8, 2019);
SIMPLE_TEST(DayOfWeek_Zeller, TestSAMPLE2, "Sunday", 18, 7, 1999);
SIMPLE_TEST(DayOfWeek_Zeller, TestSAMPLE3, "Sunday", 15, 8, 1993);


THE_BENCHMARK(DayOfWeek_Sakamoto, 31, 8, 2019);

SIMPLE_TEST(DayOfWeek_Sakamoto, TestSAMPLE1, "Saturday", 31, 8, 2019);
SIMPLE_TEST(DayOfWeek_Sakamoto, TestSAMPLE2, "Sunday", 18, 7, 1999);
SIMPLE_TEST(DayOfWeek_Sakamoto, TestSAMPLE3, "Sunday", 15, 8, 1993);
