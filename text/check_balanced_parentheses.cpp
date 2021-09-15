#include "common_header.h"


namespace {

/** Check for Balanced Brackets in an expression (well-formedness) using Stack
 *
 * @reference   https://www.geeksforgeeks.org/check-for-balanced-parentheses-in-an-expression/
 * @reference   Valid Parentheses
 *              https://leetcode.com/problems/valid-parentheses/
 *
 * Given an expression string exp, write a program to examine whether the pairs and the
 * orders of "{", "}", "(", ")", "[", "]" are correct in exp.
 */
auto AreBracketsBalanced_Stack(const std::string_view expression) {
    std::stack<char> brackets_stack;
    static const std::unordered_map<char, char> BRACKETS_MAP = {{')', '('}, {']', '['}, {'}', '{'}};

    for (const auto c : expression) {
        if (std::string_view{"([{"}.find(c) != std::string_view::npos)
            brackets_stack.push(c);
        else {
            if (brackets_stack.empty() or brackets_stack.top() != BRACKETS_MAP.at(c)) {
                return false;
            }
            brackets_stack.pop();
        }
    }

    return brackets_stack.empty();
}


/**
 * @reference   Check if given Parentheses expression is balanced or not
 *              https://www.geeksforgeeks.org/check-if-given-parentheses-expression-is-balanced-or-not/
 *
 * Given a string str of length N, consisting of '(' and ')' only, the task is to check
 * whether it is balanced or not.
 */
constexpr auto AreParenthesesBalanced(const std::string_view expression) {
    int count = 0;
    for (const auto c : expression) {
        if (c == '(') {
            ++count;
        } else {
            if (--count < 0) {
                return false;
            }
        }
    }

    return count == 0;
}


/**
 * @reference   Remove Outermost Parentheses
 *              https://leetcode.com/problems/remove-outermost-parentheses/
 *
 * A valid parentheses string is either empty "", "(" + A + ")", or A + B, where A and B
 * are valid parentheses strings, and + represents string concatenation. For example, "",
 * "()", "(())()", and "(()(()))" are all valid parentheses strings. A valid parentheses
 * string s is primitive if it is nonempty, and there does not exist a way to split it
 * into s = A + B, with A and B nonempty valid parentheses strings. Given a valid
 * parentheses string s, consider its primitive decomposition: s = P1 + P2 + ... + Pk,
 * where Pi are primitive valid parentheses strings. Return s after removing the
 * outermost parentheses of every primitive string in the primitive decomposition of s.
 */
auto RemoveOuterParentheses(const std::string_view s) {
    std::string result;
    int open = 0;
    for (const auto c : s) {
        if (c == '(') {
            if (open++ != 0) {
                result.push_back(c);
            }
        } else {
            if (open-- != 1) {
                result.push_back(c);
            }
        }
    }

    return result;
}

}//namespace


THE_BENCHMARK(AreBracketsBalanced_Stack, "[()]{}{[()()]()}");

SIMPLE_TEST(AreBracketsBalanced_Stack, TestSAMPLE1, true, "[()]{}{[()()]()}");
SIMPLE_TEST(AreBracketsBalanced_Stack, TestSAMPLE2, false, "[(])");
SIMPLE_TEST(AreBracketsBalanced_Stack, TestSAMPLE3, true, "((()))()()");
SIMPLE_TEST(AreBracketsBalanced_Stack, TestSAMPLE4, false, "())((())");


THE_BENCHMARK(AreParenthesesBalanced, "((()))()()");

SIMPLE_TEST(AreParenthesesBalanced, TestSAMPLE3, true, "((()))()()");
SIMPLE_TEST(AreParenthesesBalanced, TestSAMPLE4, false, "())((())");


THE_BENCHMARK(RemoveOuterParentheses, "(()())(())");

SIMPLE_TEST(RemoveOuterParentheses, TestSAMPLE1, "()()()", "(()())(())");
SIMPLE_TEST(RemoveOuterParentheses, TestSAMPLE2, "()()()()(())", "(()())(())(()(()))");
SIMPLE_TEST(RemoveOuterParentheses, TestSAMPLE3, "", "()()");
