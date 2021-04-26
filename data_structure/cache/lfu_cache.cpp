#include "common_header.h"


namespace {

/** Least Frequently Used (LFU) Cache Implementation
 *
 * @reference   https://www.geeksforgeeks.org/least-frequently-used-lfu-cache-implementation/
 *
 * Least Frequently Used (LFU) is a caching algorithm in which the least frequently used
 * cache block is removed whenever the cache is overflowed.
 */
class LFU_Cache {
    using KeyType = int;
    using ValueCountPair = std::pair<int, unsigned>;
    using MapType = std::unordered_map<KeyType, ValueCountPair>;
    using HeapType =
        std::vector<std::pair<ValueCountPair::second_type, MapType::const_iterator>>;
    using SizeType = MapType::size_type;

    MapType cache_map;
    SizeType CAPICITY = 0;

public:
    LFU_Cache(const SizeType capicity = 1024): CAPICITY(capicity) {
        assert(CAPICITY);
    }


    auto Size() const {
        return cache_map.size();
    }


    auto Get(const KeyType key) {
        if (const auto iter = cache_map.find(key); iter != cache_map.cend()) {
            auto &[value, count] = iter->second;
            ++count;
            return value;
        }
        return -1;
    }


    void Set(const KeyType key, const ValueCountPair::first_type new_value) {
        if (const auto iter = cache_map.find(key); iter != cache_map.cend()) {
            auto &[value, count] = iter->second;
            value = new_value;
            ++count;
        } else {
            if (Size() >= CAPICITY) {
                HeapType heap;
                for (auto iter = cache_map.cbegin(); iter != cache_map.cend(); ++iter) {
                    heap.emplace_back(iter->second.second, iter);
                }
                std::make_heap(heap.begin(), heap.end(), [](const auto & lhs, const auto & rhs) {
                    return lhs.first > rhs.first;
                });
                cache_map.erase(heap.front().second);
            }
            cache_map.emplace(key, ValueCountPair{new_value, 0});
        }
    }
};

}


TEST(LFU_CacheTest, TestSanity) {
    const auto CAPICITY = 2u;
    LFU_Cache lfu_cache{CAPICITY};
    constexpr auto ToValue = [](const auto key) {
        return key * 10;
    };


    lfu_cache.Set(1, ToValue(1));
    lfu_cache.Set(2, ToValue(2));

    EXPECT_EQ(CAPICITY, lfu_cache.Size());
    EXPECT_EQ(ToValue(1), lfu_cache.Get(1));

    lfu_cache.Set(3, ToValue(3));

    EXPECT_EQ(CAPICITY, lfu_cache.Size());
    EXPECT_EQ(-1, lfu_cache.Get(2));

    lfu_cache.Set(4, ToValue(4));

    EXPECT_EQ(CAPICITY, lfu_cache.Size());
    EXPECT_EQ(-1, lfu_cache.Get(3));
    EXPECT_EQ(ToValue(1), lfu_cache.Get(1));
    EXPECT_EQ(ToValue(4), lfu_cache.Get(4));
}
