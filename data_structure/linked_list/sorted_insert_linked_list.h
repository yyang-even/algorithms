#pragma once


/**
 * @highlight   The use of std::forward_list::cbefore_begin().
 */
static inline auto
BeforeLowerBound(const std::forward_list<int>::const_iterator cbefore_begin,
                 const std::forward_list<int>::const_iterator cbegin,
                 const std::forward_list<int>::const_iterator cend,
                 const std::forward_list<int>::value_type n) {
    assert(std::is_sorted(cbegin, cend));

    auto current = cbefore_begin;
    for (auto next = cbegin; (next != cend) and (*next < n); ++next, ++current);

    return current;
}

static inline auto
BeforeLowerBound(const std::forward_list<int> &sorted_list,
                 const std::forward_list<int>::value_type n) {
    return BeforeLowerBound(
               sorted_list.cbefore_begin(), sorted_list.cbegin(), sorted_list.cend(), n);
}


static inline auto
SortedInsert_STL(std::forward_list<int> &sorted_list,
                 std::forward_list<int> &other_list,
                 const std::forward_list<int>::const_iterator before_it,
                 const std::forward_list<int>::const_iterator it) {
    const auto after_me = BeforeLowerBound(sorted_list, *it);
    sorted_list.splice_after(after_me, other_list, before_it);

    return sorted_list;
}

static inline auto
SortedInsert_STL(std::forward_list<int> sorted_list,
                 const std::forward_list<int>::value_type n) {
    const auto after_me = BeforeLowerBound(sorted_list, n);
    sorted_list.insert_after(after_me, n);

    return sorted_list;
}
