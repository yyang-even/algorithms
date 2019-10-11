#pragma once

static auto ToCountingArray(const std::vector<int> &values, const std::size_t range,
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


inline static auto CountingSort(const std::vector<int> &values, const std::size_t range,
                                const std::function<std::size_t(const int)> to_index) {
    auto counter = ToCountingArray(values, range, to_index);

    std::vector<int> outputs(values.size(), 0);
    for (auto riter = values.crbegin(); riter != values.crend(); ++riter) {
        outputs[--counter[to_index(*riter)]] = *riter;
    }

    return outputs;
}
