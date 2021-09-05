#include "common_header.h"

#include "binary_tree.h"
#include "compare_binary_trees.h"
#include "single_order_to_binary_tree.h"


namespace {

/** Verify Preorder Serialization of a Binary Tree
 *
 * @reference   https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/
 *
 * One way to serialize a binary tree is to use preorder traversal. When we encounter a
 * non-null node, we record the node's value. If it is a null node, we record using a
 * sentinel value such as '#'. Given a string of comma-separated values preorder, return
 * true if it is a correct preorder traversal serialization of a binary tree. It is
 * guaranteed that each comma-separated value in the string must be either an integer or
 * a character '#' representing null pointer. You may assume that the input format is
 * always valid. For example, it could never contain two consecutive commas, such as
 * "1,,3". Note: You are not allowed to reconstruct the tree.
 * preoder consist of integers in the range [0, 100] and '#' separated by commas ','.
 */
constexpr auto VerifyPreorderStr_Degree(const std::string_view preorder) {
    if (preorder.empty()) {
        return false;
    }

    bool in_node = false;
    int degree = 1;
    for (const auto c : preorder) {
        if (c == ',') {
            in_node = false;
        } else if (not in_node) {
            in_node = true;
            if (--degree < 0) {
                return false;
            }
            if (c != '#') {
                degree += 2;
            }
        }
    }

    return degree == 0;
}


constexpr bool
VerifyPreorderStr_Recursive(const std::string_view preorder, std::size_t &i) {
    if (i >= preorder.size()) {
        return false;
    }

    if (preorder[i] == '#') {
        i += 2;
        return true;
    } else {
        while (i < preorder.size() and std::isdigit(preorder[i])) {
            ++i;
        }
        ++i;
        return VerifyPreorderStr_Recursive(preorder, i) and
               VerifyPreorderStr_Recursive(preorder, i);
    }
}

inline constexpr auto
VerifyPreorderStr_Recursive(const std::string_view preorder) {
    std::size_t i = 0;
    return VerifyPreorderStr_Recursive(preorder, i) and i >= preorder.size();
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


/** Create a tree in level order
 *
 * @reference   https://www.geeksforgeeks.org/create-a-tree-in-level-order/
 *
 * Given an array of elements, the task is to insert these elements in level order and
 * construct a tree.
 */
auto LevelOrderToCompleteBinaryTree(const BinaryTree::ArrayType &level_order) {
    assert(not level_order.empty());

    const auto root = std::make_shared<BinaryTree::Node>(level_order.front());
    std::queue<BinaryTree::Node::PointerType> q;
    q.push(root);
    std::size_t i = 0;
    while (not q.empty()) {
        auto &node = *q.front();
        q.pop();

        const auto left_child_index = LeftChild(i);
        if (left_child_index < level_order.size()) {
            q.push(SetLeftChild(node, level_order[left_child_index]));
        }

        const auto right_child_index = RightChild(i);
        if (right_child_index < level_order.size()) {
            q.push(SetRightChild(node, level_order[right_child_index]));
        }

        ++i;
    }

    return root;
}

}//namespace


THE_BENCHMARK(VerifyPreorderStr_Degree, "9,3,4,#,#,1,#,#,2,#,6,#,#");

SIMPLE_TEST(VerifyPreorderStr_Degree, TestSAMPLE1, true, "9,3,4,#,#,1,#,#,2,#,6,#,#");
SIMPLE_TEST(VerifyPreorderStr_Degree, TestSAMPLE2, false, "1,#");
SIMPLE_TEST(VerifyPreorderStr_Degree, TestSAMPLE3, false, "9,#,#,1");
SIMPLE_TEST(VerifyPreorderStr_Degree, TestSAMPLE4, true, "1,#,#");


THE_BENCHMARK(VerifyPreorderStr_Recursive, "9,3,4,#,#,1,#,#,2,#,6,#,#");

SIMPLE_TEST(VerifyPreorderStr_Recursive, TestSAMPLE1, true,
            "9,3,4,#,#,1,#,#,2,#,6,#,#");
SIMPLE_TEST(VerifyPreorderStr_Recursive, TestSAMPLE2, false, "1,#");
SIMPLE_TEST(VerifyPreorderStr_Recursive, TestSAMPLE3, false, "9,#,#,1");
SIMPLE_TEST(VerifyPreorderStr_Recursive, TestSAMPLE4, true, "1,#,#");


const auto SAMPLE1 = MakeTheSampleCompleteTree().GetRoot();

/**
 *     1
 *    / \
 *   2   3
 *    \
 *     4
 */
const std::vector SAMPLE2L = {1, 2, 3, SENTINEL, 4};


THE_BENCHMARK(BinaryTreeFromString, "1(2()(4))(3)");

SIMPLE_TEST(areIdenticalTrees, TestSAMPLE1, true, SAMPLE1,
            BinaryTreeFromString("1(2(4)(5))(3)"));
SIMPLE_TEST(areIdenticalTrees, TestSAMPLE2, true, LevelOrderToBinaryTree(SAMPLE2L),
            BinaryTreeFromString("1(2()(4))(3)"));


const std::vector SAMPLE1L = {1, 2, 3, 4, 5};


THE_BENCHMARK(LevelOrderToCompleteBinaryTree, SAMPLE1L);

SIMPLE_TEST(areIdenticalTrees, TestSAMPLE1C, true, SAMPLE1,
            LevelOrderToCompleteBinaryTree(SAMPLE1L));




THE_BENCHMARK(LevelOrderToBinaryTree, SAMPLE1L);

SIMPLE_TEST(areIdenticalTrees, TestSAMPLE1B, true, SAMPLE1,
            LevelOrderToBinaryTree(SAMPLE1L));
