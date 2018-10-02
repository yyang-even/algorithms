#include "common_header.h"

/** Pangram Checking
 *
 * @reference   https://www.geeksforgeeks.org/pangram-checking/
 *
 * Given a string check if it is Pangram or not. A pangram is a
 * sentence containing every letter in the English Alphabet.
 */
INT_BOOL CheckPangram(const std::string &sentence){
    std::vector<bool> counters(LOWERCASE_CHARS.size(), false);

    std::vector<bool>::size_type index;
    for(const auto c: sentence){
        if(c >= 'A' and c <= 'Z')
            index = c - 'A';
        else if(c >= 'a' and c <= 'z')
            index = c - 'a';
        else
            continue;

        counters[index] = true;
    }

    for(const auto count: counters) {
        if(not count)
            return false;
    }

    return true;
}


SIMPLE_BENCHMARK(CheckPangram, std::string("The quick brown fox jumps over the lazy dog."));

SIMPLE_TEST(CheckPangram, TestSAMPLE1, TRUE, std::string("The quick brown fox jumps over the lazy dog."));
SIMPLE_TEST(CheckPangram, TestSAMPLE2, FALSE, std::string("The quick brown fox jumps over the dog."));
