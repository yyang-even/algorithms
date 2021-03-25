#include "common_header.h"

namespace {

using ArrayType = std::vector<int>;

/** Given a sorted array and a number x, find the pair in array whose sum is closest to x
 *
 * @reference   https://www.geeksforgeeks.org/given-sorted-array-number-x-find-pair-array-whose-sum-closest-x/
 */
auto ClosestSumPair_TwoPointer(const ArrayType &elements,
                               const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));

    auto diff = std::numeric_limits<ArrayType::value_type>::max();
    std::pair<ArrayType::value_type, ArrayType::value_type> output;
    if (not elements.empty()) {
        auto left = elements.cbegin();
        auto right = std::prev(elements.cend());

        while (left != right) {
            const auto sum = *left + *right;
            const auto new_diff = std::abs(sum - x);
            if (new_diff < diff) {
                diff = new_diff;
                output = std::pair(*left, *right);
            } else if (sum < x) {
                ++left;
            } else {
                --right;
            }
        }
    }

    return output;
}

}//namespace


const ArrayType SAMPLE1 = {10, 22, 28, 29, 30, 40};
const ArrayType SAMPLE2 = {1, 3, 4, 7, 10};


THE_BENCHMARK(ClosestSumPair_TwoPointer, SAMPLE1, 54);

SIMPLE_TEST(ClosestSumPair_TwoPointer, TestSample1, std::pair(22, 30), SAMPLE1, 54);
SIMPLE_TEST(ClosestSumPair_TwoPointer, TestSample2, std::pair(4, 10), SAMPLE2, 15);
