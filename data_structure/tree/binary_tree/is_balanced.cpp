#include "common_header.h"

#include "binary_tree.h"


namespace {

/** How to determine if a binary tree is height-balanced?
 *
 * @reference   https://www.geeksforgeeks.org/how-to-determine-if-a-binary-tree-is-balanced/
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


/**
 *     1
 *    /
 *   2
 *  / \
 * 4   5
 */
inline auto MakeTheSampleUnbalancedTree() {
    BinaryTree binary_tree{1};
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
