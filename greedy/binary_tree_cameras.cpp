#include "common_header.h"

#include "data_structure/tree/binary_tree/binary_tree.h"
#include "data_structure/tree/binary_tree/single_order_to_binary_tree.h"


namespace {

/** Binary Tree Cameras
 *
 * @reference   https://leetcode.com/problems/binary-tree-cameras/
 *
 * You are given the root of a binary tree. We install cameras on the tree nodes where each
 * camera at a node can monitor its parent, itself, and its immediate children.
 * Return the minimum number of cameras needed to monitor all nodes of the tree.
 */
auto BinaryTreeCameras_Hash(const BinaryTree::Node::PointerType node,
                            const BinaryTree::Node::PointerType parent,
                            std::unordered_set<BinaryTree::Node *> &covered,
                            int &result) {
    if (not node) {
        return;
    }

    BinaryTreeCameras_Hash(node->left, node, covered, result);
    BinaryTreeCameras_Hash(node->right, node, covered, result);

    if ((not parent and covered.find(node.get()) == covered.cend()) or
        covered.find(node->left.get()) == covered.cend() or
        covered.find(node->right.get()) == covered.cend()) {
        ++result;
        covered.emplace(node.get());
        covered.emplace(parent.get());
        covered.emplace(node->left.get());
        covered.emplace(node->right.get());
    }
}

auto BinaryTreeCameras_Hash(const BinaryTree::Node::PointerType root) {
    int result = 0;
    std::unordered_set<BinaryTree::Node *> covered;
    covered.emplace(nullptr);

    BinaryTreeCameras_Hash(root, nullptr, covered, result);

    return result;
}


enum class NodeType { leaf, camera_parent_of_leaf, nocamera_covered };

auto BinaryTreeCameras(const BinaryTree::Node::PointerType node, int &result) {
    if (not node) {
        return NodeType::nocamera_covered;
    }

    const auto left_type = BinaryTreeCameras(node->left, result);
    const auto right_type = BinaryTreeCameras(node->right, result);

    if (left_type == NodeType::leaf or right_type == NodeType::leaf) {
        ++result;
        return NodeType::camera_parent_of_leaf;
    }

    if (left_type == NodeType::camera_parent_of_leaf or
        right_type == NodeType::camera_parent_of_leaf) {
        return NodeType::nocamera_covered;
    }

    return NodeType::leaf;
}

inline auto BinaryTreeCameras(const BinaryTree::Node::PointerType root) {
    int result = 0;
    const auto is_leaf = BinaryTreeCameras(root, result) == NodeType::leaf;
    return result + is_leaf;
}

} //namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();
/**
 *     0
 *    /
 *   0
 *  / \
 * 0   0
 */
const auto SAMPLE2 = LevelOrderToBinaryTree({0, 0, SENTINEL, 0, 0});


THE_BENCHMARK(BinaryTreeCameras_Hash, SAMPLE1);

SIMPLE_TEST(BinaryTreeCameras_Hash, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(BinaryTreeCameras_Hash, TestSAMPLE2, 1, SAMPLE2);


THE_BENCHMARK(BinaryTreeCameras, SAMPLE1);

SIMPLE_TEST(BinaryTreeCameras, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(BinaryTreeCameras, TestSAMPLE2, 1, SAMPLE2);
