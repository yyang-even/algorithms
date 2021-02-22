#include "common_header.h"

#include "binary_tree.h"
#include "compare_binary_trees.h"


namespace {

/** Check if a binary tree is subtree of another binary tree | Set 1
 *
 * @reference   https://www.geeksforgeeks.org/check-if-a-binary-tree-is-subtree-of-another-binary-tree/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 4.8.
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
const auto NULL_MARK = -1;

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

auto isSubtree_String(const BinaryTree::Node::PointerType origin,
                      const BinaryTree::Node::PointerType candidate) {
    BinaryTree::ArrayType origin_inorder, candidate_inorder;
    InorderTraversalWithNullMark(origin, origin_inorder);
    InorderTraversalWithNullMark(candidate, candidate_inorder);

    return std::search(origin_inorder.cbegin(), origin_inorder.cend(),
                       candidate_inorder.cbegin(), candidate_inorder.cend()) != origin_inorder.cend();
}


/**
 *   2
 *  / \
 * 4   5
 */
inline auto MakeTheSampleSubtree1() {
    BinaryTree binary_tree{2};
    auto &root = *binary_tree.GetRoot();
    SetLeftChild(root, 4);
    SetRightChild(root, 5);

    return binary_tree;
}

/**
 *   1
 *  / \
 * 2   3
 */
inline auto MakeTheSampleSubtree2() {
    BinaryTree binary_tree{1};
    auto &root = *binary_tree.GetRoot();
    SetLeftChild(root, 2);
    SetRightChild(root, 3);

    return binary_tree;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();
const auto SAMPLE_SUB1 = MakeTheSampleSubtree1().GetRoot();
const auto SAMPLE_SUB2 = MakeTheSampleSubtree2().GetRoot();


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
