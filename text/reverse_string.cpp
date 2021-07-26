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


/**
 * @reference   Reverse String II
 *              https://leetcode.com/problems/reverse-string-ii/
 *
 * Given a string s and an integer k, reverse the first k characters for every 2k
 * characters counting from the start of the string. If there are fewer than k
 * characters left, reverse all of them. If there are less than 2k but greater than or
 * equal to k characters, then reverse the first k characters and left the other as
 * original.
 */
void reverse(std::string &s, int left, int right) {
    while (left < right) {
        std::swap(s[left++], s[right--]);
    }
}

auto ReverseStringGroups(std::string s, const std::size_t k) {
    for (std::size_t i = 0; i < s.size(); i += 2 * k) {
        const auto right = std::min(i + k, s.size()) - 1;
        reverse(s, i, right);
    }

    return s;
}


/**
 * @reference   Reverse Vowels of a String
 *              https://leetcode.com/problems/reverse-vowels-of-a-string/
 *
 * Given a string s, reverse only all the vowels in the string and return it. The vowels
 * are 'a', 'e', 'i', 'o', and 'u', and they can appear in both cases.
 */
inline constexpr auto isVowel(const int c) {
    bool is_vowel[256] = {};
    is_vowel['A'] = true;
    is_vowel['E'] = true;
    is_vowel['I'] = true;
    is_vowel['O'] = true;
    is_vowel['U'] = true;
    is_vowel['a'] = true;
    is_vowel['e'] = true;
    is_vowel['i'] = true;
    is_vowel['o'] = true;
    is_vowel['u'] = true;

    return is_vowel[c];
}

auto ReverseVowels(std::string text) {
    int left = 0;
    int right = text.size() - 1;
    while (left < right) {
        if (not isVowel(text[right])) {
            --right;
        } else if (not isVowel(text[left])) {
            ++left;
        } else {
            std::swap(text[left++], text[right--]);
        }
    }

    return text;
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


THE_BENCHMARK(ReverseStringGroups, "abcdefg", 2);

SIMPLE_TEST(ReverseStringGroups, TestSAMPLE1, "bacdfeg", "abcdefg", 2);
SIMPLE_TEST(ReverseStringGroups, TestSAMPLE2, "bacd", "abcd", 2);


THE_BENCHMARK(ReverseVowels, "hello");

SIMPLE_TEST(ReverseVowels, TestSAMPLE1, "holle", "hello");
SIMPLE_TEST(ReverseVowels, TestSAMPLE2, "leotcede", "leetcode");
