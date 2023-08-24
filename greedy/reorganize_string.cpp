#include "common_header.h"

#include "hash/hash.h"


namespace {

/** Reorganize String
 *
 * @reference   https://leetcode.com/problems/reorganize-string/
 *
 * Given a string s, rearrange the characters of s so that any two adjacent characters are not the same.
 * Return any possible rearrangement of s or return "" if not possible.
 */
std::string ReorganizeStr(const std::string_view s) {
    auto counts = ToFrequencyHashTable(s);

    auto max_iter = counts.cbegin();
    for (auto iter = counts.cbegin(); iter != counts.cend(); ++iter) {
        if (iter->second > max_iter->second) {
            max_iter = iter;
        }
    }

    const int size = s.size();
    if (max_iter->second > (size + 1) / 2) {
        return {};
    }

    std::string result(size, max_iter->first);
    std::size_t i = max_iter->second * 2;
    counts.erase(max_iter);

    for (const auto &[c, n] : counts) {
        for (int j = 0; j++ < n;) {
            if (i >= result.size()) {
                i = 1;
            }

            result[i] = c;
            i += 2;
        }
    }

    return result;
}

} //namespace


THE_BENCHMARK(ReorganizeStr, "aab");

SIMPLE_TEST(ReorganizeStr, TestSAMPLE1, "aba", "aab");
SIMPLE_TEST(ReorganizeStr, TestSAMPLE2, "", "aaab");
