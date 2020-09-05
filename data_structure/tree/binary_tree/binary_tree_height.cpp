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
    LevelOrderTraversal_LevelAware_Helper(node, {},
    [&height]() {
        ++height;
        return true;
    });
    return height;
}


/**
 * @reference   Height of a complete binary tree (or Heap) with N nodes
 *              https://www.geeksforgeeks.org/height-complete-binary-tree-heap-n-nodes/
 */
std::size_t HeightOfCompleteTree(const std::size_t number_of_nodes) {
    return std::ceil(std::log2(number_of_nodes + 1));
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();


SIMPLE_BENCHMARK(Height_Recursive, Sample1, SAMPLE1);

SIMPLE_TEST(Height_Recursive, TestSAMPLE1, 3, SAMPLE1);


SIMPLE_BENCHMARK(Height_Iterative, Sample1, SAMPLE1);

SIMPLE_TEST(Height_Iterative, TestSAMPLE1, 3, SAMPLE1);


SIMPLE_BENCHMARK(HeightOfCompleteTree, Sample1, 5);

SIMPLE_TEST(HeightOfCompleteTree, TestSAMPLE1, 3, 5);
