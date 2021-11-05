#include "common_header.h"

#include "binary_tree.h"


namespace {

using ArrayType = std::vector<BinaryTree::ArrayType>;

/** Root to leaf path sum equal to a given number
 *
 * @reference   https://www.geeksforgeeks.org/root-to-leaf-path-sum-equal-to-a-given-number/
 * @reference   Root to leaf path sum equal to a given number in BST
 *              https://www.geeksforgeeks.org/root-to-leaf-path-sum-equal-to-a-given-number-in-bst/
 * @reference   Path Sum
 *              https://leetcode.com/problems/path-sum/
 */
inline bool
hasKSumFullPaths(const BinaryTree::Node::PointerType node, const int sum) {
    if (not node) {
        return false;
    }

    if (not(node->left or node->right)) {
        return sum == node->value;
    }

    const auto sub_sum = sum - node->value;
    return hasKSumFullPaths(node->left, sub_sum) or hasKSumFullPaths(node->right, sub_sum);
}


/**
 * @reference   Shortest root to leaf path sum equal to a given number
 *              https://www.geeksforgeeks.org/shortest-root-to-leaf-path-sum-equal-to-a-given-number/
 */
inline void
ShortestKSumFullPathsHelper(const BinaryTree::Node::PointerType node,
                            const int sum, const int level, int &minimum) {
    if (node) {
        const auto sub_sum = sum - node->value;
        if (sub_sum == 0 and not node->left and not node->right) {
            minimum = std::min(minimum, level);
        } else {
            ShortestKSumFullPathsHelper(node->left, sub_sum, level + 1, minimum);
            ShortestKSumFullPathsHelper(node->right, sub_sum, level + 1, minimum);
        }
    }
}

inline int
ShortestKSumFullPaths(const BinaryTree::Node::PointerType root, const int sum) {
    constexpr auto NOT_FOUND = std::numeric_limits<int>::max();
    auto result = NOT_FOUND;
    ShortestKSumFullPathsHelper(root, sum, 1, result);
    return result == NOT_FOUND ? -1 : result;
}


/** Print all the paths from root, with a specified sum in Binary tree
 *
 * @reference   https://www.geeksforgeeks.org/print-paths-root-specified-sum-binary-tree/
 *
 * Given a Binary tree and a sum S, print all the paths, starting from root, that sums
 * upto the given sum. Note that this problem is different from root to leaf paths. Here
 * path doesn't need to end on a leaf node.
 *
 * @reference   Path Sum II
 *              https://leetcode.com/problems/path-sum-ii/
 */
void AllKSumRootPathsHelper(const BinaryTree::Node::PointerType node, const int sum,
                            BinaryTree::ArrayType &path, ArrayType &results) {
    if (node) {
        const auto sub_sum = sum - node->value;
        path.push_back(node->value);

        if (sub_sum == 0) {
            results.push_back(path);
        }

        AllKSumRootPathsHelper(node->left, sub_sum, path, results);
        AllKSumRootPathsHelper(node->right, sub_sum, path, results);

        path.pop_back();
    }
}

inline auto
AllKSumRootPaths(const BinaryTree::Node::PointerType root, const int sum) {
    BinaryTree::ArrayType path;
    ArrayType results;
    AllKSumRootPathsHelper(root, sum, path, results);
    return results;
}


/**
 * @reference   Given a binary tree, print all root-to-leaf paths
 *              https://www.geeksforgeeks.org/given-a-binary-tree-print-all-root-to-leaf-paths/
 * @reference   Given a binary tree, print out all of its root-to-leaf paths one per line.
 *              https://www.geeksforgeeks.org/given-a-binary-tree-print-out-all-of-its-root-to-leaf-paths-one-per-line/
 */


/**
 * @reference   Binary Tree Paths
 *              https://leetcode.com/problems/binary-tree-paths/
 *
 * Given the root of a binary tree, return all root-to-leaf paths in any order. A leaf
 * is a node with no children.
 */


/** Print all k-sum paths in a binary tree
 *
 * @reference   https://www.geeksforgeeks.org/print-k-sum-paths-binary-tree/
 *
 * A binary tree and a number k are given. Print every path in the tree with sum of the
 * nodes in the path as k. A path can start from any node and end at any node and must
 * be downward only, i.e. they need not be root node and leaf node; and negative numbers
 * can also be there in the tree.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 4.9.
 * @reference   Path Sum III
 *              https://leetcode.com/problems/path-sum-iii/
 */
void AllKSumPathsHelper(const BinaryTree::Node::PointerType node, const int sum,
                        BinaryTree::ArrayType &path, ArrayType &results) {
    if (node) {
        path.push_back(node->value);

        int suffix_sum = 0;
        for (auto iter = path.crbegin(); iter != path.crend(); ++iter) {
            suffix_sum += *iter;
            if (suffix_sum == sum) {
                results.emplace_back(std::prev(iter.base()), path.cend());
            }
        }

        AllKSumPathsHelper(node->left, sum, path, results);
        AllKSumPathsHelper(node->right, sum, path, results);

        path.pop_back();
    }
}

inline auto
AllKSumPaths(const BinaryTree::Node::PointerType root, const int sum) {
    BinaryTree::ArrayType path;
    ArrayType results;
    AllKSumPathsHelper(root, sum, path, results);
    return results;
}


/**
 * @reference   Sum of Root To Leaf Binary Numbers
 *              https://leetcode.com/problems/sum-of-root-to-leaf-binary-numbers/
 *
 * You are given the root of a binary tree where each node has a value 0 or 1.  Each
 * root-to-leaf path represents a binary number starting with the most significant bit.
 * For example, if the path is 0 -> 1 -> 1 -> 0 -> 1, then this could represent 01101 in
 * binary, which is 13. For all leaves in the tree, consider the numbers represented by
 * the path from the root to that leaf. Return the sum of these numbers. The answer is
 * guaranteed to fit in a 32-bits integer.
 *
 * @reference   Sum Root to Leaf Numbers
 *              https://leetcode.com/problems/sum-root-to-leaf-numbers/
 *
 * You are given the root of a binary tree containing digits from 0 to 9 only. Each
 * root-to-leaf path in the tree represents a number.
 *  For example, the root-to-leaf path 1 -> 2 -> 3 represents the number 123.
 * Return the total sum of all root-to-leaf numbers. Test cases are generated so that
 * the answer will fit in a 32-bit integer. A leaf node is a node with no children.
 */

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();


THE_BENCHMARK(hasKSumFullPaths, SAMPLE1, 4);

SIMPLE_TEST(hasKSumFullPaths, TestSAMPLE0, false, nullptr, 0);
SIMPLE_TEST(hasKSumFullPaths, TestSAMPLE1, false, SAMPLE1, 1);
SIMPLE_TEST(hasKSumFullPaths, TestSAMPLE2, false, SAMPLE1, 100);
SIMPLE_TEST(hasKSumFullPaths, TestSAMPLE3, true, SAMPLE1, 4);
SIMPLE_TEST(hasKSumFullPaths, TestSAMPLE4, true, SAMPLE1, 7);


THE_BENCHMARK(ShortestKSumFullPaths, SAMPLE1, 4);

SIMPLE_TEST(ShortestKSumFullPaths, TestSAMPLE1, -1, SAMPLE1, 1);
SIMPLE_TEST(ShortestKSumFullPaths, TestSAMPLE2, -1, SAMPLE1, 100);
SIMPLE_TEST(ShortestKSumFullPaths, TestSAMPLE3, 2, SAMPLE1, 4);
SIMPLE_TEST(ShortestKSumFullPaths, TestSAMPLE4, 3, SAMPLE1, 7);


const ArrayType EXPECTED_R0 = {};
const ArrayType EXPECTED_R1 = {{1}};
const ArrayType EXPECTED_R2 = {{1, 3}};
const ArrayType EXPECTED_R3 = {{1, 2, 4}};


THE_BENCHMARK(AllKSumRootPaths, SAMPLE1, 4);

SIMPLE_TEST(AllKSumRootPaths, TestSAMPLE1, EXPECTED_R1, SAMPLE1, 1);
SIMPLE_TEST(AllKSumRootPaths, TestSAMPLE2, EXPECTED_R0, SAMPLE1, 100);
SIMPLE_TEST(AllKSumRootPaths, TestSAMPLE3, EXPECTED_R2, SAMPLE1, 4);
SIMPLE_TEST(AllKSumRootPaths, TestSAMPLE4, EXPECTED_R3, SAMPLE1, 7);


const ArrayType EXPECTED2 = {{4}, {1, 3}};
const ArrayType EXPECTED3 = {{1, 2, 4}, {2, 5}};


THE_BENCHMARK(AllKSumPaths, SAMPLE1, 4);

SIMPLE_TEST(AllKSumPaths, TestSAMPLE1, EXPECTED_R1, SAMPLE1, 1);
SIMPLE_TEST(AllKSumPaths, TestSAMPLE2, EXPECTED_R0, SAMPLE1, 100);
SIMPLE_TEST(AllKSumPaths, TestSAMPLE3, EXPECTED2, SAMPLE1, 4);
SIMPLE_TEST(AllKSumPaths, TestSAMPLE4, EXPECTED3, SAMPLE1, 7);
