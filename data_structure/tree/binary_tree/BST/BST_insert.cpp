#include "common_header.h"

#include "binary_search_tree.h"
#include "data_structure/tree/binary_tree/clone_binary_tree.h"
#include "is_BST.h"


namespace {

/** Binary Search Tree | Set 1 (Search and Insertion)
 *
 * @reference   https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 12.3. Exercises 12.3-1.
 */
auto BSTInsert_Recursive(const BinaryTree::Node::PointerType node,
                         const BinaryTree::Node::ValueType x) {
    if (not node) {
        return std::make_shared<BinaryTree::Node>(x);
    }

    if (x < node->value) {
        node->left = BSTInsert_Recursive(node->left, x);
    } else {
        node->right = BSTInsert_Recursive(node->right, x);
    }

    return node;
}


/**
 * @reference   Insert a node in Binary Search Tree Iteratively
 *              https://www.geeksforgeeks.org/insert-a-node-in-binary-search-tree-iteratively/
 */
auto BSTInsert_Iterative(const BinaryTree::Node::PointerType root_node,
                         const BinaryTree::Node::ValueType x) {
    const auto new_node = std::make_shared<BinaryTree::Node>(x);

    auto current_node = root_node;
    BinaryTree::Node::PointerType parent;
    while (current_node) {
        parent = current_node;
        if (x < current_node->value) {
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }
    }

    if (not parent) {
        return new_node;
    } else if (x < parent->value) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }

    return root_node;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleBST().GetRoot();


THE_BENCHMARK(BSTInsert_Recursive, CloneBinaryTree(SAMPLE1).GetRoot(), -1);

SIMPLE_TEST(isBST_Recursive_Inorder, TestSAMPLE1, true,
            BSTInsert_Recursive(CloneBinaryTree(SAMPLE1).GetRoot(), 14));


THE_BENCHMARK(BSTInsert_Iterative, CloneBinaryTree(SAMPLE1).GetRoot(), -1);

SIMPLE_TEST(isBST_Recursive_Inorder, TestSAMPLE2, true,
            BSTInsert_Iterative(CloneBinaryTree(SAMPLE1).GetRoot(), 14));
