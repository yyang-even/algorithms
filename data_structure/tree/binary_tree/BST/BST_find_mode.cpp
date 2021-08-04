#include "common_header.h"

#include "binary_search_tree.h"


namespace {

/** Find Mode in Binary Search Tree
 *
 * @reference   https://leetcode.com/problems/find-mode-in-binary-search-tree/
 *
 * Given the root of a binary search tree (BST) with duplicates, return all the mode(s)
 * (i.e., the most frequently occurred element) in it. If the tree has more than one
 * mode, return them in any order. Assume a BST is defined as follows:
 *  The left subtree of a node contains only nodes with keys less than or equal to the
 *      node's key.
 *  The right subtree of a node contains only nodes with keys greater than or equal to
 *      the node's key.
 *  Both the left and right subtrees must also be binary search trees.
 * Follow up: Could you do that without using any extra space? (Assume that the implicit
 * stack space incurred due to recursion does not count).
 */
void FindMode(const BinaryTree::Node::PointerType node, int &count, int &pre,
              int &max, BinaryTree::ArrayType &result) {
    if (node) {
        FindMode(node->left, count, pre, max, result);

        if (pre == node->value) {
            ++count;
        } else {
            pre = node->value;
            count = 1;
        }

        if (count > max) {
            max = count;
            result.clear();
            result.push_back(node->value);
        } else if (count == max) {
            result.push_back(node->value);
        }

        FindMode(node->right, count, pre, max, result);
    }
}

inline auto FindMode(const BinaryTree::Node::PointerType root) {
    int count = 0;
    auto pre = INT_MIN;
    auto max = INT_MIN;
    BinaryTree::ArrayType result;

    FindMode(root, count, pre, max, result);

    return result;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleBST().GetRoot();
const BinaryTree::ArrayType EXPECTED1 = {1, 2, 3, 4, 5};

/**
 *     4
 *    / \
 *   2   5
 *  / \
 * 1   2
 */
static inline auto MakeSample2() {
    const BinaryTree binary_tree{4};
    auto &root = *binary_tree.GetRoot();
    auto &left_child = *SetLeftChild(root, 2);
    SetRightChild(root, 5);
    SetLeftChild(left_child, 1);
    SetRightChild(left_child, 2);

    return binary_tree;
}

const auto SAMPLE2 = MakeSample2().GetRoot();
const BinaryTree::ArrayType EXPECTED2 = {2};


THE_BENCHMARK(FindMode, SAMPLE1);

SIMPLE_TEST(FindMode, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(FindMode, TestSAMPLE2, EXPECTED2, SAMPLE2);
