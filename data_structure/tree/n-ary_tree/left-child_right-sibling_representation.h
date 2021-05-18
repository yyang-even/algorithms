#pragma once

#include "data_structure/tree/tree.h"


/** N-ary Tree
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 10.4.
 * @reference   Left-Child Right-Sibling Representation of Tree
 *              https://www.geeksforgeeks.org/left-child-right-sibling-representation-tree/
 * @reference   Generic Trees(N-array Trees)
 *              https://www.geeksforgeeks.org/generic-treesn-array-trees/
 */
namespace n_ary_tree {

namespace child_sibling_representation {

struct Node {
    using ValueType = int;
    using PointerType = std::shared_ptr<Node>;

    PointerType left_child;
    PointerType right_sibling;
    ValueType value = 0;

    constexpr explicit Node(ValueType v) : value(std::move(v)) {}
};


/**
 * @reference   Creating a tree with Left-Child Right-Sibling Representation
 *              https://www.geeksforgeeks.org/creating-tree-left-child-right-sibling-representation/
 */
static inline auto
AddSibling(Node::PointerType node, Node::ValueType v) {
    for (; node->right_sibling; node = node->right_sibling);
    return node->right_sibling = std::make_shared<Node>(std::move(v));
}

static inline auto
AddChild(Node &parent, Node::ValueType v) {
    if (parent.left_child) {
        return AddSibling(parent.left_child, std::move(v));
    }
    return parent.left_child = std::make_shared<Node>(std::move(v));
}

} //namespace child_sibling_representation

} //namespace n_ary_tree
