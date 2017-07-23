#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

template <std::size_t N>
using ArrayType = std::array<int, N>;


/** Given an array A[] and a number x, check for pair in A[] with sum as x
 *
 * @reference   http://www.geeksforgeeks.org/recursive-insertion-sort/
 *
 * Given an array A[] of n numbers and another number x, determines
 * whether or not there exist two elements in A whose sum is exactly x.
 */
/** Using Hash map
 * @complexity: O(n)
 */
template <std::size_t N>
INT_BOOL HasPairOfElementsSumAsNHashmap(const ArrayType<N> &values, const int target) {
    std::unordered_set<int> elements{};
    int pair;

    for (const auto element : values) {
        pair = target - element;
        if (elements.find(pair) != elements.cend()) {
            return TRUE;
        }
        elements.insert(element);
    }
    return FALSE;
}

/** Using sort
 * @complexity: Same as the sorting algorithm used.
 */
template <std::size_t N>
INT_BOOL HasPairOfElementsSumAsNSort(ArrayType<N> values, const int target) {
    if (values.size() > 1) {
        std::sort(values.begin(), values.end());

        auto left = values.cbegin();
        auto right = values.cbegin() + (values.size() - 1);
        int sum;

        while (left < right) {
            sum = *left + *right;
            if (sum == target) {
                return TRUE;
            } else if (sum < target) {
                ++left;
            } else {
                --right;
            }
        }
    }
    return FALSE;
}


constexpr ArrayType<0> VALUES1 = {};
constexpr ArrayType<1> VALUES2 = {1};
constexpr ArrayType<8> VALUES3 = {1, 4, 45, 6, 10, -8, 9, 4};

SIMPLE_TEST(HasPairOfElementsSumAsNHashmap, TestSAMPLE1, FALSE, VALUES1, 16);
SIMPLE_TEST(HasPairOfElementsSumAsNHashmap, TestSAMPLE2, FALSE, VALUES2, 16);
SIMPLE_TEST(HasPairOfElementsSumAsNHashmap, TestSAMPLE3, TRUE, VALUES3, 16);
SIMPLE_TEST(HasPairOfElementsSumAsNHashmap, TestSAMPLE4, TRUE, VALUES3, 8);
SIMPLE_TEST(HasPairOfElementsSumAsNHashmap, TestSAMPLE5, FALSE, VALUES3, 6);

SIMPLE_TEST(HasPairOfElementsSumAsNSort, TestSAMPLE1, FALSE, VALUES1, 16);
SIMPLE_TEST(HasPairOfElementsSumAsNSort, TestSAMPLE2, FALSE, VALUES2, 16);
SIMPLE_TEST(HasPairOfElementsSumAsNSort, TestSAMPLE3, TRUE, VALUES3, 16);
SIMPLE_TEST(HasPairOfElementsSumAsNSort, TestSAMPLE4, TRUE, VALUES3, 8);
SIMPLE_TEST(HasPairOfElementsSumAsNSort, TestSAMPLE5, FALSE, VALUES3, 6);
