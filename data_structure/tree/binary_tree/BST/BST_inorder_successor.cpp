#include "common_header.h"

#include "binary_search_tree.h"
#include "BST_search.h"

#include "data_structure/tree/binary_tree/binary_tree_search.h"
#include "data_structure/tree/binary_tree/clone_binary_tree.h"


namespace {

/** Inorder Successor in Binary Search Tree
 *
 * @reference   https://www.geeksforgeeks.org/inorder-successor-in-binary-search-tree/
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 12.2.
 */
auto InorderSuccessor_WithoutParentPointer(BinaryTree::Node::PointerType current_node,
                                           const BinaryTree::Node::PointerType x_node) {
    assert(x_node);

    if (x_node->right) {
        return MinimumNode(x_node->right);
    }

    BinaryTree::Node::PointerType successor;
    while (current_node) {
        if (x_node->value < current_node->value) {
            successor = current_node;
            current_node = current_node->left;
        } else if (x_node->value > current_node->value) {
            current_node = current_node->right;
        } else {
            break;
        }
    }

    return successor;
}


/**
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 4.6.
 */
auto InorderSuccessor_WithParentPointer(
    const BinaryTreeNodeWithParent::PointerType x_node) {
    if (not x_node) {
        return x_node;
    }

    if (x_node->right) {
        return LeftmostNode(x_node->right);
    } else {
        auto parent = x_node->parent.lock();
        for (auto current = x_node; parent and parent->left != current;) {
            current = parent;
            parent = current->parent.lock();
        }
        return parent;
    }
}

}//namespace


const auto SAMPLE1 = MakeTheSampleBST().GetRoot();
const auto SAMPLE_P1 = ToBinaryTreeWithParents(SAMPLE1);


THE_BENCHMARK(InorderSuccessor_WithoutParentPointer, SAMPLE1, SAMPLE1);

SIMPLE_TEST(InorderSuccessor_WithoutParentPointer, TestSAMPLE1,
            SAMPLE1->right, SAMPLE1, SAMPLE1);
SIMPLE_TEST(InorderSuccessor_WithoutParentPointer, TestSAMPLE2,
            nullptr, SAMPLE1, MaximumNode(SAMPLE1));
SIMPLE_TEST(InorderSuccessor_WithoutParentPointer, TestSAMPLE3,
            SAMPLE1->left, SAMPLE1, MinimumNode(SAMPLE1));


THE_BENCHMARK(InorderSuccessor_WithParentPointer, SAMPLE_P1);

SIMPLE_TEST(InorderSuccessor_WithParentPointer, TestSAMPLE1,
            SAMPLE_P1->right, SAMPLE_P1);
SIMPLE_TEST(InorderSuccessor_WithParentPointer, TestSAMPLE2,
            nullptr, MaximumNode(SAMPLE_P1));
SIMPLE_TEST(InorderSuccessor_WithParentPointer, TestSAMPLE3,
            SAMPLE_P1->left, MinimumNode(SAMPLE_P1));
