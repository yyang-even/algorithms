#pragma once

#include "data_structure/tree/tree.h"


/** N-ary Tree
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 10.4.
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

    explicit Node(ValueType v) : value(std::move(v)) {}
};

} //namespace child_sibling_representation

} //namespace n_ary_tree
