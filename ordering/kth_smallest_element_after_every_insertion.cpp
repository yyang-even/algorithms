#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Kth smallest element after every insertion
 *
 * @reference   https://www.geeksforgeeks.org/kth-smallest-element-after-every-insertion/
 * @reference   K’th largest element in a stream
 *              https://www.geeksforgeeks.org/kth-largest-element-in-a-stream/
 *
 * Given an infinite stream of integers, find the k'th largest element at any point of time. It may be
 * assumed that 1 <= k <= n.
 */
auto KthLargestElementAfterEveryInsertion(const ArrayType &stream, const ArrayType::size_type k) {
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
 * Design a class to find the kth largest element in a stream. Note that it is the kth largest element
 * in the sorted order, not the kth distinct element.
 * Implement KthLargest class:
 *  KthLargest(int k, int[] nums) Initializes the object with the integer k and the stream of integers
 *      nums.
 *  int add(int val) Appends the integer val to the stream and returns the element representing the kth
 *      largest element in the stream.
 * It is guaranteed that there will be at least k elements in the array when you search for the kth
 * element.
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


/**
 * @reference   Maximum Subsequence Score
 *              https://leetcode.com/problems/maximum-subsequence-score/
 *
 * You are given two 0-indexed integer arrays nums1 and nums2 of equal length n and a positive integer
 * k. You must choose a subsequence of indices from nums1 of length k.
 * For chosen indices i0, i1, ..., ik - 1, your score is defined as:
 *  The sum of the selected elements from nums1 multiplied with the minimum of the selected elements
 *  from nums2.
 *  It can defined simply as: (nums1[i0] + nums1[i1] +...+ nums1[ik - 1]) * min(nums2[i0] , nums2[i1],
 *  ... ,nums2[ik - 1]).
 * Return the maximum possible score.
 * A subsequence of indices of an array is a set that can be derived from the set {0, 1, ..., n-1} by
 * deleting some or no elements.
 */
auto MaxScore(const ArrayType &nums1, const ArrayType &nums2, const int k) {
    std::vector<int> indices(nums1.size(), 0);
    std::iota(indices.begin(), indices.end(), 0);
    std::sort(indices.begin(), indices.end(), [&nums2](const auto left, const auto right) {
        return nums2[left] > nums2[right];
    });

    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
    long long sum = 0;
    for (int i = 0; i < k; ++i) {
        const auto index = indices[i];
        sum += nums1[index];
        min_heap.push(nums1[index]);
    }

    long long result = sum * nums2[indices[k - 1]];
    for (std::size_t i = k; i < indices.size(); ++i) {
        const auto index = indices[i];
        if (nums1[index] > min_heap.top()) {
            sum += nums1[index] - min_heap.top();
            min_heap.pop();
            min_heap.push(nums1[index]);
        }

        result = std::max(result, sum * nums2[index]);
    }

    return result;
}

} //namespace


const ArrayType SAMPLE_ARRAY = {10, 20, 11, 70, 50, 40, 100, 5};
const ArrayType EXPECTED_ARRAY = {0, 0, 10, 11, 20, 40, 50, 50};


THE_BENCHMARK(KthLargestElementAfterEveryInsertion, SAMPLE_ARRAY, 3);

SIMPLE_TEST(KthLargestElementAfterEveryInsertion, TestSAMPLE, EXPECTED_ARRAY, SAMPLE_ARRAY, 3);


SIMPLE_TEST(testKthLargest, TestSAMPLE, EXPECTED_ARRAY, SAMPLE_ARRAY, 3);


const ArrayType SAMPLE1M1 = {1, 3, 3, 2};
const ArrayType SAMPLE1M2 = {2, 1, 3, 4};

const ArrayType SAMPLE2M1 = {4, 2, 3, 1, 1};
const ArrayType SAMPLE2M2 = {7, 5, 10, 9, 6};


THE_BENCHMARK(MaxScore, SAMPLE1M1, SAMPLE1M2, 3);

SIMPLE_TEST(MaxScore, TestSAMPLE1, 12, SAMPLE1M1, SAMPLE1M2, 3);
SIMPLE_TEST(MaxScore, TestSAMPLE2, 30, SAMPLE2M1, SAMPLE2M2, 1);
