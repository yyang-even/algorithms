#include "common_header.h"

#include "mathematics/numbers/count_digits_in_integer.h"
#include "mathematics/numbers/reverse_digits.h"


namespace {

using ListType = std::list<unsigned>;

/** C Program to Check if a Given String is Palindrome
 *
 * @reference   https://www.geeksforgeeks.org/c-program-check-given-string-palindrome/
 * @reference   Check if a string is palindrome in C using pointers
 *              https://www.geeksforgeeks.org/check-if-a-string-is-palindrome-in-c-using-pointers/
 * @reference   Program to check if an Array is Palindrome or not
 *              https://www.geeksforgeeks.org/program-to-check-if-an-array-is-palindrome-or-not/
 * @reference   Check if the characters in a string form a Palindrome in O(1) extra space
 *              https://www.geeksforgeeks.org/check-if-the-characters-in-a-string-form-a-palindrome-in-o1-extra-space/
 * @reference   Check if a doubly linked list of characters is palindrome or not
 *              https://www.geeksforgeeks.org/check-doubly-linked-list-characters-palindrome-not/
 *
 * @reference   Check whether the given floating point number is a palindrome
 *              https://www.geeksforgeeks.org/check-whether-the-given-floating-point-number-is-a-palindrome/
 */
constexpr auto isPalindrome_Iterative(const std::string_view a_string) {
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
inline auto isPalindrome_Recursive(const std::string_view::const_iterator left,
                                   const std::string_view::const_iterator right) {
    if (left >= right) {
        return true;
    }

    if (*left != *right) {
        return false;
    }

    return isPalindrome_Recursive(std::next(left), std::prev(right));
}

inline auto isPalindrome_Recursive(const std::string_view a_string) {
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
auto isPalindrome_Stack(const std::string_view a_string) {
    std::stack<std::string_view::value_type> the_stack;
    const auto mid = a_string.size() / 2;
    std::string_view::size_type i = 0;
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


/** Function to check if a singly linked list is palindrome
 *
 * @reference   https://www.geeksforgeeks.org/function-to-check-if-a-singly-linked-list-is-palindrome/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 2.7.
 *
 * @note    If no stack is allowed, then we can reverse the second half of the list, and restore it
 * later. Or we can use function call stack.
 *
 * @reference   Palindrome Linked List
 *              https://leetcode.com/problems/palindrome-linked-list/
 *
 * Given the head of a singly linked list, return true if it is a palindrome.
 * Follow up: Could you do it in O(n) time and O(1) space?
 */
auto isSinglyListPalindrome_Stack(const ListType &a_list) {
    std::stack<ListType::value_type> the_stack;
    auto slow_ptr = a_list.cbegin();
    auto fast_ptr = slow_ptr;

    while (isThereMoreThanOneElements(fast_ptr, a_list.cend())) {
        the_stack.push(*slow_ptr);
        ++slow_ptr;
        std::advance(fast_ptr, 2);
    }

    if (fast_ptr != a_list.cend()) {
        ++slow_ptr;
    }

    while (not the_stack.empty()) {
        if (*slow_ptr++ != the_stack.top()) {
            return false;
        }

        the_stack.pop();
    }

    return true;
}


/**
 * @reference   Maximum Twin Sum of a Linked List
 *              https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list/
 *
 * In a linked list of size n, where n is even, the ith node (0-indexed) of the linked list is known as
 * the twin of the (n-1-i)th node, if 0 <= i <= (n / 2) - 1.
 *  For example, if n = 4, then node 0 is the twin of node 3, and node 1 is the twin of node 2. These
 *  are the only nodes with twins for n = 4.
 * The twin sum is defined as the sum of a node and its twin.
 * Given the head of a linked list with even length, return the maximum twin sum of the linked list.
 */


/** Check if a number is Palindrome
 *
 * @reference   https://www.geeksforgeeks.org/check-if-a-number-is-palindrome/
 * @reference   Recursive program to check if number is palindrome or not
 *              https://www.geeksforgeeks.org/recursive-program-to-check-if-number-is-palindrome-or-not/
 * @reference   Program to check the number is Palindrome or not
 *              https://www.geeksforgeeks.org/program-to-check-the-number-is-palindrome-or-not/
 * @reference   To check a number is palindrome or not without using any extra space
 *              https://www.geeksforgeeks.org/check-number-palindrome-not-without-using-extra-space/
 */
inline constexpr auto isNumberPalindrome_Reverse(const unsigned number, const unsigned base) {
    const unsigned reversed_number = ReverseDigits(number, base);
    return reversed_number == number;
}

inline constexpr auto isIntPalindrome_Reverse(const unsigned number) {
    return isNumberPalindrome_Reverse(number, 10);
}


constexpr auto
isNumberPalindrome_Recursive(const unsigned number, const unsigned base, unsigned &copy) {
    if (number < base) {
        return number == copy % base;
    }

    if (not isNumberPalindrome_Recursive(number / base, base, copy)) {
        return false;
    }

    copy /= base;
    return (number % base) == (copy % base);
}

inline constexpr auto isIntPalindrome_Recursive(const unsigned number) {
    auto copy = number;
    return isNumberPalindrome_Recursive(number, 10, copy);
}


/**
 * @reference   Palindrome Number
 *              https://leetcode.com/problems/palindrome-number/
 */
constexpr auto isIntPalindrome_Half(int x) {
    if (x < 0 or (x % 10 == 0 and x)) {
        return false;
    }

    int reverted_number = 0;
    while (x > reverted_number) {
        reverted_number = reverted_number * 10 + x % 10;
        x /= 10;
    }

    return x == reverted_number or x == reverted_number / 10;
}


/**
 * @reference   Check if a number with even number of digits is palindrome or not
 *              https://www.geeksforgeeks.org/check-if-a-number-with-even-number-of-digits-is-palindrome-or-not/
 */
inline constexpr auto isEvenDigitsIntPalindrome(const unsigned number) {
    assert(CountDigits_Iterative(number) % 2 == 0);
    return number % 11 == 0;
}


/**
 * @reference   Check if number is palindrome or not in Octal
 *              https://www.geeksforgeeks.org/check-number-palindrome-not-octal/
 */
inline constexpr auto isOctalPalindrome_Reverse(const unsigned number) {
    return isNumberPalindrome_Reverse(number, 8);
}


inline constexpr auto isOctalPalindrome_Recursive(const unsigned number) {
    auto copy = number;
    return isNumberPalindrome_Recursive(number, 8, copy);
}


/**
 * @reference   Check if actual binary representation of a number is palindrome
 *              https://www.geeksforgeeks.org/check-actual-binary-representation-number-palindrome/
 *
 * Given a non-negative integer n. The problem is to check if binary representation of n is palindrome
 * or not. Note that the actual binary representation of the number is being considered for palindrome
 * checking, no leading 0’s are being considered.
 */
inline constexpr auto isActualBinaryPalindrome_Reverse(const unsigned number) {
    return isNumberPalindrome_Reverse(number, 2);
}


/** Check if binary representation of a number is palindrome
 *
 * @reference   https://www.geeksforgeeks.org/check-binary-representation-number-palindrome/
 */
constexpr auto isBinaryPalindrome(const unsigned number) {
    unsigned least_significant = 1;
    unsigned most_significant = 1 << (BitsNumber<decltype(number)> - 1);

    for (; least_significant < most_significant; least_significant <<= 1, most_significant >>= 1)
        if (static_cast<bool>(number & least_significant) !=
            static_cast<bool>(number & most_significant)) {
            return false;
        }

    return true;
}


/**
 * @reference   Valid Palindrome
 *              https://leetcode.com/problems/valid-palindrome/
 *
 * Given a string s, determine if it is a palindrome, considering only alphanumeric characters and
 * ignoring cases.
 *
 * @reference   Sentence Palindrome (Palindrome after removing spaces, dots, .. etc)
 *              https://www.geeksforgeeks.org/sentence-palindrome-palindrome-removing-spaces-dots-etc/
 */
constexpr auto ValidPalindrome(const std::string_view text) {
    int left = 0;
    int right = text.size() - 1;
    while (left < right) {
        for (; left < right and not std::isalnum(text[left]); ++left)
            ;
        for (; right > left and not std::isalnum(text[right]); --right)
            ;

        if (std::tolower(text[left++]) != std::tolower(text[right--])) {
            return false;
        }
    }

    return true;
}


/**
 * @reference   Valid Palindrome II
 *              https://leetcode.com/problems/valid-palindrome-ii/
 *
 * Given a string s, return true if the s can be palindrome after deleting at most one character from it.
 */
constexpr auto ValidPalindromeOneRemove(const std::string_view text) {
    int left = 0;
    int right = text.size() - 1;
    while (left < right) {
        if (text[left++] != text[right--]) {
            return isPalindrome_Iterative(text.substr(left - 1, right - left + 2)) or
                   isPalindrome_Iterative(text.substr(left, right - left + 2));
        }
    }

    return true;
}


/**
 * @reference   Remove Palindromic Subsequences
 *              https://leetcode.com/problems/remove-palindromic-subsequences/
 *
 * You are given a string s consisting only of letters 'a' and 'b'. In a single step you can remove one
 * palindromic subsequence from s.
 * Return the minimum number of steps to make the given string empty.
 * A string is a subsequence of a given string if it is generated by deleting some characters of a given
 * string without changing its order. Note that a subsequence does not necessarily need to be
 * contiguous.
 * A string is called palindrome if is one that reads the same backward as well as forward.
 *
 * @hint    isPalindrome(s) ? 1 : 2;
 */


/**
 * @reference   Find First Palindromic String in the Array
 *              https://leetcode.com/problems/find-first-palindromic-string-in-the-array/
 *
 * Given an array of strings words, return the first palindromic string in the array. If there is no
 * such string, return an empty string "".
 * A string is palindromic if it reads the same forward and backward.
 */


/**
 * @reference   Lexicographically Smallest Palindrome
 *              https://leetcode.com/problems/lexicographically-smallest-palindrome/
 *
 * You are given a string s consisting of lowercase English letters, and you are allowed to perform
 * operations on it. In one operation, you can replace a character in s with another lowercase English
 * letter.
 * Your task is to make s a palindrome with the minimum number of operations possible. If there are
 * multiple palindromes that can be made using the minimum number of operations, make the
 * lexicographically smallest one.
 * A string a is lexicographically smaller than a string b (of the same length) if in the first position
 * where a and b differ, string a has a letter that appears earlier in the alphabet than the
 * corresponding letter in b.
 * Return the resulting palindrome string.
 */

} //namespace


THE_BENCHMARK(isPalindrome_Iterative, "aba");

SIMPLE_TEST(isPalindrome_Iterative, TestSAMPLE1, true, "aba");
SIMPLE_TEST(isPalindrome_Iterative, TestSAMPLE2, true, "abbccbba");
SIMPLE_TEST(isPalindrome_Iterative, TestSAMPLE3, false, "geeks");


THE_BENCHMARK(isPalindrome_Recursive, "aba");

SIMPLE_TEST(isPalindrome_Recursive, TestSAMPLE1, true, "aba");
SIMPLE_TEST(isPalindrome_Recursive, TestSAMPLE2, true, "abbccbba");
SIMPLE_TEST(isPalindrome_Recursive, TestSAMPLE3, false, "geeks");


THE_BENCHMARK(isPalindrome_Stack, "aba");

SIMPLE_TEST(isPalindrome_Stack, TestSAMPLE1, true, "aba");
SIMPLE_TEST(isPalindrome_Stack, TestSAMPLE2, true, "abbccbba");
SIMPLE_TEST(isPalindrome_Stack, TestSAMPLE3, false, "geeks");


THE_BENCHMARK(ValidPalindrome, "A man, a plan, a canal: Panama");

SIMPLE_TEST(ValidPalindrome, TestSAMPLE1, true, "aba");
SIMPLE_TEST(ValidPalindrome, TestSAMPLE2, true, "abbccbba");
SIMPLE_TEST(ValidPalindrome, TestSAMPLE3, false, "geeks");
SIMPLE_TEST(ValidPalindrome, TestSAMPLE4, true, "A man, a plan, a canal: Panama");
SIMPLE_TEST(ValidPalindrome, TestSAMPLE5, false, "race a car");


THE_BENCHMARK(ValidPalindromeOneRemove, "aba");

SIMPLE_TEST(ValidPalindromeOneRemove, TestSAMPLE1, true, "aba");
SIMPLE_TEST(ValidPalindromeOneRemove, TestSAMPLE2, true, "abbccbba");
SIMPLE_TEST(ValidPalindromeOneRemove, TestSAMPLE3, false, "geeks");
SIMPLE_TEST(ValidPalindromeOneRemove, TestSAMPLE4, true, "abca");
SIMPLE_TEST(ValidPalindromeOneRemove, TestSAMPLE5, false, "abc");


const ListType SAMPLE1 = {1, 2, 1};
const ListType SAMPLE2 = {1, 2, 2, 1};
const ListType SAMPLE3 = {2, 2, 1};


THE_BENCHMARK(isSinglyListPalindrome_Stack, SAMPLE1);

SIMPLE_TEST(isSinglyListPalindrome_Stack, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(isSinglyListPalindrome_Stack, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(isSinglyListPalindrome_Stack, TestSAMPLE3, false, SAMPLE3);


THE_BENCHMARK(isIntPalindrome_Reverse, 121);

SIMPLE_TEST(isIntPalindrome_Reverse, TestSAMPLE1, true, 121);
SIMPLE_TEST(isIntPalindrome_Reverse, TestSAMPLE2, true, 1221);
SIMPLE_TEST(isIntPalindrome_Reverse, TestSAMPLE3, false, 211);


THE_BENCHMARK(isIntPalindrome_Recursive, 121);

SIMPLE_TEST(isIntPalindrome_Recursive, TestSAMPLE1, true, 121);
SIMPLE_TEST(isIntPalindrome_Recursive, TestSAMPLE2, true, 1221);
SIMPLE_TEST(isIntPalindrome_Recursive, TestSAMPLE3, false, 211);


THE_BENCHMARK(isIntPalindrome_Half, 121);

SIMPLE_TEST(isIntPalindrome_Half, TestSAMPLE1, true, 121);
SIMPLE_TEST(isIntPalindrome_Half, TestSAMPLE2, true, 1221);
SIMPLE_TEST(isIntPalindrome_Half, TestSAMPLE3, false, 211);
SIMPLE_TEST(isIntPalindrome_Half, TestSAMPLE4, false, -121);
SIMPLE_TEST(isIntPalindrome_Half, TestSAMPLE5, false, 10);
SIMPLE_TEST(isIntPalindrome_Half, TestSAMPLE6, false, 1234567899);
SIMPLE_TEST(isIntPalindrome_Half, TestSAMPLE7, true, 2);


THE_BENCHMARK(isEvenDigitsIntPalindrome, 123321);

SIMPLE_TEST(isEvenDigitsIntPalindrome, TestSAMPLE1, true, 123321);
SIMPLE_TEST(isEvenDigitsIntPalindrome, TestSAMPLE2, true, 1221);
SIMPLE_TEST(isEvenDigitsIntPalindrome, TestSAMPLE3, false, 1234);


THE_BENCHMARK(isOctalPalindrome_Reverse, 0121);

SIMPLE_TEST(isOctalPalindrome_Reverse, TestSAMPLE1, true, 0121);
SIMPLE_TEST(isOctalPalindrome_Reverse, TestSAMPLE2, true, 01221);
SIMPLE_TEST(isOctalPalindrome_Reverse, TestSAMPLE3, false, 0211);


THE_BENCHMARK(isOctalPalindrome_Recursive, 0121);

SIMPLE_TEST(isOctalPalindrome_Recursive, TestSAMPLE1, true, 0121);
SIMPLE_TEST(isOctalPalindrome_Recursive, TestSAMPLE2, true, 01221);
SIMPLE_TEST(isOctalPalindrome_Recursive, TestSAMPLE3, false, 0211);


THE_BENCHMARK(isActualBinaryPalindrome_Reverse, 0b101);

SIMPLE_TEST(isActualBinaryPalindrome_Reverse, TestSAMPLE1, true, 0b101);
SIMPLE_TEST(isActualBinaryPalindrome_Reverse, TestSAMPLE2, true, 0b1001);
SIMPLE_TEST(isActualBinaryPalindrome_Reverse, TestSAMPLE3, false, 0b1011);


THE_BENCHMARK(isBinaryPalindrome, 0b101);

SIMPLE_TEST(isBinaryPalindrome, TestSAMPLE1, false, 0b101);
SIMPLE_TEST(isBinaryPalindrome, TestSAMPLE2, true, -1);
SIMPLE_TEST(isBinaryPalindrome, TestSAMPLE3, true, (1 << (BitsNumber<unsigned> - 1)) + 1);
SIMPLE_TEST(isBinaryPalindrome,
            TestSAMPLE4,
            true,
            (1 << ((BitsNumber<unsigned> / 2) - 1)) + (1 << (BitsNumber<unsigned> / 2)));
SIMPLE_TEST(isBinaryPalindrome, TestSAMPLE5, false, 0b1011);
