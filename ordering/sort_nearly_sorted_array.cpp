#include "common_header.h"

#include <queue>

#include "3rdParty/prettyprint.hpp"


using ArrayType = std::vector<int>;

/** Sort a nearly sorted (or K sorted) array
 *
 * @reference   https://www.geeksforgeeks.org/nearly-sorted-algorithm/
 *
 * Given an array of n elements, where each element is at most k away
 * from its target position, devise an algorithm that sorts in O(n log k) time.
 * For example, let us consider k is 2, an element at index 7 in the
 * sorted array, can be at indexes 5, 6, 7, 8, 9 in the given array.
 *
 * Method 1: use Insertion Sort.
 * @complexity  O(nk)
 *
 * Method 2: use Heap data structure.
 * @complexity  O(nlgk)
 */
auto SortNearlySortedArray(ArrayType array, const ArrayType::size_type k) {
    assert(k < array.size());

    auto read_iter = array.cbegin() + k + 1;
    std::priority_queue<ArrayType::value_type, std::vector<ArrayType::value_type>, std::greater<ArrayType::value_type> >
    heap{array.cbegin(), read_iter};

    for (auto write_iter = array.begin(); write_iter != array.cend(); ++write_iter) {
        *write_iter = heap.top();
        heap.pop();
        if (read_iter != array.cend()) {
            heap.push(*read_iter++);
        }
    }

    return array;
}


const ArrayType SampleArray = {2, 6, 3, 12, 56, 8};
const ArrayType ExpectedSortedArray = {2, 3, 6, 8, 12, 56};

SIMPLE_BENCHMARK(SortNearlySortedArray, SampleArray, 3);

SIMPLE_TEST(SortNearlySortedArray, TestSample, ExpectedSortedArray, SampleArray, 3);
