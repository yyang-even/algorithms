#include "common_header.h"

#include "binary_search_tree.h"


namespace {

/**
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 5.
 * @reference   Lowest Common Ancestor in a Binary Search Tree.
 *              https://www.geeksforgeeks.org/lowest-common-ancestor-in-a-binary-search-tree/
 *
 * Given values of two values n1 and n2 in a Binary Search Tree, find the Lowest
 * Common Ancestor (LCA). You may assume that both the values exist in the tree.
 */
auto LowestCommonAncestor_BST_Recursive(const BinaryTree::Node::PointerType node,
                                        const BinaryTree::Node::ValueType x,
                                        const BinaryTree::Node::ValueType y) {
    if (not node) {
        return node;
    }

    if (node->value > x and node->value > y) {
        return LowestCommonAncestor_BST_Recursive(node->left, x, y);
    }

    if (node->value < x and node->value < y) {
        return LowestCommonAncestor_BST_Recursive(node->right, x, y);
    }

    return node;
}


auto LowestCommonAncestor_BST_Iterative(const BinaryTree::Node::PointerType root,
                                        const BinaryTree::Node::ValueType x,
                                        const BinaryTree::Node::ValueType y) {
    auto node = root;
    while (node) {
        if (node->value > x and node->value > y) {
            node = node->left;
        } else if (node->value < x and node->value < y) {
            node = node->right;
        } else {
            break;
        }
    }

    return node;
}


template <typename LCA>
auto TestLowestCommonAncestor(const LCA lowest_common_ancestor,
                              const BinaryTree::Node::PointerType root,
                              const BinaryTree::Node::ValueType x,
                              const BinaryTree::Node::ValueType y) {
    const auto LCA_node = lowest_common_ancestor(root, x, y);
    assert(LCA_node);
    return LCA_node->value;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleBST().GetRoot();


THE_BENCHMARK(LowestCommonAncestor_BST_Recursive, SAMPLE1, 1, 3);

SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLER1, 2,
            LowestCommonAncestor_BST_Recursive, SAMPLE1, 1, 3);
SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLER2, 2,
            LowestCommonAncestor_BST_Recursive, SAMPLE1, 2, 3);
SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLER3, 4,
            LowestCommonAncestor_BST_Recursive, SAMPLE1, 3, 5);


THE_BENCHMARK(LowestCommonAncestor_BST_Iterative, SAMPLE1, 1, 3);

SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLEI1, 2,
            LowestCommonAncestor_BST_Iterative, SAMPLE1, 1, 3);
SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLEI2, 2,
            LowestCommonAncestor_BST_Iterative, SAMPLE1, 2, 3);
SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLEI3, 4,
            LowestCommonAncestor_BST_Iterative, SAMPLE1, 3, 5);
