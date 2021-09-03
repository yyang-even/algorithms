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
 * Given an integer n, return the number of structurally unique BST's (binary search
 * trees) which has exactly n nodes of unique values from 1 to n.
 * 1 <= n <= 19
 *
 * @reference   Program for nth Catalan Number
 *              https://www.geeksforgeeks.org/program-nth-catalan-number/
 * @reference   Applications of Catalan Numbers
 *              https://www.geeksforgeeks.org/applications-of-catalan-numbers/
 * @reference   Total number of possible Binary Search Trees using Catalan Number
 *              https://www.geeksforgeeks.org/total-number-of-possible-binary-search-trees-using-catalan-number/
 *
 * Catalan numbers are a sequence of natural numbers that occurs in many interesting
 * counting problems like following.
 *  Count the number of expressions containing n pairs of parentheses which are correctly
 *      matched. For n = 3, possible expressions are ((())), ()(()), ()()(), (())(), (()()).
 *  Count the number of possible Binary Search Trees with n keys
 *  Count the number of full binary trees (A rooted binary tree is full if every vertex
 *      has either two children or no children) with n+1 leaves.
 *  Given a number n, return the number of ways you can draw n chords in a circle with
 *      2 x n points such that no 2 chords intersect.
 * The first few Catalan numbers for n = 0, 1, 2, 3, ... are 1, 1, 2, 5, 14, 42, 132,
 * 429, 1430, 4862, ...
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
 * Given an integer n, return all the structurally unique BST's (binary search trees),
 * which has exactly n nodes of unique values from 1 to n. Return the answer in any order.
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

        for (const auto left : left_sub_trees) {
            for (const auto right : right_sub_trees) {
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

}//namespace


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
