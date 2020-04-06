#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;
using OutputType = std::vector<std::pair<ArrayType::size_type, ArrayType::size_type>>;

/** Word Wrap Problem
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 15.4-4.
 * @reference   Word Wrap Problem | DP-19
 *              https://www.geeksforgeeks.org/word-wrap-problem-dp-19/
 *
 * Given a sequence of words, and a limit on the number of characters that can be put in
 * one line (line width). Put line breaks in the given sequence such that the lines are
 * printed neatly. Assume that the length of each word is smaller than the line width.
 * The word processors like MS Word do task of placing line breaks. The idea is to have
 * balanced lines. In other words, not have few lines with lots of extra spaces and some
 * lines with small amount of extra spaces.
 * We wish to minimize the sum, over all lines except the last, of the cubes of the numbers
 * of extra space characters at the ends of lines.
 */
const auto INFINITE = std::numeric_limits<ArrayType::value_type>::max();

void GetWordWrapPairs(const ArrayType::size_type line_starts[], const unsigned line_end,
        OutputType &results) {
    if(line_starts[line_end] != 1)
        GetWordWrapPairs(line_starts, p[line_end] - 1, results);
    results.emplace_back(line_starts[line_end], line_end);
}

auto WordWrap(const ArrayType &word_lengths, const ArrayType::value_type M) {
    ArrayType::value_type extra_spaces[word_lengths.size() + 1][word_lengths.size() + 1] = {};
    for(ArrayType::size_type i = 1; i <= word_lengths.size(); ++i) {
        extra_spaces[i][i] = M - word_lengths[i-1];
        for(auto j = i + 1; j <= word_lengths.size(); ++j) {
            extra_spaces[i][j] = extra_spaces[i][j-1] - word_lengths[j-1] - 1;
        }
    }

    ArrayType::value_type line_costs[word_lengths.size() + 1][word_lengths.size() + 1] = {};
    for(ArrayType::size_type i = 1; i <= word_lengths.size(); ++i) {
        for(auto j = i; j <= word_lengths.size(); ++j) {
            if(extra_spaces[i][j] < 0) {
                line_costs[i][j] = INFINITE;
            } else if (j == word_lengths.size())
                line_costs[i][j] = 0;
            else
                line_costs[i][j] = extra_spaces[i][j] * extra_spaces[i][j] * extra_spaces[i][j];
        }
    }

    ArrayType::value_type total_costs[word_lengths.size() + 1] = {};
    ArrayType::size_type line_starts[word_lengths.size() + 1] = {};
    for(ArrayType::size_type j = 1; j <= word_lengths.size(); ++j) {
        total_costs[j] = INFINITE;
        for(ArrayType::size_type i = 1; i <= j; ++i) {
            if(total_costs[i-1] != INFINITE and line_costs[i][j] != INFINITE) {
                const auto cost = total_costs[i-1] + line_costs[i][j];
                if(cost < total_costs[j]) {
                    total_costs[j] = cost;
                    line_starts[j] = i;
                }
            }
        }
    }

OutputType results;
    GetWordWrapPairs(line_starts, word_lengths.size(), results);

    return results;
}

}//namespace


const ArrayType SAMPLE1 = {3, 2, 2, 5};
const OutputType EXPECTED1 = {{1,1}, {2,3}, {4,4}};


SIMPLE_BENCHMARK(WordWrap, SAMPLE1);

SIMPLE_TEST(WordWrap, TestSAMPLE1, EXPECTED1, SAMPLE1);
