#include "common_header.h"

#include "binary_search_tree.h"
#include "mathematics/arithmetics/polynomial/binomial_coefficient.h"


namespace {

using MemoType = std::unordered_map<int, int>;
using ArrayType = std::vector<BinaryTree::Node::PointerType>;

/** Unique Binary Search Trees
 *
 * @reference   https://leetcode.com/problems/unique-binary-search-trees/
 *
 * Given an integer n, return the number of structurally unique BST's (binary search trees) which has
 * exactly n nodes of unique values from 1 to n.
 * 1 <= n <= 19
 *
 * @reference   Program for nth Catalan Number
 *              https://www.geeksforgeeks.org/program-nth-catalan-number/
 * @reference   Applications of Catalan Numbers
 *              https://www.geeksforgeeks.org/applications-of-catalan-numbers/
 * @reference   Total number of possible Binary Search Trees using Catalan Number
 *              https://www.geeksforgeeks.org/total-number-of-possible-binary-search-trees-using-catalan-number/
 *
 * Catalan numbers are a sequence of natural numbers that occurs in many interesting counting problems
 * like following.
 *  Count the number of expressions containing n pairs of parentheses which are correctly matched. For n
 *      = 3, possible expressions are ((())), ()(()), ()()(), (())(), (()()).
 *  Count the number of possible Binary Search Trees with n keys
 *  Count the number of full binary trees (A rooted binary tree is full if every vertex has either two
 *      children or no children) with n+1 leaves.
 *  Given a number n, return the number of ways you can draw n chords in a circle with 2 x n points such
 *      that no 2 chords intersect.
 * The first few Catalan numbers for n = 0, 1, 2, 3, ... are 1, 1, 2, 5, 14, 42, 132, 429, 1430, 4862,
 * ...
 */
auto CountUniqueBST_Memo(const int n, MemoType &memo) {
    if (n <= 1) {
        return 1;
    }

    const auto [iter, inserted] = memo.emplace(n, 0);
    if (not inserted) {
        return iter->second;
    }

    int result = 0;
    for (int i = 0; i < n; ++i) {
        result += CountUniqueBST_Memo(i, memo) * CountUniqueBST_Memo(n - i - 1, memo);
    }

    return iter->second = result;
}

inline auto CountUniqueBST_Memo(const int n) {
    MemoType memo;
    return CountUniqueBST_Memo(n, memo);
}


constexpr auto CountUniqueBST_DP(const int n) {
    assert(n >= 1);

    int dp[n + 1] = {1, 1};
    for (int i = 2; i <= n; ++i) {
        int result = 0;
        for (int j = 0; j < i; ++j) {
            result += dp[j] * dp[i - j - 1];
        }
        dp[i] = result;
    }

    return dp[n];
}


inline constexpr auto CountUniqueBST_BC(const int n) {
    return BinomialCoefficient(2 * n, n) / (n + 1);
}


/**
 * @reference   Unique Binary Search Trees II
 *              https://leetcode.com/problems/unique-binary-search-trees-ii/
 *
 * Given an integer n, return all the structurally unique BST's (binary search trees), which has exactly
 * n nodes of unique values from 1 to n. Return the answer in any order.
 * 1 <= n <= 8
 *
 * @reference   Construct all possible BSTs for keys 1 to N
 *              https://www.geeksforgeeks.org/construct-all-possible-bsts-for-keys-1-to-n/
 */
auto AllUniqueBST(const int start, const int end) {
    ArrayType result;

    if (start > end) {
        result.push_back({});
        return result;
    }

    for (auto i = start; i <= end; ++i) {
        const auto left_sub_trees = AllUniqueBST(start, i - 1);
        const auto right_sub_trees = AllUniqueBST(i + 1, end);

        for (const auto &left : left_sub_trees) {
            for (const auto &right : right_sub_trees) {
                const auto node = std::make_shared<BinaryTree::Node>(i);
                node->left = left;
                node->right = right;
                result.push_back(node);
            }
        }
    }

    return result;
}

inline auto AllUniqueBST(const int n) {
    return AllUniqueBST(1, n);
}

inline auto AllUniqueBSTSize(const int n) {
    return AllUniqueBST(1, n).size();
}


/**
 * @reference   All Possible Full Binary Trees
 *              https://leetcode.com/problems/all-possible-full-binary-trees/
 *
 * Given an integer n, return a list of all possible full binary trees with n nodes. Each node of each
 * tree in the answer must have Node.val == 0.
 * Each element of the answer is the root node of one possible tree. You may return the final list of
 * trees in any order.
 * A full binary tree is a binary tree where each node has exactly 0 or 2 children.
 */
ArrayType AllPossibleFBT(const int n) {
    if (n % 2 == 0) {
        return {};
    }

    std::vector dp(n + 1, ArrayType {});
    dp[1].push_back(std::make_shared<BinaryTree::Node>(0));
    for (int i = 3; i <= n; i += 2) {
        for (int left = 1; left < i; left += 2) {
            const auto right = i - left - 1;
            for (const auto &left_sub : dp[left]) {
                for (const auto &right_sub : dp[right]) {
                    const auto node = std::make_shared<BinaryTree::Node>(0);
                    node->left = left_sub;
                    node->right = right_sub;
                    dp[i].push_back(node);
                }
            }
        }
    }

    return dp[n];
}

inline auto AllPossibleFBTSize(const int n) {
    return AllPossibleFBT(n).size();
}

} //namespace


THE_BENCHMARK(CountUniqueBST_Memo, 3);

SIMPLE_TEST(CountUniqueBST_Memo, TestSAMPLE1, 1, 1);
SIMPLE_TEST(CountUniqueBST_Memo, TestSAMPLE2, 5, 3);
SIMPLE_TEST(CountUniqueBST_Memo, TestSAMPLE3, 4862, 9);


THE_BENCHMARK(CountUniqueBST_DP, 3);

SIMPLE_TEST(CountUniqueBST_DP, TestSAMPLE1, 1, 1);
SIMPLE_TEST(CountUniqueBST_DP, TestSAMPLE2, 5, 3);
SIMPLE_TEST(CountUniqueBST_DP, TestSAMPLE3, 4862, 9);


THE_BENCHMARK(CountUniqueBST_BC, 3);

SIMPLE_TEST(CountUniqueBST_BC, TestSAMPLE1, 1, 1);
SIMPLE_TEST(CountUniqueBST_BC, TestSAMPLE2, 5, 3);
SIMPLE_TEST(CountUniqueBST_BC, TestSAMPLE3, 4862, 9);


THE_BENCHMARK(AllUniqueBSTSize, 3);

SIMPLE_TEST(AllUniqueBSTSize, TestSAMPLE1, 1, 1);
SIMPLE_TEST(AllUniqueBSTSize, TestSAMPLE2, 5, 3);
SIMPLE_TEST(AllUniqueBSTSize, TestSAMPLE3, 4862, 9);


THE_BENCHMARK(AllPossibleFBTSize, 7);

SIMPLE_TEST(AllPossibleFBTSize, TestSAMPLE1, 5, 7);
SIMPLE_TEST(AllPossibleFBTSize, TestSAMPLE2, 1, 3);
SIMPLE_TEST(AllPossibleFBTSize, TestSAMPLE3, 1, 1);
SIMPLE_TEST(AllPossibleFBTSize, TestSAMPLE4, 0, 6);
