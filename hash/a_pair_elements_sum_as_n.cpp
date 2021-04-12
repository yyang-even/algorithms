#include "common_header.h"

#include "a_pair_elements_sum_as_n.h"

namespace {

template <std::size_t N>
using ArrayType = std::array<int, N>;


/** Given an array A[] and a number x, check for pair in A[] with sum as x
 *
 * @reference   https://www.geeksforgeeks.org/given-an-array-a-and-a-number-x-check-for-pair-in-a-with-sum-as-x/
 *
 * Given an array A[] of n numbers and another number x, determines whether or not there
 * exist two elements in A whose sum is exactly x.
 *
 * @complexity: O(n)
 */
template <typename ArrayType>
auto HasPairOfElementsSumAsN_Hashmap(const ArrayType &values, const int target) {
    return PairOfElementsSumAsN_Hashmap<ArrayType>(values, target, nullptr);
}


/**
 * @reference   Two Pointers Technique
 *              https://www.geeksforgeeks.org/two-pointers-technique/
 *
 * @complexity: Same as the sorting algorithm used.
 *
 * @reference   Find pairs with given sum in doubly linked list
 *              https://www.geeksforgeeks.org/find-pairs-given-sum-doubly-linked-list/
 *
 * Given a sorted doubly linked list of positive distinct elements, the task is to find
 * pairs in doubly linked list whose sum is equal to given value x, without using any
 * extra space?
 */
template <std::size_t N>
auto HasPairOfElementsSumAsN_Sort(ArrayType<N> values, const int target) {
    if (values.size() > 1) {
        std::sort(values.begin(), values.end());

        auto left = values.cbegin();
        auto right = std::prev(values.cend());

        while (left != right) {
            const auto sum = *left + *right;
            if (sum == target) {
                return true;
            } else if (sum < target) {
                ++left;
            } else {
                --right;
            }
        }
    }
    return false;
}


/** Count pairs with given sum
 *
 * @reference   https://www.geeksforgeeks.org/count-pairs-with-given-sum/
 * @reference   Count pairs with given sum | Set 2
 *              https://www.geeksforgeeks.org/count-pairs-with-given-sum-set-2/
 *
 * Given an array of integers, and a number 'sum', find the number of pairs of integers
 * in the array whose sum is equal to 'sum'.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 17.12.
 */

}//namespace


constexpr ArrayType<0> VALUES1 = {};
constexpr ArrayType<1> VALUES2 = {1};
constexpr ArrayType<8> VALUES3 = {1, 4, 45, 6, 10, -8, 9, 4};


SIMPLE_BENCHMARK(HasPairOfElementsSumAsN_Hashmap, Sample1, VALUES3, 8);

SIMPLE_TEST(HasPairOfElementsSumAsN_Hashmap, TestSAMPLE1, false, VALUES1, 16);
SIMPLE_TEST(HasPairOfElementsSumAsN_Hashmap, TestSAMPLE2, false, VALUES2, 16);
SIMPLE_TEST(HasPairOfElementsSumAsN_Hashmap, TestSAMPLE3, true, VALUES3, 16);
SIMPLE_TEST(HasPairOfElementsSumAsN_Hashmap, TestSAMPLE4, true, VALUES3, 8);
SIMPLE_TEST(HasPairOfElementsSumAsN_Hashmap, TestSAMPLE5, false, VALUES3, 6);


THE_BENCHMARK(HasPairOfElementsSumAsN_Sort, VALUES3, 8);

SIMPLE_TEST(HasPairOfElementsSumAsN_Sort, TestSAMPLE1, false, VALUES1, 16);
SIMPLE_TEST(HasPairOfElementsSumAsN_Sort, TestSAMPLE2, false, VALUES2, 16);
SIMPLE_TEST(HasPairOfElementsSumAsN_Sort, TestSAMPLE3, true, VALUES3, 16);
SIMPLE_TEST(HasPairOfElementsSumAsN_Sort, TestSAMPLE4, true, VALUES3, 8);
SIMPLE_TEST(HasPairOfElementsSumAsN_Sort, TestSAMPLE5, false, VALUES3, 6);


const std::list<int> LIST1 = {};
const std::list<int> LIST2 = {1};
const std::list<int> LIST3 = {1, 4, 45, 6, 10, -8, 9, 4};


SIMPLE_BENCHMARK(HasPairOfElementsSumAsN_Hashmap, Sample3, LIST3, 8);

SIMPLE_TEST(HasPairOfElementsSumAsN_Hashmap, TestSAMPLE6, false, LIST1, 16);
SIMPLE_TEST(HasPairOfElementsSumAsN_Hashmap, TestSAMPLE7, false, LIST2, 16);
SIMPLE_TEST(HasPairOfElementsSumAsN_Hashmap, TestSAMPLE8, true, LIST3, 16);
SIMPLE_TEST(HasPairOfElementsSumAsN_Hashmap, TestSAMPLE9, true, LIST3, 8);
SIMPLE_TEST(HasPairOfElementsSumAsN_Hashmap, TestSAMPLE10, false, LIST3, 6);
