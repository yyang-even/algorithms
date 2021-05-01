#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Kth smallest element after every insertion
 *
 * @reference   https://www.geeksforgeeks.org/kth-smallest-element-after-every-insertion/
 * @reference   K’th largest element in a stream
 *              https://www.geeksforgeeks.org/kth-largest-element-in-a-stream/
 *
 * Given an infinite stream of integers, find the k'th largest element at any point of
 * time. It may be assumed that 1 <= k <= n.
 */
auto KthLargestElementAfterEveryInsertion(const ArrayType &stream,
                                          const ArrayType::size_type k) {
    assert(0 < k and k < stream.size());

    auto iter = stream.cbegin() + k;
    std::priority_queue<ArrayType::value_type, ArrayType, std::greater<ArrayType::value_type>>
            heap(stream.cbegin(), iter);
    ArrayType results(k - 1, 0);

    for (; iter != stream.cend(); ++iter) {
        results.push_back(heap.top());
        if (*iter > heap.top()) {
            heap.pop();
            heap.push(*iter);
        }
    }
    results.push_back(heap.top());

    return results;
}

}//namespace


const ArrayType SAMPLE_ARRAY = {10, 20, 11, 70, 50, 40, 100, 5};
const ArrayType EXPECTED_ARRAY = {0, 0, 10, 11, 20, 40, 50,  50};


THE_BENCHMARK(KthLargestElementAfterEveryInsertion, SAMPLE_ARRAY, 3);

SIMPLE_TEST(KthLargestElementAfterEveryInsertion, TestSAMPLE, EXPECTED_ARRAY,
            SAMPLE_ARRAY, 3);
