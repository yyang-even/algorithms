#include "common_header.h"


namespace {

using Message = std::pair<int, std::string_view>;
using ArrayType = std::vector<Message>;

/** Logger Rate Limiter
 *
 * @reference   https://tenderleo.gitbooks.io/leetcode-solutions-/content/GoogleEasy/359.html
 *
 * Design a logger system that receive stream of messages along with its timestamps,
 * each message should be printed if and only if it is not printed in the last 10
 * seconds. Given a message and a timestamp (in seconds granularity), return true if the
 * message should be printed in the given timestamp, otherwise returns false. It is
 * possible that several messages arrive roughly at the same time.
 */
auto LoggerRateLimiter_Map(const ArrayType &messages, const int limit = 10) {
    std::unordered_map<std::string_view, int> last_occurrences;

    std::vector<bool> results;
    for (const auto [timestamp, a_message] : messages) {
        const auto [iter, inserted] = last_occurrences.emplace(a_message, timestamp);
        if (not inserted) {
            if (timestamp - iter->second < limit) {
                results.push_back(false);
                continue;
            } else {
                iter->second = timestamp;
            }
        }

        results.push_back(true);
    }

    return results;
}


auto LoggerRateLimiter_Queue(const ArrayType &messages, const int limit = 10) {
    std::queue<Message> message_queue;
    std::unordered_set<std::string_view> messages_in_queue;

    std::vector<bool> results;
    for (const auto [timestamp, a_message] : messages) {
        while (not message_queue.empty() and message_queue.front().first <= timestamp - limit) {
            messages_in_queue.erase(message_queue.front().second);
            message_queue.pop();
        }

        results.push_back(messages_in_queue.insert(a_message).second);
        if (results.back()) {
            message_queue.emplace(timestamp, a_message);
        }
    }

    return results;
}


/**
 * @reference   Number of Recent Calls
 *              https://leetcode.com/problems/number-of-recent-calls/
 *
 * You have a RecentCounter class which counts the number of recent requests within a
 * certain time frame. Implement the RecentCounter class:
 *  RecentCounter() Initializes the counter with zero recent requests.
 *  int ping(int t) Adds a new request at time t, where t represents some time in
 *      milliseconds, and returns the number of requests that has happened in the past
 *      3000 milliseconds (including the new request). Specifically, return the number
 *      of requests that have happened in the inclusive range [t - 3000, t].
 * It is guaranteed that every call to ping uses a strictly larger value of t than the
 * previous call.
 */


/**
 * @reference   Design Underground System
 *              https://leetcode.com/problems/design-underground-system/
 *
 * An underground railway system is keeping track of customer travel times between
 * different stations. They are using this data to calculate the average time it takes
 * to travel from one station to another.
 * Implement the UndergroundSystem class:
 *  void checkIn(int id, string stationName, int t)
 *      A customer with a card ID equal to id, checks in at the station stationName at
 *          time t.
 *      A customer can only be checked into one place at a time.
 *  void checkOut(int id, string stationName, int t)
 *      A customer with a card ID equal to id, checks out from the station stationName
 *          at time t.
 *  double getAverageTime(string startStation, string endStation)
 *      Returns the average time it takes to travel from startStation to endStation.
 *      The average time is computed from all the previous traveling times from
 *          startStation to endStation that happened directly, meaning a check in at
 *          startStation followed by a check out from endStation.
 *      The time it takes to travel from startStation to endStation may be different
 *          from the time it takes to travel from endStation to startStation.
 *      There will be at least one customer that has traveled from startStation to
 *          endStation before getAverageTime is called.
 * You may assume all calls to the checkIn and checkOut methods are consistent. If a
 * customer checks in at time t1 then checks out at time t2, then t1 < t2. All events
 * happen in chronological order.
 */

}//namespace


const ArrayType SAMPLE1 = {{1, "foo"}, {2, "bar"}, {3, "foo"}, {8, "bar"}, {10, "foo"}, {11, "foo"}};
const std::vector EXPECTED1 = {true, true, false, false, false, true};


THE_BENCHMARK(LoggerRateLimiter_Map, SAMPLE1);

SIMPLE_TEST(LoggerRateLimiter_Map, TestSAMPLE1, EXPECTED1, SAMPLE1);


THE_BENCHMARK(LoggerRateLimiter_Queue, SAMPLE1);

SIMPLE_TEST(LoggerRateLimiter_Queue, TestSAMPLE1, EXPECTED1, SAMPLE1);
