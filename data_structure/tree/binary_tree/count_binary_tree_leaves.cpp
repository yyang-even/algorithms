#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_traversals.h"


namespace {

/** Program to count leaf nodes in a binary tree
 *
 * @reference   https://www.geeksforgeeks.org/write-a-c-program-to-get-count-of-leaf-nodes-in-a-binary-tree/
 */
auto CountLeaves_Recursive(const BinaryTree::Node::PointerType node) {
    if (not node) {
        return 0;
    }
    if (not node->left and not node->right) {
        return 1;
    }
    return CountLeaves_Recursive(node->left) + CountLeaves_Recursive(node->right);
}


/**
 * @reference   Iterative program to count leaf nodes in a Binary Tree
 *              https://www.geeksforgeeks.org/iterative-program-count-leaf-nodes-binary-tree/
 */
auto CountLeaves_Iterative(const BinaryTree::Node::PointerType root_node) {
    unsigned leaves_count = 0;
    LevelOrderTraversal_LevelAware_Helper(root_node,
    [&leaves_count](const auto & node) {
        if (not node.left and not node.right) {
            ++leaves_count;
        }
        return true;
    }, {});

    return leaves_count;
}


/** Count Non-Leaf nodes in a Binary Tree
 *
 * @reference   https://www.geeksforgeeks.org/count-non-leaf-nodes-binary-tree/
 */


/** Count half nodes in a Binary tree (Iterative and Recursive)
 *
 * @reference   https://www.geeksforgeeks.org/count-half-nodes-in-a-binary-tree-iterative-and-recursive/
 */


/** Count full nodes in a Binary tree (Iterative and Recursive)
 *
 * @reference   https://www.geeksforgeeks.org/count-full-nodes-binary-tree-iterative-recursive/
 */

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();
const auto EMPTY_TREE = BinaryTree {} .GetRoot();


SIMPLE_BENCHMARK(CountLeaves_Recursive, Sample1, SAMPLE1);

SIMPLE_TEST(CountLeaves_Recursive, TestSAMPLE0, 0, EMPTY_TREE);
SIMPLE_TEST(CountLeaves_Recursive, TestSAMPLE1, 3, SAMPLE1);


SIMPLE_BENCHMARK(CountLeaves_Iterative, Sample1, SAMPLE1);

SIMPLE_TEST(CountLeaves_Iterative, TestSAMPLE0, 0, EMPTY_TREE);
SIMPLE_TEST(CountLeaves_Iterative, TestSAMPLE1, 3, SAMPLE1);
