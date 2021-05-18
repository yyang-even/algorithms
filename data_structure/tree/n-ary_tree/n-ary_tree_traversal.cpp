#include "common_header.h"

#include "n-ary_tree_traversal.h"


namespace {

inline auto LevelOrderTraversal_Iterative(
    const n_ary_tree::array_representation::Node::PointerType root) {
    std::vector<n_ary_tree::array_representation::Node::ValueType> result;
    LevelOrderTraversal_Iterative_Helper(root,
    [&result](const auto node) {
        assert(node);

        result.push_back(node->value);
        return true;
    });

    return result;
}


/** Preorder Traversal of N-ary Tree Without Recursion
 *
 * @reference   https://www.geeksforgeeks.org/preorder-traversal-of-n-ary-tree-without-recursion/
 * @reference   Iterative Preorder Traversal of an N-ary Tree
 *              https://www.geeksforgeeks.org/iterative-preorder-traversal-of-a-n-ary-tree/
 */
auto PreorderTraversal_Iterative(
    const n_ary_tree::array_representation::Node::PointerType root) {
    std::stack<std::remove_const_t<decltype(root)>> remaining_nodes;
    PushIfNotNull(remaining_nodes, root);

    std::vector<n_ary_tree::array_representation::Node::ValueType> result;
    while (not remaining_nodes.empty()) {
        const auto node = remaining_nodes.top();
        result.push_back(node->value);
        remaining_nodes.pop();

        for (auto iter = node->children.crbegin(); iter != node->children.crend(); ++iter) {
            PushIfNotNull(remaining_nodes, *iter);
        }
    }

    return result;
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 10.4-4.
 * @reference   Creating a tree with Left-Child Right-Sibling Representation
 *              https://www.geeksforgeeks.org/creating-tree-left-child-right-sibling-representation/
 */
auto PreorderTraversal_Recursive_Helper(
    n_ary_tree::child_sibling_representation::Node::PointerType node,
    const std::function<bool(const n_ary_tree::child_sibling_representation::Node::PointerType)>
on_each_node = {}) {
    for (; node; node = node->right_sibling) {
        if (on_each_node and not on_each_node(node)) {
            return false;
        }

        if (node->left_child)
            if (not PreorderTraversal_Recursive_Helper(node->left_child, on_each_node)) {
                return false;
            }
    }

    return true;
}

inline auto
PreorderTraversal_Recursive(
    const n_ary_tree::child_sibling_representation::Node::PointerType root) {
    std::vector<n_ary_tree::child_sibling_representation::Node::ValueType> result;
    PreorderTraversal_Recursive_Helper(root,
    [&result](const auto node) {
        assert(node);

        result.push_back(node->value);
        return true;
    });

    return result;
}


inline auto
LevelOrderTraversal_Iterative(
    const n_ary_tree::child_sibling_representation::Node::PointerType root) {
    std::vector<n_ary_tree::child_sibling_representation::Node::ValueType> result;
    LevelOrderTraversal_Iterative_Helper(root,
    [&result](const auto node) {
        assert(node);

        result.push_back(node->value);
        return true;
    });

    return result;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleTree<n_ary_tree::array_representation::Node>();
const auto SAMPLE2 =
    MakeTheSampleTree<n_ary_tree::child_sibling_representation::Node>();
const decltype(LevelOrderTraversal_Iterative(SAMPLE1)) EXPECTED_LEVELORDER =
{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
const decltype(PreorderTraversal_Iterative(SAMPLE1)) EXPECTED_PREORDER =
{1, 2, 6, 7, 3, 4, 8, 5, 9, 10, 11};


SIMPLE_BENCHMARK(LevelOrderTraversal_Iterative, Sample1, SAMPLE1);
SIMPLE_BENCHMARK(LevelOrderTraversal_Iterative, Sample2, SAMPLE2);

SIMPLE_TEST(LevelOrderTraversal_Iterative, TestSAMPLE1, EXPECTED_LEVELORDER, SAMPLE1);
SIMPLE_TEST(LevelOrderTraversal_Iterative, TestSAMPLE2, EXPECTED_LEVELORDER, SAMPLE2);


THE_BENCHMARK(PreorderTraversal_Iterative, SAMPLE1);

SIMPLE_TEST(PreorderTraversal_Iterative, TestSAMPLE1, EXPECTED_PREORDER, SAMPLE1);


THE_BENCHMARK(PreorderTraversal_Recursive, SAMPLE2);

SIMPLE_TEST(PreorderTraversal_Recursive, TestSAMPLE2, EXPECTED_PREORDER, SAMPLE2);
