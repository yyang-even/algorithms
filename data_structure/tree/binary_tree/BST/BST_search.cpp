#include "common_header.h"

#include "binary_search_tree.h"
#include "BST_search.h"


namespace {

/** Binary Search Tree | Set 1 (Search and Insertion)
 *
 * @reference   https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 12.2.
 * @reference   Search in a Binary Search Tree
 *              https://leetcode.com/problems/search-in-a-binary-search-tree/
 *
 * You are given the root of a binary search tree (BST) and an integer val. Find the node
 * in the BST that the node's value equals val and return the subtree rooted with that
 * node. If such a node does not exist, return null.
 */
auto BSTSearch_Recursive(const BinaryTree::Node::PointerType node,
                         const BinaryTree::Node::ValueType x) {
    if (not node) {
        return false;
    }
    if (node->value == x) {
        return true;
    }

    if (node->value > x) {
        return BSTSearch_Recursive(node->left, x);
    } else {
        return BSTSearch_Recursive(node->right, x);
    }
}


inline auto hasNode_iterative(const BinaryTree::Node::PointerType current_node,
                              const BinaryTree::Node::ValueType x) {
    return static_cast<bool>(BSTSearch_Iterative(current_node, x));
}


/** Floor in Binary Search Tree (BST)
 *
 * @reference   https://www.geeksforgeeks.org/floor-in-binary-search-tree-bst/
 * @reference   Largest number in BST which is less than or equal to N
 *              https://www.geeksforgeeks.org/largest-number-bst-less-equal-n/
 */
auto BSTFloor_Recursive(const BinaryTree::Node::PointerType node,
                        const BinaryTree::Node::ValueType x) {
    if (not node) {
        return std::numeric_limits<BinaryTree::Node::ValueType>::max();
    }

    if (node->value == x) {
        return x;
    }
    if (node->value > x) {
        return BSTFloor_Recursive(node->left, x);
    }

    const auto right_floor = BSTFloor_Recursive(node->right, x);
    return right_floor <= x ? right_floor : node->value;
}


/**
 * @reference   Largest number less than or equal to N in BST (Iterative Approach)
 *              https://www.geeksforgeeks.org/largest-number-less-equal-n-bst-iterative-approach/
 */
auto BSTFloor_Iterative(BinaryTree::Node::PointerType node,
                        const BinaryTree::Node::ValueType x) {
    BinaryTree::Node::PointerType floor;
    while (node) {
        if (node->value <= x) {
            floor = node;
            node = node->right;
        } else {
            node = node->left;
        }
    }

    if (floor) {
        return floor->value;
    }
    return std::numeric_limits<BinaryTree::Node::ValueType>::max();
}


/** Smallest number in BST which is greater than or equal to N
 *
 * @reference   https://www.geeksforgeeks.org/smallest-number-in-bst-which-is-greater-than-or-equal-to-n/
 */
auto BSTCeil_Recursive(const BinaryTree::Node::PointerType node,
                       const BinaryTree::Node::ValueType x) {
    if (not node) {
        return std::numeric_limits<BinaryTree::Node::ValueType>::min();
    }

    if (node->value == x) {
        return x;
    }
    if (node->value < x) {
        return BSTCeil_Recursive(node->right, x);
    }

    const auto left_ceil = BSTCeil_Recursive(node->left, x);
    return left_ceil >= x ? left_ceil : node->value;
}


/**
 * @reference   Smallest number in BST which is greater than or equal to N ( Iterative Approach)
 *              https://www.geeksforgeeks.org/smallest-number-in-bst-which-is-greater-than-or-equal-to-n-iterative-approach/
 */
auto BSTCeil_Iterative(BinaryTree::Node::PointerType node,
                       const BinaryTree::Node::ValueType x) {
    BinaryTree::Node::PointerType ceil;
    while (node) {
        if (node->value >= x) {
            ceil = node;
            node = node->left;
        } else {
            node = node->right;
        }
    }

    if (ceil) {
        return ceil->value;
    }

    return std::numeric_limits<BinaryTree::Node::ValueType>::min();
}

}//namespace


const auto SAMPLE1 = MakeTheSampleBST().GetRoot();


SIMPLE_BENCHMARK(BSTSearch_Recursive, Sample1, SAMPLE1, -1);
SIMPLE_BENCHMARK(BSTSearch_Recursive, Sample2, SAMPLE1, 1);

SIMPLE_TEST(BSTSearch_Recursive, TestSAMPLE1, true, SAMPLE1, 4);
SIMPLE_TEST(BSTSearch_Recursive, TestSAMPLE2, true, SAMPLE1, 1);
SIMPLE_TEST(BSTSearch_Recursive, TestSAMPLE3, false, SAMPLE1, -1);


SIMPLE_BENCHMARK(hasNode_iterative, Sample1, SAMPLE1, -1);
SIMPLE_BENCHMARK(hasNode_iterative, Sample2, SAMPLE1, 1);

SIMPLE_TEST(hasNode_iterative, TestSAMPLE1, true, SAMPLE1, 4);
SIMPLE_TEST(hasNode_iterative, TestSAMPLE2, true, SAMPLE1, 1);
SIMPLE_TEST(hasNode_iterative, TestSAMPLE3, false, SAMPLE1, -1);


THE_BENCHMARK(MinimumNode, SAMPLE1);

SIMPLE_TEST(MinimumNode, TestSAMPLE1, SAMPLE1->left->left, SAMPLE1);


THE_BENCHMARK(MaximumNode, SAMPLE1);

SIMPLE_TEST(MaximumNode, TestSAMPLE1, SAMPLE1->right, SAMPLE1);


THE_BENCHMARK(BSTFloor_Recursive, SAMPLE1, 3);

SIMPLE_TEST(BSTFloor_Recursive, TestSAMPLE1, 4, SAMPLE1, 4);
SIMPLE_TEST(BSTFloor_Recursive, TestSAMPLE2, 1, SAMPLE1, 1);
SIMPLE_TEST(BSTFloor_Recursive, TestSAMPLE3, 3, SAMPLE1, 3);
SIMPLE_TEST(BSTFloor_Recursive, TestSAMPLE4, 5, SAMPLE1, 5);
SIMPLE_TEST(BSTFloor_Recursive, TestSAMPLE5, 5, SAMPLE1, 6);
SIMPLE_TEST(BSTFloor_Recursive, TestSAMPLE6,
            std::numeric_limits<BinaryTree::Node::ValueType>::max(), SAMPLE1, 0);


THE_BENCHMARK(BSTFloor_Iterative, SAMPLE1, 3);

SIMPLE_TEST(BSTFloor_Iterative, TestSAMPLE1, 4, SAMPLE1, 4);
SIMPLE_TEST(BSTFloor_Iterative, TestSAMPLE2, 1, SAMPLE1, 1);
SIMPLE_TEST(BSTFloor_Iterative, TestSAMPLE3, 3, SAMPLE1, 3);
SIMPLE_TEST(BSTFloor_Iterative, TestSAMPLE4, 5, SAMPLE1, 5);
SIMPLE_TEST(BSTFloor_Iterative, TestSAMPLE5, 5, SAMPLE1, 6);
SIMPLE_TEST(BSTFloor_Iterative, TestSAMPLE6,
            std::numeric_limits<BinaryTree::Node::ValueType>::max(), SAMPLE1, 0);


THE_BENCHMARK(BSTCeil_Recursive, SAMPLE1, 3);

SIMPLE_TEST(BSTCeil_Recursive, TestSAMPLE1, 4, SAMPLE1, 4);
SIMPLE_TEST(BSTCeil_Recursive, TestSAMPLE2, 1, SAMPLE1, 1);
SIMPLE_TEST(BSTCeil_Recursive, TestSAMPLE3, 3, SAMPLE1, 3);
SIMPLE_TEST(BSTCeil_Recursive, TestSAMPLE4, 5, SAMPLE1, 5);
SIMPLE_TEST(BSTCeil_Recursive, TestSAMPLE5, 1, SAMPLE1, 0);
SIMPLE_TEST(BSTCeil_Recursive, TestSAMPLE6,
            std::numeric_limits<BinaryTree::Node::ValueType>::min(), SAMPLE1, 6);


THE_BENCHMARK(BSTCeil_Iterative, SAMPLE1, 3);

SIMPLE_TEST(BSTCeil_Iterative, TestSAMPLE1, 4, SAMPLE1, 4);
SIMPLE_TEST(BSTCeil_Iterative, TestSAMPLE2, 1, SAMPLE1, 1);
SIMPLE_TEST(BSTCeil_Iterative, TestSAMPLE3, 3, SAMPLE1, 3);
SIMPLE_TEST(BSTCeil_Iterative, TestSAMPLE4, 5, SAMPLE1, 5);
SIMPLE_TEST(BSTCeil_Iterative, TestSAMPLE5, 1, SAMPLE1, 0);
SIMPLE_TEST(BSTCeil_Iterative, TestSAMPLE6,
            std::numeric_limits<BinaryTree::Node::ValueType>::min(), SAMPLE1, 6);
