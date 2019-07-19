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


auto Partition_SinglyList(std::forward_list<int> &values,
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
