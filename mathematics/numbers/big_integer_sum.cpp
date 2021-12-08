#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;
using ListType = std::forward_list<int>;

/** Add two numbers represented by linked lists | Set 1
 *
 * @reference   https://www.geeksforgeeks.org/add-two-numbers-represented-by-linked-lists/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 2.5.
 *
 * Given two numbers represented by two lists, write a function that returns the sum
 * list. The sum list is list representation of the addition of two input numbers.
 * Note: Here the least significant digit is the first node of lists and the most
 * significant digit is the last node.
 *
 * @reference   Add Two Numbers
 *              https://leetcode.com/problems/add-two-numbers/
 *
 * You are given two non-empty linked lists representing two non-negative integers. The
 * digits are stored in reverse order, and each of their nodes contains a single digit.
 * Add the two numbers and return the sum as a linked list. You may assume the two
 * numbers do not contain any leading zero, except the number 0 itself.
 */
auto Sum_LeastFirst(const ListType &lhs, const ListType &rhs) {
    auto left_current = lhs.cbegin();
    auto right_current = rhs.cbegin();
    ListType result;
    auto result_before_end = result.cbefore_begin();
    ListType::value_type carry = 0;

    for (; left_current != lhs.cend() or right_current != rhs.cend();
         ++result_before_end) {
        const auto digit_sum = carry +
                               (left_current != lhs.cend() ? *left_current++ : 0) +
                               (right_current != rhs.cend() ? *right_current++ : 0);
        carry = digit_sum / 10;

        result.insert_after(result_before_end, digit_sum % 10);
    }

    if (carry) {
        result.insert_after(result_before_end, 1);
    }

    return result;
}


/** Add two numbers represented by linked lists | Set 2
 *
 * @reference   https://www.geeksforgeeks.org/sum-of-two-linked-lists/
 *
 * Given two numbers represented by two linked lists, write a function that returns the
 * sum list. The sum list is linked list representation of the addition of two input
 * numbers. It is not allowed to modify the lists. Also, not allowed to use explicit
 * extra space (Hint: Use Recursion).
 * Note: Here the most significant digit is the first node and the least significant
 * digit is the last node.
 *
 * @reference   Add Two Numbers II
 *              https://leetcode.com/problems/add-two-numbers-ii/
 *
 * You are given two non-empty linked lists representing two non-negative integers. The
 * most significant digit comes first and each of their nodes contains a single digit.
 * Add the two numbers and return the sum as a linked list. You may assume the two
 * numbers do not contain any leading zero, except the number 0 itself.
 * Follow up: Could you solve it without reversing the input lists?
 *
 * @reference   Add 1 to a number represented as linked list
 *              https://www.geeksforgeeks.org/add-1-number-represented-linked-list/
 */
auto sum_SameSize(const ListType &longer_list,
                  const ListType::const_iterator longer_current,
                  const ListType &shorter_list,
                  const ListType::const_iterator shorter_current,
                  int &carry) {
    assert(std::distance(longer_current, longer_list.cend()) ==
           std::distance(shorter_current, shorter_list.cend()));

    if (shorter_current == shorter_list.cend())
        return ListType{};

    auto result = sum_SameSize(longer_list, std::next(longer_current),
                               shorter_list, std::next(shorter_current), carry);

    const auto digit_sum = *longer_current + *shorter_current + carry;
    carry = digit_sum / 10;
    result.push_front(digit_sum % 10);

    return result;
}

inline void addCarryToRemaining(const ListType::const_iterator cbegin,
                                const ListType::const_iterator cend,
                                int &carry, ListType &result) {
    if (cbegin != cend) {
        addCarryToRemaining(std::next(cbegin), cend, carry, result);
        const auto digit_sum = *cbegin + carry;
        carry = digit_sum / 10;
        result.push_front(digit_sum % 10);
    }
}

auto Sum_MostFirst(const ListType &lhs, const ListType &rhs) {
    const int left_size = std::distance(lhs.cbegin(), lhs.cend());
    const int right_size = std::distance(rhs.cbegin(), rhs.cend());
    int diff = 0;
    const ListType *longer_list = nullptr;
    const ListType *shorter_list = nullptr;
    if (left_size < right_size) {
        diff = right_size - left_size;
        longer_list = &rhs;
        shorter_list = &lhs;
    } else {
        diff = left_size - right_size;
        longer_list = &lhs;
        shorter_list = &rhs;
    }
    const auto current = std::next(longer_list->cbegin(), diff);
    int carry = 0;
    auto result = sum_SameSize(*longer_list, current,
                               *shorter_list, shorter_list->cbegin(), carry);
    addCarryToRemaining(longer_list->cbegin(), current, carry, result);

    if (carry) {
        result.push_front(carry);
    }

    return result;
}


auto Sum_MostFirst_Stack(const ListType &lhs, const ListType &rhs) {
    std::stack<ListType::value_type> left_stack;
    for (const auto v : lhs) {
        left_stack.push(v);
    }

    std::stack<ListType::value_type> right_stack;
    for (const auto v : rhs) {
        right_stack.push(v);
    }

    ListType result;
    int carry = 0;
    while (not left_stack.empty() or not right_stack.empty()) {
        ListType::value_type left_digit = 0;
        if (not left_stack.empty()) {
            left_digit = left_stack.top();
            left_stack.pop();
        }

        ListType::value_type right_digit = 0;
        if (not right_stack.empty()) {
            right_digit = right_stack.top();
            right_stack.pop();
        }

        const auto digit_sum = left_digit + right_digit + carry;
        carry = digit_sum / 10;
        result.push_front(digit_sum % 10);
    }

    if (carry) {
        result.push_front(carry);
    }

    return result;
}


/**
 * @reference   Add Two Numbers Represented by Linked Lists | Set 3
 *              https://www.geeksforgeeks.org/add-two-numbers-represented-by-linked-lists-set-3/
 */
inline auto Sum_MostFirst_Reverse(ListType lhs, ListType rhs) {
    lhs.reverse();
    rhs.reverse();

    auto result = Sum_LeastFirst(lhs, rhs);
    result.reverse();

    return result;
}


/**
 * @reference   Program to add two binary strings
 *              https://www.geeksforgeeks.org/program-to-add-two-binary-strings/
 * @reference   Add Binary
 *              https://leetcode.com/problems/add-binary/
 *
 * Given two binary strings a and b, return their sum as a binary string.
 *
 * @reference   Add Strings
 *              https://leetcode.com/problems/add-strings/
 *
 * Given two non-negative integers, num1 and num2 represented as string, return the sum
 * of num1 and num2 as a string. You must solve the problem without using any built-in
 * library for handling large integers (such as BigInteger). You must also not convert
 * the inputs to integers directly.
 */
auto AddStrings(const std::string_view one, const std::string_view another) {
    std::string results;

    int carry = 0;
    int one_i = one.size() - 1;
    int another_i = another.size() - 1;
    while (one_i >= 0 or another_i >= 0) {
        const auto one_digit = one_i >= 0 ? one[one_i--] - '0' : 0;
        const auto another_digit = another_i >= 0 ? another[another_i--] - '0' : 0;
        const auto sum = one_digit + another_digit + carry;
        carry = sum / 10;
        results.push_back('0' + sum % 10);
    }

    if (carry != 0) {
        results.push_back('1');
    }

    std::reverse(results.begin(), results.end());
    return results;
}


/**
 * @reference   Add to Array-Form of Integer
 *              https://leetcode.com/problems/add-to-array-form-of-integer/
 *
 * The array-form of an integer num is an array representing its digits in left to right
 * order. For example, for num = 1321, the array form is [1,3,2,1]. Given num, the
 * array-form of an integer, and an integer k, return the array-form of the integer
 * num + k.
 * 1 <= k <= 10^4
 */
auto Add(const ArrayType &number, int k) {
    ArrayType result;
    for (int i = number.size() - 1; i >= 0 or k; --i) {
        if (i >= 0) {
            k += number[i];
        }
        result.push_back(k % 10);
        k /= 10;
    }

    std::reverse(result.begin(), result.end());
    return result;
}


/**
 * @reference   Plus One
 *              https://leetcode.com/problems/plus-one/
 *
 * Given a non-empty array of decimal digits representing a non-negative integer,
 * increment one to the integer. The digits are stored such that the most significant
 * digit is at the head of the list, and each element in the array contains a single
 * digit. You may assume the integer does not contain any leading zero, except the
 * number 0 itself.
 *
 * @reference   Add one to a number represented as linked list | Set 2
 *              https://www.geeksforgeeks.org/add-one-to-a-number-represented-as-linked-list-set-2/
 *
 * Hint: Count trailing 9s.
 */


/**
 * @reference   Convert Binary Number in a Linked List to Integer
 *              https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/
 *
 * Given head which is a reference node to a singly-linked list. The value of each node
 * in the linked list is either 0 or 1. The linked list holds the binary representation
 * of a number. Return the decimal value of the number in the linked list.
 */

}//namespace


const ListType SAMPLE_L1 = {5, 6, 3};
const ListType SAMPLE_R1 = {8, 4, 2};
const ListType EXPECTED_L1 = {3, 1, 6};
const ListType EXPECTED_M1 = {1, 4, 0, 5};

const ListType SAMPLE_L2 = {7, 5, 9, 4, 6};
const ListType SAMPLE_R2 = {8, 4};
const ListType EXPECTED_L2 = {5, 0, 0, 5, 6};

const ListType SAMPLE_L3 = {9, 9, 9};
const ListType SAMPLE_R3 = {1, 8};
const ListType EXPECTED_M3 = {1, 0, 1, 7};

const ListType SAMPLE_L4 = {5, 6, 7};
const ListType SAMPLE_R4 = {1, 8};
const ListType EXPECTED_M4 = {5, 8, 5};

const ListType SAMPLE_L5 = {2, 4, 3};
const ListType SAMPLE_R5 = {5, 6, 4};
const ListType EXPECTED_L5 = {7, 0, 8};

const ListType SAMPLE_L6 = {7, 2, 4, 3};
const ListType SAMPLE_R6 = {5, 6, 4};
const ListType EXPECTED_M6 = {7, 8, 0, 7};


THE_BENCHMARK(Sum_LeastFirst, SAMPLE_L1, SAMPLE_R1);

SIMPLE_TEST(Sum_LeastFirst, TestSAMPLE1, EXPECTED_L1, SAMPLE_L1, SAMPLE_R1);
SIMPLE_TEST(Sum_LeastFirst, TestSAMPLE2, EXPECTED_L2, SAMPLE_L2, SAMPLE_R2);
SIMPLE_TEST(Sum_LeastFirst, TestSAMPLE5, EXPECTED_L5, SAMPLE_L5, SAMPLE_R5);


THE_BENCHMARK(Sum_MostFirst, SAMPLE_L1, SAMPLE_R1);

SIMPLE_TEST(Sum_MostFirst, TestSAMPLE1, EXPECTED_M1, SAMPLE_L1, SAMPLE_R1);
SIMPLE_TEST(Sum_MostFirst, TestSAMPLE3, EXPECTED_M3, SAMPLE_L3, SAMPLE_R3);
SIMPLE_TEST(Sum_MostFirst, TestSAMPLE4, EXPECTED_M4, SAMPLE_L4, SAMPLE_R4);
SIMPLE_TEST(Sum_MostFirst, TestSAMPLE6, EXPECTED_M6, SAMPLE_L6, SAMPLE_R6);


THE_BENCHMARK(Sum_MostFirst_Stack, SAMPLE_L1, SAMPLE_R1);

SIMPLE_TEST(Sum_MostFirst_Stack, TestSAMPLE1, EXPECTED_M1, SAMPLE_L1, SAMPLE_R1);
SIMPLE_TEST(Sum_MostFirst_Stack, TestSAMPLE3, EXPECTED_M3, SAMPLE_L3, SAMPLE_R3);
SIMPLE_TEST(Sum_MostFirst_Stack, TestSAMPLE4, EXPECTED_M4, SAMPLE_L4, SAMPLE_R4);
SIMPLE_TEST(Sum_MostFirst_Stack, TestSAMPLE6, EXPECTED_M6, SAMPLE_L6, SAMPLE_R6);


THE_BENCHMARK(Sum_MostFirst_Reverse, SAMPLE_L1, SAMPLE_R1);

SIMPLE_TEST(Sum_MostFirst_Reverse, TestSAMPLE1, EXPECTED_M1, SAMPLE_L1, SAMPLE_R1);
SIMPLE_TEST(Sum_MostFirst_Reverse, TestSAMPLE3, EXPECTED_M3, SAMPLE_L3, SAMPLE_R3);
SIMPLE_TEST(Sum_MostFirst_Reverse, TestSAMPLE4, EXPECTED_M4, SAMPLE_L4, SAMPLE_R4);
SIMPLE_TEST(Sum_MostFirst_Reverse, TestSAMPLE6, EXPECTED_M6, SAMPLE_L6, SAMPLE_R6);


THE_BENCHMARK(AddStrings, "11", "123");

SIMPLE_TEST(AddStrings, TestSAMPLE1, "134", "11", "123");
SIMPLE_TEST(AddStrings, TestSAMPLE2, "533", "456", "77");
SIMPLE_TEST(AddStrings, TestSAMPLE3, "0", "0", "0");
SIMPLE_TEST(AddStrings, TestSAMPLE4, "10", "1", "9");


const ArrayType SAMPLE1 = {1, 2, 0, 0};
const ArrayType EXPECTED1 = {1, 2, 3, 4};

const ArrayType SAMPLE2 = {2, 7, 4};
const ArrayType EXPECTED2 = {4, 5, 5};

const ArrayType SAMPLE3 = {2, 1, 5};
const ArrayType EXPECTED3 = {1, 0, 2, 1};

const ArrayType SAMPLE4 = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
const ArrayType EXPECTED4 = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


THE_BENCHMARK(Add, SAMPLE1, 34);

SIMPLE_TEST(Add, TestSAMPLE1, EXPECTED1, SAMPLE1, 34);
SIMPLE_TEST(Add, TestSAMPLE2, EXPECTED2, SAMPLE2, 181);
SIMPLE_TEST(Add, TestSAMPLE3, EXPECTED3, SAMPLE3, 806);
SIMPLE_TEST(Add, TestSAMPLE4, EXPECTED4, SAMPLE4, 1);
