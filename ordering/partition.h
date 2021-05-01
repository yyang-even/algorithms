#pragma once


template <typename Iterator, typename Predicate>
static constexpr inline auto
Partition(Iterator begin, const Iterator end, const Predicate predicate) {
    auto j = begin;
    for (; begin != end; ++begin) {
        if (predicate(*begin)) {
            std::iter_swap(begin, j++);
        }
    }

    return j;
}


static inline auto
Partition_SinglyList(std::forward_list<int> &values,
                     const std::forward_list<int>::const_iterator before_begin,
                     const std::forward_list<int>::const_iterator begin,
                     std::forward_list<int>::const_iterator &last) {
    const auto pivot = last;
    auto before_mid = before_begin;
    for (auto iter = begin; iter != pivot; ++iter) {
        if (*iter > *pivot) {
            values.splice_after(last, values, before_mid);
            ++last;
            iter = before_mid;
        } else {
            ++before_mid;
        }
    }

    return before_mid;
}
