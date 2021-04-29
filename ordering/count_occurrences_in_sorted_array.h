#pragma once


template<typename Compare>
static constexpr inline auto
CountAllOccurrencesInSortedArray_STL(const std::vector<int> &values,
                                     const Compare compare) {
    assert(not values.empty());
    assert(std::is_sorted(values.cbegin(), values.cend(), compare));

    std::vector<std::pair<int, std::size_t>> outputs;
    std::size_t count = 1;
    auto prev = values.cbegin();
    for (auto iter = std::next(prev); iter != values.cend(); ++iter, ++prev) {
        if (*prev != *iter) {
            outputs.emplace_back(*prev, count);
            count = 1;
        } else {
            ++count;
        }
    }
    outputs.emplace_back(values.back(), count);

    return outputs;
}
