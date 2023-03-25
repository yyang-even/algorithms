#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Capacity To Ship Packages Within D Days
 *
 * @reference   https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/
 *
 * A conveyor belt has packages that must be shipped from one port to another within days days.
 * The ith package on the conveyor belt has a weight of weights[i]. Each day, we load the ship with
 * packages on the conveyor belt (in the order given by weights). We may not load more weight than the
 * maximum weight capacity of the ship.
 * Return the least weight capacity of the ship that will result in all the packages on the conveyor
 * belt being shipped within days days.
 */
auto ShipWithinDays(const ArrayType &weights, const int days) {
    int left = 0;
    int right = 0;
    for (const auto w : weights) {
        left = std::max(left, w);
        right += w;
    }

    while (left < right) {
        const auto mid = (left + right) / 2;
        int need = 1;
        int curr_weight = 0;
        for (std::size_t i = 0; i < weights.size() and need <= days;
             curr_weight += weights[i++]) {
            if (curr_weight + weights[i] > mid) {
                curr_weight = 0;
                ++need;
            }
        }

        if (need > days) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left;
}


/**
 * @reference   Minimum Time to Complete Trips
 *              https://leetcode.com/problems/minimum-time-to-complete-trips/
 *
 * You are given an array time where time[i] denotes the time taken by the ith bus to complete one trip.
 * Each bus can make multiple trips successively; that is, the next trip can start immediately after
 * completing the current trip. Also, each bus operates independently; that is, the trips of one bus do
 * not influence the trips of any other bus.
 * You are also given an integer totalTrips, which denotes the number of trips all buses should make in
 * total. Return the minimum time required for all buses to complete at least totalTrips trips.
 */
auto countTrip(const ArrayType &time, const long long given_time) {
    long long actual_trips = 0;
    for (const auto t : time) {
        actual_trips += given_time / t;
    }

    return actual_trips;
}

auto MinTimeToCompleteTrips(const ArrayType &time, const int total_trips) {
    long long left = 1;
    const long long maximum = *(std::max_element(time.cbegin(), time.cend()));
    auto right = maximum * total_trips;

    while (left < right) {
        const auto mid = (left + right) / 2;
        const auto actual_trips = countTrip(time, mid);
        if (actual_trips >= total_trips) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return left;
}

} //namespace


const ArrayType SAMPLE1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const ArrayType SAMPLE2 = {3, 2, 2, 4, 1, 4};
const ArrayType SAMPLE3 = {1, 2, 3, 1, 1};


THE_BENCHMARK(ShipWithinDays, SAMPLE1, 5);

SIMPLE_TEST(ShipWithinDays, TestSAMPLE1, 15, SAMPLE1, 5);
SIMPLE_TEST(ShipWithinDays, TestSAMPLE2, 6, SAMPLE2, 3);
SIMPLE_TEST(ShipWithinDays, TestSAMPLE3, 3, SAMPLE3, 4);


const ArrayType SAMPLE1T = {1, 2, 3};
const ArrayType SAMPLE2T = {2};


THE_BENCHMARK(MinTimeToCompleteTrips, SAMPLE1T, 5);

SIMPLE_TEST(MinTimeToCompleteTrips, TestSAMPLE1, 3, SAMPLE1T, 5);
SIMPLE_TEST(MinTimeToCompleteTrips, TestSAMPLE2, 2, SAMPLE2T, 1);
