#include "common_header.h"

#include "binary_tree.h"


namespace {

/** Tree Traversals (Inorder, Preorder and Postorder)
 *
 * @reference   https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 10.4-2.
 */
auto InorderTraversal_Recursive(const BinaryTree::Node::PointerType node,
                                BinaryTree::ArrayType &outputs) {
    if (not node) {
        return;
    }

    InorderTraversal_Recursive(node->left, outputs);
    outputs.push_back(node->value);
    InorderTraversal_Recursive(node->right, outputs);
}


auto PreorderTraversal(const BinaryTree::Node::PointerType node, BinaryTree::ArrayType &outputs) {
    if (not node) {
        return;
    }

    outputs.push_back(node->value);
    PreorderTraversal(node->left, outputs);
    PreorderTraversal(node->right, outputs);
}


auto PostorderTraversal(const BinaryTree::Node::PointerType node, BinaryTree::ArrayType &outputs) {
    if (not node) {
        return;
    }

    PostorderTraversal(node->left, outputs);
    PostorderTraversal(node->right, outputs);
    outputs.push_back(node->value);
}


/** Inorder Tree Traversal without Recursion
 *
 * @reference   https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion/
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 10.4-3.
 */
auto InorderTraversal_Iterative(BinaryTree::Node::PointerType current_node,
                                BinaryTree::ArrayType &outputs) {
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
}


template <typename TraversalFunction>
auto TreeTraversal(const BinaryTree &binary_tree, const TraversalFunction traversal) {
    BinaryTree::ArrayType outputs;
    traversal(binary_tree.GetRoot(), outputs);
    return outputs;
}


auto MakeTheSampleTree() {
    BinaryTree binary_tree{1};
    auto &root = *binary_tree.GetRoot();
    auto &left_child = *SetLeftChild(root, 2);
    SetRightChild(root, 3);
    SetLeftChild(left_child, 4);
    SetRightChild(left_child, 5);

    return binary_tree;
}

}//namespace


#ifdef WANT_TESTS
#define BinaryTreeTraversalTest(traversalFunctionName, expectedResult) namespace {  \
    TEST(BinaryTreeTraversalTest, test##traversalFunctionName) {                    \
        const auto sample_tree = MakeTheSampleTree();                               \
        const auto result = TreeTraversal(sample_tree, traversalFunctionName);      \
        EXPECT_EQ(expectedResult, result);                                          \
    }                                                                               \
}


const BinaryTree::ArrayType EXPECTED_INORDER = {4, 2, 5, 1, 3};
const BinaryTree::ArrayType EXPECTED_PREORDER = {1, 2, 4, 5, 3};
const BinaryTree::ArrayType EXPECTED_POSTORDER = {4, 5, 2, 3, 1};


BinaryTreeTraversalTest(InorderTraversal_Recursive, EXPECTED_INORDER);


BinaryTreeTraversalTest(PreorderTraversal, EXPECTED_PREORDER);


BinaryTreeTraversalTest(PostorderTraversal, EXPECTED_POSTORDER);


BinaryTreeTraversalTest(InorderTraversal_Iterative, EXPECTED_INORDER);
#endif
