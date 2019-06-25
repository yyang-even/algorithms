#pragma once

/**
 * @highlight   The use of std::forward_list::cbefore_begin().
 */
auto SortedInsert_STL(std::forward_list<int> sorted_list,
                      const std::forward_list<int>::value_type n) {
    assert(std::is_sorted(sorted_list.cbegin(), sorted_list.cend()));

    auto current = sorted_list.cbefore_begin();
    for (auto next = sorted_list.cbegin();
         (next != sorted_list.cend()) and (*next < n); ++next, ++current);
    sorted_list.insert_after(current, n);

    return sorted_list;
}
