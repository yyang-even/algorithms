#include "common_header.h"

#include "binary_search_tree.h"
#include "BST_search.h"
#include "data_structure/tree/binary_tree/clone_binary_tree.h"
#include "is_BST.h"


namespace {

/** Binary Search Tree | Set 2 (Delete)
 *
 * @reference   https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 12.3.
 * @reference   Delete Node in a BST
 *              https://leetcode.com/problems/delete-node-in-a-bst/
 *
 * Given a root node reference of a BST and a key, delete the node with the given key in
 * the BST. Return the root node reference (possibly updated) of the BST.
 * Basically, the deletion can be divided into two stages:
 *  Search for a node to remove.
 *  If the node is found, delete the node.
 * Each node has a unique value.
 * Follow up: Could you solve it with time complexity O(height of tree)?
 */
BinaryTree::Node::PointerType BSTDelete(const BinaryTree::Node::PointerType node,
                                        const BinaryTree::Node::ValueType x) {
    if (node) {
        if (x < node->value) {
            node->left = BSTDelete(node->left, x);
        } else if (node->value < x) {
            node->right = BSTDelete(node->right, x);
        } else {
            if (not node->left) {
                return node->right;
            } else if (not node->right) {
                return node->left;
            }

            const auto successor = MinimumNode(node->right);
            node->value = successor->value;
            node->right = BSTDelete(node->right, successor->value);
        }
    }

    return node;
}

BinaryTree::Node::PointerType
BSTDelete_Optimized(const BinaryTree::Node::PointerType node,
                    const BinaryTree::Node::ValueType x) {
    if (node) {
        if (x < node->value) {
            node->left = BSTDelete(node->left, x);
        } else if (node->value < x) {
            node->right = BSTDelete(node->right, x);
        } else {
            if (not node->left) {
                return node->right;
            } else if (not node->right) {
                return node->left;
            }

            BinaryTree::Node::PointerType successor_parent;
            auto successor = node->right;
            while (successor->left) {
                successor_parent = successor;
                successor = successor->left;
            }

            node->value = successor->value;
            if (not successor_parent) {
                node->right = nullptr;
            } else {
                successor_parent->left = successor->right;
            }
        }
    }

    return node;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleBST();


THE_BENCHMARK(BSTDelete, CloneBinaryTree(SAMPLE1).GetRoot(), 4);

SIMPLE_TEST(isBST_Recursive_Inorder, TestSAMPLE0, true,
            BSTDelete(CloneBinaryTree(SAMPLE1).GetRoot(), 0));
SIMPLE_TEST(isBST_Recursive_Inorder, TestSAMPLE1, true,
            BSTDelete(CloneBinaryTree(SAMPLE1).GetRoot(), 1));
SIMPLE_TEST(isBST_Recursive_Inorder, TestSAMPLE2, true,
            BSTDelete(CloneBinaryTree(SAMPLE1).GetRoot(), 2));
SIMPLE_TEST(isBST_Recursive_Inorder, TestSAMPLE3, true,
            BSTDelete(CloneBinaryTree(SAMPLE1).GetRoot(), 3));
SIMPLE_TEST(isBST_Recursive_Inorder, TestSAMPLE4, true,
            BSTDelete(CloneBinaryTree(SAMPLE1).GetRoot(), 4));
SIMPLE_TEST(isBST_Recursive_Inorder, TestSAMPLE5, true,
            BSTDelete(CloneBinaryTree(SAMPLE1).GetRoot(), 5));


THE_BENCHMARK(BSTDelete_Optimized, CloneBinaryTree(SAMPLE1).GetRoot(), 4);

SIMPLE_TEST(isBST_Recursive_Inorder, TestSAMPLE00, true,
            BSTDelete_Optimized(CloneBinaryTree(SAMPLE1).GetRoot(), 0));
SIMPLE_TEST(isBST_Recursive_Inorder, TestSAMPLE01, true,
            BSTDelete_Optimized(CloneBinaryTree(SAMPLE1).GetRoot(), 1));
SIMPLE_TEST(isBST_Recursive_Inorder, TestSAMPLE02, true,
            BSTDelete_Optimized(CloneBinaryTree(SAMPLE1).GetRoot(), 2));
SIMPLE_TEST(isBST_Recursive_Inorder, TestSAMPLE03, true,
            BSTDelete_Optimized(CloneBinaryTree(SAMPLE1).GetRoot(), 3));
SIMPLE_TEST(isBST_Recursive_Inorder, TestSAMPLE04, true,
            BSTDelete_Optimized(CloneBinaryTree(SAMPLE1).GetRoot(), 4));
SIMPLE_TEST(isBST_Recursive_Inorder, TestSAMPLE05, true,
            BSTDelete_Optimized(CloneBinaryTree(SAMPLE1).GetRoot(), 5));
