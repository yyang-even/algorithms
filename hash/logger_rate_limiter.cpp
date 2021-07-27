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

}//namespace


const ArrayType SAMPLE1 = {{1, "foo"}, {2, "bar"}, {3, "foo"}, {8, "bar"}, {10, "foo"}, {11, "foo"}};
const std::vector EXPECTED1 = {true, true, false, false, false, true};


THE_BENCHMARK(LoggerRateLimiter_Map, SAMPLE1);

SIMPLE_TEST(LoggerRateLimiter_Map, TestSAMPLE1, EXPECTED1, SAMPLE1);


THE_BENCHMARK(LoggerRateLimiter_Queue, SAMPLE1);

SIMPLE_TEST(LoggerRateLimiter_Queue, TestSAMPLE1, EXPECTED1, SAMPLE1);
