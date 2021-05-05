#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Smallest Difference pair of values between two unsorted Arrays
 *
 * @reference   https://www.geeksforgeeks.org/smallest-difference-pair-values-two-unsorted-arrays/
 *
 * Given two arrays of integers, compute the pair of values (one value in each array)
 * with the smallest (non-negative) difference. Return the difference.
 */
auto MinDiffPairOf2SortedArrays(const ArrayType &one, const ArrayType &another) {
    assert(std::is_sorted(one.cbegin(), one.cend()));
    assert(std::is_sorted(another.cbegin(), another.cend()));

    auto result = std::numeric_limits<ArrayType::value_type>::max();
    auto one_iter = one.cbegin();
    auto another_iter = another.cbegin();
    while (one_iter != one.cend() and another_iter != another.cend()) {
        const auto diff = std::abs(*one_iter - *another_iter);
        if (diff < result) {
            result = diff;
        }

        if (*one_iter < *another_iter) {
            ++one_iter;
        } else {
            ++another_iter;
        }
    }

    return result;
}

inline auto MinDiffPairOf2UnsortedArrays(ArrayType one, ArrayType another) {
    std::sort(one.begin(), one.end());
    std::sort(another.begin(), another.end());

    return MinDiffPairOf2SortedArrays(one, another);
}

}//namespace


const ArrayType SAMPLE1_L = {1, 3, 15, 11, 2};
const ArrayType SAMPLE1_R = {23, 127, 235, 19, 8};

const ArrayType SAMPLE2_L = {10, 5, 40};
const ArrayType SAMPLE2_R = {50, 90, 80};


THE_BENCHMARK(MinDiffPairOf2UnsortedArrays, SAMPLE1_L, SAMPLE1_R);

SIMPLE_TEST(MinDiffPairOf2UnsortedArrays, TestSAMPLE1, 3, SAMPLE1_L, SAMPLE1_R);
SIMPLE_TEST(MinDiffPairOf2UnsortedArrays, TestSAMPLE2, 10, SAMPLE2_L, SAMPLE2_R);
