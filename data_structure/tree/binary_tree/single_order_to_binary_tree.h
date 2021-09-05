#pragma once

#include "binary_tree.h"

#include "data_structure/heap/heap.h"


constexpr auto SENTINEL = INT_MIN;

auto LevelOrderToBinaryTree(const BinaryTree::ArrayType &level_order) {
    assert(not level_order.empty() and level_order.front() != SENTINEL);

    const auto root = std::make_shared<BinaryTree::Node>(level_order.front());
    std::queue<BinaryTree::Node::PointerType> q;
    q.push(root);
    std::size_t i = 0;
    while (not q.empty()) {
        if (level_order[i] != SENTINEL) {
            auto &node = *q.front();
            q.pop();

            const auto left_child_index = LeftChild(i);
            if (left_child_index < level_order.size() and
                level_order[left_child_index] != SENTINEL) {
                q.push(SetLeftChild(node, level_order[left_child_index]));
            }

            const auto right_child_index = RightChild(i);
            if (right_child_index < level_order.size() and
                level_order[right_child_index] != SENTINEL) {
                q.push(SetRightChild(node, level_order[right_child_index]));
            }
        }

        ++i;
    }

    return root;
}
