#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

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
    QueueType::size_type CAPICITY = 0;

public:
    LRU_Cache(const QueueType::size_type capicity = 1024): CAPICITY(capicity) {
        assert(CAPICITY);
    }


    auto Size() const {
        return cache_queue.size();
    }


    auto Get(const KeyValuePair::first_type key) {
        if (const auto iter = cache_map.find(key); iter != cache_map.cend()) {
            const auto value = iter->second->second;
            cache_queue.splice(cache_queue.cbegin(), cache_queue, iter->second);
            iter->second = cache_queue.cbegin();
            return value;
        }
        return -1;
    }


    void Set(const KeyValuePair::first_type key, const KeyValuePair::second_type value) {
        if (const auto iter = cache_map.find(key); iter != cache_map.cend()) {
            cache_queue.splice(cache_queue.cbegin(), cache_queue, iter->second);
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


/** Program for Least Recently Used (LRU) Page Replacement algorithm
 *
 * @reference   https://www.geeksforgeeks.org/program-for-least-recently-used-lru-page-replacement-algorithm/
 * @reference   Implementation of Least Recently Used (LRU) page replacement algorithm using Counters
 *              https://www.geeksforgeeks.org/implementation-of-least-recently-used-lru-page-replacement-algorithm-using-counters/
 */
auto LRU(const ArrayType &requests, const ArrayType::size_type cache_size) {
    std::unordered_map<ArrayType::value_type, ArrayType::size_type> requests_in_cache;

    unsigned cache_hit = 0;
    for (ArrayType::size_type i = 0; i < requests.size(); ++i) {
        const auto the_request = requests[i];
        const auto iter = requests_in_cache.find(the_request);
        if (iter != requests_in_cache.cend()) {
            ++cache_hit;
            iter->second = i;
        } else {
            if (requests_in_cache.size() == cache_size) {
                auto LRU_index = std::numeric_limits<ArrayType::size_type>::max();
                for (const auto [_, index] : requests_in_cache) {
                    if (index < LRU_index) {
                        LRU_index = index;
                    }
                }

                requests_in_cache.erase(requests[LRU_index]);
            }

            requests_in_cache.emplace(the_request, i);
        }
    }

    return requests.size() - cache_hit;
}

}


#ifdef WANT_TESTS
TEST(LRU_CacheTest, TestSanity) {
    constexpr auto CAPICITY = 2u;
    LRU_Cache lru_cache{CAPICITY};
    constexpr auto ToValue = [](const auto key) {
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
#endif


const ArrayType SAMPLE1 = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
const ArrayType SAMPLE2 = {7, 1, 1};
const ArrayType SAMPLE3 = {0, 0, 0, 2, 3, 0, 5, 7, 1, 2, 0, 8};
const ArrayType SAMPLE4 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 0, 0};


THE_BENCHMARK(LRU, SAMPLE1, 4);

SIMPLE_TEST(LRU, TestSAMPLE1, 6, SAMPLE1, 4);
SIMPLE_TEST(LRU, TestSAMPLE2, 2, SAMPLE2, 3);
SIMPLE_TEST(LRU, TestSAMPLE3, 9, SAMPLE3, 3);
SIMPLE_TEST(LRU, TestSAMPLE4, 15, SAMPLE4, 3);
