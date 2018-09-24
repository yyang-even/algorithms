#include "common_header.h"

#include <queue>


using ArrayType = std::vector<int>;

/** Kth smallest element after every insertion
 *
 * @reference   https://www.geeksforgeeks.org/kth-smallest-element-after-every-insertion/
 *
 * Given an infinite stream of integers, find the k’th largest
 * element at any point of time. It may be assumed that 1 <= k <= n.
 */
auto KthSmallestElementAfterEveryInsertion(const ArrayType stream, const ArrayType::size_type k) {
    assert(k < stream.size());

    std::priority_queue<ArrayType::value_type, std::vector<ArrayType::value_type>, std::greater<ArrayType::value_type> >
    heap(stream.cbegin(), stream.cbegin() + k);
    ArrayType kth_smallest_array(k - 1, 0);

    for (auto iter = stream.cbegin() + k; iter != stream.cend(); ++iter) {
        kth_smallest_array.push_back(heap.top());
        if (*iter > heap.top()) {
            heap.pop();
            heap.push(*iter);
        }
    }
    kth_smallest_array.push_back(heap.top());

    return kth_smallest_array;
}


const ArrayType SAMPLE_ARRAY = {10, 20, 11, 70, 50, 40, 100, 5};
const ArrayType EXPECTED_ARRAY = {0, 0, 10, 11, 20, 40, 50,  50};

SIMPLE_BENCHMARK(KthSmallestElementAfterEveryInsertion, SAMPLE_ARRAY, 3);

SIMPLE_TEST(KthSmallestElementAfterEveryInsertion, TestSAMPLE, EXPECTED_ARRAY, SAMPLE_ARRAY, 3);
