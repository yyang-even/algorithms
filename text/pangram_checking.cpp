#include "common_header.h"


auto toCharCounters(const std::string &sentence) {
    std::vector<bool> counters(LOWERCASE_CHARS.size(), false);

    std::vector<bool>::size_type index;
    for(const auto c: sentence){
        if(isupper(c))
            index = c - 'A';
        else if(islower(c))
            index = c - 'a';
        else
            continue;

        counters[index] = true;
    }

    return counters;
}
/** Pangram Checking
 *
 * @reference   https://www.geeksforgeeks.org/pangram-checking/
 *
 * Given a string check if it is Pangram or not. A pangram is a
 * sentence containing every letter in the English Alphabet.
 */
INT_BOOL CheckPangram(const std::string &sentence){
    const auto counters = toCharCounters(sentence);

    for(const auto count: counters) {
        if(not count)
            return false;
    }

    return true;
}


/** Check if a String can be converted to Pangram in K changes
 *
 * @reference   https://www.geeksforgeeks.org/check-if-a-string-can-be-converted-to-pangram-in-k-changes/
 *
 * Given a String str containing only lowercase English alphabets and an integer K.
 * The task is to check that whether the string can be converted to a Pangram by
 * performing at most K changes. In one change we can remove any existing character
 * and add a new character.
 * Pangram: A pangram is a sentence containing every letter in the English Alphabet.
 * Note: Given that length of string is greater than 26 always and in one operation
 * we have to remove an existing element to add a new element.
 */
INT_BOOL CheckPangramConvertibleInK(const std::string &sentence, int K){
    assert(sentence.size() > LOWERCASE_CHARS.size());

    const auto counters = toCharCounters(sentence);

    for(const auto count: counters) {
        if(not count and --K < 0)
            return false;
    }

    return true;
}


SIMPLE_BENCHMARK(CheckPangram, std::string("The quick brown fox jumps over the lazy dog."));

SIMPLE_TEST(CheckPangram, TestSAMPLE1, TRUE, std::string("The quick brown fox jumps over the lazy dog."));
SIMPLE_TEST(CheckPangram, TestSAMPLE2, FALSE, std::string("The quick brown fox jumps over the dog."));


SIMPLE_BENCHMARK(CheckPangramConvertibleInK, std::string("qwqqwqeqqwdsdadsdasadsfsdsdsdasasas"));

SIMPLE_TEST(CheckPangramConvertibleInK, TestSAMPLE1, TRUE, std::string("qwqqwqeqqwdsdadsdasadsfsdsdsdasasas"), 24);
SIMPLE_TEST(CheckPangramConvertibleInK, TestSAMPLE2, FALSE, std::string("qwqqwqeqqwdsdadsdasadsfsdsdsdasasas"), 4);
