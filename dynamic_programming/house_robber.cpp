#include "common_header.h"

#include "data_structure/tree/binary_tree/binary_tree.h"
#include "data_structure/tree/binary_tree/single_order_to_binary_tree.h"


namespace {

using ArrayType = std::vector<int>;

/** House Robber
 *
 * @reference   https://leetcode.com/problems/house-robber/
 *
 * You are a professional robber planning to rob houses along a street. Each house has a
 * certain amount of money stashed, the only constraint stopping you from robbing each of
 * them is that adjacent houses have security systems connected and it will automatically
 * contact the police if two adjacent houses were broken into on the same night. Given an
 * integer array nums representing the amount of money of each house, return the maximum
 * amount of money you can rob tonight without alerting the police.
 */
auto HouseRobber_Memo(const ArrayType &nums, const int i, ArrayType &memo) {
    if (i < 0) {
        return 0;
    }

    if (memo[i] >= 0) {
        return memo[i];
    }

    return memo[i] = std::max(HouseRobber_Memo(nums, i - 2, memo) + nums[i],
                              HouseRobber_Memo(nums, i - 1, memo));
}

inline auto HouseRobber_Memo(const ArrayType &nums) {
    ArrayType memo(nums.size(), -1);
    return HouseRobber_Memo(nums, nums.size() - 1, memo);
}


auto HouseRobber_DP(const ArrayType &nums) {
    int dp[nums.size() + 1] = {0, nums.front()};

    for (std::size_t i = 1; i < nums.size(); ++i) {
        dp[i + 1] = std::max(dp[i], dp[i - 1] + nums[i]);
    }

    return dp[nums.size()];
}


auto HouseRobber_DP_O1(const ArrayType &nums) {
    int prev1 = 0;
    int prev2 = 0;
    for (const auto n : nums) {
        const auto tmp = prev1;
        prev1 = std::max(prev2 + n, prev1);
        prev2 = tmp;
    }

    return prev1;
}


/**
 * @reference   Min Cost Climbing Stairs
 *              https://leetcode.com/problems/min-cost-climbing-stairs/
 *
 * You are given an integer array cost where cost[i] is the cost of ith step on a
 * staircase. Once you pay the cost, you can either climb one or two steps. You can
 * either start from the step with index 0, or the step with index 1. Return the
 * minimum cost to reach the top of the floor.
 * 2 <= cost.length <= 1000
 */
auto MinCostClimbingStairs(const ArrayType &cost) {
    assert(cost.size() >= 2);

    int a = 0;
    int b = 0;

    for (const auto a_cost : cost) {
        const auto c = a_cost + std::min(a, b);
        a = b;
        b = c;
    }

    return std::min(a, b);
}


/**
 * @reference   House Robber II
 *              https://leetcode.com/problems/house-robber-ii/
 *
 * You are a professional robber planning to rob houses along a street. Each house has a
 * certain amount of money stashed. All houses at this place are arranged in a circle.
 * That means the first house is the neighbor of the last one. Meanwhile, adjacent houses
 * have a security system connected, and it will automatically contact the police if two
 * adjacent houses were broken into on the same night. Given an integer array nums
 * representing the amount of money of each house, return the maximum amount of money you
 * can rob tonight without alerting the police.
 */
auto HouseRobber_Circle(const ArrayType &nums,
                        const int left, const int right) {
    int prev1 = 0;
    int prev2 = 0;
    for (int i = left; i <= right; ++i) {
        const auto tmp = prev1;
        prev1 = std::max(prev2 + nums[i], prev1);
        prev2 = tmp;
    }

    return prev1;
}

inline auto HouseRobber_Circle(const ArrayType &nums) {
    if (nums.size() == 1) {
        return nums.front();
    }

    return std::max(HouseRobber_Circle(nums, 0, nums.size() - 2),
                    HouseRobber_Circle(nums, 1, nums.size() - 1));
}


/**
 * @reference   House Robber III
 *              https://leetcode.com/problems/house-robber-iii/
 *
 * The thief has found himself a new place for his thievery again. There is only one
 * entrance to this area, called root. Besides the root, each house has one and only one
 * parent house. After a tour, the smart thief realized that all houses in this place
 * form a binary tree. It will automatically contact the police if two directly-linked
 * houses were broken into on the same night. Given the root of the binary tree, return
 * the maximum amount of money the thief can rob without alerting the police.
 */
auto HouseRobber_Tree_Pair_Helper(const BinaryTree::Node::PointerType node) {
    if (not node) {
        return std::pair{0, 0};
    }

    const auto [left_with, left_without] = HouseRobber_Tree_Pair_Helper(node->left);
    const auto [right_with, right_without] = HouseRobber_Tree_Pair_Helper(node->right);

    return std::pair(node->value + left_without + right_without,
                     std::max(left_with, left_without) + std::max(right_with, right_without));
}

inline auto HouseRobber_Tree_Pair(const BinaryTree::Node::PointerType root) {
    const auto [with, without] = HouseRobber_Tree_Pair_Helper(root);
    return std::max(with, without);
}


auto HouseRobber_BT_Helper(const BinaryTree::Node::PointerType node,
                           int &left, int &right) {
    if (not node) {
        return 0;
    }

    int left_left = 0;
    int left_right = 0;
    int right_left = 0;
    int right_right = 0;

    left = HouseRobber_BT_Helper(node->left, left_left, left_right);
    right = HouseRobber_BT_Helper(node->right, right_left, right_right);

    return std::max(node->value + left_left + left_right + right_left + right_right,
                    left + right);
}

inline auto HouseRobber_BT(const BinaryTree::Node::PointerType root) {
    int left = 0;
    int right = 0;
    return HouseRobber_BT_Helper(root, left, right);
}

}//namespace


const ArrayType SAMPLE1 = {1, 2, 3, 1};
const ArrayType SAMPLE2 = {2, 7, 9, 3, 1};


THE_BENCHMARK(HouseRobber_Memo, SAMPLE1);

SIMPLE_TEST(HouseRobber_Memo, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(HouseRobber_Memo, TestSAMPLE2, 12, SAMPLE2);


THE_BENCHMARK(HouseRobber_DP, SAMPLE1);

SIMPLE_TEST(HouseRobber_DP, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(HouseRobber_DP, TestSAMPLE2, 12, SAMPLE2);


THE_BENCHMARK(HouseRobber_DP_O1, SAMPLE1);

SIMPLE_TEST(HouseRobber_DP_O1, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(HouseRobber_DP_O1, TestSAMPLE2, 12, SAMPLE2);


const ArrayType SAMPLE3 = {2, 3, 2};
const ArrayType SAMPLE4 = {1, 2, 3};


THE_BENCHMARK(HouseRobber_Circle, SAMPLE3);

SIMPLE_TEST(HouseRobber_Circle, TestSAMPLE3, 3, SAMPLE3);
SIMPLE_TEST(HouseRobber_Circle, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(HouseRobber_Circle, TestSAMPLE4, 3, SAMPLE4);


const ArrayType SAMPLE1C = {10, 15, 20};
const ArrayType SAMPLE2C = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};


THE_BENCHMARK(MinCostClimbingStairs, SAMPLE1C);

SIMPLE_TEST(MinCostClimbingStairs, TestSAMPLE1, 15, SAMPLE1C);
SIMPLE_TEST(MinCostClimbingStairs, TestSAMPLE2, 6, SAMPLE2C);


/**
 *      3
 *     / \
 *    2   3
 *     \   \
 *      3   1
 */
const auto SAMPLE1T = LevelOrderToBinaryTree( {
    3, 2, 3, SENTINEL, 3, SENTINEL, 1
});


THE_BENCHMARK(HouseRobber_Tree_Pair, SAMPLE1T);

SIMPLE_TEST(HouseRobber_Tree_Pair, TestSAMPLE1, 7, SAMPLE1T);


THE_BENCHMARK(HouseRobber_BT, SAMPLE1T);

SIMPLE_TEST(HouseRobber_BT, TestSAMPLE1, 7, SAMPLE1T);
