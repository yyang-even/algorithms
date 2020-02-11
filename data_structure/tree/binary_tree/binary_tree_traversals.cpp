#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_height.h"
#include "binary_tree_traversals.h"


namespace {

/** Tree Traversals (Inorder, Preorder and Postorder)
 *
 * @reference   https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 10.4-2.
 * @reference   DFS traversal of a tree using recursion
 *              https://www.geeksforgeeks.org/dfs-traversal-of-a-tree-using-recursion/
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


auto PreorderTraversal_Recursive(const BinaryTree::Node::PointerType node,
                                 BinaryTree::ArrayType &outputs) {
    if (not node) {
        return;
    }

    outputs.push_back(node->value);
    PreorderTraversal_Recursive(node->left, outputs);
    PreorderTraversal_Recursive(node->right, outputs);
}


auto PostorderTraversal_Recursive(const BinaryTree::Node::PointerType node,
                                  BinaryTree::ArrayType &outputs) {
    if (not node) {
        return;
    }

    PostorderTraversal_Recursive(node->left, outputs);
    PostorderTraversal_Recursive(node->right, outputs);
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


/** Iterative Preorder Traversal
 *
 * @reference   https://www.geeksforgeeks.org/iterative-preorder-traversal/
 */
auto PreorderTraversal_Iterative(BinaryTree::Node::PointerType current_node,
                                 BinaryTree::ArrayType &outputs) {
    std::stack<BinaryTree::Node::PointerType> remaining_nodes;

    PushIfNotNull(remaining_nodes, current_node);
    while (not remaining_nodes.empty()) {
        current_node = remaining_nodes.top();
        remaining_nodes.pop();
        outputs.push_back(current_node->value);

        PushIfNotNull(remaining_nodes, current_node->right);
        PushIfNotNull(remaining_nodes, current_node->left);
    }
}


auto PreorderTraversal_Iterative_Better(BinaryTree::Node::PointerType current_node,
                                        BinaryTree::ArrayType &outputs) {
    std::stack<BinaryTree::Node::PointerType> remaining_nodes;

    while (current_node or not remaining_nodes.empty()) {
        while (current_node) {
            outputs.push_back(current_node->value);

            PushIfNotNull(remaining_nodes, current_node->right);
            current_node = current_node->left;
        }

        if (not remaining_nodes.empty()) {
            current_node = remaining_nodes.top();
            remaining_nodes.pop();
        }
    }
}


/** Inorder Tree Traversal without recursion and without stack!
 *
 * @reference   https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion-and-without-stack/
 */
auto InorderTraversal_Morris(BinaryTree::Node::PointerType current_node,
                             BinaryTree::ArrayType &outputs) {
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
}


/** Level Order Tree Traversal
 *
 * @reference   https://www.geeksforgeeks.org/level-order-tree-traversal/
 */
auto LevelOrderTraversal(const BinaryTree::Node::PointerType root_node,
                         BinaryTree::ArrayType &outputs) {
    std::queue<BinaryTree::Node::PointerType> remaining_nodes;
    PushIfNotNull(remaining_nodes, root_node);

    while (not remaining_nodes.empty()) {
        const auto node = remaining_nodes.front();
        remaining_nodes.pop();
        outputs.push_back(node->value);

        PushIfNotNull(remaining_nodes, node->left);
        PushIfNotNull(remaining_nodes, node->right);
    }
}


auto LevelOrderTraversal_LevelAware(const BinaryTree::Node::PointerType root_node,
                                    BinaryTree::ArrayType &outputs) {
    LevelOrderTraversal_LevelAware_Helper(root_node, [&outputs](const BinaryTree::Node & node) {
        outputs.push_back(node.value);
        return true;
    });
}


/** Reverse Level Order Traversal
 *
 * @reference   https://www.geeksforgeeks.org/reverse-level-order-traversal/
 *
 * The idea is to print last level first, then second last level, and so on.
 * Like Level order traversal, every level is printed from left to right.
 */
void GetGivenLevel(const BinaryTree::Node::PointerType node, const unsigned level,
                   BinaryTree::ArrayType &outputs) {
    if (node) {
        if (level == 1) {
            outputs.push_back(node->value);
        } else if (level > 1) {
            GetGivenLevel(node->left, level - 1, outputs);
            GetGivenLevel(node->right, level - 1, outputs);
        }
    }
}

auto ReverseLevelOrderTraversal_Recursive(const BinaryTree::Node::PointerType root_node,
        BinaryTree::ArrayType &outputs) {
    const auto height = Height_Recursive(root_node);
    for (auto i = height; i; --i) {
        GetGivenLevel(root_node, i, outputs);
    }
}


auto ReverseLevelOrderTraversal_Iterative(const BinaryTree::Node::PointerType root_node,
        BinaryTree::ArrayType &outputs) {
    std::queue<BinaryTree::Node::PointerType> remaining_nodes;
    std::stack<BinaryTree::Node::PointerType> outputs_stack;

    PushIfNotNull(remaining_nodes, root_node);
    while (not remaining_nodes.empty()) {
        const auto node = remaining_nodes.front();
        remaining_nodes.pop();
        outputs_stack.push(node);

        PushIfNotNull(remaining_nodes, node->right);
        PushIfNotNull(remaining_nodes, node->left);
    }

    while (not outputs_stack.empty()) {
        outputs.push_back(outputs_stack.top()->value);
        outputs_stack.pop();
    }
}


/** ZigZag Tree Traversal
 *
 * @reference   https://www.geeksforgeeks.org/zigzag-tree-traversal/
 */
auto ZigZagTraversal(const BinaryTree::Node::PointerType root_node,
                     BinaryTree::ArrayType &outputs) {
    std::stack<BinaryTree::Node::PointerType> current_level_nodes;
    std::stack<BinaryTree::Node::PointerType> next_level_nodes;

    PushIfNotNull(current_level_nodes, root_node);
    bool is_left_to_right = true;

    while (not current_level_nodes.empty()) {
        const auto node = current_level_nodes.top();
        current_level_nodes.pop();

        outputs.push_back(node->value);
        if (is_left_to_right) {
            PushIfNotNull(next_level_nodes, node->left);
            PushIfNotNull(next_level_nodes, node->right);
        } else {
            PushIfNotNull(next_level_nodes, node->right);
            PushIfNotNull(next_level_nodes, node->left);
        }

        if (current_level_nodes.empty()) {
            is_left_to_right = not is_left_to_right;
            current_level_nodes.swap(next_level_nodes);
        }
    }
}


/** Zig Zag Level order traversal of a tree using single queue
 *
 * @reference   https://www.geeksforgeeks.org/zig-zag-level-order-traversal-of-a-tree-using-single-queue/
 */


/** Zig-Zag traversal of a Binary Tree using Recursion
 *
 * @reference   https://www.geeksforgeeks.org/zig-zag-traversal-of-a-binary-tree-using-recursion/
 */


template <typename TraversalFunction>
auto TreeTraversal(const BinaryTree &binary_tree, const TraversalFunction traversal) {
    BinaryTree::ArrayType outputs;
    traversal(binary_tree.GetRoot(), outputs);
    return outputs;
}

}//namespace


#ifdef WANT_TESTS
#define BinaryTreeTraversalTest(traversalFunctionName, expectedResult) namespace {  \
    TEST(BinaryTreeTraversalTest, test##traversalFunctionName) {                    \
        const auto sample_tree = MakeTheSampleCompleteTree();                               \
        const auto result = TreeTraversal(sample_tree, traversalFunctionName);      \
        EXPECT_EQ(expectedResult, result);                                          \
    }                                                                               \
}


const BinaryTree::ArrayType EXPECTED_INORDER = {4, 2, 5, 1, 3};
const BinaryTree::ArrayType EXPECTED_PREORDER = {1, 2, 4, 5, 3};
const BinaryTree::ArrayType EXPECTED_POSTORDER = {4, 5, 2, 3, 1};
const BinaryTree::ArrayType EXPECTED_LEVELORDER = {1, 2, 3, 4, 5};
const BinaryTree::ArrayType EXPECTED_ZIGZAG = {1, 3, 2, 4, 5};
const BinaryTree::ArrayType EXPECTED_REVERSE_LEVELORDER = {4, 5, 2, 3, 1};


BinaryTreeTraversalTest(InorderTraversal_Recursive, EXPECTED_INORDER);


BinaryTreeTraversalTest(PreorderTraversal_Recursive, EXPECTED_PREORDER);


BinaryTreeTraversalTest(PreorderTraversal_Iterative, EXPECTED_PREORDER);


BinaryTreeTraversalTest(PreorderTraversal_Iterative_Better, EXPECTED_PREORDER);


BinaryTreeTraversalTest(PostorderTraversal_Recursive, EXPECTED_POSTORDER);


BinaryTreeTraversalTest(InorderTraversal_Iterative, EXPECTED_INORDER);


BinaryTreeTraversalTest(InorderTraversal_Morris, EXPECTED_INORDER);


BinaryTreeTraversalTest(LevelOrderTraversal, EXPECTED_LEVELORDER);


BinaryTreeTraversalTest(LevelOrderTraversal_LevelAware, EXPECTED_LEVELORDER);


BinaryTreeTraversalTest(ZigZagTraversal, EXPECTED_ZIGZAG);


BinaryTreeTraversalTest(ReverseLevelOrderTraversal_Recursive, EXPECTED_REVERSE_LEVELORDER);


BinaryTreeTraversalTest(ReverseLevelOrderTraversal_Iterative, EXPECTED_REVERSE_LEVELORDER);
#endif
