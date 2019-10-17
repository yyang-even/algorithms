#pragma once

template <typename ArrayType, typename SortFunc>
static auto BucketSort_STL(ArrayType elements,
                           const std::function<std::size_t(const typename ArrayType::value_type &)> to_index,
                           const SortFunc sort_func) {
    typename std::map<std::size_t, ArrayType> buckets;
    for (auto &elem : elements) {
        buckets[to_index(elem)].emplace_back(std::move(elem));
    }

    auto iter = elements.begin();
    for (auto &key_value_pair : buckets) {
        sort_func(key_value_pair.second.begin(), key_value_pair.second.end());
        iter = std::copy(std::make_move_iterator(key_value_pair.second.cbegin()),
                         std::make_move_iterator(key_value_pair.second.cend()), iter);
    }

    return elements;
}
