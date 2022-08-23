#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Stamping The Sequence
 *
 * @reference   https://leetcode.com/problems/stamping-the-sequence/
 *
 * You are given two strings stamp and target. Initially, there is a string s of length target.length
 * with all s[i] == '?'.
 * In one turn, you can place stamp over s and replace every letter in the s with the corresponding
 * letter from stamp.
 *  For example, if stamp = "abc" and target = "abcba", then s is "?????" initially. In one turn you can:
 *      place stamp at index 0 of s to obtain "abc??",
 *      place stamp at index 1 of s to obtain "?abc?", or
 *      place stamp at index 2 of s to obtain "??abc".
 *  Note that stamp must be fully contained in the boundaries of s in order to stamp (i.e., you cannot
 *      place stamp at index 3 of s).
 * We want to convert s to target using at most 10 * target.length turns.
 * Return an array of the index of the left-most letter being stamped at each turn. If we cannot obtain
 * target from s within 10 * target.length turns, return an empty array.
 */
auto StampingTheSequence(const std::string &stamp, std::string target) {
    ArrayType result;

    std::size_t total_stamp = 0;
    for (std::size_t turn_stamp = -1; turn_stamp;) {
        turn_stamp = 0;
        for (int size = stamp.size(); size > 0; --size) {
            for (std::size_t i = 0; i <= stamp.size() - size; ++i) {
                const auto new_stamp = std::string(i, '?') + stamp.substr(i, size) +
                                       std::string(stamp.size() - size - i, '?');
                for (auto pos = target.find(new_stamp); pos != std::string::npos;
                     pos = target.find(new_stamp)) {
                    result.push_back(pos);
                    turn_stamp += size;
                    std::fill(begin(target) + pos, begin(target) + pos + stamp.size(), '?');
                }
            }
        }
        total_stamp += turn_stamp;
    }

    std::reverse(begin(result), end(result));
    return total_stamp == target.size() ? result : ArrayType {};
}

} //namespace


const ArrayType EXPECTED1 = {4, 2, 0, 1};
const ArrayType EXPECTED2 = {0, 2};
const ArrayType EXPECTED3 = {0, 3, 1};


THE_BENCHMARK(StampingTheSequence, "abc", "aabccbc");

SIMPLE_TEST(StampingTheSequence, TestSAMPLE1, EXPECTED1, "abc", "aabccbc");
SIMPLE_TEST(StampingTheSequence, TestSAMPLE2, EXPECTED2, "abc", "ababc");
SIMPLE_TEST(StampingTheSequence, TestSAMPLE3, EXPECTED3, "abca", "aabcaca");
