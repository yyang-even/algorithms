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


/**
 * @reference   Kth Largest Element in a Stream
 *              https://leetcode.com/problems/kth-largest-element-in-a-stream/
 *
 * Design a class to find the kth largest element in a stream. Note that it is the kth
 * largest element in the sorted order, not the kth distinct element.
 * Implement KthLargest class:
 *  KthLargest(int k, int[] nums) Initializes the object with the integer k and the
 *      stream of integers nums.
 *  int add(int val) Appends the integer val to the stream and returns the element
 *      representing the kth largest element in the stream.
 * It is guaranteed that there will be at least k elements in the array when you search
 * for the kth element.
 */
class KthLargest {
    std::priority_queue<int, ArrayType, std::greater<int>> heap;
    std::size_t K;

public:
    auto add(const int value) {
        if (heap.size() < K) {
            heap.push(value);
        } else if (value > heap.top()) {
            heap.pop();
            heap.push(value);
        }

        return heap.top();
    }

    KthLargest(const std::size_t k, const ArrayType &nums) : K(k) {
        for (const auto n : nums) {
            add(n);
        }
    }
};

inline auto testKthLargest(const ArrayType &nums, const std::size_t k) {
    assert(0 < k and k < nums.size());

    auto iter = nums.cbegin() + k - 1;
    const ArrayType head(nums.cbegin(), iter);

    KthLargest kth(k, head);
    ArrayType results(k - 1, 0);
    for (; iter != nums.cend(); ++iter) {
        results.push_back(kth.add(*iter));
    }

    return results;
}

}//namespace


const ArrayType SAMPLE_ARRAY = {10, 20, 11, 70, 50, 40, 100, 5};
const ArrayType EXPECTED_ARRAY = {0, 0, 10, 11, 20, 40, 50,  50};


THE_BENCHMARK(KthLargestElementAfterEveryInsertion, SAMPLE_ARRAY, 3);

SIMPLE_TEST(KthLargestElementAfterEveryInsertion, TestSAMPLE, EXPECTED_ARRAY,
            SAMPLE_ARRAY, 3);


SIMPLE_TEST(testKthLargest, TestSAMPLE, EXPECTED_ARRAY, SAMPLE_ARRAY, 3);
