#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Pancake Sort
 *
 * @reference   https://www.geeksforgeeks.org/pancake-sorting/
 * @reference   C Program for Pancake sorting
 *              https://www.geeksforgeeks.org/c-program-for-pancake-sorting/
 *
 * Given an unsorted array, sort the given array. You are allowed to do only following
 * operation on array.
 *
 * flip(arr, i): Reverse array from 0 to i
 *
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 8.
 *
 * Imagine you have a stack of n pancakes, each with a different diameter. You also have
 * a pancake flipper. You can insert your flipper into the stack at any point, lift up
 * all the pancakes in the substack above the flipper and flip them over as a unit. Sort
 * all the pancakes by size (largest at the bottom ).
 */
auto PancakeSort(ArrayType elements) {
    for (auto iter = elements.end(); iter != elements.begin(); --iter) {
        const auto the_max_element = std::max_element(elements.begin(), iter);

        const auto next_to_max = std::next(the_max_element);
        if (next_to_max != iter) {
            std::reverse(elements.begin(), next_to_max);
            std::reverse(elements.begin(), iter);
        }
    }

    return elements;
}

}//namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {1};
const ArrayType VALUES3 = {1, 2};
const ArrayType VALUES4 = {2, 3, 1};
const ArrayType EXPECTED4 = {1, 2, 3};
const ArrayType VALUES5 = {4, 3, 2, 1};
const ArrayType EXPECTED5 = {1, 2, 3, 4};


THE_BENCHMARK(PancakeSort, VALUES5);

SIMPLE_TEST(PancakeSort, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(PancakeSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(PancakeSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(PancakeSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(PancakeSort, TestSAMPLE5, EXPECTED5, VALUES5);
