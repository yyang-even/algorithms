#pragma once


template <typename PointerType>
static inline auto Search(const PointerType root, const decltype(root->value) x) {
    PointerType target;
    LevelOrderTraversal_Iterative_Helper(root,
    [&target, x](const auto node) {
        if (node->value == x) {
            target = node;
            return false;
        }
        return true;
    });

    return target;
}
