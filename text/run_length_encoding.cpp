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
 * @reference   Run Length Encoding
 *              https://www.geeksforgeeks.org/run-length-encoding/
 *
 * Given an input string, write a function that returns the Run Length Encoded string for
 * the input string. For example, if the input string is "wwwwaaadexxxxxx", then the
 * function should return "w4a3d1e1x6".
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 1.5.
 */
auto RunLengthEncoding(const std::string &text) {
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


THE_BENCHMARK(RunLengthEncoding, "GeeeEEKKKss");

SIMPLE_TEST(RunLengthEncoding, TestSAMPLE1, "G1e3E2K3s2", "GeeeEEKKKss");
SIMPLE_TEST(RunLengthEncoding, TestSAMPLE2, "c4O1d2E3", "ccccOddEEE");
SIMPLE_TEST(RunLengthEncoding, TestSAMPLE3, "a2b1c5a3", "aabcccccaaa");
SIMPLE_TEST(RunLengthEncoding, TestSAMPLE4, "w4a3d1e1x6", "wwwwaaadexxxxxx");
