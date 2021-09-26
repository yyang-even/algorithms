#include "common_header.h"


namespace {

/** Calculate the angle between hour hand and minute hand
 *
 * @reference   https://www.geeksforgeeks.org/calculate-angle-hour-hand-minute-hand/
 * @reference   Section VI. Five Algorithm Approaches.
 *              Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *
 * This problem is known as Clock angle problem where we need to find angle between
 * hands of an analog clock at a given time.
 */
inline constexpr auto
AngleBetweenHourAndMinuteHands(const double hour, const double minute) {
    assert(0 <= hour and hour <= 12);
    assert(0 <= minute and minute <= 60);

    const auto angle = std::abs(30 * hour - 5.5 * minute);
    return std::min(360 - angle, angle);
}

}//namespace


THE_BENCHMARK(AngleBetweenHourAndMinuteHands, 12, 30);

SIMPLE_DOUBLE_TEST(AngleBetweenHourAndMinuteHands, TestSAMPLE1, 165, 12, 30);
SIMPLE_DOUBLE_TEST(AngleBetweenHourAndMinuteHands, TestSAMPLE2, 75, 3, 30);
SIMPLE_DOUBLE_TEST(AngleBetweenHourAndMinuteHands, TestSAMPLE3, 60, 9, 60);
