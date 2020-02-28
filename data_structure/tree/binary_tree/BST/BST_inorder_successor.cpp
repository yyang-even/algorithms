#include "common_header.h"

#include "binary_search_tree.h"
#include "BST_search.h"

namespace {

/** Inorder Successor in Binary Search Tree
 *
 * @reference   https://www.geeksforgeeks.org/inorder-successor-in-binary-search-tree/
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 12.2.
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

inline auto InorderSuccessor_WithoutParentPointer(const BinaryTree::Node::PointerType root_node,
        const BinaryTree::Node::ValueType x) {
    const auto x_node = BSTSearch_Iterative(root_node, x);
    return InorderSuccessor_WithoutParentPointer(root_node, x_node);
}

}//namespace


const auto SAMPLE1 = MakeTheSampleBST().GetRoot();


SIMPLE_BENCHMARK(InorderSuccessor_WithoutParentPointer, SAMPLE1, SAMPLE1);

SIMPLE_TEST(InorderSuccessor_WithoutParentPointer, TestSAMPLE1,
            SAMPLE1->right, SAMPLE1, SAMPLE1->value);
SIMPLE_TEST(InorderSuccessor_WithoutParentPointer, TestSAMPLE2,
            nullptr, SAMPLE1, SAMPLE1->right);
SIMPLE_TEST(InorderSuccessor_WithoutParentPointer, TestSAMPLE3,
            SAMPLE1->left, SAMPLE1, MinimumNode(SAMPLE1));
