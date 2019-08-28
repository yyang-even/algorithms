#include "common_header.h"

#include <stack>

#include "reverse.h"
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
 * @reference   TCS Coding Practice Question | Reverse a String
 *              https://www.geeksforgeeks.org/tcs-coding-practice-question-reverse-a-string/
 *
 * @reference   Reverse string without using any temporary variable
 *              https://www.geeksforgeeks.org/reverse-string-without-using-any-temporary-variable/
 * @reference   Print reverse of a string using recursion
 *              https://www.geeksforgeeks.org/reverse-a-string-using-recursion/
 *
 * @reference   Reverse an array without using subtract sign ‘-‘ anywhere in the code
 *              https://www.geeksforgeeks.org/reverse-array-without-using-subtract-sign-anywhere-code/
 *
 * Given a string, write a C/C++ program to reverse it.
 */
template <typename SwapFunc>
auto Reverse(std::string input, const SwapFunc swap) {
    Reverse_TwoPointers(input.begin(), input.end(), swap);

    return input;
}


auto Reverse(const std::string &input) {
    return Reverse(input, ToLambda(std::swap));
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


auto Reverse_Stack(std::string input) {
    std::stack<std::string::value_type> s;
    for (auto &c : input) {
        s.push(std::move(c));
    }

    for (std::string::size_type i = 0; not s.empty(); ++i) {
        input[i] = std::move(s.top());
        s.pop();
    }

    return input;
}

}//namespace


SIMPLE_BENCHMARK(Reverse, "ab4c12ed3");

SIMPLE_TEST(Reverse, TestSAMPLE1, "", "");
SIMPLE_TEST(Reverse, TestSAMPLE2, "a", "a");
SIMPLE_TEST(Reverse, TestSAMPLE3, "ba", "ab");
SIMPLE_TEST(Reverse, TestSAMPLE4, "cba", "abc");


SIMPLE_BENCHMARK(Reverse_Recursive, "ab4c12ed3");

SIMPLE_TEST(Reverse_Recursive, TestSAMPLE1, "", "");
SIMPLE_TEST(Reverse_Recursive, TestSAMPLE2, "a", "a");
SIMPLE_TEST(Reverse_Recursive, TestSAMPLE3, "ba", "ab");
SIMPLE_TEST(Reverse_Recursive, TestSAMPLE4, "cba", "abc");


SIMPLE_BENCHMARK(Reverse_Xor, "ab4c12ed3");

SIMPLE_TEST(Reverse_Xor, TestSAMPLE1, "", "");
SIMPLE_TEST(Reverse_Xor, TestSAMPLE2, "a", "a");
SIMPLE_TEST(Reverse_Xor, TestSAMPLE3, "ba", "ab");
SIMPLE_TEST(Reverse_Xor, TestSAMPLE4, "cba", "abc");


SIMPLE_BENCHMARK(Reverse_Stack, "ab4c12ed3");

SIMPLE_TEST(Reverse_Stack, TestSAMPLE1, "", "");
SIMPLE_TEST(Reverse_Stack, TestSAMPLE2, "a", "a");
SIMPLE_TEST(Reverse_Stack, TestSAMPLE3, "ba", "ab");
SIMPLE_TEST(Reverse_Stack, TestSAMPLE4, "cba", "abc");
