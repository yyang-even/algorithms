#pragma once

template <typename ArrayType>
auto Partition(typename ArrayType::iterator begin, typename ArrayType::iterator end,
               const std::function<bool(const typename ArrayType::value_type)> predicate) {
    auto j = begin;
    for (; begin != end; ++begin) {
        if (predicate(*begin)) {
            std::iter_swap(begin, j++);
        }
    }

    return j;
}
