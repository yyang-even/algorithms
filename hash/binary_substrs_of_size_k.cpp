#include "common_header.h"


namespace {

/** Check If a String Contains All Binary Codes of Size K
 *
 * @reference   https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/
 *
 * Given a binary string s and an integer k, return true if every binary code of length k is a
 * substring of s. Otherwise, return false.
 * 1 <= k <= 20
 */
auto BinarySubstrsOfSizeK(const std::string_view s, const std::size_t K) {
    if (K >= s.size())
        return false;

    unsigned mask = 0;
    for (std::size_t i = 0; i < K; ++i) {
        mask |= (s[i] - '0') << i;
    }

    std::unordered_set<unsigned> substrs;
    substrs.insert(mask);

    for (std::size_t i = K; i < s.size(); ++i) {
        mask >>= 1;
        mask |= (s[i] - '0') << (K - 1);
        substrs.insert(mask);
    }

    return substrs.size() == (1u << K);
}

} //namespace


THE_BENCHMARK(BinarySubstrsOfSizeK, "00110110", 2);

SIMPLE_TEST(BinarySubstrsOfSizeK, TestSAMPLE1, true, "00110110", 2);
SIMPLE_TEST(BinarySubstrsOfSizeK, TestSAMPLE2, true, "0110", 1);
SIMPLE_TEST(BinarySubstrsOfSizeK, TestSAMPLE3, false, "0110", 2);
SIMPLE_TEST(BinarySubstrsOfSizeK, TestSAMPLE4, false, "0", 20);
