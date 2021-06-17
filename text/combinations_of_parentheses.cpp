#include "common_header.h"


namespace {

using ArrayType = std::unordered_multiset<std::string>;

/** Print all combinations of balanced parentheses
 *
 * @reference   https://www.geeksforgeeks.org/print-all-combinations-of-balanced-parentheses/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 9.6.
 * @reference   Generate Parentheses
 *              https://leetcode.com/problems/generate-parentheses/
 */
void CombinationsOfParentheses(const unsigned number_pairs,
                               const unsigned count_open, const unsigned count_close,
                               std::string &one_combination, ArrayType &results) {
    if (count_close == number_pairs) {
        results.insert(one_combination);
        return;
    }

    if (count_open > count_close) {
        one_combination.push_back('}');
        CombinationsOfParentheses(number_pairs, count_open, count_close + 1,
                                  one_combination, results);
        one_combination.pop_back();
    }

    if (count_open < number_pairs) {
        one_combination.push_back('{');
        CombinationsOfParentheses(number_pairs, count_open + 1, count_close,
                                  one_combination, results);
        one_combination.pop_back();
    }
}

inline auto CombinationsOfParentheses(const unsigned number_pairs) {
    assert(number_pairs != 0);

    std::string one_combination;
    ArrayType results;
    CombinationsOfParentheses(number_pairs, 0, 0, one_combination, results);

    return results;
}

}//namespace


const ArrayType EXPECTED1 = {"{}"};
const ArrayType EXPECTED2 = {"{}{}", "{{}}"};
const ArrayType EXPECTED3 = {"{}{}{}", "{}{{}}", "{{}}{}", "{{}{}}", "{{{}}}"};


THE_BENCHMARK(CombinationsOfParentheses, 4);

SIMPLE_TEST(CombinationsOfParentheses, TestSAMPLE1, EXPECTED1, 1);
SIMPLE_TEST(CombinationsOfParentheses, TestSAMPLE2, EXPECTED2, 2);
SIMPLE_TEST(CombinationsOfParentheses, TestSAMPLE3, EXPECTED3, 3);
