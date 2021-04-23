#pragma once


template <typename Iterator, typename SwapFunc>
static constexpr inline void
Reverse_TwoPointers(const Iterator begin, const Iterator end, const SwapFunc swap) {
    if (begin != end) {
        auto l_iter = begin;
        auto r_iter = std::prev(end);
        while (l_iter < r_iter) {
            swap(*l_iter++, *r_iter--);
        }
    }
}
