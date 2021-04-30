#pragma once


static inline void
SortedInsert(const std::vector<int>::iterator begin,
             const std::vector<int>::iterator last) {
    assert(std::is_sorted(begin, last));
    const auto insertion_point = std::upper_bound(begin, last, *last);
    std::rotate(insertion_point, last, std::next(last));
}
