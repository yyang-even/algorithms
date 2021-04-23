#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string>;

/** Print all interleavings of given two strings
 *
 * @reference   https://www.geeksforgeeks.org/print-all-interleavings-of-given-two-strings/
 *
 * Given two strings str1 and str2, write a function that prints all interleavings of the
 * given two strings. You may assume that all characters in both strings are different.
 * An interleaved string of given two strings preserves the order of characters in
 * individual strings.
 */
void InterleavingsOfTwoStringHelper(const std::string_view::const_iterator cbegin1,
                                    const std::string_view::const_iterator cend1,
                                    const std::string_view::const_iterator cbegin2,
                                    const std::string_view::const_iterator cend2,
                                    const std::string &buffer,
                                    const std::string::iterator buffer_iter,
                                    ArrayType &outputs) {
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

auto InterleavingsOfTwoString(const std::string_view str1,
                              const std::string_view str2) {
    ArrayType outputs;
    std::string buffer(str1.size() + str2.size(), '0');

    InterleavingsOfTwoStringHelper(str1.cbegin(), str1.cend(),
                                   str2.cbegin(), str2.cend(),
                                   buffer, buffer.begin(), outputs);

    return outputs;
}

}//namespace


const ArrayType EXPECTED1 = {"abc", "acb", "cab"};
const ArrayType EXPECTED2 = {"abcd", "acbd", "acdb", "cabd", "cadb", "cdab"};


THE_BENCHMARK(InterleavingsOfTwoString, "abcde", "12345");

SIMPLE_TEST(InterleavingsOfTwoString, TestSAMPLE1, EXPECTED1, "ab", "c");
SIMPLE_TEST(InterleavingsOfTwoString, TestSAMPLE2, EXPECTED2, "ab", "cd");
