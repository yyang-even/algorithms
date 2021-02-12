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


/** Function to check if a singly linked list is palindrome
 *
 * @reference   https://www.geeksforgeeks.org/function-to-check-if-a-singly-linked-list-is-palindrome/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 2.7.
 *
 * @note    If no stack is allowed, then we can reverse the second half of the list, and
 * restore it later. Or we can use function call stack.
 */
auto isSinglyListPalindrome_Stack(const ListType &a_list) {
    std::stack<ListType::value_type> the_stack;
    auto slow_ptr = a_list.cbegin();
    auto fast_ptr = slow_ptr;

    while (fast_ptr != a_list.cend() and std::next(fast_ptr) != a_list.cend()) {
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
inline auto isNumberPalindrome_Reverse(const unsigned number, const unsigned base) {
    const unsigned reversed_number = ReverseDigits(number, base);
    return reversed_number == number;
}

inline auto isIntPalindrome_Reverse(const unsigned number) {
    return isNumberPalindrome_Reverse(number, 10);
}


auto isNumberPalindrome_Recursive(const unsigned number, const unsigned base,
                                  unsigned &copy) {
    if (number < base) {
        return number == copy % base;
    }

    if (not isNumberPalindrome_Recursive(number / base, base, copy)) {
        return false;
    }

    copy /= base;
    return (number % base) == (copy % base);
}

auto isIntPalindrome_Recursive(const unsigned number) {
    auto copy = number;
    return isNumberPalindrome_Recursive(number, 10, copy);
}


/**
 * @reference   Check if a number with even number of digits is palindrome or not
 *              https://www.geeksforgeeks.org/check-if-a-number-with-even-number-of-digits-is-palindrome-or-not/
 */
auto isEvenDigitsIntPalindrome(const unsigned number) {
    assert(CountDigits_Iterative(number) % 2 == 0);
    return number % 11 == 0;
}


/**
 * @reference   Check if number is palindrome or not in Octal
 *              https://www.geeksforgeeks.org/check-number-palindrome-not-octal/
 */
inline auto isOctalPalindrome_Reverse(const unsigned number) {
    return isNumberPalindrome_Reverse(number, 8);
}


inline auto isOctalPalindrome_Recursive(const unsigned number) {
    auto copy = number;
    return isNumberPalindrome_Recursive(number, 8, copy);
}


/**
 * @reference   Check if actual binary representation of a number is palindrome
 *              https://www.geeksforgeeks.org/check-actual-binary-representation-number-palindrome/
 *
 * Given a non-negative integer n. The problem is to check if binary representation of n
 * is palindrome or not. Note that the actual binary representation of the number is being
 * considered for palindrome checking, no leading 0’s are being considered.
 */
inline auto isActualBinaryPalindrome_Reverse(const unsigned number) {
    return isNumberPalindrome_Reverse(number, 2);
}


/** Check if binary representation of a number is palindrome
 *
 * @reference   https://www.geeksforgeeks.org/check-binary-representation-number-palindrome/
 */
auto isBinaryPalindrome(const unsigned number) {
    unsigned least_significant = 1;
    unsigned most_significant = 1 << (BitsNumber<decltype(number)> - 1);

    for (; least_significant < most_significant;
         least_significant <<= 1, most_significant >>= 1)
        if (static_cast<bool>(number & least_significant) !=
            static_cast<bool>(number & most_significant)) {
            return false;
        }

    return true;
}

}//namespace


SIMPLE_BENCHMARK(isPalindrome_Iterative, Sample1, "aba");

SIMPLE_TEST(isPalindrome_Iterative, TestSAMPLE1, true, "aba");
SIMPLE_TEST(isPalindrome_Iterative, TestSAMPLE2, true, "abbccbba");
SIMPLE_TEST(isPalindrome_Iterative, TestSAMPLE3, false, "geeks");


SIMPLE_BENCHMARK(isPalindrome_Recursive, Sample1, "aba");

SIMPLE_TEST(isPalindrome_Recursive, TestSAMPLE1, true, "aba");
SIMPLE_TEST(isPalindrome_Recursive, TestSAMPLE2, true, "abbccbba");
SIMPLE_TEST(isPalindrome_Recursive, TestSAMPLE3, false, "geeks");


SIMPLE_BENCHMARK(isPalindrome_Stack, Sample1, "aba");

SIMPLE_TEST(isPalindrome_Stack, TestSAMPLE1, true, "aba");
SIMPLE_TEST(isPalindrome_Stack, TestSAMPLE2, true, "abbccbba");
SIMPLE_TEST(isPalindrome_Stack, TestSAMPLE3, false, "geeks");


const ListType SAMPLE1 = {1, 2, 1};
const ListType SAMPLE2 = {1, 2, 2, 1};
const ListType SAMPLE3 = {2, 2, 1};


SIMPLE_BENCHMARK(isSinglyListPalindrome_Stack, Sample1, SAMPLE1);

SIMPLE_TEST(isSinglyListPalindrome_Stack, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(isSinglyListPalindrome_Stack, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(isSinglyListPalindrome_Stack, TestSAMPLE3, false, SAMPLE3);


SIMPLE_BENCHMARK(isIntPalindrome_Reverse, Sample1, 121);

SIMPLE_TEST(isIntPalindrome_Reverse, TestSAMPLE1, true, 121);
SIMPLE_TEST(isIntPalindrome_Reverse, TestSAMPLE2, true, 1221);
SIMPLE_TEST(isIntPalindrome_Reverse, TestSAMPLE3, false, 211);


SIMPLE_BENCHMARK(isIntPalindrome_Recursive, Sample1, 121);

SIMPLE_TEST(isIntPalindrome_Recursive, TestSAMPLE1, true, 121);
SIMPLE_TEST(isIntPalindrome_Recursive, TestSAMPLE2, true, 1221);
SIMPLE_TEST(isIntPalindrome_Recursive, TestSAMPLE3, false, 211);


SIMPLE_BENCHMARK(isEvenDigitsIntPalindrome, Sample1, 123321);

SIMPLE_TEST(isEvenDigitsIntPalindrome, TestSAMPLE1, true, 123321);
SIMPLE_TEST(isEvenDigitsIntPalindrome, TestSAMPLE2, true, 1221);
SIMPLE_TEST(isEvenDigitsIntPalindrome, TestSAMPLE3, false, 1234);


SIMPLE_BENCHMARK(isOctalPalindrome_Reverse, Sample1, 0121);

SIMPLE_TEST(isOctalPalindrome_Reverse, TestSAMPLE1, true, 0121);
SIMPLE_TEST(isOctalPalindrome_Reverse, TestSAMPLE2, true, 01221);
SIMPLE_TEST(isOctalPalindrome_Reverse, TestSAMPLE3, false, 0211);


SIMPLE_BENCHMARK(isOctalPalindrome_Recursive, Sample1, 0121);

SIMPLE_TEST(isOctalPalindrome_Recursive, TestSAMPLE1, true, 0121);
SIMPLE_TEST(isOctalPalindrome_Recursive, TestSAMPLE2, true, 01221);
SIMPLE_TEST(isOctalPalindrome_Recursive, TestSAMPLE3, false, 0211);


SIMPLE_BENCHMARK(isActualBinaryPalindrome_Reverse, Sample1, 0b101);

SIMPLE_TEST(isActualBinaryPalindrome_Reverse, TestSAMPLE1, true, 0b101);
SIMPLE_TEST(isActualBinaryPalindrome_Reverse, TestSAMPLE2, true, 0b1001);
SIMPLE_TEST(isActualBinaryPalindrome_Reverse, TestSAMPLE3, false, 0b1011);


SIMPLE_BENCHMARK(isBinaryPalindrome, Sample1, 0b101);

SIMPLE_TEST(isBinaryPalindrome, TestSAMPLE1, false, 0b101);
SIMPLE_TEST(isBinaryPalindrome, TestSAMPLE2, true, -1);
SIMPLE_TEST(isBinaryPalindrome, TestSAMPLE3, true,
            (1 << (BitsNumber<unsigned> - 1)) + 1);
SIMPLE_TEST(isBinaryPalindrome, TestSAMPLE4, true,
            (1 << ((BitsNumber<unsigned> / 2) - 1)) + (1 << (BitsNumber<unsigned> / 2)));
SIMPLE_TEST(isBinaryPalindrome, TestSAMPLE5, false, 0b1011);
