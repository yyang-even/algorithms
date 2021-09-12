#include "common_header.h"


namespace {

/** Basic Calculator
 *
 * @reference   https://leetcode.com/problems/basic-calculator/
 *
 * Given a string s representing a valid expression, implement a basic calculator to
 * evaluate it, and return the result of the evaluation. Note: You are not allowed to
 * use any built-in function which evaluates strings as mathematical expressions, such
 * as eval().
 * s consists of digits, '+', '-', '(', ')', and ' '.
 * s represents a valid expression.
 */
auto Calculator_Stack(const std::string_view expression) {
    int result = 0, sign = 1;
    std::stack<std::pair<int, int>> s;
    for (std::size_t i = 0; i < expression.size(); ++i) {
        const char c = expression[i];
        if (std::isdigit(c)) {
            int num = 0;
            while (i < expression.size() and std::isdigit(expression[i])) {
                num = 10 * num + (expression[i++] - '0');
            }
            result += sign * num;
            --i;
        } else if (c == '+') {
            sign = 1;
        } else if (c == '-') {
            sign = -1;
        } else if (c == '(') {
            s.emplace(result, sign);
            result = 0;
            sign = 1;
        } else if (c == ')') {
            const auto [prev_result, prev_sign] = s.top();
            s.pop();
            result = prev_result + prev_sign * result;
        }
    }

    return result;
}


/**
 * @reference   Basic Calculator II
 *              https://leetcode.com/problems/basic-calculator-ii/
 *
 * Given a string s which represents an expression, evaluate this expression and return
 * its value. The integer division should truncate toward zero. You may assume that the
 * given expression is always valid. All intermediate results will be in the range of
 * [-2^31, 2^31 - 1]. Note: You are not allowed to use any built-in function which
 * evaluates strings as mathematical expressions, such as eval().
 * s consists of integers and operators ('+', '-', '*', '/') separated by some number of
 * spaces.
 * s represents a valid expression.
 */
auto Calculator2_Stack(const std::string_view expression) {
    std::stack<int> s;
    int num = 0;
    char operation = '+';
    for (std::size_t i = 0; i < expression.size(); ++i) {
        const auto c = expression[i];
        if (std::isdigit(c)) {
            num = (num * 10) + (c - '0');
        }
        if ((not std::isdigit(c) and c != ' ') or i + 1 == expression.size()) {
            if (operation == '-') {
                s.push(-num);
            } else if (operation == '+') {
                s.push(num);
            } else if (operation == '*') {
                const auto answer = s.top() * num;
                s.pop();
                s.push(answer);
            } else if (operation == '/') {
                const auto answer = s.top() / num;
                s.pop();
                s.push(answer);
            }
            operation = c;
            num = 0;
        }
    }

    int result = 0;
    while (not s.empty()) {
        result += s.top();
        s.pop();
    }

    return result;
}


constexpr auto Calculator2(const std::string_view expression) {
    int current = 0, prev = 0, result = 0;
    char operation = '+';
    for (std::size_t i = 0; i < expression.size(); ++i) {
        const auto c = expression[i];
        if (std::isdigit(c)) {
            current = (current * 10) + (c - '0');
        }
        if ((not std::isdigit(c) and c != ' ') or i + 1 == expression.size()) {
            if (operation == '+' or operation == '-') {
                result += prev;
                prev = (operation == '+') ? current : -current;
            } else if (operation == '*') {
                prev *= current;
            } else if (operation == '/') {
                prev /= current;
            }
            operation = c;
            current = 0;
        }
    }

    result += prev;

    return result;
}


/**
 * @reference   Basic Calculator III
 *              https://github.com/grandyang/leetcode/issues/772
 *
 * Implement a basic calculator to evaluate a simple expression string. The expression
 * string may contain open ( and closing parentheses ), the plus + or minus sign -,
 * non-negative integers and empty spaces ' '. The expression string contains only
 * non-negative integers, +, -, *, / operators , open ( and closing parentheses ) and
 * empty spaces ' '. The integer division should truncate toward zero. You may assume
 * that the given expression is always valid. All intermediate results will be in the
 * range of [-2147483648, 2147483647].
 * Note: Do not use the eval built-in library function.
 */
constexpr int Calculator3(const std::string_view expression) {
    int num = 0, curRes = 0, result = 0;
    char operation = '+';
    for (std::size_t i = 0; i < expression.size(); ++i) {
        const char c = expression[i];
        if (std::isdigit(c)) {
            num = num * 10 + c - '0';
        } else if (c == '(') {
            const auto j = i;
            for (int count = 0; i < expression.size(); ++i) {
                if (expression[i] == '(') {
                    ++count;
                }
                if (expression[i] == ')') {
                    if (count-- == 1) {
                        break;
                    }
                }
            }
            num = Calculator3(expression.substr(j + 1, i - j - 1));
        }
        if (c == '+' or c == '-' or c == '*' or c == '/' or i + 1 == expression.size()) {
            switch (operation) {
                case '+':
                    curRes += num;
                    break;
                case '-':
                    curRes -= num;
                    break;
                case '*':
                    curRes *= num;
                    break;
                case '/':
                    curRes /= num;
                    break;
            }
            if (c == '+' or c == '-' or i + 1 == expression.size()) {
                result += curRes;
                curRes = 0;
            }
            operation = c;
            num = 0;
        }
    }

    return result;
}

}//namespace


THE_BENCHMARK(Calculator_Stack, "(1+(4+5+2)-3)+(6+8)");

SIMPLE_TEST(Calculator_Stack, TestSAMPLE1, 2, "1 + 1");
SIMPLE_TEST(Calculator_Stack, TestSAMPLE2, 3, " 2-1 + 2 ");
SIMPLE_TEST(Calculator_Stack, TestSAMPLE3, 23, "(1+(4+5+2)-3)+(6+8)");


THE_BENCHMARK(Calculator2_Stack, "(1+(4+5+2)-3)+(6+8)");

SIMPLE_TEST(Calculator2_Stack, TestSAMPLE1, 2, "1 + 1");
SIMPLE_TEST(Calculator2_Stack, TestSAMPLE2, 3, " 2-1 + 2 ");
SIMPLE_TEST(Calculator2_Stack, TestSAMPLE3, 7, "3+2*2");
SIMPLE_TEST(Calculator2_Stack, TestSAMPLE4, 1, "3/2");
SIMPLE_TEST(Calculator2_Stack, TestSAMPLE5, 5, " 3+5 / 2 ");


THE_BENCHMARK(Calculator2, "(1+(4+5+2)-3)+(6+8)");

SIMPLE_TEST(Calculator2, TestSAMPLE1, 2, "1 + 1");
SIMPLE_TEST(Calculator2, TestSAMPLE2, 3, " 2-1 + 2 ");
SIMPLE_TEST(Calculator2, TestSAMPLE3, 7, "3+2*2");
SIMPLE_TEST(Calculator2, TestSAMPLE4, 1, "3/2");
SIMPLE_TEST(Calculator2, TestSAMPLE5, 5, " 3+5 / 2 ");


THE_BENCHMARK(Calculator3, "(2+6* 3+5- (3*14/7+2)*5)+3");

SIMPLE_TEST(Calculator3, TestSAMPLE1, 2, "1 + 1");
SIMPLE_TEST(Calculator3, TestSAMPLE2, 3, " 2-1 + 2 ");
SIMPLE_TEST(Calculator3, TestSAMPLE3, 23, "(1+(4+5+2)-3)+(6+8)");
SIMPLE_TEST(Calculator3, TestSAMPLE4, 2, "1 + 1");
SIMPLE_TEST(Calculator3, TestSAMPLE5, 3, " 2-1 + 2 ");
SIMPLE_TEST(Calculator3, TestSAMPLE6, 7, "3+2*2");
SIMPLE_TEST(Calculator3, TestSAMPLE7, 1, "3/2");
SIMPLE_TEST(Calculator3, TestSAMPLE8, 5, " 3+5 / 2 ");
SIMPLE_TEST(Calculator3, TestSAMPLE9, 21, "2*(5+5*2)/3+(6/2+8)");
SIMPLE_TEST(Calculator3, TestSAMPLE10, -12, "(2+6* 3+5- (3*14/7+2)*5)+3");
