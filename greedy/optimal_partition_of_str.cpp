#include "common_header.h"


namespace {

/** Optimal Partition of String
 *
 * @reference   https://leetcode.com/problems/optimal-partition-of-string/
 *
 * Given a string s, partition the string into one or more substrings such that the characters in each
 * substring are unique. That is, no letter appears in a single substring more than once.
 * Return the minimum number of substrings in such a partition.
 * Note that each character should belong to exactly one substring in a partition.
 */
auto OptimalPartitionOfStr(const std::string_view s) {
    std::vector<int> last_seen(26, -1);
    int result = 1;
    int start = 0;

    for (std::size_t i = 0; i < s.size(); ++i) {
        const int index = s[i] - 'a';
        if (last_seen[index] >= start) {
            ++result;
            start = i;
        }
        last_seen[index] = i;
    }

    return result;
}

} //namespace


THE_BENCHMARK(OptimalPartitionOfStr, "abacaba");

SIMPLE_TEST(OptimalPartitionOfStr, TestSAMPLE1, 4, "abacaba");
SIMPLE_TEST(OptimalPartitionOfStr, TestSAMPLE2, 6, "ssssss");
