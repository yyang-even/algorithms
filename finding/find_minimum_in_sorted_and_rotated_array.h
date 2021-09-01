#pragma once


/** Find the minimum element in a sorted and rotated array
 *
 * @reference   https://www.geeksforgeeks.org/find-minimum-element-in-a-sorted-and-rotated-array/
 * @reference   Section VI. Five Algorithm Approaches.
 *              Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *
 * Assumes that all elements are distinct.
 *
 * @reference   Find the Rotation Count in Rotated Sorted array
 *              https://www.geeksforgeeks.org/find-rotation-count-rotated-sorted-array/
 */
static inline auto
FindMinInSortedAndRotated_Neighbor(const ArrayType::const_iterator cbegin,
                                   const ArrayType::size_type length) {
    if (length) {
        const auto half = length / 2;
        const auto mid = cbegin + half;
        const auto length_minus_1 = length - 1;

        if (not half or * mid < *std::prev(mid)) {
            return mid;
        }
        if (*cbegin < *std::next(cbegin, length_minus_1)) {
            return cbegin;
        }
        if (*cbegin > *mid) {
            return FindMinInSortedAndRotated_Neighbor(cbegin, half);
        }
        return FindMinInSortedAndRotated_Neighbor(std::next(mid),
                                                  length_minus_1 - half);
    }

    return cbegin;
}
