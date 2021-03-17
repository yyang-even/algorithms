#include "common_header.h"


namespace {

using MemoType = std::vector<std::vector<std::vector<int>>>;

/** Boolean Parenthesization Problem | DP-37
 *
 * @reference   https://www.geeksforgeeks.org/boolean-parenthesization-problem-dp-37/
 *
 * Count the number of ways we can parenthesize the expression so that the value of
 * expression evaluates to true.
 */
auto BooleanParenthesization_DP(const std::string &symbols,
                                const std::string &operators) {
    assert(symbols.size() == operators.size() + 1);

    auto false_table = std::vector(symbols.size(), std::vector(symbols.size(), 0));
    auto true_table = std::vector(symbols.size(), std::vector(symbols.size(), 0));

    for (std::size_t i = 0; i < symbols.size(); ++i) {
        false_table[i][i] = (symbols[i] == 'F');
        true_table[i][i] = not false_table[i][i];
    }

    for (std::size_t gap = 1; gap < symbols.size(); ++gap) {
        for (std::size_t i = 0, j = gap; j < symbols.size(); ++i, ++j) {
            for (std::size_t g = 0; g < gap; ++g) {
                const auto k = i + g;

                const auto total_i_k = true_table[i][k] + false_table[i][k];
                const auto total_k_j = true_table[k + 1][j] + false_table[k + 1][j];

                if (operators[k] == '&') {
                    true_table[i][j] += true_table[i][k] * true_table[k + 1][j];
                    false_table[i][j] += (total_i_k * total_k_j - true_table[i][k] * true_table[k + 1][j]);
                }
                if (operators[k] == '|') {
                    false_table[i][j] += false_table[i][k] * false_table[k + 1][j];
                    true_table[i][j] += (total_i_k * total_k_j - false_table[i][k] * false_table[k + 1][j]);
                }
                if (operators[k] == '^') {
                    true_table[i][j] += false_table[i][k] * true_table[k + 1][j] +
                                        true_table[i][k] * false_table[k + 1][j];
                    false_table[i][j] += true_table[i][k] * true_table[k + 1][j] +
                                         false_table[i][k] * false_table[k + 1][j];
                }
            }
        }
    }

    return true_table[0][symbols.size() - 1];
}


/**
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 9.11.
 *
 * Given a boolean expression consisting of the symbols 0, 1, &, |, and ^, and a desired
 * boolean result value result, implement a function to count the number of ways of
 * parenthesizing the expression such that it evaluates to result.
 */
int BooleanParenthesization_Memoization(const std::string &expression,
                                        const bool expected_true,
                                        const int i, const int j,
                                        MemoType &memo) {
    if (i > j) {
        return false;
    }

    if (i == j) {
        if (expected_true) {
            return expression[i] == 'T';
        } else {
            return expression[i] == 'F';
        }
    }

    if (memo[i][j][expected_true] != -1) {
        return memo[i][j][expected_true];
    }

    int result = 0;
    for (auto k = i + 1; k <= j - 1; k = k + 2) {
        int leftF, leftT, rightT, rightF;
        if (memo[i][k - 1][1] == -1) {
            leftT = BooleanParenthesization_Memoization(expression, true, i, k - 1, memo);
        } else {
            leftT = memo[i][k - 1][1];
        }

        if (memo[k + 1][j][1] == -1) {
            rightT = BooleanParenthesization_Memoization(expression, true, k + 1, j, memo);
        } else {
            rightT = memo[k + 1][j][1];
        }

        if (memo[i][k - 1][0] == -1) {
            leftF = BooleanParenthesization_Memoization(expression, false, i, k - 1, memo);
        } else {
            leftF = memo[i][k - 1][0];
        }

        if (memo[k + 1][j][0] == -1) {
            rightF = BooleanParenthesization_Memoization(expression, false, k + 1, j, memo);
        } else {
            rightF = memo[k + 1][j][0];
        }

        if (expression[k] == '&') {
            if (expected_true) {
                result += leftT * rightT;
            } else {
                result += leftF * rightF + leftT * rightF + leftF * rightT;
            }
        } else if (expression[k] == '|') {
            if (expected_true) {
                result += leftT * rightT + leftT * rightF + leftF * rightT;
            } else {
                result = result + leftF * rightF;
            }
        } else if (expression[k] == '^') {
            if (expected_true) {
                result = result + leftF * rightT + leftT * rightF;
            } else {
                result = result + leftT * rightT + leftF * rightF;
            }
        }
        memo[i][j][expected_true] = result;
    }

    return result;
}

auto BooleanParenthesization_Memoization(const std::string &expression) {
    auto memo = std::vector(expression.size(),
                            std::vector(expression.size(), std::vector(2, -1)));
    return BooleanParenthesization_Memoization(expression, true,
                                               0, expression.size() - 1, memo);
}

}//namespace


THE_BENCHMARK(BooleanParenthesization_DP, "TFT", "^&");

SIMPLE_TEST(BooleanParenthesization_DP, TestSAMPLE1, 2, "TFT", "^&");
SIMPLE_TEST(BooleanParenthesization_DP, TestSAMPLE2, 2, "TFF", "^|");
SIMPLE_TEST(BooleanParenthesization_DP, TestSAMPLE3, 4, "TTFT", "|&^");


THE_BENCHMARK(BooleanParenthesization_Memoization, "T^F&T");

SIMPLE_TEST(BooleanParenthesization_Memoization, TestSAMPLE1, 2, "T^F&T");
SIMPLE_TEST(BooleanParenthesization_Memoization, TestSAMPLE2, 2, "T^F|F");
SIMPLE_TEST(BooleanParenthesization_Memoization, TestSAMPLE3, 4, "T|T&F^T");
