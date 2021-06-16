#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Find k closest elements to a given value
 *
 * @reference   https://www.geeksforgeeks.org/find-k-closest-elements-given-value/
 *
 * Given a sorted array arr[] and a value X, find the k closest elements to X in arr[].
 */
auto FindKClosestElementsToX(const ArrayType &elements, const ArrayType::value_type X,
                             ArrayType::size_type K) {
    assert(elements.size() >= K);
    assert(std::is_sorted(elements.cbegin(), elements.cend()));

    const auto upper = std::upper_bound(elements.cbegin(), elements.cend(), X);
    ArrayType outputs(K, 0);
    auto left = std::prev(upper);
    auto right = upper;
    auto output_iter = outputs.begin();

    if (upper != elements.cbegin() and * left == X) {
        --left;
    }

    while (left >= elements.cbegin() and right != elements.cend() and K) {
        if (X - *left < *right - X) {
            *output_iter++ = *left--;
        } else {
            *output_iter++ = *right++;
        }
        --K;
    }

    if (K and right != elements.cend()) {
        std::copy(right, std::next(right, K), output_iter);
    } else {
        std::copy(std::prev(left, K - 1), std::next(left), output_iter);
    }

    return outputs;
}


/** Find k closest numbers in an unsorted array
 *
 * @reference   https://www.geeksforgeeks.org/find-k-closest-numbers-in-an-unsorted-array/
 */
auto FindKClosestElementsToX_Unsorted(const ArrayType &elements,
                                      const ArrayType::value_type X,
                                      const ArrayType::size_type K) {
    assert(elements.size() >= K);

    using DiffIndexPair = std::pair<int, ArrayType::size_type>;
    std::priority_queue<DiffIndexPair> max_diff_heap;
    for (ArrayType::size_type i = 0; i < K; ++i) {
        max_diff_heap.emplace(std::abs(X - elements[i]), i);
    }

    for (auto i = K; i < elements.size(); ++i) {
        const auto diff = std::abs(X - elements[i]);

        if (diff < max_diff_heap.top().first) {
            max_diff_heap.pop();
            max_diff_heap.emplace(diff, i);
        }
    }

    ArrayType outputs;
    while (not max_diff_heap.empty()) {
        outputs.emplace_back(elements[max_diff_heap.top().second]);
        max_diff_heap.pop();
    }

    return outputs;
}

}//namespace


const ArrayType SAMPLE1 = {12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56};
const ArrayType EXPECTED1 = {39, 30, 42, 45};
const auto EXPECTED_FRONT =
    ArrayType(SAMPLE1.cbegin(), std::next(SAMPLE1.cbegin(), EXPECTED1.size()));
const auto EXPECTED_BACK =
    ArrayType(std::prev(SAMPLE1.cend(), EXPECTED1.size()), SAMPLE1.cend());
const ArrayType EXPECTED2 = {42, 45, 39, 48};


THE_BENCHMARK(FindKClosestElementsToX, SAMPLE1, 35, EXPECTED1.size());

SIMPLE_TEST(FindKClosestElementsToX, TestSAMPLE1, EXPECTED1, SAMPLE1, 35,
            EXPECTED1.size());
SIMPLE_TEST(FindKClosestElementsToX, TestSAMPLE_FRONT, EXPECTED_FRONT, SAMPLE1,
            SAMPLE1.front() - 1, EXPECTED1.size());
SIMPLE_TEST(FindKClosestElementsToX, TestSAMPLE_BACK, EXPECTED_BACK, SAMPLE1,
            SAMPLE1.back() + 1, EXPECTED1.size());
SIMPLE_TEST(FindKClosestElementsToX, TestSAMPLE2, EXPECTED2, SAMPLE1, 43,
            EXPECTED2.size());


const ArrayType SAMPLE3 = {10, 2, 14, 4, 7, 6};
const ArrayType EXPECTED3 = {7, 6, 4};
const ArrayType SAMPLE4 = {-10, -50, 20, 17, 80};
const ArrayType EXPECTED4 = {17, 20};


THE_BENCHMARK(FindKClosestElementsToX_Unsorted, SAMPLE3, 5, EXPECTED3.size());

SIMPLE_TEST(FindKClosestElementsToX_Unsorted, TestSAMPLE3, EXPECTED3, SAMPLE3, 5,
            EXPECTED3.size());
SIMPLE_TEST(FindKClosestElementsToX_Unsorted, TestSAMPLE4, EXPECTED4, SAMPLE4, 20,
            EXPECTED4.size());
