#include "common_header.h"

#include "binary_tree.h"
#include "compare_binary_trees.h"
#include "single_order_to_binary_tree.h"


namespace {

/** Check if a binary tree is subtree of another binary tree | Set 1
 *
 * @reference   https://www.geeksforgeeks.org/check-if-a-binary-tree-is-subtree-of-another-binary-tree/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 4.8.
 * @reference   Subtree of Another Tree
 *              https://leetcode.com/problems/subtree-of-another-tree/
 *
 * Given the roots of two binary trees root and subRoot, return true if there is a
 * subtree of root with the same structure and node values of subRoot and false
 * otherwise. A subtree of a binary tree tree is a tree that consists of a node in tree
 * and all of this node's descendants. The tree tree could also be considered as a
 * subtree of itself.
 */
auto isSubtree(const BinaryTree::Node::PointerType origin,
               const BinaryTree::Node::PointerType candidate) {
    if (not candidate) {
        return true;
    }

    if (not origin) {
        return false;
    }

    if (areIdenticalTrees(origin, candidate)) {
        return true;
    }

    return isSubtree(origin->left, candidate) or isSubtree(origin->right, candidate);
}


/**
 * @reference   Check if a binary tree is subtree of another binary tree using preorder traversal : Iterative
 *              https://www.geeksforgeeks.org/check-if-a-binary-tree-is-subtree-of-another-binary-tree-using-preorder-traversal-iterative/
 */


/**
 * @reference   Check if a binary tree is subtree of another binary tree | Set 2
 *              https://www.geeksforgeeks.org/check-binary-tree-subtree-another-binary-tree-set-2/
 */
constexpr auto NULL_MARK = -1;

auto InorderTraversalWithNullMark(const BinaryTree::Node::PointerType node,
                                  BinaryTree::ArrayType &outputs) {
    if (not node) {
        outputs.push_back(NULL_MARK);
        return;
    }

    InorderTraversalWithNullMark(node->left, outputs);
    assert(node->value != NULL_MARK);
    outputs.push_back(node->value);
    InorderTraversalWithNullMark(node->right, outputs);
}

inline auto isSubtree_String(const BinaryTree::Node::PointerType origin,
                             const BinaryTree::Node::PointerType candidate) {
    BinaryTree::ArrayType origin_inorder, candidate_inorder;
    InorderTraversalWithNullMark(origin, origin_inorder);
    InorderTraversalWithNullMark(candidate, candidate_inorder);

    return std::search(origin_inorder.cbegin(), origin_inorder.cend(),
                       candidate_inorder.cbegin(), candidate_inorder.cend()) != origin_inorder.cend();
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();
/**
 *   2
 *  / \
 * 4   5
 */
const auto SAMPLE_SUB1 = LevelOrderToBinaryTree( {
    2, 4, 5
});
/**
 *   1
 *  / \
 * 2   3
 */
const auto SAMPLE_SUB2 = LevelOrderToBinaryTree( {
    1, 2, 3
});


THE_BENCHMARK(isSubtree, SAMPLE1, SAMPLE_SUB1);

SIMPLE_TEST(isSubtree, TestSAMPLE0, true, SAMPLE1, nullptr);
SIMPLE_TEST(isSubtree, TestSAMPLE1, true, SAMPLE1, SAMPLE_SUB1);
SIMPLE_TEST(isSubtree, TestSAMPLE2, false, SAMPLE_SUB1, SAMPLE1);
SIMPLE_TEST(isSubtree, TestSAMPLE3, false, SAMPLE1, SAMPLE_SUB2);


THE_BENCHMARK(isSubtree_String, SAMPLE1, SAMPLE_SUB1);

SIMPLE_TEST(isSubtree_String, TestSAMPLE0, true, SAMPLE1, nullptr);
SIMPLE_TEST(isSubtree_String, TestSAMPLE1, true, SAMPLE1, SAMPLE_SUB1);
SIMPLE_TEST(isSubtree_String, TestSAMPLE2, false, SAMPLE_SUB1, SAMPLE1);
SIMPLE_TEST(isSubtree_String, TestSAMPLE3, false, SAMPLE1, SAMPLE_SUB2);
