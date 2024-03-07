#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_traversals.h"
#include "clone_binary_tree.h"
#include "single_order_to_binary_tree.h"


namespace {

using ArrayType = std::vector<BinaryTree::ArrayType>;

/** Print level order traversal line by line | Set 1
 *
 * @reference   https://www.geeksforgeeks.org/print-level-order-traversal-line-line/
 * @reference   Level order traversal line by line | Set 2 (Using Two Queues)
 *              https://www.geeksforgeeks.org/level-order-traversal-line-line-set-2-using-two-queues/
 * @reference   Level order traversal line by line | Set 3 (Using One Queue)
 *              https://www.geeksforgeeks.org/level-order-traversal-line-line-set-3-using-one-queue/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 4.4.
 *
 * @reference   Binary Tree Level Order Traversal
 *              https://leetcode.com/problems/binary-tree-level-order-traversal/
 *
 * Given the root of a binary tree, return the level order traversal of its nodes' values.  (i.e., from
 * left to right, level by level).
 */
inline auto PrintLevelOrderLineByLine(const BinaryTree::Node::PointerType root_node) {
    ArrayType results;
    LevelOrderTraversal_LevelAware_Helper(
        root_node,
        [&results](const auto &node) {
            results.back().push_back(node.value);
            return true;
        },
        [&results]() {
            results.emplace_back();
            return true;
        });

    return results;
}


/**
 * @reference   Binary Tree Level Order Traversal II
 *              https://leetcode.com/problems/binary-tree-level-order-traversal-ii/
 *
 * Given the root of a binary tree, return the bottom-up level order traversal of its nodes' values.
 * (i.e., from left to right, level by level from leaf to root).
 */


/**
 * @reference   Average of Levels in Binary Tree
 *              https://leetcode.com/problems/average-of-levels-in-binary-tree/
 *
 * Given the root of a binary tree, return the average value of the nodes on each level in the form of
 * an array. Answers within 10^-5 of the actual answer will be accepted.
 */


/**
 * @reference   Maximum Level Sum of a Binary Tree
 *              https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/
 *
 * Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so
 * on.
 * Return the smallest level x such that the sum of all the values of nodes at level x is maximal.
 */


/**
 * @reference   Deepest Leaves Sum
 *              https://leetcode.com/problems/deepest-leaves-sum/
 *
 * Given the root of a binary tree, return the sum of values of its deepest leaves.
 */


/**
 * @reference   Find Largest Value in Each Tree Row
 *              https://leetcode.com/problems/find-largest-value-in-each-tree-row/
 *
 * Given the root of a binary tree, return an array of the largest value in each row of the tree
 * (0-indexed).
 */


/**
 * @reference   Find Bottom Left Tree Value
 *              https://leetcode.com/problems/find-bottom-left-tree-value/
 *
 * Given the root of a binary tree, return the leftmost value in the last row of the tree.
 */


/**
 * @reference   Populating Next Right Pointers in Each Node
 *              https://leetcode.com/problems/populating-next-right-pointers-in-each-node/
 *
 * You are given a perfect binary tree where all leaves are on the same level, and every parent has two
 * children. The binary tree has the following definition:
 *  struct Node {
 *      int val;
 *      Node *left;
 *      Node *right;
 *      Node *next;
 *  }
 * Populate each next pointer to point to its next right node. If there is no next right node, the next
 * pointer should be set to NULL. Initially, all next pointers are set to NULL.
 * You may only use constant extra space.
 * The recursive approach is fine. You may assume implicit stack space does not count as extra space for
 * this problem.
 */
inline auto ConnectLevelNext_BFS(const BinaryTreeNodeWithNext::PointerType root) {
    if (not root) {
        return;
    }

    std::queue<BinaryTreeNodeWithNext::PointerType> q;
    q.push(root);

    while (not q.empty()) {
        BinaryTreeNodeWithNext::PointerType next;
        for (int i = q.size(); i--;) {
            const auto curr = q.front();
            q.pop();

            curr->next = next;
            next = curr;

            if (curr->right) {
                q.push(curr->right);
            }
            if (curr->left) {
                q.push(curr->left);
            }
        }
    }
}


auto ConnectLevelNext_DFS(const BinaryTreeNodeWithNext::PointerType root) {
    if (not root) {
        return root;
    }

    if (root->left) {
        root->left->next = root->right;
        if (root->next) {
            root->right->next = root->next->left;
        }
        ConnectLevelNext_DFS(root->left);
        ConnectLevelNext_DFS(root->right);
    }

    return root;
}


template<typename Func>
constexpr auto testConnectLevelNext(const BinaryTree::Node::PointerType root,
                                    const Func connect) {
    const auto new_root = CopyBinaryTree<BinaryTreeNodeWithNext>(root);

    connect(new_root);

    ArrayType result;
    for (auto curr = new_root; curr; curr = curr->left) {
        result.emplace_back();
        for (auto node = curr; node; node = node->next) {
            result.back().push_back(node->value);
        }
    }

    return result;
}


/**
 * @reference   Populating Next Right Pointers in Each Node II
 *              https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/
 *
 * Populate each next pointer to point to its next right node. If there is no next right node, the next
 * pointer should be set to NULL. Initially, all next pointers are set to NULL.
 * You may only use constant extra space.
 * The recursive approach is fine. You may assume implicit stack space does not count as extra space for
 * this problem.
 */
inline auto ConnectLevelNext_Any_BFS(BinaryTreeNodeWithNext::PointerType root) {
    const auto dummy = std::make_shared<BinaryTreeNodeWithNext>(0);
    while (root) {
        dummy->next = nullptr;
        auto curr = dummy;

        while (root) {
            if (root->left) {
                curr->next = root->left;
                curr = curr->next;
            }
            if (root->right) {
                curr->next = root->right;
                curr = curr->next;
            }
            root = root->next;
        }

        root = dummy->next;
    }
}


/**
 * @reference   Binary Tree Right Side View
 *              https://leetcode.com/problems/binary-tree-right-side-view/
 *
 * Given the root of a binary tree, imagine yourself standing on the right side of it, return the values
 * of the nodes you can see ordered from top to bottom.
 */
auto RightSideView(const BinaryTree::Node::PointerType node,
                   const std::size_t level,
                   BinaryTree::ArrayType &result) {
    if (not node) {
        return;
    }

    if (level == result.size()) {
        result.push_back(node->value);
    }

    RightSideView(node->right, level + 1, result);
    RightSideView(node->left, level + 1, result);
}

inline auto RightSideView(const BinaryTree::Node::PointerType root) {
    BinaryTree::ArrayType result;
    RightSideView(root, 0, result);

    return result;
}


/**
 * @reference   Even Odd Tree
 *              https://leetcode.com/problems/even-odd-tree/
 *
 * A binary tree is named Even-Odd if it meets the following conditions:
 *  The root of the binary tree is at level index 0, its children are at level index 1, their children
 *  are at level index 2, etc.
 *  For every even-indexed level, all nodes at the level have odd integer values in strictly increasing
 *  order (from left to right).
 *  For every odd-indexed level, all nodes at the level have even integer values in strictly decreasing
 *  order (from left to right).
 * Given the root of a binary tree, return true if the binary tree is Even-Odd, otherwise return false.
 */

} //namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();
// clang-format off
const ArrayType EXPECTED1 = {
    {1},
    {2, 3},
    {4, 5}
};
// clang-format on


THE_BENCHMARK(PrintLevelOrderLineByLine, SAMPLE1);

SIMPLE_TEST(PrintLevelOrderLineByLine, TestSAMPLE1, EXPECTED1, SAMPLE1);


/**
 *     1
 *    /  \
 *   2    3
 *  / \  / \
 * 4  5 6   7
 */
const auto SAMPLE2 = LevelOrderToBinaryTree({1, 2, 3, 4, 5, 6, 7});
// clang-format off
const ArrayType EXPECTED2 = {
    {1},
    {2, 3},
    {4, 5, 6, 7}
};
// clang-format on


SIMPLE_TEST(testConnectLevelNext, TestSAMPLE1B, EXPECTED1, SAMPLE1, ConnectLevelNext_BFS);
SIMPLE_TEST(testConnectLevelNext, TestSAMPLE2B, EXPECTED2, SAMPLE2, ConnectLevelNext_BFS);


SIMPLE_TEST(testConnectLevelNext, TestSAMPLE2D, EXPECTED2, SAMPLE2, ConnectLevelNext_DFS);


SIMPLE_TEST(testConnectLevelNext, TestSAMPLE1AB, EXPECTED1, SAMPLE1, ConnectLevelNext_Any_BFS);
SIMPLE_TEST(testConnectLevelNext, TestSAMPLE2AB, EXPECTED2, SAMPLE2, ConnectLevelNext_Any_BFS);


const BinaryTree::ArrayType EXPECTED1R = {1, 3, 5};
const BinaryTree::ArrayType EXPECTED2R = {1, 3, 7};


THE_BENCHMARK(RightSideView, SAMPLE1);

SIMPLE_TEST(RightSideView, TestSAMPLE1, EXPECTED1R, SAMPLE1);
SIMPLE_TEST(RightSideView, TestSAMPLE2, EXPECTED2R, SAMPLE2);
