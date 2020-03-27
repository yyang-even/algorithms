#include "common_header.h"


namespace {

/** C Program to Check if a Given String is Palindrome
 *
 * @reference   https://www.geeksforgeeks.org/c-program-check-given-string-palindrome/
 * @reference   Check if a string is palindrome in C using pointers
 *              https://www.geeksforgeeks.org/check-if-a-string-is-palindrome-in-c-using-pointers/
 * @reference   Program to check if an Array is Palindrome or not
 *              https://www.geeksforgeeks.org/program-to-check-if-an-array-is-palindrome-or-not/
 */
auto isPalindrome_Iterative(const std::string &a_string) {
    assert(not a_string.empty());

    auto left = a_string.cbegin();
    auto right = std::prev(a_string.cend());
    while (left < right) {
        if (*(left++) != *(right--)) {
            return false;
        }
    }

    return true;
}


/**
 * @reference   Recursive function to check if a string is palindrome
 *              https://www.geeksforgeeks.org/recursive-function-check-string-palindrome/
 * @reference   Program to check if an array is palindrome or not using Recursion
 *              https://www.geeksforgeeks.org/program-to-check-if-an-array-is-palindrome-or-not-using-recursion/
 */
auto isPalindrome_Recursive(const std::string::const_iterator left,
                            const std::string::const_iterator right) {
    if (left >= right) {
        return true;
    }

    if (*left != *right) {
        return false;
    }

    return isPalindrome_Recursive(std::next(left), std::prev(right));
}

auto isPalindrome_Recursive(const std::string &a_string) {
    return isPalindrome_Recursive(a_string.cbegin(), std::prev(a_string.cend()));
}


/**
 * @reference   Program to check if an Array is Palindrome or not using STL in C++
 *              https://www.geeksforgeeks.org/program-to-check-if-an-array-is-palindrome-or-not-using-stl-in-c/
 *
 * @note    Copy and reverse, are too expensive.
 */


/**
 * @reference   Check whether the given string is Palindrome using Stack
 *              https://www.geeksforgeeks.org/check-whether-the-given-string-is-palindrome-using-stack/
 */
auto isPalindrome_Stack(const std::string &a_string) {
    std::stack<std::string::value_type> the_stack;
    const auto mid = a_string.size() / 2;
    std::string::size_type i = 0;
    for (; i < mid; ++i) {
        the_stack.push(a_string[i]);
    }

    if (a_string.size() % 2 != 0) {
        ++i;
    }

    while (not the_stack.empty()) {
        if (a_string[i++] != the_stack.top()) {
            return false;
        }
        the_stack.pop();
    }

    return true;
}

}//namespace


SIMPLE_BENCHMARK(isPalindrome_Iterative, "aba");

SIMPLE_TEST(isPalindrome_Iterative, TestSAMPLE1, true, "aba");
SIMPLE_TEST(isPalindrome_Iterative, TestSAMPLE2, true, "abbccbba");
SIMPLE_TEST(isPalindrome_Iterative, TestSAMPLE3, false, "geeks");


SIMPLE_BENCHMARK(isPalindrome_Recursive, "aba");

SIMPLE_TEST(isPalindrome_Recursive, TestSAMPLE1, true, "aba");
SIMPLE_TEST(isPalindrome_Recursive, TestSAMPLE2, true, "abbccbba");
SIMPLE_TEST(isPalindrome_Recursive, TestSAMPLE3, false, "geeks");


SIMPLE_BENCHMARK(isPalindrome_Stack, "aba");

SIMPLE_TEST(isPalindrome_Stack, TestSAMPLE1, true, "aba");
SIMPLE_TEST(isPalindrome_Stack, TestSAMPLE2, true, "abbccbba");
SIMPLE_TEST(isPalindrome_Stack, TestSAMPLE3, false, "geeks");
