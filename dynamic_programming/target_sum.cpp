#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;
using MemoType = std::unordered_map<std::size_t, std::unordered_map<int, int>>;
using OutputType = std::unordered_multiset<std::string>;

/** Target Sum
 *
 * @reference   https://leetcode.com/problems/target-sum/
 *
 * You are given an integer array nums and an integer target. You want to build an
 * expression out of nums by adding one of the symbols '+' and '-' before each integer
 * in nums and then concatenate all the integers.
 *  For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and
 *  concatenate them to build the expression "+2-1".
 * Return the number of different expressions that you can build, which evaluates to
 * target.
 */
int
CountTargetSum_Memo(const ArrayType &nums, const std::size_t i,
                    const int target, MemoType &memo) {
    if (i == nums.size()) {
        return target == 0;
    } else {
        const auto [iter, inserted] = memo[i].emplace(target, 0);
        if (inserted)
            iter->second = CountTargetSum_Memo(nums, i + 1, target + nums[i], memo) +
                           CountTargetSum_Memo(nums, i + 1, target - nums[i], memo);

        return iter->second;
    }
}

inline auto CountTargetSum_Memo(const ArrayType &nums, const int target) {
    MemoType memo;
    return CountTargetSum_Memo(nums, 0, target, memo);
}


auto CountTargetSum_DP_2D(const ArrayType &nums, const int target) {
    const auto total = std::accumulate(nums.cbegin(), nums.cend(), 0);
    int dp[nums.size()][2 * total + 1] = {};
    dp[0][nums.front() + total] = 1;
    dp[0][-nums.front() + total] += 1;

    for (std::size_t i = 1; i < nums.size(); ++i) {
        for (auto sum = -total; sum <= total; ++sum) {
            if (dp[i - 1][sum + total] > 0) {
                dp[i][sum + nums[i] + total] += dp[i - 1][sum + total];
                dp[i][sum - nums[i] + total] += dp[i - 1][sum + total];
            }
        }
    }

    return std::abs(target) > total ? 0 : dp[nums.size() - 1][target + total];
}


auto CountTargetSum_DP_1D(const ArrayType &nums, const int target) {
    const auto total = std::accumulate(nums.cbegin(), nums.cend(), 0);
    std::vector dp(2 * total + 1, 0);
    dp[nums.front() + total] = 1;
    dp[-nums.front() + total] += 1;

    for (std::size_t i = 1; i < nums.size(); ++i) {
        std::vector temp(2 * total + 1, 0);
        for (auto sum = -total; sum <= total; ++sum) {
            if (dp[sum + total] > 0) {
                temp[sum + nums[i] + total] += dp[sum + total];
                temp[sum - nums[i] + total] += dp[sum + total];
            }
        }

        dp = temp;
    }

    return std::abs(target) > total ? 0 : dp[target + total];
}


/**
 * @reference   Expression Add Operators
 *              https://leetcode.com/problems/expression-add-operators/
 * @reference   https://www.cnblogs.com/grandyang/p/4814506.html
 *
 * Given a string num that contains only digits and an integer target, return all
 * possibilities to add the binary operators '+', '-', or '*' between the digits of num
 * so that the resultant expression evaluates to the target value.
 */
void
ExpressionAddOperators(const std::string_view num, const long target,
                       const long diff, const long current,
                       const std::string expression, OutputType &result) {
    if (num.size() == 0 and current == target) {
        result.insert(expression);
        return;
    }

    for (std::size_t i = 1; i <= num.size(); ++i) {
        const std::string operand_str{num.substr(0, i)};
        if (operand_str.size() > 1 and operand_str.front() == '0') {
            return;
        }
        const auto operand = std::stoll(operand_str);
        const auto next = num.substr(i);
        if (not expression.empty()) {
            ExpressionAddOperators(next, target, operand, current + operand,
                                   expression + "+" + operand_str, result);
            ExpressionAddOperators(next, target, -operand, current - operand,
                                   expression + "-" + operand_str, result);
            ExpressionAddOperators(next, target, diff * operand, (current - diff) + diff * operand,
                                   expression + "*" + operand_str, result);
        } else {
            ExpressionAddOperators(next, target, operand, operand, operand_str, result);
        }
    }
}

inline auto ExpressionAddOperators(const std::string_view num, const int target) {
    OutputType result;
    ExpressionAddOperators(num, target, 0, 0, "", result);
    return result;
}

}//namespace


const ArrayType SAMPLE1 = {1, 1, 1, 1, 1};
const ArrayType SAMPLE2 = {1};


THE_BENCHMARK(CountTargetSum_Memo, SAMPLE1, 3);

SIMPLE_TEST(CountTargetSum_Memo, TestSAMPLE1, 5, SAMPLE1, 3);
SIMPLE_TEST(CountTargetSum_Memo, TestSAMPLE2, 1, SAMPLE2, 1);


THE_BENCHMARK(CountTargetSum_DP_2D, SAMPLE1, 3);

SIMPLE_TEST(CountTargetSum_DP_2D, TestSAMPLE1, 5, SAMPLE1, 3);
SIMPLE_TEST(CountTargetSum_DP_2D, TestSAMPLE2, 1, SAMPLE2, 1);


THE_BENCHMARK(CountTargetSum_DP_1D, SAMPLE1, 3);

SIMPLE_TEST(CountTargetSum_DP_1D, TestSAMPLE1, 5, SAMPLE1, 3);
SIMPLE_TEST(CountTargetSum_DP_1D, TestSAMPLE2, 1, SAMPLE2, 1);


const OutputType EXPECTED1 = {"1+2+3", "1*2*3"};
const OutputType EXPECTED2 = {"2+3*2", "2*3+2"};
const OutputType EXPECTED3 = {"1*0+5", "10-5"};
const OutputType EXPECTED4 = {"0*0", "0+0", "0-0"};
const OutputType EXPECTED5 = {};

THE_BENCHMARK(ExpressionAddOperators, "123", 6);

SIMPLE_TEST(ExpressionAddOperators, TestSAMPLE1, EXPECTED1, "123", 6);
SIMPLE_TEST(ExpressionAddOperators, TestSAMPLE2, EXPECTED2, "232", 8);
SIMPLE_TEST(ExpressionAddOperators, TestSAMPLE3, EXPECTED3, "105", 5);
SIMPLE_TEST(ExpressionAddOperators, TestSAMPLE4, EXPECTED4, "00", 0);
SIMPLE_TEST(ExpressionAddOperators, TestSAMPLE5, EXPECTED5, "3456237490", 9191);
