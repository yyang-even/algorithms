#include "common_header.h"

#include "binary_search_tree.h"


namespace {

/**
 * @reference   Second Minimum Node In a Binary Tree
 *              https://leetcode.com/problems/second-minimum-node-in-a-binary-tree/
 *
 * Given a non-empty special binary tree consisting of nodes with the non-negative value,
 * where each node in this tree has exactly two or zero sub-node. If the node has two
 * sub-nodes, then this node's value is the smaller value among its two sub-nodes. More
 * formally, the property root.val = min(root.left.val, root.right.val) always holds.
 * Given such a binary tree, you need to output the second minimum value in the set made
 * of all the nodes' value in the whole tree. If no such second minimum value exists,
 * output -1 instead.
 */
void
SecondMinValue(const BinaryTree::Node::PointerType node,
               const int minimum, long &result) {
    if (node) {
        if (minimum < node->value and node->value < result) {
            result = node->value;
        } else if (minimum == node->value) {
            SecondMinValue(node->left, minimum, result);
            SecondMinValue(node->right, minimum, result);
        }
    }
}

int SecondMinValue(const BinaryTree::Node::PointerType root) {
    auto result = LONG_MAX;
    SecondMinValue(root, root->value, result);
    return result != LONG_MAX ? result : -1;
}


/**
 * @reference   Kth Smallest Element in a BST
 *              https://leetcode.com/problems/kth-smallest-element-in-a-bst/
 *
 * Given the root of a binary search tree, and an integer k, return the kth (1-indexed)
 * smallest element in the tree.
 * Follow up: If the BST is modified often (i.e., we can do insert and delete operations)
 * and you need to find the kth smallest frequently, how would you optimize?
 */
auto kthSmallest(const BinaryTree::Node::PointerType node, int &k, int &result) {
    if (not node) {
        return false;
    }

    if (kthSmallest(node->left, k, result)) {
        return true;
    }

    if (k-- == 1) {
        result = node->value;
        return true;
    }

    return kthSmallest(node->right, k, result);
}

inline auto kthSmallest(const BinaryTree::Node::PointerType root, int k) {
    int result = 0;
    kthSmallest(root, k, result);

    return result;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleBST().GetRoot();

/**
 *     2
 *    / \
 *   5   2
 *  / \
 * 5   7
 */
static inline auto MakeTheSample2() {
    const BinaryTree binary_tree{2};
    auto &root = *binary_tree.GetRoot();
    auto &left_child = *SetLeftChild(root, 5);
    SetRightChild(root, 2);
    SetLeftChild(left_child, 5);
    SetRightChild(left_child, 7);

    return binary_tree;
}

const auto SAMPLE2 = MakeTheSample2().GetRoot();


THE_BENCHMARK(SecondMinValue, SAMPLE2);

SIMPLE_TEST(SecondMinValue, TestSAMPLE2, 5, SAMPLE2);


THE_BENCHMARK(kthSmallest, SAMPLE1, 4);

SIMPLE_TEST(kthSmallest, TestSAMPLE1, 1, SAMPLE1, 1);
SIMPLE_TEST(kthSmallest, TestSAMPLE3, 3, SAMPLE1, 3);
SIMPLE_TEST(kthSmallest, TestSAMPLE5, 5, SAMPLE1, 5);
