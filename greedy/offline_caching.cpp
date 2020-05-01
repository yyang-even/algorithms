#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Off-line Caching
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Problems 16-5.
 * @reference   Page Replacement Algorithms in Operating Systems
 *              https://www.geeksforgeeks.org/page-replacement-algorithms-in-operating-systems/
 * @reference   Optimal Page Replacement Algorithm
 *              https://www.geeksforgeeks.org/optimal-page-replacement-algorithm/
 */
auto FurthestInFuture(const ArrayType &requests, const ArrayType::size_type cache_size) {
    assert(requests.size() > cache_size);

    auto requests_iter = requests.cbegin() + cache_size;
    std::unordered_set<ArrayType::value_type> cache(requests.cbegin(), requests_iter);

    unsigned cache_hit = 0;
    for (; requests_iter != requests.cend(); ++requests_iter) {
        if (cache.find(*requests_iter) != cache.cend()) {
            ++cache_hit;
        } else {
            const auto cbegin = std::next(requests_iter);
            auto request_to_be_replaced = *cache.cbegin();
            auto furthest_in_future = cbegin;

            for (const auto request_in_cache : cache) {
                const auto iter = std::find(cbegin, requests.cend(), request_in_cache);
                if (iter == requests.cend()) {
                    request_to_be_replaced = request_in_cache;
                    break;
                } else {
                    if (iter > furthest_in_future) {
                        furthest_in_future = iter;
                        request_to_be_replaced = request_in_cache;
                    }
                }
            }

            cache.erase(request_to_be_replaced);
            cache.insert(*requests_iter);
        }
    }

    return requests.size() - cache_hit;
}

}//namespace


const ArrayType SAMPLE1 = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
const ArrayType SAMPLE2 = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};


SIMPLE_BENCHMARK(FurthestInFuture, SAMPLE1, 3);

SIMPLE_TEST(FurthestInFuture, TestSAMPLE1, 9, SAMPLE1, 3);
SIMPLE_TEST(FurthestInFuture, TestSAMPLE2, 6, SAMPLE2, 4);
