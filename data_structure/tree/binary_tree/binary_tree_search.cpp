#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_search.h"
#include "binary_tree_traversals.h"


namespace {

/** Iterative Search for a key 'x' in Binary Tree
 *
 * @reference   https://www.geeksforgeeks.org/iterative-search-for-a-key-x-in-binary-tree/
 * @reference   Search a node in Binary Tree
 *              https://www.geeksforgeeks.org/search-a-node-in-binary-tree/
 *
 * Given a Binary Tree and a key to be searched in it, write an iterative method that
 * returns true if key is present in Binary Tree, else false.
 */
inline auto
BinaryTreeSearch_LevelOrder(const BinaryTree::Node::PointerType root_node,
                            const BinaryTree::Node::ValueType x) {
    return not LevelOrderTraversal_LevelAware_Helper(root_node,
    [x](const auto & node) {
        return node.value != x;
    });
}


inline auto
BinaryTreePath_Preorder(const BinaryTree::Node::PointerType root_node,
                        const BinaryTree::Node::ValueType x) {
    BinaryTree::ArrayType path;
    if (not BinaryTreeSearch_Preorder(root_node, x, &path)) {
        path.clear();
    }

    return path;
}


/**
 * @reference   Check if two nodes are in same subtree of the root node
 *              https://www.geeksforgeeks.org/check-if-two-nodes-are-in-same-subtree-of-the-root-node/
 */


/**
 * @reference   Iterative program to find distance of a node from root
 *              https://www.geeksforgeeks.org/iterative-program-to-find-distance-of-a-node-from-root/
 *
 * @reference   Get level of a node in binary tree | iterative approach
 *              https://www.geeksforgeeks.org/get-level-node-binary-tree-iterative-approach/
 */
inline auto
BinaryTreeDistance_LevelOrder(const BinaryTree::Node::PointerType root_node,
                              const BinaryTree::Node::ValueType x) {
    int distance = -1;
    if (LevelOrderTraversal_LevelAware_Helper(root_node,
    [x](const auto & node) {
    return node.value != x;
},
[&distance]() {
    ++distance;
    return true;
})) {
        distance = -1;
    }
    return distance;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();


SIMPLE_BENCHMARK(BinaryTreeSearch_LevelOrder, Sample1, SAMPLE1, 3);
SIMPLE_BENCHMARK(BinaryTreeSearch_LevelOrder, Sample2, SAMPLE1, -1);

SIMPLE_TEST(BinaryTreeSearch_LevelOrder, TestSAMPLE1, true, SAMPLE1, 3);
SIMPLE_TEST(BinaryTreeSearch_LevelOrder, TestSAMPLE2, false, SAMPLE1, -1);


SIMPLE_BENCHMARK(BinaryTreeSearch_Preorder, Sample1, SAMPLE1, 3);
SIMPLE_BENCHMARK(BinaryTreeSearch_Preorder, Sample2, SAMPLE1, -1);

SIMPLE_TEST(BinaryTreeSearch_Preorder, TestSAMPLE1, true, SAMPLE1, 3);
SIMPLE_TEST(BinaryTreeSearch_Preorder, TestSAMPLE2, false, SAMPLE1, -1);


const BinaryTree::ArrayType EXPECTED1 = {1, 2, 5};


THE_BENCHMARK(BinaryTreePath_Preorder, SAMPLE1, 5);

SIMPLE_TEST(BinaryTreePath_Preorder, TestSAMPLE1, EXPECTED1, SAMPLE1, 5);


SIMPLE_BENCHMARK(BinaryTreeDistance_LevelOrder, Sample1, SAMPLE1, 3);
SIMPLE_BENCHMARK(BinaryTreeDistance_LevelOrder, Sample2, SAMPLE1, -1);

SIMPLE_TEST(BinaryTreeDistance_LevelOrder, TestSAMPLE1, 1, SAMPLE1, 3);
SIMPLE_TEST(BinaryTreeDistance_LevelOrder, TestSAMPLE2, 2, SAMPLE1, 5);
SIMPLE_TEST(BinaryTreeDistance_LevelOrder, TestSAMPLE3, 0, SAMPLE1, 1);
SIMPLE_TEST(BinaryTreeDistance_LevelOrder, TestSAMPLE4, -1, SAMPLE1, -1);
