#pragma once


template <typename NodePointer>
static inline constexpr void
Advance(NodePointer &current, unsigned distance) {
    for (; distance--; current = current->next);
}
