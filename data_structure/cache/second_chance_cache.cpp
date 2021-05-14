#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Second Chance (or Clock) Page Replacement Policy
 *
 * @reference   https://www.geeksforgeeks.org/second-chance-or-clock-page-replacement-policy/
 * @reference   LRU Approximation (Second Chance Algorithm)
 *              https://www.geeksforgeeks.org/lru-approximation-second-chance-algorithm/
 */
auto SecondChanceCache(const ArrayType &requests,
                       const ArrayType::size_type cache_size) {
    ArrayType cache;
    std::vector<bool> second_chances;
    ArrayType::size_type front_index = 0;

    unsigned cache_hit = 0;
    for (const auto one_request : requests) {
        const auto iter = std::find(cache.cbegin(), cache.cend(), one_request);
        if (iter != cache.cend()) {
            ++cache_hit;
            second_chances[std::distance(cache.cbegin(), iter)] = true;
        } else {
            if (cache.size() < cache_size) {
                cache.push_back(one_request);
                second_chances.push_back(false);
            } else {
                for (bool to_be_continued = true; to_be_continued;) {
                    if (not second_chances[front_index]) {
                        cache[front_index] = one_request;
                        to_be_continued = false;
                    } else {
                        second_chances[front_index] = false;
                    }

                    front_index = (front_index + 1) % cache_size;
                }
            }
        }
    }

    return requests.size() - cache_hit;
}

}//namespace


const ArrayType SAMPLE1 = {0, 4, 1, 4, 2, 4, 3, 4, 2, 4, 0, 4, 1, 4, 2, 4, 3, 4};
const ArrayType SAMPLE2 = {2, 5, 10, 1, 2, 2, 6, 9, 1, 2, 10, 2, 6, 1, 2, 1, 6, 9, 5, 1};
const ArrayType SAMPLE4 = {2, 3, 2, 1, 5, 2, 4, 5, 3, 2, 5, 2};


THE_BENCHMARK(SecondChanceCache, SAMPLE1, 3);

SIMPLE_TEST(SecondChanceCache, TestSAMPLE1, 9, SAMPLE1, 3);
SIMPLE_TEST(SecondChanceCache, TestSAMPLE2, 13, SAMPLE2, 3);
SIMPLE_TEST(SecondChanceCache, TestSAMPLE3, 11, SAMPLE2, 4);
SIMPLE_TEST(SecondChanceCache, TestSAMPLE4, 6, SAMPLE4, 4);
