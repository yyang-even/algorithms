#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_traversals.h"


namespace {

/** Write a program to Calculate Size of a tree | Recursion
 *
 * @reference   https://www.geeksforgeeks.org/write-a-c-program-to-calculate-size-of-a-tree/
 * @reference   Relationship between number of nodes and height of binary tree
 *              https://www.geeksforgeeks.org/relationship-number-nodes-height-binary-tree/
 */
unsigned Size_Recursive(const BinaryTree::Node::PointerType node) {
    if (node) {
        return Size_Recursive(node->left) + 1 + Size_Recursive(node->right);
    }
    return 0;
}


/**
 * @reference   Iterative program to Calculate Size of a tree
 *              https://www.geeksforgeeks.org/write-program-calculate-size-tree-iterative/
 */
auto Size_Iterative(const BinaryTree::Node::PointerType root_node) {
    unsigned size = 0;
    LevelOrderTraversal_LevelAware_Helper(root_node,
    [&size](const auto &) {
        ++size;
        return true;
    }, {});

    return size;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();


SIMPLE_BENCHMARK(Size_Recursive, Sample1, SAMPLE1);

SIMPLE_TEST(Size_Recursive, TestSAMPLE1, 5, SAMPLE1);


SIMPLE_BENCHMARK(Size_Iterative, Sample1, SAMPLE1);

SIMPLE_TEST(Size_Iterative, TestSAMPLE1, 5, SAMPLE1);
