#include "common_header.h"


namespace {

/** Design a data structure for LRU Cache
 *
 * @reference   https://www.geeksforgeeks.org/design-a-data-structure-for-lru-cache/
 * @reference   LRU Cache Implementation
 *              https://www.geeksforgeeks.org/lru-cache-implementation/
 */
class LRU_Cache {
    using KeyValuePair = std::pair<int, int>;
    using QueueType = std::list<KeyValuePair>;

    QueueType cache_queue;
    std::unordered_map<KeyValuePair::first_type, QueueType::const_iterator> cache_map;
    const QueueType::size_type CAPICITY = 0;

public:
    LRU_Cache(const QueueType::size_type capicity = 1024): CAPICITY(capicity) {
        assert(CAPICITY);
    }


    auto Size() const {
        return cache_queue.size();
    }


    auto Get(const KeyValuePair::first_type key) {
        auto iter = cache_map.find(key);
        if (iter != cache_map.cend()) {
            const auto value = iter->second->second;
            cache_queue.splice(cache_queue.cbegin(), cache_queue, iter->second);
            iter->second = cache_queue.cbegin();
            return value;
        }
        return -1;
    }


    void Set(const KeyValuePair::first_type key, const KeyValuePair::second_type value) {
        const auto iter = cache_map.find(key);
        if (iter != cache_map.cend()) {
            cache_queue.erase(iter->second);
            cache_queue.emplace_back(key, value);
            iter->second = cache_queue.cbegin();
        } else {
            if (Size() >= CAPICITY) {
                cache_map.erase(cache_queue.back().first);
                cache_queue.pop_back();
            }
            cache_queue.emplace_front(key, value);
            cache_map.emplace(key, cache_queue.cbegin());
        }
    }
};

}


TEST(LRU_CacheTest, TestSanity) {
    const auto CAPICITY = 2u;
    LRU_Cache lru_cache{CAPICITY};
    const auto ToValue = [](const auto key) {
        return key * 10;
    };

    lru_cache.Set(1, ToValue(1));
    lru_cache.Set(2, ToValue(2));

    EXPECT_EQ(CAPICITY, lru_cache.Size());
    EXPECT_EQ(ToValue(1), lru_cache.Get(1));

    lru_cache.Set(3, ToValue(3));

    EXPECT_EQ(CAPICITY, lru_cache.Size());
    EXPECT_EQ(-1, lru_cache.Get(2));

    lru_cache.Set(4, ToValue(4));

    EXPECT_EQ(CAPICITY, lru_cache.Size());
    EXPECT_EQ(-1, lru_cache.Get(1));
    EXPECT_EQ(ToValue(3), lru_cache.Get(3));
    EXPECT_EQ(ToValue(4), lru_cache.Get(4));
}
