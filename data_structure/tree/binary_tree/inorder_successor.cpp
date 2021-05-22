#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_search.h"


namespace {

/** Inorder Successor of a node in Binary Tree
 *
 * @reference   https://www.geeksforgeeks.org/inorder-succesor-node-binary-tree/
 */
BinaryTree::Node::PointerType
InorderSuccessor_Recursive(const BinaryTree::Node::PointerType node,
                           const BinaryTree::Node::PointerType x_node,
                           BinaryTree::Node::PointerType &successor) {
    if (node) {
        const auto right_result = InorderSuccessor_Recursive(node->right, x_node, successor);

        if (node->value == x_node->value) {
            return successor;
        }
        successor = node;

        const auto left_result = InorderSuccessor_Recursive(node->left, x_node, successor);

        return right_result ? right_result : left_result;
    }

    return BinaryTree::Node::PointerType{};
}

inline auto InorderSuccessor_Recursive(const BinaryTree::Node::PointerType node,
                                       const BinaryTree::Node::PointerType x_node) {
    BinaryTree::Node::PointerType successor;
    return InorderSuccessor_Recursive(node, x_node, successor);
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();


THE_BENCHMARK(InorderSuccessor_Recursive, SAMPLE1, SAMPLE1);

SIMPLE_TEST(InorderSuccessor_Recursive, TestSAMPLE1,
            SAMPLE1->right, SAMPLE1, SAMPLE1);
SIMPLE_TEST(InorderSuccessor_Recursive, TestSAMPLE2,
            nullptr, SAMPLE1, SAMPLE1->right);
SIMPLE_TEST(InorderSuccessor_Recursive, TestSAMPLE3,
            SAMPLE1->left, SAMPLE1, LeftmostNode(SAMPLE1));
