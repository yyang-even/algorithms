#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_height.h"
#include "binary_tree_traversals.h"


namespace {

/**
 * @reference   Iterative Method to find Height of Binary Tree
 *              https://www.geeksforgeeks.org/iterative-method-to-find-height-of-binary-tree/
 */
auto Height_Iterative(const BinaryTree::Node::PointerType node) {
    unsigned height = 0;
    LevelOrderTraversal_LevelAware_Helper(node, nullptr, [&height]() {
        ++height;
    });
    return height;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleTree().GetRoot();


SIMPLE_BENCHMARK(Height_Recursive, SAMPLE1);

SIMPLE_TEST(Height_Recursive, TestSAMPLE1, 3, SAMPLE1);


SIMPLE_BENCHMARK(Height_Iterative, SAMPLE1);

SIMPLE_TEST(Height_Iterative, TestSAMPLE1, 3, SAMPLE1);
