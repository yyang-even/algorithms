#include "common_header.h"

#include "data_structure/disjoint_set.h"
#include "text/split_into_words.h"


namespace {

using ArrayType = std::vector<std::string_view>;
using PairArray = std::vector<std::pair<std::string_view, std::string_view>>;

/** Sentence Similarity
 *
 * @reference   https://zxi.mytechroad.com/blog/hashtable/leetcode-734-sentence-similarity/
 *
 * Given two sentences words1, words2 (each represented as an array of strings), and a
 * list of similar word pairs pairs, determine if two sentences are similar. For example,
 * "great acting skills" and "fine drama talent" are similar, if the similar word pairs
 * are pairs = [["great", "fine"], ["acting","drama"], ["skills","talent"]]. Note that
 * the similarity relation is not transitive. For example, if "great" and "fine" are
 * similar, and "fine" and "good" are similar, "great" and "good" are not necessarily
 * similar. However, similarity is symmetric. For example, "great" and "fine" being
 * similar is the same as "fine" and "great" being similar. Also, a word is always
 * similar with itself. For example, the sentences words1 = ["great"], words2 = ["great"],
 * pairs = [] are similar, even though there are no specified similar word pairs. Finally,
 * sentences can only be similar if they have the same number of words. So a sentence
 * like words1 = ["great"] can never be similar to words2 = ["doubleplus","good"].
 */
auto SentenceSimilarity(const ArrayType &one, const ArrayType &another,
                        const PairArray &similar_pairs) {
    if (one.size() != another.size()) {
        return false;
    }

    std::unordered_map<std::string_view, std::unordered_set<std::string_view>> hash;
    for (const auto [x, y] : similar_pairs) {
        hash[x].insert(y);
        hash[y].insert(x);
    }

    for (std::size_t i = 0; i < one.size(); ++i) {
        if (one[i] != another[i] and not hash[one[i]].count(another[i])) {
            return false;
        }
    }

    return true;
}


/**
 * @reference   Sentence Similarity II
 *              https://zxi.mytechroad.com/blog/hashtable/leetcode-737-sentence-similarity-ii/
 *
 * Given two sentences words1, words2 (each represented as an array of strings), and a
 * list of similar word pairs pairs, determine if two sentences are similar. For example,
 * words1 = ["great", "acting", "skills"] and words2 = ["fine", "drama", "talent"] are
 * similar, if the similar word pairs are pairs = [["great", "good"], ["fine", "good"],
 * ["acting","drama"], ["skills","talent"]]. Note that the similarity relation is
 * transitive. For example, if "great" and "good" are similar, and "fine" and "good" are
 * similar, then "great" and "fine" are similar. Similarity is also symmetric. For
 * example, "great" and "fine" being similar is the same as "fine" and "great" being
 * similar. Also, a word is always similar with itself. For example, the sentences
 * words1 = ["great"], words2 = ["great"], pairs = [] are similar, even though there are
 * no specified similar word pairs. Finally, sentences can only be similar if they have
 * the same number of words. So a sentence like words1 = ["great"] can never be similar
 * to words2 = ["doubleplus","good"].
 */
inline auto
emplace(std::unordered_map<std::string_view, int> &index_map,
        const std::string_view word) {
    return index_map.emplace(word, index_map.size()).first->second;
}

inline auto
getIndex(const std::unordered_map<std::string_view, int> &index_map,
         const std::string_view word) {
    const auto iter = index_map.find(word);
    return iter == index_map.cend() ? -1 : iter->second;
}

auto
SentenceSimilarityTransitive_DisjointSet(const ArrayType &one, const ArrayType &another,
                                         const PairArray &similar_pairs) {
    if (one.size() != another.size()) {
        return false;
    }

    DisjointSet_Array disjoint_set(similar_pairs.size() * 2);
    std::unordered_map<std::string_view, int> index_map;
    for (const auto [x, y] : similar_pairs) {
        const auto u = emplace(index_map, x);
        const auto v = emplace(index_map, y);
        disjoint_set.Union(u, v);
    }

    for (std::size_t i = 0; i < one.size(); ++i) {
        if (one[i] == another[i]) {
            continue;
        }

        const auto u = getIndex(index_map, one[i]);
        const auto v = getIndex(index_map, another[i]);
        if (u == -1 or v == -1 or disjoint_set.Find(u) != disjoint_set.Find(v)) {
            return false;
        }
    }

    return true;
}


/**
 * @reference   Sentence Similarity III
 *              https://leetcode.com/problems/sentence-similarity-iii/
 *
 * A sentence is a list of words that are separated by a single space with no leading or
 * trailing spaces. For example, "Hello World", "HELLO", "hello world hello world" are
 * all sentences. Words consist of only uppercase and lowercase English letters. Two
 * sentences sentence1 and sentence2 are similar if it is possible to insert an arbitrary
 * sentence (possibly empty) inside one of these sentences such that the two sentences
 * become equal. For example, sentence1 = "Hello my name is Jane" and
 * sentence2 = "Hello Jane" can be made equal by inserting "my name is" between "Hello"
 * and "Jane" in sentence2. Given two sentences sentence1 and sentence2, return true if
 * sentence1 and sentence2 are similar. Otherwise, return false.
 */
constexpr auto SplitIntoWords = SplitIntoWords_StringStream<std::deque<std::string>>;

auto
SentenceSimilarityPrefixSuffix(const std::string &one, const std::string &another) {
    auto one_q = SplitIntoWords(one);
    auto another_q = SplitIntoWords(another);

    while (not one_q.empty() and not another_q.empty() and
           one_q.front() == another_q.front()) {
        one_q.pop_front();
        another_q.pop_front();
    }

    while (not one_q.empty() and not another_q.empty() and
           one_q.back() == another_q.back()) {
        one_q.pop_back();
        another_q.pop_back();
    }

    return one_q.empty() or another_q.empty();
}

}//namespace


const ArrayType SAMPLE1L = {"great", "acting", "skills"};
const ArrayType SAMPLE1R = {"fine", "drama", "talent"};
const PairArray SAMPLE1P = {
    {"great", "fine"},
    {"drama", "acting"},
    {"skills", "talent"}
};

const ArrayType SAMPLE2 = {"great"};
const PairArray SAMPLE2P = {};

const PairArray SAMPLE4P = {
    {"great", "good"},
    {"fine", "good"},
    {"drama", "acting"},
    {"skills", "talent"}
};


THE_BENCHMARK(SentenceSimilarity, SAMPLE1L, SAMPLE1R, SAMPLE1P);

SIMPLE_TEST(SentenceSimilarity, TestSAMPLE1, true, SAMPLE1L, SAMPLE1R, SAMPLE1P);
SIMPLE_TEST(SentenceSimilarity, TestSAMPLE2, true, SAMPLE2, SAMPLE2, SAMPLE2P);
SIMPLE_TEST(SentenceSimilarity, TestSAMPLE3, false, SAMPLE1L, SAMPLE2, SAMPLE1P);


THE_BENCHMARK(SentenceSimilarityTransitive_DisjointSet, SAMPLE1L, SAMPLE1R, SAMPLE1P);

SIMPLE_TEST(SentenceSimilarityTransitive_DisjointSet, TestSAMPLE1, true,
            SAMPLE1L, SAMPLE1R, SAMPLE1P);
SIMPLE_TEST(SentenceSimilarityTransitive_DisjointSet, TestSAMPLE2, true,
            SAMPLE2, SAMPLE2, SAMPLE2P);
SIMPLE_TEST(SentenceSimilarityTransitive_DisjointSet, TestSAMPLE3, false,
            SAMPLE1L, SAMPLE2, SAMPLE1P);
SIMPLE_TEST(SentenceSimilarityTransitive_DisjointSet, TestSAMPLE4, true,
            SAMPLE1L, SAMPLE1R, SAMPLE4P);


THE_BENCHMARK(SentenceSimilarityPrefixSuffix, "My name is Haley", "My Haley");

SIMPLE_TEST(SentenceSimilarityPrefixSuffix, TestSAMPLE1, true,
            "My name is Haley", "My Haley");
SIMPLE_TEST(SentenceSimilarityPrefixSuffix, TestSAMPLE2, false, "of", "A lot of words");
SIMPLE_TEST(SentenceSimilarityPrefixSuffix, TestSAMPLE3, true,
            "Eating right now", "Eating");
SIMPLE_TEST(SentenceSimilarityPrefixSuffix, TestSAMPLE4, false, "Lucky", "Lucccky");
