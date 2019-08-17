#pragma once

template <typename Container>
auto ToFrequencyHashTable(const Container &container) {
    std::unordered_map<typename Container::value_type, typename Container::size_type> counter;
    for (const auto &c : container) {
        ++counter[c];
    }

    return counter;
}
