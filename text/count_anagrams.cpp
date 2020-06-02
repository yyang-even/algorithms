#include "common_header.h"


namespace {

/** Count Occurences of Anagrams
 *
 * @reference   https://www.geeksforgeeks.org/count-occurences-of-anagrams/
 *
 * Given a word and a text, return the count of the occurences of anagrams of the
 * word in the text(For eg: anagrams of word for are for, ofr, rof etc.))
 */
auto AreAllCharZero(const std::unordered_map<std::string::value_type, int> &char_counts) {
    for (const auto &pair : char_counts) {
        if (pair.second) {
            return false;
        }
    }

    return true;
}

auto CountAnagrams(const std::string &text, const std::string &word) {
    std::unordered_map<std::string::value_type, int> char_counts;
    for (std::string::size_type i = 0; i < word.size(); ++i) {
        ++(char_counts[text[i]]);
        --(char_counts[word[i]]);
    }

    int count = AreAllCharZero(char_counts);

    for (auto i = word.size(); i < text.size(); ++i) {
        --(char_counts[text[i - word.size()]]);
        ++(char_counts[text[i]]);

        if (AreAllCharZero(char_counts)) {
            ++count;
        }
    }

    return count;
}

}//namespace


SIMPLE_BENCHMARK(CountAnagrams, "forxxorfxdofr", "for");

SIMPLE_TEST(CountAnagrams, TestSAMPLE1, 3, "forxxorfxdofr", "for");
SIMPLE_TEST(CountAnagrams, TestSAMPLE2, 4, "aabaabaa", "aaba");
