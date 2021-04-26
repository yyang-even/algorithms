#pragma once


template <typename Container>
static constexpr inline auto ToFrequencyHashTable(const Container &container) {
    std::unordered_map<typename Container::value_type, typename Container::size_type>
    counter;
    for (const auto &c : container) {
        ++counter[c];
    }

    return counter;
}


template <typename Container>
static constexpr inline auto ToUnorderedSet(const Container &container) {
    return ContainerCast<std::unordered_set<typename Container::value_type>>(container);
}
