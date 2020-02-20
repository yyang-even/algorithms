#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_deletion.h"
#include "binary_tree_traversals.h"
#include "clone_binary_tree.h"


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
    return LevelOrderTraversal_LevelAware_Helper(root_node,
    [&has_nonfull_node_found](const BinaryTree::Node & node) {
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


/** Check whether a binary tree is a complete tree or not | Set 2 (Recursive Solution)
 *
 * @reference   https://www.geeksforgeeks.org/check-whether-binary-tree-complete-not-set-2-recursive-solution/
 */

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();
/**
 *     1
 *    / \
 *   2   3
 *  /
 * 4
 */
const auto SAMPLE2 = BinaryTreeDeletion_Subtree(CloneBinaryTree(SAMPLE1), 5).GetRoot();
/**
 *     1
 *    / \
 *   2   3
 */
const auto SAMPLE3 = BinaryTreeDeletion_Subtree(CloneBinaryTree(SAMPLE2), 4).GetRoot();
/**
 *      1
 *    /   \
 *   2     3
 *  / \   /
 * 4   5 6
 */
static inline auto MakeCompleteTree4() {
    auto binary_tree = CloneBinaryTree(SAMPLE1);
    auto &right_child_of_root = *(binary_tree.GetRoot()->right);
    SetLeftChild(right_child_of_root, 6);

    return binary_tree;
}
const auto SAMPLE4 = MakeCompleteTree4().GetRoot();
/**
 *     1
 *    / \
 *   2   3
 *    \
 *     5
 */
const auto SAMPLE5 = BinaryTreeDeletion_Subtree(CloneBinaryTree(SAMPLE1), 4).GetRoot();
/**
 *      1
 *    /   \
 *   2     3
 *        / \
 *       6   7
 */
static inline auto MakeIncompleteTree6() {
    auto binary_tree = CloneBinaryTree(SAMPLE3);
    auto &right_child_of_root = *(binary_tree.GetRoot()->right);
    SetLeftChild(right_child_of_root, 6);
    SetRightChild(right_child_of_root, 7);

    return binary_tree;
}
const auto SAMPLE6 = MakeIncompleteTree6().GetRoot();


SIMPLE_BENCHMARK(isCompleteBinaryTree, SAMPLE1);
SIMPLE_BENCHMARK(isCompleteBinaryTree, SAMPLE6);

SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE3, true, SAMPLE3);
SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE4, true, SAMPLE4);
SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE5, false, SAMPLE5);
SIMPLE_TEST(isCompleteBinaryTree, TestSAMPLE6, false, SAMPLE6);
