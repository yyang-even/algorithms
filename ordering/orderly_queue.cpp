#include "common_header.h"


namespace {

/** Orderly Queue
 *
 * @reference   https://leetcode.com/problems/orderly-queue/
 *
 * You are given a string s and an integer k. You can choose one of the first k letters
 * of s and append it at the end of the string. Return the lexicographically smallest
 * string you could have after applying the mentioned step any number of moves.
 */
auto OrderlyQueue(std::string s, const int k) {
    if (k == 1) {
        auto temp = s;
        for (std::size_t i = 1; i < s.length(); ++i) {
            std::rotate(temp.begin(), temp.begin() + 1, temp.end());
            if (temp < s) {
                s = temp;
            }
        }
    } else {
        std::sort(s.begin(), s.end());
    }

    return s;
}

}//namespace


THE_BENCHMARK(OrderlyQueue, "cba", 1);

SIMPLE_TEST(OrderlyQueue, TestSAMPLE1, "acb", "cba", 1);
SIMPLE_TEST(OrderlyQueue, TestSAMPLE2, "aaabc", "baaca", 3);
