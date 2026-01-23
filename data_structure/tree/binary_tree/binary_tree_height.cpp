#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_height.h"
#include "binary_tree_traversals.h"
#include "compare_binary_trees.h"
#include "single_order_to_binary_tree.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Iterative Method to find Height of Binary Tree
 *              https://www.geeksforgeeks.org/iterative-method-to-find-height-of-binary-tree/
 *
 * @tags    #binary-tree #BFS
 */
inline auto Height_Iterative(const BinaryTree::Node::PointerType node) {
    unsigned height = 0;
    LevelOrderTraversal_LevelAware_Helper(node, {}, [&height]() {
        ++height;
        return true;
    });
    return height;
}


/**
 * @reference   Height of a complete binary tree (or Heap) with N nodes
 *              https://www.geeksforgeeks.org/height-complete-binary-tree-heap-n-nodes/
 */
inline constexpr std::size_t HeightOfCompleteTree(const std::size_t number_of_nodes) {
    return std::ceil(std::log2(number_of_nodes + 1));
}


/**
 * @reference   Maximum Width of Binary Tree
 *              https://leetcode.com/problems/maximum-width-of-binary-tree/
 *
 * Given the root of a binary tree, return the maximum width of the given tree.
 * The maximum width of a tree is the maximum width among all levels.
 * The width of one level is defined as the length between the end-nodes (the leftmost and rightmost
 * non-null nodes), where the null nodes between the end-nodes are also counted into the length
 * calculation.
 * It is guaranteed that the answer will in the range of 32-bit signed integer.
 *
 * @tags    #binary-tree #BFS #DFS #postorder-traversal
 */
unsigned WidthOfBinaryTree_DFS(const BinaryTree::Node::PointerType node,
                               const unsigned level,
                               const unsigned index,
                               ArrayType &starts) {
    if (not node) {
        return 0;
    }

    if (starts.size() == level) {
        starts.push_back(index);
    }

    const unsigned current_level_width = index + 1 - starts[level];
    const auto left_width = WidthOfBinaryTree_DFS(node->left, level + 1, 2 * index, starts);
    const auto right_width = WidthOfBinaryTree_DFS(node->right, level + 1, 2 * index + 1, starts);
    return std::max({current_level_width, left_width, right_width});
}

inline auto WidthOfBinaryTree_DFS(const BinaryTree::Node::PointerType root) {
    ArrayType starts;
    return WidthOfBinaryTree_DFS(root, 0, 1, starts);
}


auto WidthOfBinaryTree_BFS(const BinaryTree::Node::PointerType root) {
    if (not root) {
        return 0;
    }

    std::queue<std::pair<BinaryTree::Node::PointerType, int>> q;
    q.emplace(root, 1);

    int result = 0;
    while (not q.empty()) {
        const auto left = q.front().second;
        auto right = left;
        for (int i = q.size(); i--;) {
            const auto node = q.front().first;
            right = q.front().second;
            q.pop();

            if (node->left) {
                q.emplace(node->left, right * 2);
            }
            if (node->right) {
                q.emplace(node->right, right * 2 + 1);
            }
        }
        result = std::max(result, right + 1 - left);
    }

    return result;
}


/**
 * @reference   Add One Row to Tree
 *              https://leetcode.com/problems/add-one-row-to-tree/
 *
 * Given the root of a binary tree and two integers val and depth, add a row of nodes with value val at
 * the given depth depth.
 * Note that the root node is at depth 1.
 * The adding rule is:
 *  Given the integer depth, for each not null tree node cur at the depth depth - 1, create two tree
 *      nodes with value val as cur's left subtree root and right subtree root.
 *  cur's original left subtree should be the left subtree of the new left subtree root.
 *  cur's original right subtree should be the right subtree of the new right subtree root.
 *  If depth == 1 that means there is no depth depth - 1 at all, then create a tree node with value val
 *      as the new root of the whole original tree, and the original tree is the new root's left subtree.
 *
 * @tags    #binary-tree #DFS #preorder-traversal
 */
auto AddOneRow(const BinaryTree::Node::PointerType node, const int value, const int depth) {
    if (not node)
        return node;

    if (depth == 1) {
        const auto new_root = std::make_shared<BinaryTree::Node>(value);
        new_root->left = node;
        return new_root;
    }

    if (depth == 2) {
        const auto new_left = std::make_shared<BinaryTree::Node>(value);
        new_left->left = node->left;
        const auto new_right = std::make_shared<BinaryTree::Node>(value);
        new_right->right = node->right;
        node->left = new_left;
        node->right = new_right;
        return node;
    }

    AddOneRow(node->left, value, depth - 1);
    AddOneRow(node->right, value, depth - 1);
    return node;
}


/**
 * @reference   Smallest Subtree with all the Deepest Nodes
 *              https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/
 *
 * Given the root of a binary tree, the depth of each node is the shortest distance to the root.
 * Return the smallest subtree such that it contains all the deepest nodes in the original tree.
 * A node is called the deepest if it has the largest depth possible among any node in the entire tree.
 * The subtree of a node is a tree consisting of that node, plus the set of all descendants of that
 * node.
 *
 * @reference   Lowest Common Ancestor of Deepest Leaves
 *              https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/
 *
 * Given the root of a binary tree, return the lowest common ancestor of its deepest leaves.
 * Recall that:
 *  The node of a binary tree is a leaf if and only if it has no children
 *  The depth of the root of the tree is 0. if the depth of a node is d, the depth of each of its
 *  children is d + 1.
 *  The lowest common ancestor of a set S of nodes, is the node A with the largest depth such that every
 *  node in S is in the subtree with root A.
 *
 * @tags    #binary-tree #DFS #postorder-traversal
 */
std::pair<BinaryTree::Node::PointerType, int>
LowestCommonAncestorOfDeepestLeavesHelper(const BinaryTree::Node::PointerType node) {
    if (not node) {
        return std::pair(node, 0);
    }

    const auto [left_node, left_depth] = LowestCommonAncestorOfDeepestLeavesHelper(node->left);
    const auto [right_node, right_depth] = LowestCommonAncestorOfDeepestLeavesHelper(node->right);

    if (left_depth > right_depth) {
        return std::pair(left_node, left_depth + 1);
    } else if (left_depth < right_depth) {
        return std::pair(right_node, right_depth + 1);
    } else {
        return std::pair(node, left_depth + 1);
    }
}

auto LowestCommonAncestorOfDeepestLeaves(const BinaryTree::Node::PointerType root) {
    return LowestCommonAncestorOfDeepestLeavesHelper(root).first->value;
}

} //namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();


THE_BENCHMARK(Height_Recursive, SAMPLE1);

SIMPLE_TEST(Height_Recursive, TestSAMPLE1, 3, SAMPLE1);


THE_BENCHMARK(Height_Iterative, SAMPLE1);

SIMPLE_TEST(Height_Iterative, TestSAMPLE1, 3, SAMPLE1);


THE_BENCHMARK(HeightOfCompleteTree, 5);

SIMPLE_TEST(HeightOfCompleteTree, TestSAMPLE1, 3, 5);


THE_BENCHMARK(WidthOfBinaryTree_DFS, SAMPLE1);

SIMPLE_TEST(WidthOfBinaryTree_DFS, TestSAMPLE1, 2, SAMPLE1);


THE_BENCHMARK(WidthOfBinaryTree_BFS, SAMPLE1);

SIMPLE_TEST(WidthOfBinaryTree_BFS, TestSAMPLE1, 2, SAMPLE1);


/**
 *       0
 *      /
 *     1
 *    / \
 *   2   3
 *  / \
 * 4   5
 */
const auto EXPECTED1 = []() {
    const auto left = MakeTheSampleCompleteTree().GetRoot();
    const auto root = std::make_shared<BinaryTree::Node>(0);
    root->left = left;
    return root;
}();

/**
 *     1
 *    / \
 *   2   3
 */
const auto SAMPLE2 = LevelOrderToBinaryTree({1, 2, 3});
/**
 *     1
 *    / \
 *   0   0
 *  /     \
 * 2       3
 */
const auto EXPECTED2 = LevelOrderToBinaryTree({1, 0, 0, 2, SENTINEL, SENTINEL, 3});


THE_BENCHMARK(AddOneRow, MakeTheSampleCompleteTree().GetRoot(), 0, 1);

SIMPLE_TEST(areIdenticalTrees,
            TestSAMPLE1,
            true,
            EXPECTED1,
            AddOneRow(MakeTheSampleCompleteTree().GetRoot(), 0, 1));
SIMPLE_TEST(areIdenticalTrees, TestSAMPLE2, true, EXPECTED2, AddOneRow(SAMPLE2, 0, 2));


THE_BENCHMARK(LowestCommonAncestorOfDeepestLeaves, SAMPLE2);

SIMPLE_TEST(LowestCommonAncestorOfDeepestLeaves, TestSAMPLE1, 1, SAMPLE2);
