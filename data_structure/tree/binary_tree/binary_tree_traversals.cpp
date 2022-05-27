#include "common_header.h"

#include "binary_tree_height.h"
#include "binary_tree_traversals.h"


namespace {

/** Tree Traversals (Inorder, Preorder and Postorder)
 *
 * @reference   https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 10.4-2. Exercises 12.1-4.
 * @reference   DFS traversal of a tree using recursion
 *              https://www.geeksforgeeks.org/dfs-traversal-of-a-tree-using-recursion/
 * @reference   BFS vs DFS for Binary Tree
 *              https://www.geeksforgeeks.org/bfs-vs-dfs-binary-tree/
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 5.
 * @reference   Binary Tree Preorder Traversal
 *              https://leetcode.com/problems/binary-tree-preorder-traversal/
 * @reference   Binary Tree Postorder Traversal
 *              https://leetcode.com/problems/binary-tree-postorder-traversal/
 */
inline auto PreorderTraversal_Recursive(const BinaryTree::Node::PointerType node,
                                        BinaryTree::ArrayType &outputs) {
    if (not node) {
        return;
    }

    outputs.push_back(node->value);
    PreorderTraversal_Recursive(node->left, outputs);
    PreorderTraversal_Recursive(node->right, outputs);
}


/**
 * @reference   Univalued Binary Tree
 *              https://leetcode.com/problems/univalued-binary-tree/
 *
 * A binary tree is uni-valued if every node in the tree has the same value.
 * Given the root of a binary tree, return true if the given tree is uni-valued, or false otherwise.
 */


inline auto PostorderTraversal_Recursive(const BinaryTree::Node::PointerType node,
                                         BinaryTree::ArrayType &outputs) {
    if (not node) {
        return;
    }

    PostorderTraversal_Recursive(node->left, outputs);
    PostorderTraversal_Recursive(node->right, outputs);
    outputs.push_back(node->value);
}


/** Iterative Postorder Traversal | Set 1 (Using Two Stacks)
 *
 * @reference   https://www.geeksforgeeks.org/iterative-postorder-traversal/
 */
inline auto PostorderTraversal_Iterative_TwoStacks(BinaryTree::Node::PointerType current_node,
                                                   BinaryTree::ArrayType &outputs) {
    std::stack<BinaryTree::Node::PointerType> remaining_nodes;
    std::stack<BinaryTree::Node::PointerType> reverse_outputs;

    PushIfNotNull(remaining_nodes, current_node);
    while (not remaining_nodes.empty()) {
        current_node = remaining_nodes.top();
        remaining_nodes.pop();
        reverse_outputs.push(current_node);

        PushIfNotNull(remaining_nodes, current_node->left);
        PushIfNotNull(remaining_nodes, current_node->right);
    }

    while (not reverse_outputs.empty()) {
        current_node = reverse_outputs.top();
        reverse_outputs.pop();
        outputs.push_back(current_node->value);
    }
}


/** Iterative Postorder Traversal | Set 2 (Using One Stack)
 *
 * @reference   https://www.geeksforgeeks.org/iterative-postorder-traversal-using-stack/
 */
inline auto PostorderTraversal_Iterative_OneStack(BinaryTree::Node::PointerType current_node,
                                                  BinaryTree::ArrayType &outputs) {
    std::stack<BinaryTree::Node::PointerType> remaining_nodes;

    while (current_node or not remaining_nodes.empty()) {
        while (current_node) {
            PushIfNotNull(remaining_nodes, current_node->right);
            remaining_nodes.push(current_node);
            current_node = current_node->left;
        }

        current_node = remaining_nodes.top();
        remaining_nodes.pop();

        if (current_node->right and not remaining_nodes.empty() and
            current_node->right == remaining_nodes.top()) {
            remaining_nodes.top().swap(current_node);
        } else {
            outputs.push_back(current_node->value);
            current_node = nullptr;
        }
    }
}


/**
 * @reference   Iterative Postorder traversal | Set 3
 *              https://www.geeksforgeeks.org/iterative-postorder-traversal-set-3/
 */
inline auto
PostorderTraversal_Iterative_OneStack_Count(BinaryTree::Node::PointerType current_node,
                                            BinaryTree::ArrayType &outputs) {
    std::stack<std::pair<BinaryTree::Node::PointerType, int>> remaining_node_pairs;

    if (current_node) {
        remaining_node_pairs.emplace(current_node, 0);
    }
    while (not remaining_node_pairs.empty()) {
        current_node = remaining_node_pairs.top().first;
        const auto count = remaining_node_pairs.top().second;
        remaining_node_pairs.pop();

        switch (count) {
        case 0:
            remaining_node_pairs.emplace(current_node, 1);
            if (current_node->left) {
                remaining_node_pairs.emplace(current_node->left, 0);
            }
            break;
        case 1:
            remaining_node_pairs.emplace(current_node, 2);
            if (current_node->right) {
                remaining_node_pairs.emplace(current_node->right, 0);
            }
            break;
        default:
            outputs.push_back(current_node->value);
        }
    }
}


/**
 * @reference   Postorder traversal of Binary Tree without recursion and without stack
 *              https://www.geeksforgeeks.org/postorder-traversal-binary-tree-without-recursion-without-stack/
 */
inline auto PostorderTraversal_Iterative_Hash(const BinaryTree::Node::PointerType root_node,
                                              BinaryTree::ArrayType &outputs) {
    auto current_node = root_node;
    std::unordered_set<BinaryTree::Node *> visited_nodes;

    while (current_node and visited_nodes.find(current_node.get()) == visited_nodes.cend()) {
        if (current_node->left and
            visited_nodes.find(current_node->left.get()) == visited_nodes.cend()) {
            current_node = current_node->left;
        } else if (current_node->right and
                   visited_nodes.find(current_node->right.get()) == visited_nodes.cend()) {
            current_node = current_node->right;
        } else {
            outputs.push_back(current_node->value);
            visited_nodes.emplace(current_node.get());
            current_node = root_node;
        }
    }
}


inline auto PostorderTraversal_Iterative_Map(BinaryTree::Node::PointerType current_node,
                                             BinaryTree::ArrayType &outputs) {
    std::unordered_map<BinaryTree::Node *, BinaryTree::Node::PointerType> parent_map;
    parent_map.emplace(current_node.get(), nullptr);

    while (current_node) {
        if (current_node->left and
            parent_map.find(current_node->left.get()) == parent_map.cend()) {
            parent_map.emplace(current_node->left.get(), current_node);
            current_node = current_node->left;
        } else if (current_node->right and
                   parent_map.find(current_node->right.get()) == parent_map.cend()) {
            parent_map.emplace(current_node->right.get(), current_node);
            current_node = current_node->right;
        } else {
            outputs.push_back(current_node->value);
            current_node = parent_map.find(current_node.get())->second;
        }
    }
}


/** Iterative Preorder Traversal
 *
 * @reference   https://www.geeksforgeeks.org/iterative-preorder-traversal/
 */
inline auto PreorderTraversal_Iterative(BinaryTree::Node::PointerType current_node,
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


inline auto PreorderTraversal_Iterative_Better(BinaryTree::Node::PointerType current_node,
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


/** Level Order Tree Traversal
 *
 * @reference   https://www.geeksforgeeks.org/level-order-tree-traversal/
 */
inline auto LevelOrderTraversal(const BinaryTree::Node::PointerType root_node,
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


inline auto LevelOrderTraversal_LevelAware(const BinaryTree::Node::PointerType root_node,
                                           BinaryTree::ArrayType &outputs) {
    LevelOrderTraversal_LevelAware_Helper(root_node, [&outputs](const auto &node) {
        outputs.push_back(node.value);
        return true;
    });
}


/** Reverse Level Order Traversal
 *
 * @reference   https://www.geeksforgeeks.org/reverse-level-order-traversal/
 *
 * The idea is to print last level first, then second last level, and so on. Like Level order
 * traversal, every level is printed from left to right.
 */
inline void GetGivenLevel(const BinaryTree::Node::PointerType node,
                          const unsigned level,
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

inline auto ReverseLevelOrderTraversal_Recursive(const BinaryTree::Node::PointerType root_node,
                                                 BinaryTree::ArrayType &outputs) {
    const auto height = Height_Recursive(root_node);
    for (auto i = height; i; --i) {
        GetGivenLevel(root_node, i, outputs);
    }
}


inline auto ReverseLevelOrderTraversal_Iterative(const BinaryTree::Node::PointerType root_node,
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
inline auto ZigZagTraversal(const BinaryTree::Node::PointerType root_node,
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


template<typename TraversalFunction>
inline constexpr auto TreeTraversal(const BinaryTree &binary_tree,
                                    const TraversalFunction traversal) {
    BinaryTree::ArrayType outputs;
    traversal(binary_tree.GetRoot(), outputs);
    return outputs;
}

} //namespace


#ifdef WANT_TESTS
#define BinaryTreeTraversalTest(traversalFunctionName, expectedResult)         \
    namespace {                                                                \
    TEST(BinaryTreeTraversalTest, test##traversalFunctionName) {               \
        const auto sample_tree = MakeTheSampleCompleteTree();                  \
        const auto result = TreeTraversal(sample_tree, traversalFunctionName); \
        EXPECT_EQ(expectedResult, result);                                     \
    }                                                                          \
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


BinaryTreeTraversalTest(PostorderTraversal_Iterative_TwoStacks, EXPECTED_POSTORDER);


BinaryTreeTraversalTest(PostorderTraversal_Iterative_OneStack, EXPECTED_POSTORDER);


BinaryTreeTraversalTest(PostorderTraversal_Iterative_OneStack_Count, EXPECTED_POSTORDER);


BinaryTreeTraversalTest(PostorderTraversal_Iterative_Hash, EXPECTED_POSTORDER);


BinaryTreeTraversalTest(PostorderTraversal_Iterative_Map, EXPECTED_POSTORDER);


BinaryTreeTraversalTest(LevelOrderTraversal, EXPECTED_LEVELORDER);


BinaryTreeTraversalTest(LevelOrderTraversal_LevelAware, EXPECTED_LEVELORDER);


BinaryTreeTraversalTest(ZigZagTraversal, EXPECTED_ZIGZAG);


BinaryTreeTraversalTest(ReverseLevelOrderTraversal_Recursive, EXPECTED_REVERSE_LEVELORDER);


BinaryTreeTraversalTest(ReverseLevelOrderTraversal_Iterative, EXPECTED_REVERSE_LEVELORDER);
#endif
