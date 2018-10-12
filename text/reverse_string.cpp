#include "common_header.h"

/** Different methods to reverse a string in C/C++
 *
 * @reference   https://www.geeksforgeeks.org/reverse-a-string-in-c-cpp-different-methods/
 * @reference   Write a program to reverse an array or string
 *              https://www.geeksforgeeks.org/write-a-program-to-reverse-an-array-or-string/
 *
 * Given a string, write a C/C++ program to reverse it.
 */
auto Reverse(std::string input) {
    if (not input.empty()) {
        auto l_iter = input.begin();
        auto r_iter = input.begin() + input.size() - 1ul;
        for (; l_iter < r_iter; ++l_iter, --r_iter) {
            std::iter_swap(l_iter, r_iter);
        }
    }

    return input;
}

void ReverseRecursive(const std::string::iterator begin, const std::string::iterator last) {
    if (begin < last) {
        std::iter_swap(begin, last);
        ReverseRecursive(begin + 1, last - 1);
    }
}
auto ReverseRecursive(std::string input) {
    if (not input.empty()) {
        ReverseRecursive(input.begin(), input.begin() + input.size() - 1ul);
    }
    return input;
}


SIMPLE_BENCHMARK(Reverse, std::string("ab4c12ed3"));

SIMPLE_TEST(Reverse, TestSAMPLE1, std::string(""), std::string(""));
SIMPLE_TEST(Reverse, TestSAMPLE2, std::string("a"), std::string("a"));
SIMPLE_TEST(Reverse, TestSAMPLE3, std::string("ba"), std::string("ab"));
SIMPLE_TEST(Reverse, TestSAMPLE4, std::string("cba"), std::string("abc"));

SIMPLE_BENCHMARK(ReverseRecursive, std::string("ab4c12ed3"));

SIMPLE_TEST(ReverseRecursive, TestSAMPLE1, std::string(""), std::string(""));
SIMPLE_TEST(ReverseRecursive, TestSAMPLE2, std::string("a"), std::string("a"));
SIMPLE_TEST(ReverseRecursive, TestSAMPLE3, std::string("ba"), std::string("ab"));
SIMPLE_TEST(ReverseRecursive, TestSAMPLE4, std::string("cba"), std::string("abc"));
