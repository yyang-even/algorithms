#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Find k closest elements to a given value
 *
 * @reference   https://www.geeksforgeeks.org/find-k-closest-elements-given-value/
 *
 * Given a sorted array arr[] and a value X, find the k closest elements to X in arr[].
 * Note: Not including X itself.
 */
auto
FindKClosestElementsToX_Sorted_NoX(const ArrayType &elements,
                                   const ArrayType::value_type X,
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


/**
 * @reference   Find K Closest Elements
 *              https://leetcode.com/problems/find-k-closest-elements/
 *
 * Given a sorted integer array arr, two integers k and x, return the k closest integers
 * to x in the array. The result should also be sorted in ascending order. An integer a
 * is closer to x than an integer b if:
 *  |a - x| < |b - x|, or
 *  |a - x| == |b - x| and a < b
 */
auto
FindKClosestElementsToX_Sorted_SlidingWindow(const ArrayType &elements,
                                             const ArrayType::value_type X,
                                             const ArrayType::size_type K) {
    assert(elements.size() >= K);
    assert(std::is_sorted(elements.cbegin(), elements.cend()));

    if (elements.size() == K) {
        return elements;
    }

    int left = 0;
    int right = elements.size() - 1;
    int mid = 0;
    while (left <= right) {
        mid = (left + right) / 2;
        if (elements[mid] > X) {
            right = mid - 1;
        } else if (elements[mid] < X) {
            left = mid + 1;
        } else {
            break;
        }
    }

    left = std::max(0, mid - 1);
    right = left + 1;

    while (right - left - 1 < static_cast<int>(K)) {
        if (left == -1) {
            right += 1;
            continue;
        }

        if (right == static_cast<int>(elements.size()) or
            std::abs(elements[left] - X) <= std::abs(elements[right] - X)) {
            left -= 1;
        } else {
            right += 1;
        }
    }

    return ArrayType(elements.cbegin() + left + 1, elements.cbegin() + right);
}


auto
FindKClosestElementsToX_Sorted_BinarySearch(const ArrayType &elements,
                                            const ArrayType::value_type X,
                                            const ArrayType::size_type K) {
    assert(elements.size() >= K);
    assert(std::is_sorted(elements.cbegin(), elements.cend()));

    int left = 0;
    int right = elements.size() - K;

    while (left < right) {
        const auto mid = (left + right) / 2;
        if (X - elements[mid] > elements[mid + K] - X) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return ArrayType(elements.cbegin() + left, elements.cbegin() + left + K);
}


/**
 * @reference   Find closest number in array
 *              https://www.geeksforgeeks.org/find-closest-number-array/
 *
 * Given an array of sorted integers. We need to find the closest value to the given
 * number. Array may contain duplicate values and negative numbers.
 */


/**
 * @reference   Find the Distance Value Between Two Arrays
 *              https://leetcode.com/problems/find-the-distance-value-between-two-arrays/
 *
 * Given two integer arrays arr1 and arr2, and the integer d, return the distance value
 * between the two arrays. The distance value is defined as the number of elements arr1[i]
 * such that there is not any element arr2[j] where |arr1[i]-arr2[j]| <= d.
 */
auto FindTheDistanceValue(const ArrayType &one, ArrayType another, const int d) {
    std::sort(another.begin(), another.end());

    int result = 0;
    for (const auto n : one) {
        if (std::upper_bound(another.cbegin(), another.cend(), n + d) ==
            std::lower_bound(another.cbegin(), another.cend(), n - d)) {
            ++result;
        }
    }

    return result;
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


/**
 * @reference   Find Closest Number to Zero
 *              https://leetcode.com/problems/find-closest-number-to-zero/
 *
 * Given an integer array nums of size n, return the number with the value closest to 0
 * in nums. If there are multiple answers, return the number with the largest value.
 */

}//namespace


const ArrayType SAMPLE1 = {12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56};
const ArrayType EXPECTED1 = {39, 30, 42, 45};
const auto EXPECTED_FRONT =
    ArrayType(SAMPLE1.cbegin(), std::next(SAMPLE1.cbegin(), EXPECTED1.size()));
const auto EXPECTED_BACK =
    ArrayType(std::prev(SAMPLE1.cend(), EXPECTED1.size()), SAMPLE1.cend());
const ArrayType EXPECTED2 = {42, 45, 39, 48};
const ArrayType SAMPLE5 = {1, 2, 4, 5, 6, 6, 8, 9};
const ArrayType EXPECTED5 = {9};
const ArrayType SAMPLE6 = {2, 5, 6, 7, 8, 8, 9};
const ArrayType EXPECTED6 = {5};
const ArrayType EXPECTED7 = {2};


THE_BENCHMARK(FindKClosestElementsToX_Sorted_NoX, SAMPLE1, 35, EXPECTED1.size());

SIMPLE_TEST(FindKClosestElementsToX_Sorted_NoX, TestSAMPLE1, EXPECTED1,
            SAMPLE1, 35, EXPECTED1.size());
SIMPLE_TEST(FindKClosestElementsToX_Sorted_NoX, TestSAMPLE_FRONT, EXPECTED_FRONT,
            SAMPLE1, SAMPLE1.front() - 1, EXPECTED1.size());
SIMPLE_TEST(FindKClosestElementsToX_Sorted_NoX, TestSAMPLE_BACK, EXPECTED_BACK,
            SAMPLE1, SAMPLE1.back() + 1, EXPECTED1.size());
SIMPLE_TEST(FindKClosestElementsToX_Sorted_NoX, TestSAMPLE2, EXPECTED2,
            SAMPLE1, 43, EXPECTED2.size());
SIMPLE_TEST(FindKClosestElementsToX_Sorted_NoX, TestSAMPLE5, EXPECTED5, SAMPLE5, 11, 1);
SIMPLE_TEST(FindKClosestElementsToX_Sorted_NoX, TestSAMPLE6, EXPECTED6, SAMPLE6, 4, 1);
SIMPLE_TEST(FindKClosestElementsToX_Sorted_NoX, TestSAMPLE7, EXPECTED7, SAMPLE6, 3, 1);


const ArrayType SAMPLE8 = {1, 2, 3, 4, 5};
const ArrayType EXPECTED8 = {1, 2, 3, 4};


THE_BENCHMARK(FindKClosestElementsToX_Sorted_SlidingWindow,
              SAMPLE1, 35, EXPECTED1.size());

SIMPLE_TEST(FindKClosestElementsToX_Sorted_SlidingWindow, TestSAMPLE_FRONT,
            EXPECTED_FRONT, SAMPLE1, SAMPLE1.front() - 1, EXPECTED1.size());
SIMPLE_TEST(FindKClosestElementsToX_Sorted_SlidingWindow, TestSAMPLE_BACK,
            EXPECTED_BACK, SAMPLE1, SAMPLE1.back() + 1, EXPECTED1.size());
SIMPLE_TEST(FindKClosestElementsToX_Sorted_SlidingWindow, TestSAMPLE5, EXPECTED5,
            SAMPLE5, 11, 1);
SIMPLE_TEST(FindKClosestElementsToX_Sorted_SlidingWindow, TestSAMPLE6, EXPECTED6,
            SAMPLE6, 4, 1);
SIMPLE_TEST(FindKClosestElementsToX_Sorted_SlidingWindow, TestSAMPLE7, EXPECTED6,
            SAMPLE6, 5, 1);
SIMPLE_TEST(FindKClosestElementsToX_Sorted_SlidingWindow, TestSAMPLE8, EXPECTED7,
            SAMPLE6, 3, 1);
SIMPLE_TEST(FindKClosestElementsToX_Sorted_SlidingWindow, TestSAMPLE9, EXPECTED8,
            SAMPLE8, 3, 4);


THE_BENCHMARK(FindKClosestElementsToX_Sorted_BinarySearch,
              SAMPLE1, 35, EXPECTED1.size());

SIMPLE_TEST(FindKClosestElementsToX_Sorted_BinarySearch, TestSAMPLE_FRONT,
            EXPECTED_FRONT, SAMPLE1, SAMPLE1.front() - 1, EXPECTED1.size());
SIMPLE_TEST(FindKClosestElementsToX_Sorted_BinarySearch, TestSAMPLE_BACK,
            EXPECTED_BACK, SAMPLE1, SAMPLE1.back() + 1, EXPECTED1.size());
SIMPLE_TEST(FindKClosestElementsToX_Sorted_BinarySearch, TestSAMPLE5, EXPECTED5,
            SAMPLE5, 11, 1);
SIMPLE_TEST(FindKClosestElementsToX_Sorted_BinarySearch, TestSAMPLE6, EXPECTED6,
            SAMPLE6, 4, 1);
SIMPLE_TEST(FindKClosestElementsToX_Sorted_BinarySearch, TestSAMPLE7, EXPECTED6,
            SAMPLE6, 5, 1);
SIMPLE_TEST(FindKClosestElementsToX_Sorted_BinarySearch, TestSAMPLE8, EXPECTED7,
            SAMPLE6, 3, 1);
SIMPLE_TEST(FindKClosestElementsToX_Sorted_BinarySearch, TestSAMPLE9, EXPECTED8,
            SAMPLE8, 3, 4);


const ArrayType SAMPLE3 = {10, 2, 14, 4, 7, 6};
const ArrayType EXPECTED3 = {7, 6, 4};
const ArrayType SAMPLE4 = {-10, -50, 20, 17, 80};
const ArrayType EXPECTED4 = {17, 20};


THE_BENCHMARK(FindKClosestElementsToX_Unsorted, SAMPLE3, 5, EXPECTED3.size());

SIMPLE_TEST(FindKClosestElementsToX_Unsorted, TestSAMPLE3, EXPECTED3, SAMPLE3, 5,
            EXPECTED3.size());
SIMPLE_TEST(FindKClosestElementsToX_Unsorted, TestSAMPLE4, EXPECTED4, SAMPLE4, 20,
            EXPECTED4.size());


const ArrayType SAMPLE1A = {4, 5, 8};
const ArrayType SAMPLE1B = {10, 9, 1, 8};

const ArrayType SAMPLE2A = {1, 4, 2, 3};
const ArrayType SAMPLE2B = {-4, -3, 6, 10, 20, 30};

const ArrayType SAMPLE3A = {2, 1, 100, 3};
const ArrayType SAMPLE3B = {-5, -2, 10, -3, 7};


THE_BENCHMARK(FindTheDistanceValue, SAMPLE1A, SAMPLE1B, 2);

SIMPLE_TEST(FindTheDistanceValue, TestSAMPLE1, 2, SAMPLE1A, SAMPLE1B, 2);
SIMPLE_TEST(FindTheDistanceValue, TestSAMPLE2, 2, SAMPLE2A, SAMPLE2B, 3);
SIMPLE_TEST(FindTheDistanceValue, TestSAMPLE3, 1, SAMPLE3A, SAMPLE3B, 6);
