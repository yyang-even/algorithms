#pragma once


template <typename Container>
static inline constexpr auto
ToFrequencyHashTable(const Container &container) {
    std::unordered_map<typename Container::value_type, int> counter;
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


struct PairHash {
    template <class T1, class T2>
    auto operator()(const std::pair<T1, T2> &p) const {
        const auto h1 = std::hash<T1> {}(p.first);
        const auto h2 = std::hash<T2> {}(p.second);

        return h1 ^ h2;
    }
};
