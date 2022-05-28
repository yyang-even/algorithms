#pragma once


static inline auto CountAllOccurrencesInSortedArray_STL(const std::vector<int> &values) {
    assert(not values.empty());

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
