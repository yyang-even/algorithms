#include "common_header.h"


namespace {

/** Insert Delete GetRandom O(1)
 *
 * @reference   https://leetcode.com/problems/insert-delete-getrandom-o1/
 *
 * Implement the RandomizedSet class:
 *  RandomizedSet() Initializes the RandomizedSet object.
 *  bool insert(int val) Inserts an item val into the set if not present. Returns true if
 *      the item was not present, false otherwise.
 *  bool remove(int val) Removes an item val from the set if present. Returns true if the
 *      item was present, false otherwise.
 *  int getRandom() Returns a random element from the current set of elements (it's
 *      guaranteed that at least one element exists when this method is called). Each
 *      element must have the same probability of being returned.
 * You must implement the functions of the class such that each function works in average
 * O(1) time complexity.
 */
class RandomizedSet {
    std::vector<int> values;
    std::unordered_map<int, std::size_t> value_index_map;

public:
    auto insert(const int v) {
        const auto result = value_index_map.emplace(v, values.size()).second;
        if (result) {
            values.push_back(v);
        }

        return result;
    }

    auto remove(const int v) {
        const auto iter = value_index_map.find(v);
        if (iter == value_index_map.cend()) {
            return false;
        }

        const auto to_be_removed_index = iter->second;
        value_index_map.erase(iter);
        if (to_be_removed_index + 1 != values.size()) {
            values[to_be_removed_index] = values.back();
            value_index_map[values.back()] = to_be_removed_index;
        }
        values.pop_back();

        return true;
    }

    auto getRandom() const {
        assert(not values.empty());
        return values[Random_Number(0, values.size() - 1)];
    }
};


/**
 * @reference   Insert Delete GetRandom O(1) - Duplicates allowed
 *              https://leetcode.com/problems/insert-delete-getrandom-o1-duplicates-allowed/
 *
 * Implement the RandomizedCollection class:
 *  RandomizedCollection() Initializes the RandomizedCollection object.
 *  bool insert(int val) Inserts an item val into the multiset if not present. Returns
 *      true if the item was not present, false otherwise.
 *  bool remove(int val) Removes an item val from the multiset if present. Returns true
 *      if the item was present, false otherwise. Note that if val has multiple occurrences
 *      in the multiset, we only remove one of them.
 *  int getRandom() Returns a random element from the current multiset of elements (it's
 *      guaranteed that at least one element exists when this method is called). The
 *      probability of each element being returned is linearly related to the number of
 *      same values the multiset contains.
 * You must implement the functions of the class such that each function works in average
 * O(1) time complexity.
 */
class RandomizedMultiSet {
    std::vector<int> values;
    std::unordered_map<int, std::unordered_set<std::size_t>> value_index_map;

public:
    auto insert(const int v) {
        auto &s = value_index_map[v];
        s.emplace(values.size());
        values.push_back(v);

        return s.size() == 1;
    }

    auto remove(const int v) {
        const auto iter = value_index_map.find(v);
        if (iter == value_index_map.cend() or iter->second.empty()) {
            return false;
        }

        auto &s = iter->second;
        const auto to_be_removed_index = *(s.cbegin());
        s.erase(s.cbegin());
        if (to_be_removed_index + 1 != values.size()) {
            values[to_be_removed_index] = values.back();
            value_index_map[values.back()].emplace(to_be_removed_index);
            value_index_map[values.back()].erase(values.size() - 1);
        }
        values.pop_back();

        return true;
    }

    auto getRandom() const {
        assert(not values.empty());
        return values[Random_Number(0, values.size() - 1)];
    }
};

}//namespace


#ifdef WANT_TESTS
TEST(RandomizedSetTest, TestSanity) {
    RandomizedSet set;

    EXPECT_TRUE(set.insert(1));
    EXPECT_FALSE(set.remove(2));
    EXPECT_EQ(1, set.getRandom());
    EXPECT_TRUE(set.insert(2));

    EXPECT_TRUE(set.getRandom());
    EXPECT_TRUE(set.remove(1));
    EXPECT_FALSE(set.insert(2));
    EXPECT_EQ(2, set.getRandom());
    EXPECT_EQ(2, set.getRandom());
}


TEST(RandomizedSetTest, TestSanity2) {
    RandomizedSet set;

    EXPECT_TRUE(set.insert(3));
    EXPECT_FALSE(set.insert(3));
    EXPECT_EQ(3, set.getRandom());
    EXPECT_EQ(3, set.getRandom());
    EXPECT_TRUE(set.insert(1));
    EXPECT_TRUE(set.remove(3));
    EXPECT_EQ(1, set.getRandom());
    EXPECT_EQ(1, set.getRandom());
    EXPECT_TRUE(set.insert(0));
    EXPECT_TRUE(set.remove(0));
}


TEST(RandomizedMultiSetTest, TestSanity1) {
    RandomizedMultiSet set;

    EXPECT_TRUE(set.insert(1));
    EXPECT_FALSE(set.insert(1));
    EXPECT_TRUE(set.insert(2));
    EXPECT_TRUE(set.getRandom());
    EXPECT_TRUE(set.remove(2));
    EXPECT_TRUE(set.remove(1));
    EXPECT_EQ(1, set.getRandom());
    EXPECT_EQ(1, set.getRandom());
}
#endif
