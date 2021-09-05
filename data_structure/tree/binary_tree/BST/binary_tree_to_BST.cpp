#include "common_header.h"

#include "binary_search_tree.h"
#include "data_structure/tree/binary_tree/binary_tree_traversals.h"
#include "data_structure/tree/binary_tree/clone_binary_tree.h"
#include "data_structure/tree/binary_tree/compare_binary_trees.h"


namespace {

/** Binary Tree to Binary Search Tree Conversion
 *
 * @reference   https://www.geeksforgeeks.org/binary-tree-to-binary-search-tree-conversion/
 * @reference   Binary Tree to Binary Search Tree Conversion using STL set
 *              https://www.geeksforgeeks.org/binary-tree-binary-search-tree-conversion-using-stl-set/
 *
 * Given a Binary Tree, convert it to a Binary Search Tree. The conversion must be done
 * in such a way that keeps the original structure of Binary Tree.
 */
inline void copyToBST(BinaryTree::ArrayType::const_iterator &iter,
                      const BinaryTree::Node::PointerType node) {
    if (node) {
        copyToBST(iter, node->left);

        node->value = *(iter++);

        copyToBST(iter, node->right);
    }
}

auto ToBST(const BinaryTree::Node::PointerType binary_tree_root) {
    BinaryTree::ArrayType inorder_array;
    InorderTraversal_Recursive(binary_tree_root, inorder_array);

    std::sort(inorder_array.begin(), inorder_array.end());

    auto cbegin = inorder_array.cbegin();
    copyToBST(cbegin, binary_tree_root);

    return binary_tree_root;
}

}//namespace


const auto SAMPLE_BINARY_TREE = MakeTheSampleCompleteTree().GetRoot();
const auto SAMPLE_BST = MakeTheSampleBST();


THE_BENCHMARK(ToBST, CloneBinaryTree(SAMPLE_BINARY_TREE).GetRoot());

SIMPLE_TEST(areIdenticalTrees, TestSAMPLE1, true,
            SAMPLE_BST, ToBST(CloneBinaryTree(SAMPLE_BINARY_TREE).GetRoot()));
