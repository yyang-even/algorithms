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

inline auto
areIsomorphicStrings_Transform(const std::string_view s,
                               const std::string_view t) {
    return transform(s) == transform(t);
}


/**
 * @reference   Word Pattern
 *              https://leetcode.com/problems/word-pattern/
 *
 * Given a pattern and a string s, find if s follows the same pattern. Here follow means
 * a full match, such that there is a bijection between a letter in pattern and a
 * non-empty word in s.
 */


/**
 * @reference   Word Pattern II
 *              https://kennyzhuang.gitbooks.io/leetcode-lock/content/291_word_pattern_ii.html
 *
 * Given a pattern and a string str, find if str follows the same pattern. Here follow
 * means a full match, such that there is a bijection between a letter in pattern and a
 * non-empty substring in str.
 */
bool WordPattern(const std::string_view pattern, const std::size_t p_begin,
                 const std::string_view str, const std::size_t s_begin,
                 std::unordered_map<char, std::string_view> &to_word,
                 std::unordered_set<std::string_view> &seen_words) {
    if (p_begin == pattern.size() and s_begin == str.size()) {
        return true;
    }
    if (p_begin == pattern.size() or s_begin == str.size()) {
        return false;
    }

    const char c = pattern[p_begin];
    for (auto i = s_begin; i < str.size(); ++i) {
        const auto a_word = str.substr(s_begin, i - s_begin + 1);

        const auto iter = to_word.find(c);
        if (iter != to_word.cend()) {
            if ((iter->second == a_word) and
                (WordPattern(pattern, p_begin + 1, str, i + 1, to_word, seen_words))) {
                return true;
            }
        } else {
            const auto [_, inserted] = seen_words.insert(a_word);
            if (inserted) {
                to_word.emplace(c, a_word);
                if (WordPattern(pattern, p_begin + 1, str, i + 1, to_word, seen_words)) {
                    return true;
                }
                to_word.erase(c);
                seen_words.erase(a_word);
            }
        }
    }
    return false;
}

inline auto
WordPattern(const std::string_view pattern, const std::string_view str) {
    std::unordered_map<char, std::string_view> to_word;
    std::unordered_set<std::string_view> seen_words;
    return WordPattern(pattern, 0, str, 0, to_word, seen_words);
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


THE_BENCHMARK(WordPattern, "abab", "redblueredblue");

SIMPLE_TEST(WordPattern, TestSAMPLE1, true, "egg", "add");
SIMPLE_TEST(WordPattern, TestSAMPLE2, false, "foo", "bar");
SIMPLE_TEST(WordPattern, TestSAMPLE3, true, "paper", "title");
SIMPLE_TEST(WordPattern, TestSAMPLE4, false, "badc", "baba");
SIMPLE_TEST(WordPattern, TestSAMPLE5, true, "abab", "redblueredblue");
SIMPLE_TEST(WordPattern, TestSAMPLE6, true, "aaaa", "asdasdasdasd");
SIMPLE_TEST(WordPattern, TestSAMPLE7, false, "aabb", "xyzabcxzyabc");
