#include "common_header.h"


namespace {

/** Compare Version Numbers
 *
 * @reference   https://leetcode.com/problems/compare-version-numbers/
 *
 * Given two version numbers, version1 and version2, compare them.
 * Version numbers consist of one or more revisions joined by a dot '.'. Each revision
 * consists of digits and may contain leading zeros. Every revision contains at least one
 * character. Revisions are 0-indexed from left to right, with the leftmost revision being
 * revision 0, the next revision being revision 1, and so on. For example 2.5.33 and 0.1
 * are valid version numbers.
 * To compare version numbers, compare their revisions in left-to-right order. Revisions
 * are compared using their integer value ignoring any leading zeros. This means that
 * revisions 1 and 001 are considered equal. If a version number does not specify a
 * revision at an index, then treat the revision as 0. For example, version 1.0 is less
 * than version 1.1 because their revision 0s are the same, but their revision 1s are 0
 * and 1 respectively, and 0 < 1.
 * Return the following:
 *  If version1 < version2, return -1.
 *  If version1 > version2, return 1.
 *  Otherwise, return 0.
 */
constexpr auto
CompareVersions(const std::string_view version1, const std::string_view version2) {
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

}//namespace


THE_BENCHMARK(CompareVersions, "1.01", "1.001");

SIMPLE_TEST(CompareVersions, TestSAMPLE1, 0, "1.01", "1.001");
SIMPLE_TEST(CompareVersions, TestSAMPLE2, 0, "1.0", "1.0.0");
SIMPLE_TEST(CompareVersions, TestSAMPLE3, -1, "0.1", "1.1");
SIMPLE_TEST(CompareVersions, TestSAMPLE4, 1, "1.1", "1.0");
