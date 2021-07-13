#include "common_header.h"


namespace {

/** Isomorphic Strings
 *
 * @reference   https://leetcode.com/problems/isomorphic-strings/
 *
 * Given two strings s and t, determine if they are isomorphic. Two strings s and t are
 * isomorphic if the characters in s can be replaced to get t. All occurrences of a
 * character must be replaced with another character while preserving the order of
 * characters. No two characters may map to the same character, but a character may map
 * to itself.
 */
constexpr auto
areIsomorphicStrings_Hash(const std::string_view s, const std::string_view t) {
    assert(s.size() == t.size());

    char map_from[256] = {};
    char map_to[256] = {};

    for (std::size_t i = 0; i < s.size(); ++i) {
        const int from = s[i];
        const int to = t[i];

        if (not map_from[from] and not map_to[to]) {
            map_from[from] = to;
            map_to[to] = from;
        } else if (map_from[from] != to or map_to[to] != from) {
            return false;
        }
    }

    return true;
}


auto transform(const std::string_view text) {
    std::unordered_map<char, std::size_t> first_occurences;

    std::vector<std::size_t> result;
    for (std::size_t i = 0; i < text.size(); ++i) {
        const auto c = text[i];
        first_occurences.emplace(c, i);
        result.push_back(first_occurences[c]);
    }

    return result;
}

auto areIsomorphicStrings_Transform(const std::string_view s,
                                    const std::string_view t) {
    return transform(s) == transform(t);
}

}//namespace


THE_BENCHMARK(areIsomorphicStrings_Hash, "paper", "title");

SIMPLE_TEST(areIsomorphicStrings_Hash, TestSAMPLE1, true, "egg", "add");
SIMPLE_TEST(areIsomorphicStrings_Hash, TestSAMPLE2, false, "foo", "bar");
SIMPLE_TEST(areIsomorphicStrings_Hash, TestSAMPLE3, true, "paper", "title");
SIMPLE_TEST(areIsomorphicStrings_Hash, TestSAMPLE4, false, "badc", "baba");


THE_BENCHMARK(areIsomorphicStrings_Transform, "paper", "title");

SIMPLE_TEST(areIsomorphicStrings_Transform, TestSAMPLE1, true, "egg", "add");
SIMPLE_TEST(areIsomorphicStrings_Transform, TestSAMPLE2, false, "foo", "bar");
SIMPLE_TEST(areIsomorphicStrings_Transform, TestSAMPLE3, true, "paper", "title");
SIMPLE_TEST(areIsomorphicStrings_Transform, TestSAMPLE4, false, "badc", "baba");
