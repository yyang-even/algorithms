#include "common_header.h"


namespace {

/**
 * @reference   Fraction to Recurring Decimal
 *              https://leetcode.com/problems/fraction-to-recurring-decimal/
 *
 * Given two integers representing the numerator and denominator of a fraction, return the fraction in
 * string format.
 * If the fractional part is repeating, enclose the repeating part in parentheses.
 * If multiple answers are possible, return any of them.
 * It is guaranteed that the length of the answer string is less than 104 for all the given inputs.
 *
 * @tags    #hash-table #division
 */
std::string FractionToRecurringDecimal(long numerator, long denominator) {
    if (numerator == 0) {
        return "0";
    }

    std::string result;
    const auto is_negative = (numerator < 0) ^ (denominator < 0);
    if (is_negative) {
        result.push_back('-');
    }

    numerator = std::abs(numerator);
    denominator = std::abs(denominator);

    result.append(std::to_string(numerator / denominator));

    auto remainder = numerator % denominator;
    if (remainder == 0) {
        return result;
    }

    result.push_back('.');

    std::unordered_map<long, int> seen_remainders;
    while (remainder) {
        const auto [iter, inserted] = seen_remainders.emplace(remainder, result.size());
        if (not inserted) {
            result.insert(iter->second, "(");
            result.push_back(')');
            break;
        }

        remainder *= 10;
        result.push_back('0' + (remainder / denominator));
        remainder %= denominator;
    }

    return result;
}

} //namespace


THE_BENCHMARK(FractionToRecurringDecimal, 4, 333);

SIMPLE_TEST(FractionToRecurringDecimal, TestSAMPLE1, "0.5", 1, 2);
SIMPLE_TEST(FractionToRecurringDecimal, TestSAMPLE2, "2", 2, 1);
SIMPLE_TEST(FractionToRecurringDecimal, TestSAMPLE3, "0.(012)", 4, 333);
SIMPLE_TEST(FractionToRecurringDecimal, TestSAMPLE4, "0.1(6)", 1, 6);
