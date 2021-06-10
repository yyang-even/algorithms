#include "common_header.h"

#include "binary_search_tree.h"
#include "data_structure/tree/binary_tree/binary_tree_search.h"


namespace {

/**
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 5.
 * @reference   Lowest Common Ancestor in a Binary Search Tree.
 *              https://www.geeksforgeeks.org/lowest-common-ancestor-in-a-binary-search-tree/
 *
 * Given values of two values n1 and n2 in a Binary Search Tree, find the Lowest Common
 * Ancestor (LCA). You may assume that both the values exist in the tree.
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


/**
 * @reference   Lowest Common Ancestor in a Binary Tree | Set 1
 *              https://www.geeksforgeeks.org/lowest-common-ancestor-binary-tree-set-1/
 *
 * Given a binary tree (not a binary search tree) and two values say n1 and n2, write a
 * program to find the least common ancestor.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 4.7.
 *
 * @reference   Print the path common to the two paths from the root to the two given nodes
 *              https://www.geeksforgeeks.org/print-path-common-two-paths-root-two-given-nodes/
 * @reference   Print common nodes on path from root (or common ancestors)
 *              https://www.geeksforgeeks.org/print-common-nodes-path-root-common-ancestors/
 */
auto LowestCommonAncestor_CommonPath(const BinaryTree::Node::PointerType root,
                                     const BinaryTree::Node::ValueType x,
                                     const BinaryTree::Node::ValueType y) {
    BinaryTree::ArrayType path_x, path_y;
    BinaryTreeSearch_Preorder(root, x, &path_x);
    BinaryTreeSearch_Preorder(root, y, &path_y);

    BinaryTree::ArrayType::size_type i = 0;
    for (; i < path_x.size() and i < path_y.size(); ++i) {
        if (path_x[i] != path_y[i]) {
            break;
        }
    }

    return path_x[i - 1];
}


auto LowestCommonAncestor_SingleTraversal(const BinaryTree::Node::PointerType node,
                                          const BinaryTree::Node::ValueType x,
                                          const BinaryTree::Node::ValueType y) {
    if (not node or node->value == x or node->value == y) {
        return node;
    }

    const auto left_LCA = LowestCommonAncestor_SingleTraversal(node->left, x, y);
    const auto right_LCA = LowestCommonAncestor_SingleTraversal(node->right, x, y);

    if (left_LCA and right_LCA) {
        return node;
    }

    return left_LCA ? left_LCA : right_LCA;
}


/**
 * @reference   Lowest Common Ancestor in a Binary Tree | Set 2 (Using Parent Pointer)
 *              https://www.geeksforgeeks.org/lowest-common-ancestor-in-a-binary-tree-set-2-using-parent-pointer/
 */


template <typename LCA>
inline constexpr auto
TestLowestCommonAncestor(const LCA lowest_common_ancestor,
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


THE_BENCHMARK(LowestCommonAncestor_CommonPath, SAMPLE1, 1, 3);

SIMPLE_TEST(LowestCommonAncestor_CommonPath, TestSAMPLE1, 2, SAMPLE1, 1, 3);
SIMPLE_TEST(LowestCommonAncestor_CommonPath, TestSAMPLE2, 2, SAMPLE1, 2, 3);
SIMPLE_TEST(LowestCommonAncestor_CommonPath, TestSAMPLE3, 4, SAMPLE1, 3, 5);


THE_BENCHMARK(LowestCommonAncestor_SingleTraversal, SAMPLE1, 1, 3);

SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLES1, 2,
            LowestCommonAncestor_SingleTraversal, SAMPLE1, 1, 3);
SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLES2, 2,
            LowestCommonAncestor_SingleTraversal, SAMPLE1, 2, 3);
SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLES3, 4,
            LowestCommonAncestor_SingleTraversal, SAMPLE1, 3, 5);
