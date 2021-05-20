#include "common_header.h"

#include "binary_search_tree.h"
#include "BST_search.h"


namespace {

/** Inorder Predecessor in Binary Search Tree
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 12.2-3.
 */
auto InorderPredecessor_WithoutParentPointer(BinaryTree::Node::PointerType current_node,
                                             const BinaryTree::Node::PointerType x_node) {
    assert(x_node);

    if (x_node->left) {
        return MaximumNode(x_node->left);
    }

    BinaryTree::Node::PointerType predecessor;
    while (current_node) {
        if (x_node->value < current_node->value) {
            current_node = current_node->left;
        } else if (x_node->value > current_node->value) {
            predecessor = current_node;
            current_node = current_node->right;
        } else {
            break;
        }
    }

    return predecessor;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleBST().GetRoot();


THE_BENCHMARK(InorderPredecessor_WithoutParentPointer, SAMPLE1, SAMPLE1);

SIMPLE_TEST(InorderPredecessor_WithoutParentPointer, TestSAMPLE1,
            SAMPLE1->left->right, SAMPLE1, SAMPLE1);
SIMPLE_TEST(InorderPredecessor_WithoutParentPointer, TestSAMPLE2,
            SAMPLE1, SAMPLE1, MaximumNode(SAMPLE1));
SIMPLE_TEST(InorderPredecessor_WithoutParentPointer, TestSAMPLE3,
            nullptr, SAMPLE1, MinimumNode(SAMPLE1));
