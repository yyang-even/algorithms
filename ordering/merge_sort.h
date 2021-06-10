#pragma once


template <typename Iterator, typename MergeFunc>
static inline constexpr void
MergeSort(const Iterator begin, const std::size_t n, const MergeFunc merge) {
    if (n > 1) {
        const auto middle = n >> 1;
        const auto middle_begin = begin + middle;
        MergeSort(begin, middle, merge);
        MergeSort(middle_begin, n - middle, merge);
        merge(begin, middle_begin, begin + n);
    }
}
