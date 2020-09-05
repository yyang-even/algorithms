#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_search.h"
#include "binary_tree_traversals.h"


namespace {

/** Iterative Search for a key ‘x’ in Binary Tree
 *
 * @reference   https://www.geeksforgeeks.org/iterative-search-for-a-key-x-in-binary-tree/
 * @reference   Search a node in Binary Tree
 *              https://www.geeksforgeeks.org/search-a-node-in-binary-tree/
 *
 * Given a Binary Tree and a key to be searched in it, write an iterative method that
 * returns true if key is present in Binary Tree, else false.
 */
auto BinaryTreeSearch_LevelOrder(const BinaryTree::Node::PointerType root_node,
                                 const BinaryTree::Node::ValueType x) {
    return not LevelOrderTraversal_LevelAware_Helper(root_node,
    [x](const BinaryTree::Node & node) {
        return node.value != x;
    });
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();


SIMPLE_BENCHMARK(BinaryTreeSearch_LevelOrder, Sample1, SAMPLE1, 3);
SIMPLE_BENCHMARK(BinaryTreeSearch_LevelOrder, Sample2, SAMPLE1, -1);

SIMPLE_TEST(BinaryTreeSearch_LevelOrder, TestSAMPLE1, true, SAMPLE1, 3);
SIMPLE_TEST(BinaryTreeSearch_LevelOrder, TestSAMPLE2, false, SAMPLE1, -1);
