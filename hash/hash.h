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


/**
 * @reference   Design HashSet
 *              https://leetcode.com/problems/design-hashset/
 *
 * Design a HashSet without using any built-in hash table libraries. Implement MyHashSet
 * class:
 *  void add(key) Inserts the value key into the HashSet.
 *  bool contains(key) Returns whether the value key exists in the HashSet or not.
 *  void remove(key) Removes the value key in the HashSet. If key does not exist in the
 *      HashSet, do nothing.
 * 0 <= key <= 10^6
 */


/**
 * @reference   Design HashMap
 *              https://leetcode.com/problems/design-hashmap/
 *
 * Design a HashMap without using any built-in hash table libraries. Implement the
 * MyHashMap class:
 *  MyHashMap() initializes the object with an empty map.
 *  void put(int key, int value) inserts a (key, value) pair into the HashMap. If the
 *      key already exists in the map, update the corresponding value.
 *  int get(int key) returns the value to which the specified key is mapped, or -1 if
 *      this map contains no mapping for the key.
 *  void remove(key) removes the key and its corresponding value if the map contains
 *      the mapping for the key.
 * 0 <= key, value <= 10^6
 */
