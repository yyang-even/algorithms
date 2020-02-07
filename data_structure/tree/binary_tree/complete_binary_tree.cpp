#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_traversals.h"


namespace {

/** Check whether a given Binary Tree is Complete or not | Set 1 (Iterative Solution)
 *
 * @reference   https://www.geeksforgeeks.org/check-if-a-given-binary-tree-is-complete-tree-or-not/
 *
 * A complete binary tree is a binary tree in which every level, except possibly the last,
 * is completely filled, and all nodes are as far left as possible. See the following examples.
 * A node is ‘Full Node’ if both left and right children are not empty (or not NULL).
 * The approach is to do a level order traversal starting from the root. In the traversal,
 * once a node is found which is NOT a Full Node, all the following nodes must be leaf nodes.
 */
auto isCompleteBinaryTree(const BinaryTree::Node::PointerType root_node) {
    bool has_nonfull_node_found = false;
    return LevelOrderTraversal_LevelAware_Helper(root_node, [&has_nonfull_node_found](
    const BinaryTree::Node & node) {
        const auto node_type = CheckType(node);

        if (has_nonfull_node_found) {
            if (node_type != BinaryTree::Node::Type::leaf) {
                return false;
            }
        } else {
            if (node_type != BinaryTree::Node::Type::full) {
                if (node_type == BinaryTree::Node::Type::right_sided) {
                    return false;
                }
                has_nonfull_node_found = true;
            }
        }

        return true;
    }, {});
}


/**
 *     1
 *    / \
 *   2   3
 */
inline auto MakeCompleteTree2() {
    BinaryTree binary_tree{1};
    auto &root = *binary_tree.GetRoot();
    SetLeftChild(root, 2);
    SetRightChild(root, 3);

    return binary_tree;
}


/**
 *     1
 *    / \
 *   2   3
 *  /
 * 4
 */
inline auto MakeCompleteTree3() {
    BinaryTree binary_tree{1};
    auto &root = *binary_tree.GetRoot();
    auto &left_child = *SetLeftChild(root, 2);
    SetRightChild(root, 3);
    SetLeftChild(left_child, 4);

    return binary_tree;
}


/**
 *      1
 *    /   \
 *   2     3
 *  / \   /
 * 4   5 6
 */
static inline auto MakeCompleteTree4() {
    BinaryTree binary_tree{1};
    auto &root = *binary_tree.GetRoot();
    auto &left_child = *SetLeftChild(root, 2);
    auto &right_child = *SetRightChild(root, 3);
    SetLeftChild(left_child, 4);
    SetRightChild(left_child, 5);
    SetLeftChild(right_child, 6);

    return binary_tree;
}


/**
 *     1
 *    / \
 *   2   3
 *    \
 *     5
 */
inline auto MakeIncompleteTree5() {
    BinaryTree binary_tree{1};
    auto &root = *binary_tree.GetRoot();
    auto &left_child = *SetLeftChild(root, 2);
    SetRightChild(root, 3);
    SetRightChild(left_child, 5);

    return binary_tree;
}


/**
 *      1
 *    /   \
 *   2     3
 *        / \
 *       6   7
 */
inline auto MakeIncompleteTree6() {
    BinaryTree binary_tree{1};
    auto &root = *binary_tree.GetRoot();
    SetLeftChild(root, 2);
    auto &right_child = *SetRightChild(root, 3);
    SetLeftChild(right_child, 6);
    SetRightChild(right_child, 7);

    return binary_tree;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();
const auto SAMPLE2 = MakeCompleteTree2().GetRoot();
const auto SAMPLE3 = MakeCompleteTree3().GetRoot();
const auto SAMPLE4 = MakeCompleteTree4().GetRoot();
const auto SAMPLE5 = MakeIncompleteTree5().GetRoot();
const auto SAMPLE6 = MakeIncompleteTree6().GetRoot();


SIMPLE_BENCHMARK(isCompleteBinaryTree, SAMPLE1);
SIMPLE_BENCHMARK(isCompleteBinaryTree, SAMPLE2);

SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE3, true, SAMPLE3);
SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE4, true, SAMPLE4);
SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE5, false, SAMPLE5);
SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE6, false, SAMPLE6);
