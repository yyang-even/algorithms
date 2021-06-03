#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Find maximum (or minimum) sum of a subarray of size k
 *
 * @reference   https://www.geeksforgeeks.org/find-maximum-minimum-sum-subarray-size-k/
 * @reference   Window Sliding Technique
 *              https://www.geeksforgeeks.org/window-sliding-technique/
 */
auto MaxSumOfSubarrayOfSizeK(const ArrayType &elements, const ArrayType::size_type K) {
    assert(elements.size() >= K);

    auto max_sum = std::accumulate(elements.cbegin(), elements.cbegin() + K, 0);
    auto current_sum = max_sum;
    for (auto i = K; i < elements.size(); ++i) {
        current_sum += elements[i] - elements[i - K];
        if (max_sum < current_sum) {
            max_sum = current_sum;
        }
    }

    return max_sum;
}


/**
 * @reference   Subarray of size k with given sum
 *              https://www.geeksforgeeks.org/subarray-of-size-k-with-given-sum/
 */


/**
 * @reference   Largest product of a subarray of size k
 *              https://www.geeksforgeeks.org/largest-product-subarray-size-k/
 */


/**
 * @reference   Find the subarray of size K with minimum XOR
 *              https://www.geeksforgeeks.org/find-the-subarray-of-size-k-with-minimum-xor/
 */

}//namespace


const ArrayType SAMPLE1 = {100, 200, 300, 400};
const ArrayType SAMPLE2 = {1, 4, 2, 10, 23, 3, 1, 0, 20};


THE_BENCHMARK(MaxSumOfSubarrayOfSizeK, SAMPLE1, 2);

SIMPLE_TEST(MaxSumOfSubarrayOfSizeK, TestSAMPLE1, 700, SAMPLE1, 2);
SIMPLE_TEST(MaxSumOfSubarrayOfSizeK, TestSAMPLE2, 39, SAMPLE2, 4);
