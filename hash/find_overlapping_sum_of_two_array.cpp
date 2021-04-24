#include "common_header.h"

#include "hash.h"


namespace {

using ArrayType = std::vector<int>;

/** Find the overlapping sum of two arrays
 *
 * @reference   https://www.geeksforgeeks.org/find-the-overlapping-sum-of-two-arrays/
 *
 * Given two arrays A[] and B[] having n unique elements each. The task is to find the
 * overlapping sum of the two arrays. That is the sum of elements which is common in both
 * of the arrays.
 *
 * @complexity  O(n)
 */
auto OverlappingSumOfArrays(const ArrayType &a1, const ArrayType &a2) {
    const ArrayType *smaller = &a1;
    const ArrayType *larger = &a2;
    if (smaller->size() > larger->size()) {
        std::swap(smaller, larger);
    }

    const auto counters = ToUnorderedSet(*larger);
    ArrayType::value_type sum = 0;

    for (const auto elem : *smaller) {
        if (counters.find(elem) != counters.cend()) {
            sum += elem * 2;
        }
    }

    return sum;
}

}//namespace


const ArrayType SAMPLE1 = {1, 5, 3, 8};
const ArrayType SAMPLE2 = {5, 4, 6, 7};


THE_BENCHMARK(OverlappingSumOfArrays, SAMPLE1, SAMPLE2);

SIMPLE_TEST(OverlappingSumOfArrays, TestSAMPLE1, 10, SAMPLE1, SAMPLE2);
