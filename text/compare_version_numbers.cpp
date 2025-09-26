#include "common_header.h"


namespace {

/**
 * @reference   Compare Version Numbers
 *              https://leetcode.com/problems/compare-version-numbers/
 *
 * Given two version strings, version1 and version2, compare them. A version string consists of
 * revisions separated by dots '.'. The value of the revision is its integer conversion ignoring leading
 * zeros.
 * To compare version strings, compare their revision values in left-to-right order. If one of the
 * version strings has fewer revisions, treat the missing revision values as 0.
 * Return the following:
 *  If version1 < version2, return -1.
 *  If version1 > version2, return 1.
 *  Otherwise, return 0.
 *
 * @tags    #tokenizing #numeric-string
 */
constexpr auto CompareVersions(const std::string_view version1, const std::string_view version2) {
    for (std::size_t i_one = 0, i_another = 0;
         i_one < version1.size() or i_another < version2.size();
         ++i_one, ++i_another) {
        int one_number = 0;
        while (i_one < version1.size() and version1[i_one] != '.') {
            one_number = one_number * 10 + (version1[i_one++] - '0');
        }

        int another_number = 0;
        while (i_another < version2.size() and version2[i_another] != '.') {
            another_number = another_number * 10 + (version2[i_another++] - '0');
        }

        if (one_number > another_number) {
            return 1;
        } else if (one_number < another_number) {
            return -1;
        }
    }

    return 0;
}

} //namespace


THE_BENCHMARK(CompareVersions, "1.01", "1.001");

SIMPLE_TEST(CompareVersions, TestSAMPLE1, 0, "1.01", "1.001");
SIMPLE_TEST(CompareVersions, TestSAMPLE2, 0, "1.0", "1.0.0");
SIMPLE_TEST(CompareVersions, TestSAMPLE3, -1, "0.1", "1.1");
SIMPLE_TEST(CompareVersions, TestSAMPLE4, 1, "1.1", "1.0");
