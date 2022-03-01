#include "common_header.h"

#include "binary_tree.h"
#include "binary_tree_height.h"
#include "binary_tree_traversals.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Iterative Method to find Height of Binary Tree
 *              https://www.geeksforgeeks.org/iterative-method-to-find-height-of-binary-tree/
 */
inline auto
Height_Iterative(const BinaryTree::Node::PointerType node) {
    unsigned height = 0;
    LevelOrderTraversal_LevelAware_Helper(node, {},
    [&height]() {
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
 * The width of one level is defined as the length between the end-nodes (the leftmost
 * and rightmost non-null nodes), where the null nodes between the end-nodes are also
 * counted into the length calculation.
 * It is guaranteed that the answer will in the range of 32-bit signed integer.
 */
auto
WidthOfBinaryTree_DFS(const BinaryTree::Node::PointerType node, const std::size_t level,
                      const int index, ArrayType &starts) {
    if (not node) {
        return 0;
    }

    if (starts.size() == level) {
        starts.push_back(index);
    }

    const int current_level_width = index + 1 - starts[level];
    const auto left_width =
        WidthOfBinaryTree_DFS(node->left, level + 1, 2 * index, starts);
    const auto right_width =
        WidthOfBinaryTree_DFS(node->right, level + 1, 2 * index + 1, starts);
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

}//namespace


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
