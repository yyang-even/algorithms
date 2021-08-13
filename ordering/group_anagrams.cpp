#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string_view>;
using ResultType =
    std::unordered_map<std::string, std::unordered_multiset<std::string_view>>;

/** Given a sequence of words, print all anagrams together | Set 1
 *
 * @reference   https://www.geeksforgeeks.org/given-a-sequence-of-words-print-all-anagrams-together/
 * @reference   Given a sequence of words, print all anagrams together | Set 2
 *              https://www.geeksforgeeks.org/given-a-sequence-of-words-print-all-anagrams-together-set-2/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 11.2.
 */
auto GroupAnagrams_Sort(const ArrayType &words) {
    std::vector<std::pair<std::string, std::size_t>> sorted_words;
    for (std::size_t i = 0; i < words.size(); ++i) {
        std::string a_word{words[i]};
        std::sort(a_word.begin(), a_word.end());
        sorted_words.emplace_back(std::move(a_word), i);
    }

    std::sort(sorted_words.begin(), sorted_words.end(),
    [](const auto & lhs, const auto & rhs) {
        return lhs.first < rhs.first;
    });

    ResultType results;
    for (const auto &[key, index] : sorted_words) {
        results[key].insert(words[index]);
    }

    return results;
}


/**
 * @reference   Given a sequence of words, print all anagrams together using STL
 *              https://www.geeksforgeeks.org/given-a-sequence-of-words-print-all-anagrams-together-using-stl/
 *
 * @reference   Group Anagrams
 *              https://leetcode.com/problems/group-anagrams/
 *
 * Given an array of strings strs, group the anagrams together. You can return the answer
 * in any order. An Anagram is a word or phrase formed by rearranging the letters of a
 * different word or phrase, typically using all the original letters exactly once.
 */
auto GroupAnagrams_Hash(const ArrayType &words) {
    ResultType buckets;

    for (const auto &original_word : words) {
        std::string sorted_word{original_word};
        std::sort(sorted_word.begin(), sorted_word.end());
        buckets[sorted_word].insert(original_word);
    }

    return buckets;
}

}//namespace


const ArrayType SAMPLE1 = {"cat", "dog", "tac", "god", "act"};
const ResultType EXPECTED1 = {{"act", {"cat", "tac", "act"}}, {"dgo", {"dog", "god"}}};

const ArrayType SAMPLE2 = {"cat", "dog", "tac", "god", "act", "gdo"};
const ResultType EXPECTED2 = {{"act", {"cat", "tac", "act"}}, {"dgo", {"dog", "god", "gdo"}}};

const ArrayType SAMPLE3 = {"abc", "def", "ghi"};
const ResultType EXPECTED3 = {{"abc", {"abc"}}, {"def", {"def"}}, {"ghi", {"ghi"}}};


THE_BENCHMARK(GroupAnagrams_Sort, SAMPLE1);

SIMPLE_TEST(GroupAnagrams_Sort, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(GroupAnagrams_Sort, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(GroupAnagrams_Sort, TestSAMPLE3, EXPECTED3, SAMPLE3);


THE_BENCHMARK(GroupAnagrams_Hash, SAMPLE1);

SIMPLE_TEST(GroupAnagrams_Hash, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(GroupAnagrams_Hash, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(GroupAnagrams_Hash, TestSAMPLE3, EXPECTED3, SAMPLE3);
