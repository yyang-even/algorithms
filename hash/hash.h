#pragma once


template <typename Container>
static inline constexpr auto
ToFrequencyHashTable(const Container &container) {
    std::unordered_map<typename Container::value_type, typename Container::size_type>
    counter;
    for (const auto &c : container) {
        ++counter[c];
    }

    return counter;
}


template <typename Container>
static inline constexpr auto
ToUnorderedSet(Container container) {
    using SetType = std::unordered_set<typename Container::value_type>;
    return ContainerCast<SetType>(std::move(container));
}
