#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_traversals.h"


namespace {

/** Program to count leaf nodes in a binary tree
 *
 * @reference   https://www.geeksforgeeks.org/write-a-c-program-to-get-count-of-leaf-nodes-in-a-binary-tree/
 */
inline auto CountLeaves_Recursive(const BinaryTree::Node::PointerType node) {
    if (not node) {
        return 0;
    }
    if (not node->left and not node->right) {
        return 1;
    }
    return CountLeaves_Recursive(node->left) + CountLeaves_Recursive(node->right);
}


/**
 * @reference   Iterative program to count leaf nodes in a Binary Tree
 *              https://www.geeksforgeeks.org/iterative-program-count-leaf-nodes-binary-tree/
 */
inline auto CountLeaves_Iterative(const BinaryTree::Node::PointerType root_node) {
    unsigned leaves_count = 0;
    LevelOrderTraversal_LevelAware_Helper(root_node,
    [&leaves_count](const auto & node) {
        if (not node.left and not node.right) {
            ++leaves_count;
        }
        return true;
    }, {});

    return leaves_count;
}


/** Count Non-Leaf nodes in a Binary Tree
 *
 * @reference   https://www.geeksforgeeks.org/count-non-leaf-nodes-binary-tree/
 */


/** Count half nodes in a Binary tree (Iterative and Recursive)
 *
 * @reference   https://www.geeksforgeeks.org/count-half-nodes-in-a-binary-tree-iterative-and-recursive/
 */


/** Count full nodes in a Binary tree (Iterative and Recursive)
 *
 * @reference   https://www.geeksforgeeks.org/count-full-nodes-binary-tree-iterative-recursive/
 */


/**
 * @reference   Leaf-Similar Trees
 *              https://leetcode.com/problems/leaf-similar-trees/
 *
 * Consider all the leaves of a binary tree, from left to right order, the values of
 * those leaves form a leaf value sequence. Two binary trees are considered leaf-similar
 * if their leaf value sequence is the same. Return true if and only if the two given
 * trees with head nodes root1 and root2 are leaf-similar.
 */
void leafSequence(const BinaryTree::Node::PointerType node, std::vector<int> &result) {
    if (not node) {
        return;
    }

    if (not node->left and not node->right) {
        result.push_back(node->value);
    } else {
        leafSequence(node->left, result);
        leafSequence(node->right, result);
    }
}

auto LeafSimilar(const BinaryTree::Node::PointerType one_root,
                 const BinaryTree::Node::PointerType another) {
    BinaryTree::ArrayType one_sequence;
    leafSequence(one_root, one_sequence);

    BinaryTree::ArrayType another_sequence;
    leafSequence(another, another_sequence);

    return one_sequence == another_sequence;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();
const auto EMPTY_TREE = BinaryTree {} .GetRoot();


THE_BENCHMARK(CountLeaves_Recursive, SAMPLE1);

SIMPLE_TEST(CountLeaves_Recursive, TestSAMPLE0, 0, EMPTY_TREE);
SIMPLE_TEST(CountLeaves_Recursive, TestSAMPLE1, 3, SAMPLE1);


THE_BENCHMARK(CountLeaves_Iterative, SAMPLE1);

SIMPLE_TEST(CountLeaves_Iterative, TestSAMPLE0, 0, EMPTY_TREE);
SIMPLE_TEST(CountLeaves_Iterative, TestSAMPLE1, 3, SAMPLE1);


THE_BENCHMARK(LeafSimilar, SAMPLE1, EMPTY_TREE);

SIMPLE_TEST(LeafSimilar, TestSAMPLE0, false, EMPTY_TREE, SAMPLE1);
SIMPLE_TEST(LeafSimilar, TestSAMPLE1, true, SAMPLE1, SAMPLE1);
