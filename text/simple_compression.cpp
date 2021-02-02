#include "common_header.h"


namespace {

/** Printing frequency of each character just after its consecutive occurrences
 *
 * @reference   https://www.geeksforgeeks.org/printing-frequency-of-each-character-just-after-its-consecutive-occurrences/
 *
 * Given a string in such a way that every character occurs in a repeated manner. Your
 * task is to print the string by inserting the frequency of each unique character after
 * it and also eliminating all repeated characters.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 1.5.
 */
auto SimpleCompression(const std::string &text) {
    std::string result;
    for (std::string::size_type i = 0; text[i]; ++i) {
        int count = 1;
        for (; text[i] == text[i + 1]; ++i) {
            ++count;
        }

        result.push_back(text[i]);
        result.append(std::to_string(count));
    }

    return result;
}

}//namespace


THE_BENCHMARK(SimpleCompression, "GeeeEEKKKss");

SIMPLE_TEST(SimpleCompression, TestSAMPLE1, "G1e3E2K3s2", "GeeeEEKKKss");
SIMPLE_TEST(SimpleCompression, TestSAMPLE2, "c4O1d2E3", "ccccOddEEE");
SIMPLE_TEST(SimpleCompression, TestSAMPLE3, "a2b1c5a3", "aabcccccaaa");
