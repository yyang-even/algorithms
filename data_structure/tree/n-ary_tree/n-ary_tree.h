#pragma once

#include "array_representation.h"
#include "left-child_right-sibling_representation.h"


/**
 *            1
 *     /    /    \    \
 *    2    3     4     5
 *   / \         |   / | \
 *  6   7        8  9 10 11
 */
template <typename Node>
static inline constexpr auto MakeTheSampleTree() {
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
