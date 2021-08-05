#include "common_header.h"


namespace {

/** Detect Capital
 *
 * @reference   https://leetcode.com/problems/detect-capital/
 *
 * We define the usage of capitals in a word to be right when one of the following cases
 * holds:
 *  All letters in this word are capitals, like "USA".
 *  All letters in this word are not capitals, like "leetcode".
 *  Only the first letter in this word is capital, like "Google".
 * Given a string word, return true if the usage of capitals in it is right.
 */
inline auto DetectCapital(const std::string_view word) {
    const std::size_t number_capitals =
        std::count_if(word.cbegin(), word.cend(), ToLambda(std::isupper));
    if (number_capitals == 0 or number_capitals == word.size()) {
        return true;
    }
    return number_capitals == 1 and std::isupper(word.front());
}

}//namespace


THE_BENCHMARK(DetectCapital, "USA");

SIMPLE_TEST(DetectCapital, TestSAMPLE1, true, "USA");
SIMPLE_TEST(DetectCapital, TestSAMPLE2, true, "leetcode");
SIMPLE_TEST(DetectCapital, TestSAMPLE3, true, "Google");
SIMPLE_TEST(DetectCapital, TestSAMPLE4, false, "FlaG");
