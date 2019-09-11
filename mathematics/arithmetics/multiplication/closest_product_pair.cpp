#include "common_header.h"

namespace {

using ArrayType = std::vector<int>;

/** Closest product pair in an array
 *
 * @reference   https://www.geeksforgeeks.org/closest-product-pair-array/
 */
auto ClosestProductPair_Sort_Bound(ArrayType elements, const ArrayType::value_type x) {
    std::sort(elements.begin(), elements.end());

    auto diff = std::numeric_limits<ArrayType::value_type>::max();
    std::pair<ArrayType::value_type, ArrayType::value_type> output;
    for (auto iter = elements.cbegin(); iter != elements.cend(); ++iter) {
        const auto lower_upper_pair = std::equal_range(std::next(iter), elements.cend(), *iter);
        if (lower_upper_pair.first != elements.cend()) {
            const auto lower_diff = std::abs((*iter * *lower_upper_pair.first) - x);
            if (lower_diff < diff) {
                diff = lower_diff;
                output = std::make_pair(*iter, *lower_upper_pair.first);
            }
        }

        if (lower_upper_pair.second != elements.cend()) {
            const auto upper_diff = std::abs((*iter * *lower_upper_pair.second) - x);
            if (upper_diff < diff) {
                diff = upper_diff;
                output = std::make_pair(*iter, *lower_upper_pair.second);
            }
        }
    }

    return output;
}


auto ClosestProductPair_TwoPointer(const ArrayType &elements, const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));

    auto diff = std::numeric_limits<ArrayType::value_type>::max();
    std::pair<ArrayType::value_type, ArrayType::value_type> output;
    if (not elements.empty()) {
        auto left = elements.cbegin();
        auto right = std::prev(elements.cend());

        while (left != right) {
            const auto product = *left * *right;
            const auto new_diff = std::abs(product - x);
            if (new_diff < diff) {
                diff = new_diff;
                output = std::make_pair(*left, *right);
            } else if (product < x) {
                ++left;
            } else {
                --right;
            }
        }
    }

    return output;
}

}//namespace


const ArrayType SAMPLE1 = {2, 3, 5, 9};


SIMPLE_BENCHMARK(ClosestProductPair_Sort_Bound, SAMPLE1, 47);

SIMPLE_TEST(ClosestProductPair_Sort_Bound, TestSample1, std::make_pair(5, 9), SAMPLE1, 47);
SIMPLE_TEST(ClosestProductPair_Sort_Bound, TestSample2, std::make_pair(2, 3), SAMPLE1, 8);


SIMPLE_BENCHMARK(ClosestProductPair_TwoPointer, SAMPLE1, 47);

SIMPLE_TEST(ClosestProductPair_TwoPointer, TestSample1, std::make_pair(5, 9), SAMPLE1, 47);
SIMPLE_TEST(ClosestProductPair_TwoPointer, TestSample2, std::make_pair(2, 5), SAMPLE1, 8);
