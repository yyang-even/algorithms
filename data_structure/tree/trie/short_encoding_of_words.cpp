#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string_view>;

/** Short Encoding of Words
 *
 * @reference   https://leetcode.com/problems/short-encoding-of-words/
 *
 * A valid encoding of an array of words is any reference string s and array of indices indices
 * such that:
 *  words.length == indices.length
 *  The reference string s ends with the '#' character.
 *  For each index indices[i], the substring of s starting from indices[i] and up to (but not
 *      including) the next '#' character is equal to words[i].
 * Given an array of words, return the length of the shortest reference string s possible of any
 * valid encoding of words.
 */
auto ShortEncodingOfWords_Hash(const ArrayType &words) {
    std::unordered_set<std::string_view> goods(words.cbegin(), words.cend());

    for (const auto s : words) {
        for (std::size_t i = 1; i < s.size(); ++i) {
            goods.erase(s.substr(i));
        }
    }

    int result = 0;
    for (const auto s : goods) {
        result += s.size() + 1;
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {"time", "me", "bell"};
const ArrayType SAMPLE2 = {"t"};


THE_BENCHMARK(ShortEncodingOfWords_Hash, SAMPLE1);

SIMPLE_TEST(ShortEncodingOfWords_Hash, TestSAMPLE1, 10, SAMPLE1);
SIMPLE_TEST(ShortEncodingOfWords_Hash, TestSAMPLE2, 2, SAMPLE2);
