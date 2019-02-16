#pragma once

#include <forward_list>


auto GetBeforeMiddleTwoPointersSTL(const std::forward_list<int>::const_iterator cbefore_begin,
                                   const std::forward_list<int>::const_iterator cbegin,
                                   const std::forward_list<int>::const_iterator cend) {
    assert(cbegin != cend);

    auto fast_ptr = cbegin;
    auto slow_ptr = cbefore_begin;

    while (fast_ptr != cend and ++fast_ptr != cend) {
        ++fast_ptr;
        ++slow_ptr;
    }

    return slow_ptr;
}
