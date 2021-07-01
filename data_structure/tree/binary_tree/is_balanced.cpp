#include "common_header.h"

#include "binary_tree.h"


namespace {

/** How to determine if a binary tree is height-balanced?
 *
 * @reference   https://www.geeksforgeeks.org/how-to-determine-if-a-binary-tree-is-balanced/
 *
 * A tree where no leaf is much farther away from the root than any other leaf. Different
 * balancing schemes allow different definitions of "much farther" and different amounts
 * of work to keep them balanced.
 * Consider a height-balancing scheme where following conditions should be checked to
 * determine if a binary tree is balanced.
 * An empty tree is height-balanced. A non-empty binary tree T is balanced if:
 *  1) Left subtree of T is balanced
 *  2) Right subtree of T is balanced
 *  3) The difference between heights of left subtree and right subtree is not more than 1.
 * The above height-balancing scheme is used in AVL trees.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 4.1.
 * @reference   Balanced Binary Tree
 *              https://leetcode.com/problems/balanced-binary-tree/
 */
auto isBalanced(const BinaryTree::Node::PointerType node,
                int *const height = nullptr) {
    if (not node) {
        if (height) {
            *height = 0;
        }
        return true;
    }

    int left_subtree_height = 0;
    int right_subtree_height = 0;
    const auto is_left_subtree_balanced = isBalanced(node->left, &left_subtree_height);
    const auto is_right_subtree_balanced = isBalanced(node->right, &right_subtree_height);

    if (std::abs(left_subtree_height - right_subtree_height) > 1) {
        return false;
    }

    if (height) {
        *height = std::max(left_subtree_height, right_subtree_height) + 1;
    }
    return is_left_subtree_balanced and is_right_subtree_balanced;
}


auto isBalanced_Flag(const BinaryTree::Node::PointerType node, bool &flag) {
    if (not node) {
        return 0;
    }

    const auto left_subtree_height = isBalanced_Flag(node->left, flag);
    const auto right_subtree_height = isBalanced_Flag(node->right, flag);

    if (std::abs(left_subtree_height - right_subtree_height) > 1) {
        flag = false;
    }

    return 1 + std::max(left_subtree_height, right_subtree_height);
}

inline auto
isBalanced_Flag(const BinaryTree::Node::PointerType root) {
    bool flag = true;
    isBalanced_Flag(root, flag);
    return flag;
}

/**
 *     1
 *    /
 *   2
 *  / \
 * 4   5
 */
inline auto MakeTheSampleUnbalancedTree() {
    const BinaryTree binary_tree{1};
    auto &root = *binary_tree.GetRoot();
    auto &left_child = *SetLeftChild(root, 2);
    SetLeftChild(left_child, 4);
    SetRightChild(left_child, 5);

    return binary_tree;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();
const auto SAMPLE2 = MakeTheSampleUnbalancedTree().GetRoot();


THE_BENCHMARK(isBalanced, SAMPLE1);

SIMPLE_TEST(isBalanced, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(isBalanced, TestSAMPLE2, false, SAMPLE2);


THE_BENCHMARK(isBalanced_Flag, SAMPLE1);

SIMPLE_TEST(isBalanced_Flag, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(isBalanced_Flag, TestSAMPLE2, false, SAMPLE2);
