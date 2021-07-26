#include "common_header.h"

#include "reverse.h"
#include "mathematics/numbers/binary/swap.h"
#include "mathematics/arithmetics/subtract/subtract.h"


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
 * @reference   Program to reverse a string (Iterative and Recursive)
 *              https://www.geeksforgeeks.org/program-reverse-string-iterative-recursive/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 1.2.
 *
 * @reference   Reverse string without using any temporary variable
 *              https://www.geeksforgeeks.org/reverse-string-without-using-any-temporary-variable/
 * @reference   Print reverse of a string using recursion
 *              https://www.geeksforgeeks.org/reverse-a-string-using-recursion/
 *
 * @reference   Program to reverse an array using pointers
 *              https://www.geeksforgeeks.org/program-reverse-array-using-pointers/
 * @reference   Reverse an array without using subtract sign ‘-‘ anywhere in the code
 *              https://www.geeksforgeeks.org/reverse-array-without-using-subtract-sign-anywhere-code/
 *
 * Given a string, write a C/C++ program to reverse it.
 *
 * @reference   Program to copy the contents of one array into another in the reverse order
 *              https://www.geeksforgeeks.org/program-to-copy-the-contents-of-one-array-into-another-in-the-reverse-order/
 *
 * @reference   Reverse String
 *              https://leetcode.com/problems/reverse-string/
 *
 * Follow up: Do not allocate extra space for another array. You must do this by
 * modifying the input array in-place with O(1) extra memory.
 */
template <typename SwapFunc>
inline auto Reverse(std::string input, const SwapFunc swap) {
    Reverse_TwoPointers(input.begin(), input.end(), swap);

    return input;
}


inline auto Reverse(std::string input) {
    return Reverse(std::move(input), ToLambda(std::swap));
}


inline void Reverse_Recursive(const std::string::iterator begin,
                              const std::string::iterator last) {
    if (begin < last) {
        std::iter_swap(begin, last);
        Reverse_Recursive(std::next(begin), std::prev(last));
    }
}

inline auto Reverse_Recursive(std::string input) {
    if (not input.empty()) {
        Reverse_Recursive(input.begin(), std::prev(input.end()));
    }
    return input;
}


inline auto Reverse_Xor(std::string input) {
    return Reverse(std::move(input), Swap_Xor<std::string::value_type>);
}


/**
 * @reference   Stack | Set 3 (Reverse a string using stack)
 *              https://www.geeksforgeeks.org/stack-set-3-reverse-string-using-stack/
 */
auto Reverse_Stack(std::string input) {
    std::stack<std::string::value_type> s;
    for (const auto c : input) {
        s.push(c);
    }

    for (std::string::size_type i = 0; not s.empty();) {
        input[i++] = s.top();
        s.pop();
    }

    return input;
}


auto Reverse_Variable(std::string input) {
    static constexpr auto minus_one = std::numeric_limits<int>::min() /
                                      std::numeric_limits<int>::max();

    for (std::string::size_type i = 0; i < input.size() / 2; ++i) {
        std::swap(input[i], input[input.size() + (minus_one * i) + minus_one]);
    }

    return input;
}


inline auto Reverse_BitSubtract(std::string input) {
    for (std::string::size_type i = 0; i < input.size() / 2; ++i) {
        std::swap(input[i], input[Subtract_Bits(input.size(), (i + 1))]);
    }

    return input;
}

}//namespace


THE_BENCHMARK(Reverse, "ab4c12ed3");

SIMPLE_TEST(Reverse, TestSAMPLE1, "", "");
SIMPLE_TEST(Reverse, TestSAMPLE2, "a", "a");
SIMPLE_TEST(Reverse, TestSAMPLE3, "ba", "ab");
SIMPLE_TEST(Reverse, TestSAMPLE4, "cba", "abc");


THE_BENCHMARK(Reverse_Recursive, "ab4c12ed3");

SIMPLE_TEST(Reverse_Recursive, TestSAMPLE1, "", "");
SIMPLE_TEST(Reverse_Recursive, TestSAMPLE2, "a", "a");
SIMPLE_TEST(Reverse_Recursive, TestSAMPLE3, "ba", "ab");
SIMPLE_TEST(Reverse_Recursive, TestSAMPLE4, "cba", "abc");


THE_BENCHMARK(Reverse_Xor, "ab4c12ed3");

SIMPLE_TEST(Reverse_Xor, TestSAMPLE1, "", "");
SIMPLE_TEST(Reverse_Xor, TestSAMPLE2, "a", "a");
SIMPLE_TEST(Reverse_Xor, TestSAMPLE3, "ba", "ab");
SIMPLE_TEST(Reverse_Xor, TestSAMPLE4, "cba", "abc");


THE_BENCHMARK(Reverse_Stack, "ab4c12ed3");

SIMPLE_TEST(Reverse_Stack, TestSAMPLE1, "", "");
SIMPLE_TEST(Reverse_Stack, TestSAMPLE2, "a", "a");
SIMPLE_TEST(Reverse_Stack, TestSAMPLE3, "ba", "ab");
SIMPLE_TEST(Reverse_Stack, TestSAMPLE4, "cba", "abc");


THE_BENCHMARK(Reverse_Variable, "ab4c12ed3");

SIMPLE_TEST(Reverse_Variable, TestSAMPLE1, "", "");
SIMPLE_TEST(Reverse_Variable, TestSAMPLE2, "a", "a");
SIMPLE_TEST(Reverse_Variable, TestSAMPLE3, "ba", "ab");
SIMPLE_TEST(Reverse_Variable, TestSAMPLE4, "cba", "abc");


THE_BENCHMARK(Reverse_BitSubtract, "ab4c12ed3");

SIMPLE_TEST(Reverse_BitSubtract, TestSAMPLE1, "", "");
SIMPLE_TEST(Reverse_BitSubtract, TestSAMPLE2, "a", "a");
SIMPLE_TEST(Reverse_BitSubtract, TestSAMPLE3, "ba", "ab");
SIMPLE_TEST(Reverse_BitSubtract, TestSAMPLE4, "cba", "abc");
