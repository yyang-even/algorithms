#include "common_header.h"

#include "binary_tree.h"
#include "clone_binary_tree.h"


namespace {

auto isSameTree(const BinaryTree::Node::PointerType lhs_node,
                const BinaryTree::Node::PointerType rhs_node) {
    return lhs_node == rhs_node;
}

/** Write Code to Determine if Two Trees are Identical
 *
 * @reference   https://www.geeksforgeeks.org/write-c-code-to-determine-if-two-trees-are-identical/
 */
auto areIdenticalTrees(const BinaryTree::Node::PointerType lhs_node,
                       const BinaryTree::Node::PointerType rhs_node) {
    if (isSameTree(lhs_node, rhs_node)) {
        return true;
    }

    if (lhs_node and rhs_node) {
        return lhs_node->value == rhs_node->value and
               areIdenticalTrees(lhs_node->left, rhs_node->left) and
               areIdenticalTrees(lhs_node->right, rhs_node->right);
    }
    return false;
}


/** Iterative function to check if two trees are identical
 *
 * @reference   https://www.geeksforgeeks.org/iterative-function-check-two-trees-identical/
 */
auto areIdenticalTrees_Iterative(BinaryTree::Node::PointerType lhs_node,
                                 BinaryTree::Node::PointerType rhs_node) {
    std::queue<BinaryTree::Node::PointerType> lhs_remaining_nodes;
    std::queue<BinaryTree::Node::PointerType> rhs_remaining_nodes;
    lhs_remaining_nodes.push(lhs_node);
    rhs_remaining_nodes.push(rhs_node);

    while (not lhs_remaining_nodes.empty()) {
        lhs_node = lhs_remaining_nodes.front();
        lhs_remaining_nodes.pop();
        rhs_node = rhs_remaining_nodes.front();
        rhs_remaining_nodes.pop();

        if (isSameTree(lhs_node, rhs_node)) {
            return true;
        }
        if (not(lhs_node and rhs_node and lhs_node->value == rhs_node->value)) {
            return false;
        }

        lhs_remaining_nodes.push(lhs_node->left);
        lhs_remaining_nodes.push(lhs_node->right);
        rhs_remaining_nodes.push(rhs_node->left);
        rhs_remaining_nodes.push(rhs_node->right);
    }

    return true;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();
const auto EMPTY_TREE = BinaryTree {} .GetRoot();
const auto CLONE_SAMPLE1 = CloneBinaryTree(SAMPLE1).GetRoot();


SIMPLE_BENCHMARK(isSameTree, SAMPLE1, SAMPLE1);

SIMPLE_TEST(isSameTree, TestSAMPLE1, true, SAMPLE1, SAMPLE1);
SIMPLE_TEST(isSameTree, TestSAMPLE2, true, EMPTY_TREE, EMPTY_TREE);
SIMPLE_TEST(isSameTree, TestSAMPLE3, false, SAMPLE1, EMPTY_TREE);
SIMPLE_TEST(isSameTree, TestSAMPLE4, false, SAMPLE1, CLONE_SAMPLE1);


SIMPLE_BENCHMARK(areIdenticalTrees, SAMPLE1, SAMPLE1);

SIMPLE_TEST(areIdenticalTrees, TestSAMPLE1, true, SAMPLE1, SAMPLE1);
SIMPLE_TEST(areIdenticalTrees, TestSAMPLE2, true, EMPTY_TREE, EMPTY_TREE);
SIMPLE_TEST(areIdenticalTrees, TestSAMPLE3, false, SAMPLE1, EMPTY_TREE);
SIMPLE_TEST(areIdenticalTrees, TestSAMPLE4, true, SAMPLE1, CLONE_SAMPLE1);


SIMPLE_BENCHMARK(areIdenticalTrees_Iterative, SAMPLE1, SAMPLE1);

SIMPLE_TEST(areIdenticalTrees_Iterative, TestSAMPLE1, true, SAMPLE1, SAMPLE1);
SIMPLE_TEST(areIdenticalTrees_Iterative, TestSAMPLE2, true, EMPTY_TREE, EMPTY_TREE);
SIMPLE_TEST(areIdenticalTrees_Iterative, TestSAMPLE3, false, SAMPLE1, EMPTY_TREE);
SIMPLE_TEST(areIdenticalTrees_Iterative, TestSAMPLE4, true, SAMPLE1, CLONE_SAMPLE1);
