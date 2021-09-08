#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** DI String Match
 *
 * @reference   https://leetcode.com/problems/di-string-match/
 *
 * A permutation perm of n + 1 integers of all the integers in the range [0, n] can be
 * represented as a string s of length n where:
 *  s[i] == 'I' if perm[i] < perm[i + 1], and
 *  s[i] == 'D' if perm[i] > perm[i + 1].
 * Given a string s, reconstruct the permutation perm and return it. If there are
 * multiple valid permutations perm, return any of them.
 */
auto DIStrMatch(const std::string_view s) {
    int high = s.size();
    int low = 0;

    ArrayType result;
    for (const auto c : s) {
        if (c == 'I') {
            result.push_back(low++);
        } else {
            result.push_back(high--);
        }
    }

    result.push_back(low);
    return result;
}

}//namespace


const ArrayType EXPECTED1 = {0, 4, 1, 3, 2};
const ArrayType EXPECTED2 = {0, 1, 2, 3};
const ArrayType EXPECTED3 = {3, 2, 0, 1};


THE_BENCHMARK(DIStrMatch, "IDID");

SIMPLE_TEST(DIStrMatch, TestSAMPLE1, EXPECTED1, "IDID");
SIMPLE_TEST(DIStrMatch, TestSAMPLE2, EXPECTED2, "III");
SIMPLE_TEST(DIStrMatch, TestSAMPLE3, EXPECTED3, "DDI");
