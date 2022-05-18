#include "common_header.h"


namespace {

/** Check for Balanced Brackets in an expression (well-formedness) using Stack
 *
 * @reference   https://www.geeksforgeeks.org/check-for-balanced-parentheses-in-an-expression/
 * @reference   Valid Parentheses
 *              https://leetcode.com/problems/valid-parentheses/
 *
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if
 * the input string is valid.
 * An input string is valid if:
 *  Open brackets must be closed by the same type of brackets.
 *  Open brackets must be closed in the correct order.
 */
auto AreBracketsBalanced_Stack(const std::string_view expression) {
    std::stack<char> brackets_stack;
    static const std::unordered_map<char, char> BRACKETS_MAP = {
        {')', '('}, {']', '['}, {'}', '{'}};

    for (const auto c : expression) {
        if (std::string_view {"([{"}.find(c) != std::string_view::npos)
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
 * Given a string str of length N, consisting of '(' and ')' only, the task is to check whether
 * it is balanced or not.
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
 * A valid parentheses string is either empty "", "(" + A + ")", or A + B, where A and B are
 * valid parentheses strings, and + represents string concatenation.
 *  For example, "", "()", "(())()", and "(()(()))" are all valid parentheses strings.
 * A valid parentheses string s is primitive if it is nonempty, and there does not exist a way
 * to split it into s = A + B, with A and B nonempty valid parentheses strings.
 * Given a valid parentheses string s, consider its primitive decomposition:
 * s = P1 + P2 + ... + Pk, where Pi are primitive valid parentheses strings.
 * Return s after removing the outermost parentheses of every primitive string in the primitive
 * decomposition of s.
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


/**
 * @reference   Minimum Remove to Make Valid Parentheses
 *              https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/
 *
 * Given a string s of '(' , ')' and lowercase English characters.
 * Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions ) so
 * that the resulting parentheses string is valid and return any valid string.
 * Formally, a parentheses string is valid if and only if:
 *  It is the empty string, contains only lowercase characters, or
 *  It can be written as AB (A concatenated with B), where A and B are valid strings, or
 *  It can be written as (A), where A is a valid string.
 */
auto MakeValidParentheses_Stack(std::string s) {
    std::stack<std::size_t> opens;
    for (std::size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '(') {
            opens.push(i);
        } else if (s[i] == ')') {
            if (not opens.empty()) {
                opens.pop();
            } else {
                s[i] = '*';
            }
        }
    }

    while (not opens.empty()) {
        s[opens.top()] = '*';
        opens.pop();
    }

    s.erase(std::remove(s.begin(), s.end(), '*'), s.end());
    return s;
}


/**
 * @reference   Score of Parentheses
 *              https://leetcode.com/problems/score-of-parentheses/
 *
 * Given a balanced parentheses string s, return the score of the string.
 *
 * The score of a balanced parentheses string is based on the following rule:
 *  "()" has score 1.
 *  AB has score A + B, where A and B are balanced parentheses strings.
 *  (A) has score 2 * A, where A is a balanced parentheses string.
 */
auto ScoreOfParentheses_Stack(const std::string_view s) {
    std::stack<int> scores;
    scores.push(0);

    for (const auto c : s) {
        if (c == '(') {
            scores.push(0);
        } else {
            const auto curr = scores.top();
            scores.pop();
            scores.top() += std::max(curr * 2, 1);
        }
    }

    return scores.top();
}


constexpr auto ScoreOfParentheses(const std::string_view s) {
    int result = 0;
    int open = 0;
    for (std::size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '(') {
            ++open;
        } else {
            --open;
            if (s[i - 1] == '(') {
                result += 1 << open;
            }
        }
    }

    return result;
}

} //namespace


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


THE_BENCHMARK(MakeValidParentheses_Stack, "lee(t(c)o)de)");

SIMPLE_TEST(MakeValidParentheses_Stack, TestSAMPLE1, "lee(t(c)o)de", "lee(t(c)o)de)");
SIMPLE_TEST(MakeValidParentheses_Stack, TestSAMPLE2, "ab(c)d", "a)b(c)d");
SIMPLE_TEST(MakeValidParentheses_Stack, TestSAMPLE3, "", "))((");
SIMPLE_TEST(MakeValidParentheses_Stack, TestSAMPLE4, "a(b(c)d)", "(a(b(c)d)");
SIMPLE_TEST(MakeValidParentheses_Stack, TestSAMPLE5, "()()", "())()(((");


THE_BENCHMARK(ScoreOfParentheses_Stack, "(()(()))");

SIMPLE_TEST(ScoreOfParentheses_Stack, TestSAMPLE1, 6, "(()(()))");
SIMPLE_TEST(ScoreOfParentheses_Stack, TestSAMPLE2, 1, "()");
SIMPLE_TEST(ScoreOfParentheses_Stack, TestSAMPLE3, 2, "(())");
SIMPLE_TEST(ScoreOfParentheses_Stack, TestSAMPLE4, 2, "()()");


THE_BENCHMARK(ScoreOfParentheses, "(()(()))");

SIMPLE_TEST(ScoreOfParentheses, TestSAMPLE1, 6, "(()(()))");
SIMPLE_TEST(ScoreOfParentheses, TestSAMPLE2, 1, "()");
SIMPLE_TEST(ScoreOfParentheses, TestSAMPLE3, 2, "(())");
SIMPLE_TEST(ScoreOfParentheses, TestSAMPLE4, 2, "()()");
