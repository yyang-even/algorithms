#include "common_header.h"

/** Print all interleavings of given two strings
 *
 * @reference   https://www.geeksforgeeks.org/print-all-interleavings-of-given-two-strings/
 *
 * Given two strings str1 and str2, write a function that prints all interleavings
 * of the given two strings. You may assume that all characters in both strings are
 * different.
 * An interleaved string of given two strings preserves the order of characters in
 * individual strings.
 */
void InterleavingsOfTwoStringHelper(const std::string::const_iterator cbegin1,
                                    const std::string::const_iterator cend1,
                                    const std::string::const_iterator cbegin2,
                                    const std::string::const_iterator cend2,
                                    const std::string &buffer,
                                    const std::string::iterator buffer_iter,
                                    std::vector<std::string> &outputs) {
    if (cbegin1 == cend1 and cbegin2 == cend2) {
        outputs.push_back(buffer);
    } else {
        if (cbegin1 != cend1) {
            *buffer_iter = *cbegin1;
            InterleavingsOfTwoStringHelper(cbegin1 + 1, cend1, cbegin2, cend2, buffer,
                                           buffer_iter + 1, outputs);
        }
        if (cbegin2 != cend2) {
            *buffer_iter = *cbegin2;
            InterleavingsOfTwoStringHelper(cbegin1, cend1, cbegin2 + 1, cend2, buffer,
                                           buffer_iter + 1, outputs);
        }
    }
}
auto InterleavingsOfTwoString(const std::string str1, const std::string str2) {
    std::vector<std::string> outputs;
    std::string buffer(str1.size() + str2.size(), '0');

    InterleavingsOfTwoStringHelper(str1.cbegin(), str1.cend(),
                                   str2.begin(), str2.cend(),
                                   buffer, buffer.begin(), outputs);

    return outputs;
}


const std::vector<std::string> EXPECTED1 = {"abc", "acb", "cab"};
const std::vector<std::string> EXPECTED2 = {"abcd", "acbd", "acdb", "cabd", "cadb", "cdab"};

SIMPLE_BENCHMARK(InterleavingsOfTwoString, std::string("abcde"), std::string("12345"));

SIMPLE_TEST(InterleavingsOfTwoString, TestSAMPLE1, EXPECTED1, std::string("ab"), std::string("c"));
SIMPLE_TEST(InterleavingsOfTwoString, TestSAMPLE2, EXPECTED2, std::string("ab"), std::string("cd"));
