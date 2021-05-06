#pragma once


/** Check whether a given array is a k sorted array or not
 *
 * @reference   https://www.geeksforgeeks.org/check-whether-given-array-k-sorted-array-not/
 *
 * Given an array of n distinct elements. Check whether the given array is a k sorted
 * array or not. A k sorted array is an array where each element is at most k distance
 * away from its target position in the sorted array.
 */
static inline auto
IsKSorted(const ArrayType &values, const ArrayType::difference_type K) {
    auto sorted = values;
    std::sort(sorted.begin(), sorted.end());

    for (ArrayType::size_type i = 0; i < values.size(); ++i) {
        const auto iter = std::lower_bound(sorted.cbegin(), sorted.cend(), values[i]);
        if (K < std::abs(
                std::distance(sorted.cbegin(), iter) - static_cast<ArrayType::difference_type>(i))) {
            return false;
        }
    }

    return true;
}
