#pragma once


template <typename Container, typename PointerType>
static inline void PushIfNotNull(Container &container, const PointerType node) {
    if (node) {
        container.push(node);
    }
}