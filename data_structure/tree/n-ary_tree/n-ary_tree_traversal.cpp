#include "common_header.h"

#include "n-ary_tree.h"


namespace {

/** General Tree (Each node can have arbitrary number of children) Level Order Traversal
 *
 * @reference   https://www.geeksforgeeks.org/generic-tree-level-order-traversal/
 */
auto InorderTraversal_Iterative_Helper(
    const n_ary_tree::array_representation::Node::PointerType root,
const std::function<bool(const n_ary_tree::array_representation::Node::PointerType)> on_each_node = {}) {
    std::queue<std::remove_const_t<decltype(root)>> remaining_nodes;
    PushIfNotNull(remaining_nodes, root);

    while (not remaining_nodes.empty()) {
        for (auto current_level_nodes_number = remaining_nodes.size();
             current_level_nodes_number; --current_level_nodes_number) {

            const auto current_node = remaining_nodes.front();
            if (on_each_node and not on_each_node(current_node)) {
                return false;
            }
            remaining_nodes.pop();

            for (const auto child : current_node->children) {
                PushIfNotNull(remaining_nodes, child);
            }
        }
    }

    return true;
}

auto InorderTraversal_Iterative(const n_ary_tree::array_representation::Node::PointerType root) {
    std::vector<n_ary_tree::array_representation::Node::ValueType> result;
    InorderTraversal_Iterative_Helper(root,
    [&result](const n_ary_tree::array_representation::Node::PointerType node) {
        assert(node);

        result.push_back(node->value);
        return true;
    });

    return result;
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 10.4-4.
 */

}//namespace


const auto SAMPLE1 = n_ary_tree::array_representation::MakeTheSampleTree();
const decltype(InorderTraversal_Iterative(SAMPLE1)) EXPECTED1 =
{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};


SIMPLE_BENCHMARK(InorderTraversal_Iterative, SAMPLE1);

SIMPLE_TEST(InorderTraversal_Iterative, TestSAMPLE1, EXPECTED1, SAMPLE1);
