#include "common_header.h"

#include "binary_tree_search.h"
#include "binary_tree_traversals.h"
#include "clone_binary_tree.h"

#include "data_structure/tree/binary_tree/BST/binary_search_tree.h"
#include "data_structure/tree/binary_tree/BST/BST_search.h"


namespace {

/** Inorder Tree Traversal without Recursion
 *
 * @reference   https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion/
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 10.4-3.
 * @reference   Binary Tree Inorder Traversal
 *              https://leetcode.com/problems/binary-tree-inorder-traversal/
 */
auto InorderTraversal_Iterative(BinaryTree::Node::PointerType current_node) {
    BinaryTree::ArrayType outputs;

    std::stack<BinaryTree::Node::PointerType> remaining_nodes;
    while (current_node or not remaining_nodes.empty()) {
        while (current_node) {
            remaining_nodes.push(current_node);
            current_node = current_node->left;
        }

        current_node = remaining_nodes.top();
        remaining_nodes.pop();

        outputs.push_back(current_node->value);

        current_node = current_node->right;
    }

    return outputs;
}


/** Inorder Tree Traversal without recursion and without stack!
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 12.1-3.
 * @reference   https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion-and-without-stack/
 */
auto InorderTraversal_Morris(BinaryTree::Node::PointerType current_node) {
    BinaryTree::ArrayType outputs;

    auto previous_node = current_node;
    while (current_node) {
        if (not current_node->left) {
            outputs.push_back(current_node->value);
            current_node = current_node->right;
        } else {
            previous_node = current_node->left;
            while (previous_node->right and previous_node->right != current_node) {
                previous_node = previous_node->right;
            }

            if (not previous_node->right) {
                previous_node->right = current_node;
                current_node = current_node->left;
            } else {
                previous_node->right = nullptr;
                outputs.push_back(current_node->value);
                current_node = current_node->right;
            }
        }
    }

    return outputs;
}


inline auto
testInorderTraversal_Recursive(const BinaryTree::Node::PointerType root) {
    BinaryTree::ArrayType outputs;
    InorderTraversal_Recursive(root, outputs);
    return outputs;
}


/** Inorder Successor of a node in Binary Tree
 *
 * @reference   https://www.geeksforgeeks.org/inorder-succesor-node-binary-tree/
 */
BinaryTree::Node::PointerType
InorderSuccessor_Recursive(const BinaryTree::Node::PointerType node,
                           const BinaryTree::Node::PointerType x_node,
                           BinaryTree::Node::PointerType &successor) {
    if (node) {
        const auto right_result = InorderSuccessor_Recursive(node->right, x_node, successor);

        if (node->value == x_node->value) {
            return successor;
        }
        successor = node;

        const auto left_result = InorderSuccessor_Recursive(node->left, x_node, successor);

        return right_result ? right_result : left_result;
    }

    return BinaryTree::Node::PointerType{};
}

inline auto InorderSuccessor_Recursive(const BinaryTree::Node::PointerType node,
                                       const BinaryTree::Node::PointerType x_node) {
    BinaryTree::Node::PointerType successor;
    return InorderSuccessor_Recursive(node, x_node, successor);
}


/**
 * @reference   Convert BST to Greater Tree
 *              https://leetcode.com/problems/convert-bst-to-greater-tree/
 *
 * Given the root of a Binary Search Tree (BST), convert it to a Greater Tree such that
 * every key of the original BST is changed to the original key plus the sum of all keys
 * greater than the original key in BST.
 * As a reminder, a binary search tree is a tree that satisfies these constraints:
 *  The left subtree of a node contains only nodes with keys less than the node's key.
 *  The right subtree of a node contains only nodes with keys greater than the node's key.
 *  Both the left and right subtrees must also be binary search trees.
 *
 * @reference   Binary Search Tree to Greater Sum Tree
 *              https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/
 *
 * Given the root of a Binary Search Tree (BST), convert it to a Greater Tree such that
 * every key of the original BST is changed to the original key plus the sum of all keys
 * greater than the original key in BST.
 * As a reminder, a binary search tree is a tree that satisfies these constraints:
 *  The left subtree of a node contains only nodes with keys less than the node's key.
 *  The right subtree of a node contains only nodes with keys greater than the node's key.
 *  Both the left and right subtrees must also be binary search trees.
 */


/** Inorder Successor in Binary Search Tree
 *
 * @reference   https://www.geeksforgeeks.org/inorder-successor-in-binary-search-tree/
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 12.2.
 */
auto InorderSuccessor_WithoutParentPointer(BinaryTree::Node::PointerType current_node,
                                           const BinaryTree::Node::PointerType x_node) {
    assert(x_node);

    if (x_node->right) {
        return MinimumNode(x_node->right);
    }

    BinaryTree::Node::PointerType successor;
    while (current_node) {
        if (x_node->value < current_node->value) {
            successor = current_node;
            current_node = current_node->left;
        } else if (x_node->value > current_node->value) {
            current_node = current_node->right;
        } else {
            break;
        }
    }

    return successor;
}


/**
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 4.6.
 */
auto InorderSuccessor_WithParentPointer(
    const BinaryTreeNodeWithParent::PointerType x_node) {
    if (not x_node) {
        return x_node;
    }

    if (x_node->right) {
        return LeftmostNode(x_node->right);
    } else {
        auto parent = x_node->parent.lock();
        for (auto current = x_node; parent and parent->left != current;) {
            current = parent;
            parent = current->parent.lock();
        }
        return parent;
    }
}


/** Inorder Predecessor in Binary Search Tree
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 12.2-3.
 */
auto InorderPredecessor_WithoutParentPointer(BinaryTree::Node::PointerType current_node,
                                             const BinaryTree::Node::PointerType x_node) {
    assert(x_node);

    if (x_node->left) {
        return MaximumNode(x_node->left);
    }

    BinaryTree::Node::PointerType predecessor;
    while (current_node) {
        if (x_node->value < current_node->value) {
            current_node = current_node->left;
        } else if (x_node->value > current_node->value) {
            predecessor = current_node;
            current_node = current_node->right;
        } else {
            break;
        }
    }

    return predecessor;
}


/**
 * @reference   Binary Search Tree Iterator
 *              https://leetcode.com/problems/binary-search-tree-iterator/
 *
 * Implement the BSTIterator class that represents an iterator over the in-order traversal
 * of a binary search tree (BST):
 *  BSTIterator(TreeNode root) Initializes an object of the BSTIterator class. The root of
 *      the BST is given as part of the constructor. The pointer should be initialized to
 *      a non-existent number smaller than any element in the BST.
 *  boolean hasNext() Returns true if there exists a number in the traversal to the right
 *      of the pointer, otherwise returns false.
 *  int next() Moves the pointer to the right, then returns the number at the pointer.
 * Notice that by initializing the pointer to a non-existent smallest number, the first
 * call to next() will return the smallest element in the BST.
 * You may assume that next() calls will always be valid. That is, there will be at least
 * a next number in the in-order traversal when next() is called.
 * Follow up: Could you implement next() and hasNext() to run in average O(1) time and use
 * O(h) memory, where h is the height of the tree?
 */
class BSTIterator {
public:
    explicit BSTIterator(const BinaryTree::Node::PointerType root) {
        pushAll(root);
    }

    auto hasNext() const {
        return not m_stack.empty();
    }

    auto next() {
        const auto node = m_stack.top();
        m_stack.pop();
        pushAll(node->right);
        return node->value;
    }

private:
    void pushAll(BinaryTree::Node::PointerType node) {
        for (; node; node = node->left) {
            m_stack.push(node);
        }
    }

    std::stack<BinaryTree::Node::PointerType> m_stack;
};

inline auto testBSTIterator(const BinaryTree::Node::PointerType root) {
    BSTIterator iter{root};

    BinaryTree::ArrayType result;
    while (iter.hasNext()) {
        result.push_back(iter.next());
    }

    return result;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleBST();
const auto SAMPLE_P1 = ToBinaryTreeWithParents(SAMPLE1);


THE_BENCHMARK(InorderSuccessor_WithoutParentPointer, SAMPLE1, SAMPLE1);

SIMPLE_TEST(InorderSuccessor_WithoutParentPointer, TestSAMPLE1,
            SAMPLE1->right, SAMPLE1, SAMPLE1);
SIMPLE_TEST(InorderSuccessor_WithoutParentPointer, TestSAMPLE2,
            nullptr, SAMPLE1, MaximumNode(SAMPLE1));
SIMPLE_TEST(InorderSuccessor_WithoutParentPointer, TestSAMPLE3,
            SAMPLE1->left, SAMPLE1, MinimumNode(SAMPLE1));


THE_BENCHMARK(InorderSuccessor_WithParentPointer, SAMPLE_P1);

SIMPLE_TEST(InorderSuccessor_WithParentPointer, TestSAMPLE1,
            SAMPLE_P1->right, SAMPLE_P1);
SIMPLE_TEST(InorderSuccessor_WithParentPointer, TestSAMPLE2,
            nullptr, MaximumNode(SAMPLE_P1));
SIMPLE_TEST(InorderSuccessor_WithParentPointer, TestSAMPLE3,
            SAMPLE_P1->left, MinimumNode(SAMPLE_P1));


THE_BENCHMARK(InorderPredecessor_WithoutParentPointer, SAMPLE1, SAMPLE1);

SIMPLE_TEST(InorderPredecessor_WithoutParentPointer, TestSAMPLE1,
            SAMPLE1->left->right, SAMPLE1, SAMPLE1);
SIMPLE_TEST(InorderPredecessor_WithoutParentPointer, TestSAMPLE2,
            SAMPLE1, SAMPLE1, MaximumNode(SAMPLE1));
SIMPLE_TEST(InorderPredecessor_WithoutParentPointer, TestSAMPLE3,
            nullptr, SAMPLE1, MinimumNode(SAMPLE1));


const auto SAMPLE1C = MakeTheSampleCompleteTree().GetRoot();


THE_BENCHMARK(InorderSuccessor_Recursive, SAMPLE1C, SAMPLE1C);

SIMPLE_TEST(InorderSuccessor_Recursive, TestSAMPLE1,
            SAMPLE1C->right, SAMPLE1C, SAMPLE1C);
SIMPLE_TEST(InorderSuccessor_Recursive, TestSAMPLE2,
            nullptr, SAMPLE1C, SAMPLE1C->right);
SIMPLE_TEST(InorderSuccessor_Recursive, TestSAMPLE3,
            SAMPLE1C->left, SAMPLE1C, LeftmostNode(SAMPLE1C));


const BinaryTree::ArrayType EXPECTED_INORDER = {4, 2, 5, 1, 3};


SIMPLE_TEST(testBSTIterator, TestSAMPLE1, EXPECTED_INORDER, SAMPLE1C);


THE_BENCHMARK(InorderTraversal_Iterative, SAMPLE1C);

SIMPLE_TEST(InorderTraversal_Iterative, TestSAMPLE1, EXPECTED_INORDER, SAMPLE1C);


THE_BENCHMARK(InorderTraversal_Morris, SAMPLE1C);

SIMPLE_TEST(InorderTraversal_Morris, TestSAMPLE1, EXPECTED_INORDER, SAMPLE1C);


SIMPLE_TEST(testInorderTraversal_Recursive, TestSAMPLE1, EXPECTED_INORDER, SAMPLE1C);
