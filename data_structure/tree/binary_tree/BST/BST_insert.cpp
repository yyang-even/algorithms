#include "common_header.h"

#include "binary_search_tree.h"
#include "is_BST.h"


namespace {

/** Binary Search Tree | Set 1 (Search and Insertion)
 *
 * @reference   https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
 */
auto BSTInsert(const BinaryTree::Node::PointerType node,
               const BinaryTree::Node::ValueType x) {
    if (not node) {
        return std::make_shared<BinaryTree::Node>(x);
    }

    if (x < node->value) {
        node->left = BSTInsert(node->left, x);
    } else {
        node->right = BSTInsert(node->right, x);
    }

    return node;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleBST().GetRoot();


SIMPLE_BENCHMARK(BSTInsert, SAMPLE1, -1);

SIMPLE_TEST(isBST_Recursive_Inorder, TestSAMPLE1, true, BSTInsert(SAMPLE1, 14));
