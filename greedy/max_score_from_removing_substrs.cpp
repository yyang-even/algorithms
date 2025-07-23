#include "common_header.h"


namespace {

/**
 * @reference   Maximum Score From Removing Substrings
 *              https://leetcode.com/problems/maximum-score-from-removing-substrings/
 *
 * You are given a string s and two integers x and y. You can perform two types of operations any number
 * of times.
 *  Remove substring "ab" and gain x points.
 *      For example, when removing "ab" from "cabxbae" it becomes "cxbae".
 *  Remove substring "ba" and gain y points.
 *      For example, when removing "ba" from "cabxbae" it becomes "cabxe".
 * Return the maximum points you can gain after applying the above operations on s.
 *
 * @tags    #greedy #2-way-partition
 */
int MaxScoreFromRemovingTheSubstrs(std::string &s,
                                   const std::string_view target,
                                   const int score) {
    const int original_size = s.size();

    int write_index = 0;
    for (const auto c : s) {
        if (write_index > 0 and s[write_index - 1] == target.front() and c == target.back()) {
            --write_index;
        } else {
            s[write_index++] = c;
        }
    }

    s.erase(s.cbegin() + write_index, s.cend());

    return (original_size - s.size()) / 2 * score;
}

auto MaxScoreFromRemovingSubstrs(std::string s, const int x, const int y) {
    int result = 0;

    if (x >= y) {
        result += MaxScoreFromRemovingTheSubstrs(s, "ab", x);
        result += MaxScoreFromRemovingTheSubstrs(s, "ba", y);
    } else {
        result += MaxScoreFromRemovingTheSubstrs(s, "ba", y);
        result += MaxScoreFromRemovingTheSubstrs(s, "ab", x);
    }

    return result;
}

} //namespace


THE_BENCHMARK(MaxScoreFromRemovingSubstrs, "cdbcbbaaabab", 4, 5);

SIMPLE_TEST(MaxScoreFromRemovingSubstrs, TestSAMPLE1, 19, "cdbcbbaaabab", 4, 5);
SIMPLE_TEST(MaxScoreFromRemovingSubstrs, TestSAMPLE2, 20, "aabbaaxybbaabb", 5, 4);
