#pragma once

#include "data_structure/tree/tree.h"


/** N-ary Tree
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 10.4.
 */
namespace n_ary_tree {

namespace array_representation {

struct Node {
    using ValueType = int;
    using PointerType = std::shared_ptr<Node>;

    ValueType value = 0;
    std::vector<PointerType> children;

    explicit Node(ValueType v) : value(std::move(v)) {}
};


auto AddChild(Node &parent, Node::ValueType v) {
    parent.children.emplace_back(std::make_shared<Node>(std::move(v)));
    return parent.children.back();
}


/**
 *            1
 *     /    /    \    \
 *    2    3     4     5
 *   / \         |   / | \
 *  6   7        8  9 10 11
 */
auto MakeTheSampleTree() {
    const auto root = std::make_shared<Node>(1);
    auto &node2 = *AddChild(*root, 2);
    AddChild(*root, 3);
    auto &node4 = *AddChild(*root, 4);
    auto &node5 = *AddChild(*root, 5);
    AddChild(node2, 6);
    AddChild(node2, 7);
    AddChild(node4, 8);
    for (auto i = 9; i < 12; ++i) {
        AddChild(node5, i);
    }

    return root;
}

} //namespace array_representation

} //namespace n_ary_tree
