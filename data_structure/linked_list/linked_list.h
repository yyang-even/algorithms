#pragma once


template <typename NodePointer>
static constexpr inline void
Advance(NodePointer &current, unsigned distance) {
    for (; distance--; current = current->next);
}
