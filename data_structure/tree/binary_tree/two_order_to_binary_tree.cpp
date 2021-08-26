#include "common_header.h"

#include "binary_tree.h"
#include "compare_binary_trees.h"


namespace {

/** Construct Binary Tree from Preorder and Inorder Traversal
 *
 * @reference   https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
 *
 * Given two integer arrays preorder and inorder where preorder is the preorder traversal
 * of a binary tree and inorder is the inorder traversal of the same tree, construct and
 * return the binary tree.
 * preorder and inorder consist of unique values.
 */
auto ConstructBinaryTree_PreAndIn(const BinaryTree::ArrayType &preorder,
                                  std::size_t &pre_i, const std::unordered_map<int, int> &inorder_map,
                                  const int left, const int right) {
    if (left > right)
        return BinaryTree::Node::PointerType{};

    const auto root_value = preorder[pre_i++];
    const auto root = std::make_shared<BinaryTree::Node>(root_value);

    const auto mid = inorder_map.at(root_value);
    root->left = ConstructBinaryTree_PreAndIn(preorder, pre_i, inorder_map, left, mid - 1);
    root->right =
        ConstructBinaryTree_PreAndIn(preorder, pre_i, inorder_map, mid + 1, right);

    return root;
}

auto ConstructBinaryTree_PreAndIn(const BinaryTree::ArrayType &preorder,
                                  const BinaryTree::ArrayType &inorder) {
    assert(inorder.size() == preorder.size());

    std::unordered_map<int, int> index_map;
    for (std::size_t i = 0; i < inorder.size(); ++i) {
        index_map[inorder[i]] = i;
    }

    std::size_t pre_i = 0;
    return ConstructBinaryTree_PreAndIn(preorder, pre_i, index_map, 0, inorder.size() - 1);
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();
const BinaryTree::ArrayType SAMPLE1IN = {4, 2, 5, 1, 3};
const BinaryTree::ArrayType SAMPLE1PRE = {1, 2, 4, 5, 3};


THE_BENCHMARK(ConstructBinaryTree_PreAndIn, SAMPLE1PRE, SAMPLE1IN);

SIMPLE_TEST(areIdenticalTrees, TestSAMPLE1, true,
            SAMPLE1, ConstructBinaryTree_PreAndIn(SAMPLE1PRE, SAMPLE1IN));
