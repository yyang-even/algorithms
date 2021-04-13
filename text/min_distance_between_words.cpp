#include "common_header.h"


namespace {

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
 *
 * @hint    Use a hash table of each word and the locations where it occurs.
 */
unsigned MinDistanceBetweenWords(std::string text, const std::string &w1,
                                 const std::string &w2) {
    if (w1 == w2) {
        return 0;
    }

    constexpr auto *delimiters = " ";

    std::vector<std::string_view> words;
    for (auto *token = std::strtok(text.data(), delimiters);
         token != nullptr;
         token = std::strtok(nullptr, delimiters)) {
        words.push_back(token);
    }

    auto previous = words.size();
    auto min_distance = previous;
    for (std::size_t i = 0; i < words.size(); ++i) {
        if (words[i] == w1 or words[i] == w2) {
            if (previous != words.size() and words[previous] != words[i]) {
                const auto distance = i - previous - 1;
                if (distance < min_distance) {
                    min_distance = distance;
                }
            }
            previous = i;
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
