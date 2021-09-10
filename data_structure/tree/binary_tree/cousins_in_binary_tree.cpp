#include "common_header.h"

#include "binary_tree.h"
#include "single_order_to_binary_tree.h"


namespace {

/** Cousins in Binary Tree
 *
 * @reference   https://leetcode.com/problems/cousins-in-binary-tree/
 *
 * Given the root of a binary tree with unique values and the values of two different
 * nodes of the tree x and y, return true if the nodes corresponding to the values x and
 * y in the tree are cousins, or false otherwise. Two nodes of a binary tree are cousins
 * if they have the same depth with different parents. Note that in a binary tree, the
 * root node is at the depth 0, and children of each depth k node are at the depth k + 1.
 *
 * @reference   Check if two nodes are cousins in a Binary Tree
 *              https://www.geeksforgeeks.org/check-two-nodes-cousins-binary-tree/
 * @reference   Check if two nodes are cousins in a Binary Tree | Set-2
 *              https://www.geeksforgeeks.org/check-if-two-nodes-are-cousins-in-a-binary-tree-set-2/
 */
auto AreCousins(const BinaryTree::Node::PointerType root,
                const int x, const int y) {
    if (not root) {
        return false;
    }

    std::queue<std::pair<BinaryTree::Node::PointerType, BinaryTree::Node::PointerType>> q;
    q.emplace(root, nullptr);
    BinaryTree::Node::PointerType one_parent;
    while (not q.empty()) {
        for (int size = q.size(); size > 0; --size) {
            const auto [node, parent] = q.front();
            q.pop();

            if (node->value == x or node->value == y) {
                if (one_parent) {
                    return one_parent != parent;
                } else {
                    one_parent = parent;
                }
            }

            if (node->left) {
                q.emplace(node->left, node);
            }

            if (node->right) {
                q.emplace(node->right, node);
            }
        }

        if (one_parent) {
            return false;
        }
    }

    return false;
}

}//namespace


/**
 *      1
 *    /   \
 *   2     3
 *  / \   / \
 * 4   5 6   7
 */
const auto SAMPLE1 = LevelOrderToBinaryTree( {
    1, 2, 3, 4, 5, 6, 7
});


THE_BENCHMARK(AreCousins, SAMPLE1, 5, 6);

SIMPLE_TEST(AreCousins, TestSAMPLE1, true, SAMPLE1, 5, 6);
SIMPLE_TEST(AreCousins, TestSAMPLE2, true, SAMPLE1, 4, 7);
SIMPLE_TEST(AreCousins, TestSAMPLE3, false, SAMPLE1, 2, 3);
SIMPLE_TEST(AreCousins, TestSAMPLE4, false, SAMPLE1, 4, 5);
