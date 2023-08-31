#include "common_header.h"


namespace {

using namespace std::string_literals;

/** Time Based Key-Value Store
 *
 * @reference   https://leetcode.com/problems/time-based-key-value-store/
 *
 * Design a time-based key-value data structure that can store multiple values for the same key at
 * different time stamps and retrieve the key's value at a certain timestamp.
 * Implement the TimeMap class:
 *  TimeMap() Initializes the object of the data structure.
 *  void set(String key, String value, int timestamp) Stores the key key with the value value at the
 *      given time timestamp.
 *  String get(String key, int timestamp) Returns a value such that set was called previously, with
 *      timestamp_prev <= timestamp. If there are multiple such values, it returns the value associated
 *      with the largest timestamp_prev. If there are no values, it returns "".
 * All the timestamps timestamp of set are strictly increasing.
 */
class TimeMap {
    std::unordered_map<std::string, std::map<int, std::string>> m;

public:
    void set(const std::string &key, const std::string &value, const int timestamp) {
        m[key][timestamp] = value;
    }

    auto get(const std::string &key, const int timestamp) const {
        const auto outer = m.find(key);
        if (outer == m.cend()) {
            return ""s;
        }

        const auto inner = outer->second.upper_bound(timestamp);
        if (inner == outer->second.cbegin()) {
            return ""s;
        }
        return std::prev(inner)->second;
    }
};


class TimeMap_Array {
    std::unordered_map<std::string, std::vector<std::pair<int, std::string>>> m;

public:
    void set(const std::string &key, const std::string &value, const int timestamp) {
        m[key].emplace_back(timestamp, value);
    }

    auto get(const std::string &key, const int timestamp) const {
        const auto outer = m.find(key);
        if (outer == m.cend()) {
            return ""s;
        }

        const auto inner =
            upper_bound(outer->second.cbegin(), outer->second.cend(), std::pair(timestamp, ""s));
        if (inner == outer->second.cbegin()) {
            return ""s;
        }
        return std::prev(inner)->second;
    }
};


/**
 * @reference   Design Twitter
 *              https://leetcode.com/problems/design-twitter/
 *
 * Design a simplified version of Twitter where users can post tweets, follow/unfollow another user, and
 * is able to see the 10 most recent tweets in the user's news feed.
 * Implement the Twitter class:
 *  Twitter() Initializes your twitter object.
 *  void postTweet(int userId, int tweetId) Composes a new tweet with ID tweetId by the user userId.
 *      Each call to this function will be made with a unique tweetId.
 *  List<Integer> getNewsFeed(int userId) Retrieves the 10 most recent tweet IDs in the user's news
 *      feed. Each item in the news feed must be posted by users who the user followed or by the user
 *      themself. Tweets must be ordered from most recent to least recent.
 *  void follow(int followerId, int followeeId) The user with ID followerId started following the user
 *      with ID followeeId.
 *  void unfollow(int followerId, int followeeId) The user with ID followerId started unfollowing the
 *      user with ID followeeId.
 */

} //namespace


#ifdef WANT_TESTS
#define TimeMapTest(MapType)                \
    namespace {                             \
    TEST(Time_MapTest, test##MapType) {     \
        TimeMap m;                          \
                                            \
        m.set("foo", "bar", 1);             \
        EXPECT_EQ("bar", m.get("foo", 1));  \
        EXPECT_EQ("bar", m.get("foo", 3));  \
                                            \
        m.set("foo", "bar2", 4);            \
        EXPECT_EQ("bar", m.get("foo", 1));  \
        EXPECT_EQ("bar", m.get("foo", 3));  \
        EXPECT_EQ("bar2", m.get("foo", 4)); \
        EXPECT_EQ("bar2", m.get("foo", 5)); \
        EXPECT_EQ("", m.get("foo", 0));     \
    }                                       \
    }

TimeMapTest(TimeMap);
TimeMapTest(TimeMap_Array);
#endif
