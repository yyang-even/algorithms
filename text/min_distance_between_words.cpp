#include "common_header.h"

#include "ordering/min_diff_pair_between_2_arrays.h"


namespace {

using ArrayType = std::vector<std::string_view>;

/**
 * @reference   Shortest Word Distance
 *              https://tenderleo.gitbooks.io/leetcode-solutions-/content/GoogleEasy/243.html
 *
 * Given a list of words and two words word1 and word2, return the shortest distance
 * between these two words in the list.
 * Note: You may assume that word1 does not equal to word2, and word1 and word2 are both
 * in the list.
 */
auto MinDistanceBetweenWords(const ArrayType &words,
                             const std::string_view one_word,
                             const std::string_view another) {
    assert(one_word != another);

    int last_one = -1;
    int last_another = -1;
    int min_distance = words.size();
    for (std::size_t i = 0; i < words.size(); ++i) {
        bool meet = false;
        if (words[i] == one_word) {
            meet = true;
            last_one = i;
        } else if (words[i] == another) {
            meet = true;
            last_another = i;
        }

        if (meet and last_one != -1 and last_another != -1) {
            const auto distance = std::abs(last_one - last_another);
            if (distance < min_distance) {
                min_distance = distance;
            }
        }
    }

    return min_distance;
}


/** Minimum Distance Between Words of a String
 *
 * @reference   https://www.geeksforgeeks.org/minimum-distance-between-words-of-a-string/
 *
 * Given a string s and two words w1 and w2 that are present in S. The task is to find
 * the minimum distance between w1 and w2. Here distance is the number of steps or words
 * between the first and the second word.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 18.5.
 *
 * You have a large text file containing words. Given any two words, find the shortest
 * distance (in terms of number of words) between them in the file. If the operation
 * will be repeated many times for the same file (but different pairs of words), can
 * you optimize your solution?
 */
unsigned MinDistanceBetweenWords(std::string text,
                                 const std::string_view w1,
                                 const std::string_view w2) {
    if (w1 == w2) {
        return 0;
    }

    ArrayType words;
    for (auto *token = std::strtok(text.data(), SPACES);
         token != nullptr;
         token = std::strtok(nullptr, SPACES)) {
        words.push_back(token);
    }

    return MinDistanceBetweenWords(words, w1, w2) - 1;
}


/**
 * @reference   Shortest Word Distance II
 *              https://cheonhyangzhang.gitbooks.io/leetcode-solutions/content/244-shortest-word-distance-ii-medium.html
 *
 * Design a class which receives a list of words in the constructor, and implements a
 * method that takes two words word1 and word2 and return the shortest distance between
 * these two words in the list. Your method will be called repeatedly many times with
 * different parameters. Note: You may assume that word1 does not equal to word2, and
 * word1 and word2 are both in the list.
 */
auto buildOccurrenceMap(const ArrayType &words) {
    std::unordered_map<ArrayType::value_type, std::vector<int>> occurrences;
    for (std::size_t i = 0; i < words.size(); ++i) {
        occurrences[words[i]].push_back(i);
    }

    return occurrences;
}

inline auto
MinDistanceBetweenWords_MultiQueries_Hash(const ArrayType &words,
                                          const std::string_view one_word,
                                          const std::string_view another) {
    assert(one_word != another);

    const auto occurrences_map = buildOccurrenceMap(words);

    const auto &one_occurrences = occurrences_map.at(one_word);
    const auto &another_occurrences = occurrences_map.at(another);
    return MinDiffPairOf2SortedArrays(one_occurrences, another_occurrences);
}


/**
 * @reference   Shortest Word Distance III
 *              https://tenderleo.gitbooks.io/leetcode-solutions-/content/GoogleMedium/245.html
 *
 * Given a list of words and two words word1 and word2, return the shortest distance
 * between these two words in the list. word1 and word2 may be the same and they
 * represent two individual words in the list. Note: You may assume word1 and word2
 * are both in the list.
 */
unsigned
MinDistanceBetweenWords_MayBeIdentical(const ArrayType &words,
                                       const std::string_view one_word,
                                       const std::string_view another) {
    if (one_word != another) {
        return MinDistanceBetweenWords(words, one_word, another);
    }

    int prev = -1;
    auto min = words.size();
    for (std::size_t i = 0; i < words.size(); ++i) {
        if (words[i] == one_word) {
            if (prev != -1) {
                min = std::min(min, i - prev);
            }
            prev = i;
        }
    }

    return min;
}


unsigned
MinDistanceBetweenWords_MayBeIdentical_Short(const ArrayType &words,
                                             const std::string_view one_word,
                                             const std::string_view another) {
    int last_one = -1;
    int last_another = -1;
    int min_distance = words.size();
    for (std::size_t i = 0; i < words.size(); ++i) {
        if (words[i] == one_word) {
            last_one = i;
            if (last_one != -1 and last_another != -1) {
                if (last_one != last_another) {
                    min_distance = std::min(min_distance, last_one - last_another);
                }
            }
        }

        if (words[i] == another) {
            last_another = i;
            if (last_one != -1 and last_another != -1) {
                if (last_one != last_another) {
                    min_distance = std::min(min_distance, last_another - last_one);
                }
            }
        }
    }

    return min_distance;
}

}//namespace


THE_BENCHMARK(MinDistanceBetweenWords,
              "geeks for geeks contribute practice", "geeks", "practice");

SIMPLE_TEST(MinDistanceBetweenWords, TestSAMPLE1, 1,
            "geeks for geeks contribute practice", "geeks", "practice");
SIMPLE_TEST(MinDistanceBetweenWords, TestSAMPLE2, 2,
            "the quick the brown quick brown the frog", "quick", "frog");


const ArrayType SAMPLE1 = {"practice", "makes", "perfect", "coding", "makes"};


SIMPLE_TEST(MinDistanceBetweenWords, TestSAMPLE3, 3, SAMPLE1, "practice", "coding");
SIMPLE_TEST(MinDistanceBetweenWords, TestSAMPLE4, 1, SAMPLE1, "makes", "coding");


THE_BENCHMARK(MinDistanceBetweenWords_MultiQueries_Hash, SAMPLE1, "practice", "coding");

SIMPLE_TEST(MinDistanceBetweenWords_MultiQueries_Hash, TestSAMPLE1, 3,
            SAMPLE1, "practice", "coding");
SIMPLE_TEST(MinDistanceBetweenWords_MultiQueries_Hash, TestSAMPLE2, 1,
            SAMPLE1, "makes", "coding");


THE_BENCHMARK(MinDistanceBetweenWords_MayBeIdentical, SAMPLE1, "practice", "coding");

SIMPLE_TEST(MinDistanceBetweenWords_MayBeIdentical, TestSAMPLE1, 3,
            SAMPLE1, "practice", "coding");
SIMPLE_TEST(MinDistanceBetweenWords_MayBeIdentical, TestSAMPLE2, 1,
            SAMPLE1, "makes", "coding");
SIMPLE_TEST(MinDistanceBetweenWords_MayBeIdentical, TestSAMPLE3, 3,
            SAMPLE1, "makes", "makes");


THE_BENCHMARK(MinDistanceBetweenWords_MayBeIdentical_Short,
              SAMPLE1, "practice", "coding");

SIMPLE_TEST(MinDistanceBetweenWords_MayBeIdentical_Short, TestSAMPLE1, 3,
            SAMPLE1, "practice", "coding");
SIMPLE_TEST(MinDistanceBetweenWords_MayBeIdentical_Short, TestSAMPLE2, 1,
            SAMPLE1, "makes", "coding");
SIMPLE_TEST(MinDistanceBetweenWords_MayBeIdentical_Short, TestSAMPLE3, 3,
            SAMPLE1, "makes", "makes");
