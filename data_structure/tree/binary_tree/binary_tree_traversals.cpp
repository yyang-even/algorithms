#include "common_header.h"

#include "binary_tree_traversals.h"
#include "binary_tree_height.h"
#include "compare_binary_trees.h"


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
auto PreorderTraversal_Recursive(const BinaryTree::Node::PointerType node,
                                 BinaryTree::ArrayType &outputs) {
    if (not node) {
        return;
    }

    outputs.push_back(node->value);
    PreorderTraversal_Recursive(node->left, outputs);
    PreorderTraversal_Recursive(node->right, outputs);
}


/**
 * @reference   Construct String from Binary Tree
 *              https://leetcode.com/problems/construct-string-from-binary-tree/
 *
 * Given the root of a binary tree, construct a string consists of parenthesis and
 * integers from a binary tree with the preorder traversing way, and return it. Omit
 * all the empty parenthesis pairs that do not affect the one-to-one mapping relationship
 * between the string and the original binary tree.
 */


/**
 * @reference   Construct Binary Tree from String with bracket representation
 *              https://www.geeksforgeeks.org/construct-binary-tree-string-bracket-representation/
 *
 * @reference   Construct Binary Tree from String
 *              https://evelynn.gitbooks.io/amazon-interview/content/binary-tree/construct-binary-tree-from-string.html
 *
 * You need to construct a binary tree from a string consisting of parenthesis and
 * integers. The whole input represents a binary tree. It contains an integer followed
 * by zero, one or two pairs of parenthesis. The integer represents the root's value and
 * a pair of parenthesis contains a child binary tree with the same structure. You always
 * start to construct the left child node of the parent first if it exists.
 */
auto BinaryTreeFromString(const std::string_view str, std::size_t &i) {
    if (i == str.size() or str[i] == ')') {
        return BinaryTree::Node::PointerType{};
    }

    int value = 0;
    while (i < str.size() and std::isdigit(str[i])) {
        value = value * 10 + str[i++] - '0';
    }

    const auto node = std::make_shared<BinaryTree::Node>(value);

    if (i < str.size() and str[i] == '(') {
        ++i;
        node->left = BinaryTreeFromString(str, i);
        ++i;

        if (i < str.size() and str[i] == '(') {
            ++i;
            node->right = BinaryTreeFromString(str, i);
            ++i;
        }
    }

    return node;
}

inline auto BinaryTreeFromString(const std::string_view str) {
    std::size_t i = 0;
    return BinaryTreeFromString(str, i);
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


/** Iterative Postorder Traversal | Set 1 (Using Two Stacks)
 *
 * @reference   https://www.geeksforgeeks.org/iterative-postorder-traversal/
 */
auto PostorderTraversal_Iterative_TwoStacks(BinaryTree::Node::PointerType current_node,
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
auto PostorderTraversal_Iterative_OneStack(BinaryTree::Node::PointerType current_node,
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
auto PostorderTraversal_Iterative_OneStack_Count(
    BinaryTree::Node::PointerType current_node,
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
auto PostorderTraversal_Iterative_Hash(const BinaryTree::Node::PointerType root_node,
                                       BinaryTree::ArrayType &outputs) {
    auto current_node = root_node;
    std::unordered_set<BinaryTree::Node *> visited_nodes;

    while (current_node and
           visited_nodes.find(current_node.get()) == visited_nodes.cend()) {
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


auto PostorderTraversal_Iterative_Map(BinaryTree::Node::PointerType current_node,
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


/** Inorder Tree Traversal without Recursion
 *
 * @reference   https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion/
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 10.4-3.
 * @reference   Binary Tree Inorder Traversal
 *              https://leetcode.com/problems/binary-tree-inorder-traversal/
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
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 12.1-3.
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


inline auto
LevelOrderTraversal_LevelAware(const BinaryTree::Node::PointerType root_node,
                               BinaryTree::ArrayType &outputs) {
    LevelOrderTraversal_LevelAware_Helper(root_node,
    [&outputs](const auto & node) {
        outputs.push_back(node.value);
        return true;
    });
}


/** Reverse Level Order Traversal
 *
 * @reference   https://www.geeksforgeeks.org/reverse-level-order-traversal/
 *
 * The idea is to print last level first, then second last level, and so on. Like Level
 * order traversal, every level is printed from left to right.
 */
inline void
GetGivenLevel(const BinaryTree::Node::PointerType node, const unsigned level,
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

inline auto
ReverseLevelOrderTraversal_Recursive(const BinaryTree::Node::PointerType root_node,
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
inline constexpr auto
TreeTraversal(const BinaryTree &binary_tree, const TraversalFunction traversal) {
    BinaryTree::ArrayType outputs;
    traversal(binary_tree.GetRoot(), outputs);
    return outputs;
}

}//namespace


#ifdef WANT_TESTS
#define BinaryTreeTraversalTest(traversalFunctionName, expectedResult) namespace {  \
    TEST(BinaryTreeTraversalTest, test##traversalFunctionName) {                    \
        const auto sample_tree = MakeTheSampleCompleteTree();                       \
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


BinaryTreeTraversalTest(PostorderTraversal_Iterative_TwoStacks, EXPECTED_POSTORDER);


BinaryTreeTraversalTest(PostorderTraversal_Iterative_OneStack, EXPECTED_POSTORDER);


BinaryTreeTraversalTest(PostorderTraversal_Iterative_OneStack_Count,
                        EXPECTED_POSTORDER);


BinaryTreeTraversalTest(PostorderTraversal_Iterative_Hash, EXPECTED_POSTORDER);


BinaryTreeTraversalTest(PostorderTraversal_Iterative_Map, EXPECTED_POSTORDER);


BinaryTreeTraversalTest(InorderTraversal_Iterative, EXPECTED_INORDER);


BinaryTreeTraversalTest(InorderTraversal_Morris, EXPECTED_INORDER);


BinaryTreeTraversalTest(LevelOrderTraversal, EXPECTED_LEVELORDER);


BinaryTreeTraversalTest(LevelOrderTraversal_LevelAware, EXPECTED_LEVELORDER);


BinaryTreeTraversalTest(ZigZagTraversal, EXPECTED_ZIGZAG);


BinaryTreeTraversalTest(ReverseLevelOrderTraversal_Recursive,
                        EXPECTED_REVERSE_LEVELORDER);


BinaryTreeTraversalTest(ReverseLevelOrderTraversal_Iterative,
                        EXPECTED_REVERSE_LEVELORDER);
#endif


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();

/**
 *     1
 *    / \
 *   2   3
 *    \
 *     4
 */
static inline auto MakeTheSample2() {
    const BinaryTree binary_tree{1};
    auto &root = *binary_tree.GetRoot();
    auto &left_child = *SetLeftChild(root, 2);
    SetRightChild(root, 3);
    SetRightChild(left_child, 4);

    return binary_tree;
}

const auto SAMPLE2 = MakeTheSample2().GetRoot();


THE_BENCHMARK(BinaryTreeFromString, "1(2()(4))(3)");

SIMPLE_TEST(areIdenticalTrees, TestSAMPLE1, true, SAMPLE1,
            BinaryTreeFromString("1(2(4)(5))(3)"));
SIMPLE_TEST(areIdenticalTrees, TestSAMPLE2, true, SAMPLE2,
            BinaryTreeFromString("1(2()(4))(3)"));
