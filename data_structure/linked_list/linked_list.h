#pragma once


template <typename NodePointer>
void Advance(NodePointer &current, unsigned distance) {
    for (; distance--; current = current->next);
}
