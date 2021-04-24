#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_deletion.h"
#include "binary_tree_traversals.h"
#include "clone_binary_tree.h"
#include "compare_binary_trees.h"


namespace {

/** Insertion in a Binary Tree in level order
 *
 * @reference   https://www.geeksforgeeks.org/insertion-in-a-binary-tree-in-level-order/
 *
 * Given a binary tree and a key, insert the key into the binary tree at first position
 * available in level order.
 */
auto LevelOrderInsert(const BinaryTree::Node::PointerType root_node,
                      const BinaryTree::Node::ValueType x) {
    assert(root_node);

    LevelOrderTraversal_LevelAware_Helper(root_node,
    [x](auto & node) {
        if (not node.left) {
            node.left = std::make_shared<BinaryTree::Node>(x);
            return false;
        }

        if (not node.right) {
            node.right = std::make_shared<BinaryTree::Node>(x);
            return false;
        }

        return true;
    }, {});

    return root_node;
}

}//namespace


const auto SAMPLE0 = MakeTheSampleCompleteTree().GetRoot();
const auto SAMPLE1 = LevelOrderInsert(
                         BinaryTreeDeletion_Subtree(CloneBinaryTree(SAMPLE0), 4).GetRoot(), 4);


SIMPLE_BENCHMARK(LevelOrderInsert, Sample1, CloneBinaryTree(SAMPLE0).GetRoot(), 4);

SIMPLE_TEST(areIdenticalTrees, TestSAMPLE1, true, SAMPLE0, SAMPLE1);
