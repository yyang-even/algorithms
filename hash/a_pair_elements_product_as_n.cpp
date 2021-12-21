#include "common_header.h"

#include "a_pair_elements_product_as_n.h"


namespace {

using ArrayType = std::vector<int>;

/** Pair with given product | Set 1 (Find if any pair exists)
 *
 * @reference   https://www.geeksforgeeks.org/pair-with-given-product-set-1-find-if-any-pair-exists/
 *
 * Given an array of distinct elements and a number x, find if there is a pair with
 * product equal to x.
 *
 * @reference   Check if a pair with given product exists in Linked list
 *              https://www.geeksforgeeks.org/check-if-a-pair-with-given-product-exists-in-linked-list/
 */
inline auto
PairElementsProductAsN_Hash(const ArrayType &elements, const ArrayType::value_type N) {
    return PairElementsProductAsN(elements, N, nullptr);
}


/**
 * @reference   Find pairs with given product in a sorted Doubly Linked List
 *              https://www.geeksforgeeks.org/find-pairs-with-given-product-in-a-sorted-doubly-linked-list/
 *
 * Given a sorted doubly linked list of positive distinct elements, the task is to find
 * pairs in the doubly linked list whose product is equal to given value x, without using
 * any extra space.
 */
auto PairElementsProductAsN_TwoPointers(const std::list<int> &elements,
                                        const int N) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));

    if (not elements.empty()) {
        auto left = elements.cbegin();
        auto right = std::prev(elements.cend());

        while (left != right) {
            const auto product = *left * *right;
            if (product == N) {
                return true;
            } else if (product < N) {
                ++left;
            } else {
                --right;
            }
        }
    }

    return false;
}


/**
 * @reference   Check If N and Its Double Exist
 *              https://leetcode.com/problems/check-if-n-and-its-double-exist/
 *
 * Given an array arr of integers, check if there exists two integers N and M such that N
 * is the double of M ( i.e. N = 2 * M). More formally check if there exists two indices
 * i and j such that :
 *  i != j
 *  0 <= i, j < arr.length
 *  arr[i] == 2 * arr[j]
 */

}//namespace


const ArrayType SAMPLE1 = {10, 20, 9, 40};
const ArrayType SAMPLE2 = {10, 20, 9, 40};
const ArrayType SAMPLE3 = { -10, 20, 9, -40};
const ArrayType SAMPLE4 = { -10, 20, 9, 40};
const ArrayType SAMPLE5 = {0, 20, 9, 40};


THE_BENCHMARK(PairElementsProductAsN_Hash, SAMPLE1, 33);

SIMPLE_TEST(PairElementsProductAsN_Hash, TestSample1, true, SAMPLE1, 400);
SIMPLE_TEST(PairElementsProductAsN_Hash, TestSample2, false, SAMPLE2, 190);
SIMPLE_TEST(PairElementsProductAsN_Hash, TestSample3, true, SAMPLE3, 400);
SIMPLE_TEST(PairElementsProductAsN_Hash, TestSample4, true, SAMPLE4, -400);
SIMPLE_TEST(PairElementsProductAsN_Hash, TestSample5, true, SAMPLE5, 0);


const std::list<int> LIST1 = {1, 2, 4, 5, 6, 8, 9};
const std::list<int> LIST_EVEN = {1, 2, 3, 4, 5, 6, 7};
const std::list<int> LIST_ODD = {1, 2, 3, 4, 5, 6};


THE_BENCHMARK(PairElementsProductAsN_TwoPointers, LIST1, 8);

SIMPLE_TEST(PairElementsProductAsN_TwoPointers, TestSample1, true, LIST1, 8);
SIMPLE_TEST(PairElementsProductAsN_TwoPointers, TestSample2, true, LIST_EVEN, 6);
SIMPLE_TEST(PairElementsProductAsN_TwoPointers, TestEven, false, LIST_EVEN, 0);
SIMPLE_TEST(PairElementsProductAsN_TwoPointers, TestOdd, false, LIST_ODD, 0);
