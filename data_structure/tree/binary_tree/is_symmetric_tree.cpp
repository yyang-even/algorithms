#include "common_header.h"

#include "binary_tree.h"
#include "single_order_to_binary_tree.h"


namespace {

/** Symmetric Tree
 *
 * @reference   https://leetcode.com/problems/symmetric-tree/
 *
 * Given the root of a binary tree, check whether it is a mirror of itself (i.e.,
 * symmetric around its center).
 */
inline auto isMirror(const BinaryTree::Node::PointerType left_sub,
                     const BinaryTree::Node::PointerType right_sub) {
    if (not left_sub and not right_sub) {
        return true;
    }

    if (left_sub and right_sub)
        return left_sub->value == right_sub->value and
               isMirror(left_sub->left, right_sub->right) and
               isMirror(left_sub->right, right_sub->left);

    return false;
}

inline auto isSymmetric_Recursive(const BinaryTree::Node::PointerType root) {
    return root and isMirror(root->left, root->right);
}


auto isSymmetric_Iterative(const BinaryTree::Node::PointerType root) {
    std::queue<BinaryTree::Node::PointerType> q;
    q.push(root);
    q.push(root);

    while (not q.empty()) {
        const auto left_sub = q.front();
        q.pop();
        const auto right_sub = q.front();
        q.pop();

        if (not left_sub and not right_sub) {
            continue;
        }

        if ((not left_sub or not right_sub) or (left_sub->value != right_sub->value)) {
            return false;
        }

        q.push(left_sub->left);
        q.push(right_sub->right);
        q.push(left_sub->right);
        q.push(right_sub->left);
    }

    return true;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();

/**
 *      1
 *    /   \
 *   2     2
 *  / \   / \
 * 3   4 4   3
 */
const auto SAMPLE2 = LevelOrderToBinaryTree( {
    1, 2, 2, 3, 4, 4, 3
});


THE_BENCHMARK(isSymmetric_Recursive, SAMPLE1);

SIMPLE_TEST(isSymmetric_Recursive, TestSAMPLE1, false, SAMPLE1);
SIMPLE_TEST(isSymmetric_Recursive, TestSAMPLE2, true, SAMPLE2);


THE_BENCHMARK(isSymmetric_Iterative, SAMPLE1);

SIMPLE_TEST(isSymmetric_Iterative, TestSAMPLE1, false, SAMPLE1);
SIMPLE_TEST(isSymmetric_Iterative, TestSAMPLE2, true, SAMPLE2);
