#include "common_header.h"

#include "mathematics/numbers/binary/swap.h"

namespace {

/** Different methods to reverse a string in C/C++
 *
 * @reference   https://www.geeksforgeeks.org/reverse-a-string-in-c-cpp-different-methods/
 * @reference   Write a program to reverse an array or string
 *              https://www.geeksforgeeks.org/write-a-program-to-reverse-an-array-or-string/
 * @reference   Program to Reverse a String using Pointers
 *              https://www.geeksforgeeks.org/program-to-reverse-a-string-using-pointers/
 * @reference   C Program to Reverse Array of Strings
 *              https://www.geeksforgeeks.org/c-program-to-reverse-array-of-strings/
 *
 * @reference   Reverse string without using any temporary variable
 *              https://www.geeksforgeeks.org/reverse-string-without-using-any-temporary-variable/
 *
 * Given a string, write a C/C++ program to reverse it.
 */
template <typename SwapFunc>
auto Reverse(std::string input, const SwapFunc swap) {
    if (not input.empty()) {
        auto l_iter = input.begin();
        auto r_iter = input.begin() + input.size() - 1ul;
        for (; l_iter < r_iter; ++l_iter, --r_iter) {
            swap(*l_iter, *r_iter);
        }
    }

    return input;
}


auto Reverse(const std::string &input) {
    return Reverse(input, [](std::string::value_type & lhs, std::string::value_type & rhs) {
        std::swap(lhs, rhs);
    });
}


void Reverse_Recursive(const std::string::iterator begin, const std::string::iterator last) {
    if (begin < last) {
        std::iter_swap(begin, last);
        Reverse_Recursive(begin + 1, last - 1);
    }
}
auto Reverse_Recursive(std::string input) {
    if (not input.empty()) {
        Reverse_Recursive(input.begin(), input.begin() + input.size() - 1ul);
    }
    return input;
}


auto Reverse_Xor(const std::string &input) {
    return Reverse(input, Swap_Xor<std::string::value_type>);
}

}//namespace


SIMPLE_BENCHMARK(Reverse, std::string("ab4c12ed3"));

SIMPLE_TEST(Reverse, TestSAMPLE1, std::string(""), std::string(""));
SIMPLE_TEST(Reverse, TestSAMPLE2, std::string("a"), std::string("a"));
SIMPLE_TEST(Reverse, TestSAMPLE3, std::string("ba"), std::string("ab"));
SIMPLE_TEST(Reverse, TestSAMPLE4, std::string("cba"), std::string("abc"));


SIMPLE_BENCHMARK(Reverse_Recursive, std::string("ab4c12ed3"));

SIMPLE_TEST(Reverse_Recursive, TestSAMPLE1, std::string(""), std::string(""));
SIMPLE_TEST(Reverse_Recursive, TestSAMPLE2, std::string("a"), std::string("a"));
SIMPLE_TEST(Reverse_Recursive, TestSAMPLE3, std::string("ba"), std::string("ab"));
SIMPLE_TEST(Reverse_Recursive, TestSAMPLE4, std::string("cba"), std::string("abc"));


SIMPLE_BENCHMARK(Reverse_Xor, std::string("ab4c12ed3"));

SIMPLE_TEST(Reverse_Xor, TestSAMPLE1, std::string(""), std::string(""));
SIMPLE_TEST(Reverse_Xor, TestSAMPLE2, std::string("a"), std::string("a"));
SIMPLE_TEST(Reverse_Xor, TestSAMPLE3, std::string("ba"), std::string("ab"));
SIMPLE_TEST(Reverse_Xor, TestSAMPLE4, std::string("cba"), std::string("abc"));
