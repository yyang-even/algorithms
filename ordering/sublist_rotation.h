#pragma once

auto SublistLeftRotate_SinglyList(std::forward_list<int> &elements,
                                  const std::forward_list<int>::const_iterator cbefore_begin,
                                  const std::forward_list<int>::const_iterator cend,
                                  const std::forward_list<int>::difference_type k) {
    assert(k < std::distance(cbefore_begin, cend));

    auto mid = cbefore_begin;
    std::advance(mid, k);
    elements.splice_after(cbefore_begin, elements, mid, cend);

    return elements;
}
