#pragma once

#include "data_structure/tree/tree.h"


/** N-ary Tree
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 10.4.
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


static inline auto
AddChild(Node &parent, Node::ValueType v) {
    parent.children.emplace_back(std::make_shared<Node>(std::move(v)));
    return parent.children.back();
}

} //namespace array_representation

} //namespace n_ary_tree
