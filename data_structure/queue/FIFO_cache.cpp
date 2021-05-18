#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Program for Page Replacement Algorithms | Set 2 (FIFO)
 *
 * @reference   https://www.geeksforgeeks.org/program-page-replacement-algorithms-set-2-fifo/
 * @reference   Belady’s Anomaly in Page Replacement Algorithms
 *              https://www.geeksforgeeks.org/beladys-anomaly-in-page-replacement-algorithms/
 * @reference   Program to show Belady’s Anomaly
 *              https://www.geeksforgeeks.org/program-to-show-beladys-anomaly/
 */
auto FIFOCache(const ArrayType &requests, const ArrayType::size_type cache_size) {
    std::unordered_set<ArrayType::value_type> pages_in_cache;
    std::queue<ArrayType::value_type> pages_queue;

    unsigned cache_hit = 0;
    for (const auto one_request : requests) {
        if (pages_in_cache.find(one_request) != pages_in_cache.cend()) {
            ++cache_hit;
        } else {
            if (pages_in_cache.size() == cache_size) {
                pages_in_cache.erase(pages_queue.front());
                pages_queue.pop();
            }

            pages_in_cache.insert(one_request);
            pages_queue.push(one_request);
        }
    }

    return requests.size() - cache_hit;
}

}//namespace


const ArrayType SAMPLE1 = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
const ArrayType SAMPLE2 = {7, 1, 1};


THE_BENCHMARK(FIFOCache, SAMPLE1, 4);

SIMPLE_TEST(FIFOCache, TestSAMPLE1, 7, SAMPLE1, 4);
SIMPLE_TEST(FIFOCache, TestSAMPLE2, 2, SAMPLE2, 3);
