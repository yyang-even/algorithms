#pragma once


static inline auto
ToCountingArray(const std::vector<int> &values, const std::size_t range,
                const std::function<std::size_t(const int)> to_index) {
    assert(not values.empty());

    std::vector<int> counter(range, 0);
    for (const auto v : values) {
        ++counter[to_index(v)];
    }

    for (auto iter = std::next(counter.begin()); iter != counter.end(); ++iter) {
        *iter += *std::prev(iter);
    }

    return counter;
}


static inline auto
CountingSort(std::vector<int> values, const std::size_t range,
             const std::function<std::size_t(const int)> to_index) {
    if (values.empty()) {
        return values;
    }

    auto counter = ToCountingArray(values, range, to_index);

    std::vector<int> outputs(values.size(), 0);
    for (auto riter = values.rbegin(); riter != values.rend(); ++riter) {
        outputs[--counter[to_index(*riter)]] = std::move(*riter);
    }

    return outputs;
}


/**
 * @reference   Implementing Counting Sort using map in C++
 *              https://www.geeksforgeeks.org/implementing-counting-sort-using-map-in-c/
 */
template <typename ArrayType, typename ToIndexFunc>
static inline constexpr auto
CountingSort_STL(ArrayType values, const ToIndexFunc to_index) {
    if (values.empty()) {
        return values;
    }

    std::map<decltype(to_index(values.front())), std::size_t> counter;
    for (const auto &v : values) {
        ++counter[to_index(v)];
    }

    auto prev = counter.begin();
    for (auto iter = std::next(prev); iter != counter.end(); ++iter, ++prev) {
        iter->second += prev->second;
    }

    ArrayType outputs(values.size());
    for (auto riter = values.rbegin(); riter != values.rend(); ++riter) {
        outputs[--counter[to_index(*riter)]] = std::move(*riter);
    }

    return outputs;
}
