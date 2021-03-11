#include "common_header.h"


namespace {

/** Check for Balanced Brackets in an expression (well-formedness) using Stack
 *
 * @reference   https://www.geeksforgeeks.org/check-for-balanced-parentheses-in-an-expression/
 *
 * Given an expression string exp, write a program to examine whether the pairs and the
 * orders of "{", "}", "(", ")", "[", "]" are correct in exp.
 */
auto AreBracketsBalanced_Stack(const std::string &expression) {
    std::stack<char> brackets_stack;
    static const std::unordered_map<char, char> BRACKETS_MAP = {{')', '('}, {']', '['}, {'}', '{'}};

    for (const auto c : expression) {
        if (std::string{"([{"}.find(c) != std::string::npos)
            brackets_stack.push(c);
        else {
            if (brackets_stack.empty()) {
                return false;
            }

            if (brackets_stack.top() != BRACKETS_MAP.at(c)) {
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
auto AreParenthesesBalanced(const std::string &expression) {
    int count = 0;
    for (const auto c : expression) {
        if (c == '(') {
            ++count;
        } else {
            --count;
        }
        if (count < 0) {
            return false;
        }
    }

    return count == 0;
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
