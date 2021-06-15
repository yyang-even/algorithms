#include "common_header.h"

#include "data_structure/tree/n-ary_tree/n-ary_tree.h"


namespace {

using NodeType = n_ary_tree::child_sibling_representation::Node;
using TableType = std::unordered_map<NodeType *, NodeType::ValueType>;

/** Planning a company party
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Problems 15-6.
 * @reference   Maximize the total profit of all the persons
 *              https://www.geeksforgeeks.org/maximize-the-total-profit-of-all-the-persons/
 *
 * There is a hierarchical structure in an organization. A party is to be organized. No two
 * immediate subordinates can come to the party. A profit is associated with every person.
 * You have to maximize the total profit of all the persons who come to the party.
 */
auto CompanyPartyPlanning(const NodeType::PointerType node, TableType &max_profits) {
    if (not node) {
        return 0;
    }

    if (max_profits.find(node.get()) != max_profits.cend()) {
        return max_profits[node.get()];
    }

    auto profit_with_node = node->value;
    decltype(profit_with_node) profit_without_node = 0;
    for (auto child = node->left_child; child; child = child->right_sibling) {
        profit_without_node += CompanyPartyPlanning(child, max_profits);

        for (auto grandchild = child->left_child;
             grandchild;
             grandchild = grandchild->right_sibling) {
            profit_with_node += CompanyPartyPlanning(grandchild, max_profits);
        }
    }

    return max_profits[node.get()] = std::max(profit_with_node, profit_without_node);
}

inline auto CompanyPartyPlanning(const NodeType::PointerType root) {
    TableType max_profits;
    return CompanyPartyPlanning(root, max_profits);
}

}//namespace


const NodeType::PointerType SAMPLE0 = nullptr;
const auto SAMPLE1 = std::make_shared<NodeType>(1);

/**
 *   1
 *  /
 * 2
 */
inline auto MakeSample2() {
    const auto root = std::make_shared<NodeType>(1);
    AddChild(*root, 2);

    return root;
}
const auto SAMPLE2 = MakeSample2();

const auto SAMPLE3 = MakeTheSampleTree<NodeType>();


THE_BENCHMARK(CompanyPartyPlanning, SAMPLE3);

SIMPLE_TEST(CompanyPartyPlanning, TestSAMPLE0, 0, SAMPLE0);
SIMPLE_TEST(CompanyPartyPlanning, TestSAMPLE1, SAMPLE1->value, SAMPLE1);
SIMPLE_TEST(CompanyPartyPlanning, TestSAMPLE2, SAMPLE2->left_child->value, SAMPLE2);
SIMPLE_TEST(CompanyPartyPlanning, TestSAMPLE3, 54, SAMPLE3);
