#include "common_header.h"

#include "repeated_elements.h"


namespace {

using ArrayType = std::vector<int>;
/** Array elements that appear more than once
 *
 * @reference   https://www.geeksforgeeks.org/array-elements-that-appear-more-than-once/
 * @reference   Find duplicates in a given array when elements are not limited to a range
 *              https://www.geeksforgeeks.org/find-duplicates-given-array-elements-not-limited-range/
 *
 * Given an integer array, print all repeating elements (Elements that appear
 * more than once) in array. The output should contain elements according to
 * their first occurrences.
 *
 * @complexity  O(n)
 */
auto FindRepeatedElements(const ArrayType &values) {
    std::unordered_map<ArrayType::value_type, ArrayType::size_type> counters;
    for (const auto elem : values) {
        ++counters[elem];
    }

    ArrayType output;
    for (const auto elem : values) {
        auto iter = counters.find(elem);
        if (iter->second > 1) {
            iter->second = 0;
            output.push_back(elem);
        }
    }

    return output;
}

/** Find unique elements in linked list
 *
 * @reference   https://www.geeksforgeeks.org/find-unique-elements-linked-list/
 *
 * Given a linked list. We need to find unique elements in the linked list i.e, those elements
 * which are not repeated in the linked list or those elements whose frequency is 1. If No such
 * elements are present in list so Print ” No Unique Elements”.
 */

/** Count minimum frequency elements in a linked list
 *
 * @reference   https://www.geeksforgeeks.org/count-minimum-frequency-elements-in-a-linked-list/
 *
 * Given a linked list containing duplicate elements. The task is to find the count of all minimum
 * occurring elements in the given linked list. That is the count of all such elements whose
 * frequency is minimum in the matrix.
 */

/** Print all the duplicates in the input string
 *
 * @reference   https://www.geeksforgeeks.org/print-all-the-duplicates-in-the-input-string/
 *
 * Write an efficient C program to print all the duplicates and their counts in the input string.
 */

/** Print All Distinct Elements of a given integer array
 *
 * @reference   https://www.geeksforgeeks.org/print-distinct-elements-given-integer-array/
 *
 * Given an integer array, print all distinct elements in array. The given array may contain
 * duplicates and the output should print every element only once. The given array is not sorted.
 */


/** Find duplicates in O(n) time and O(1) extra space | Set 1
 *
 * @reference   https://www.geeksforgeeks.org/find-duplicates-in-on-time-and-constant-extra-space/
 *
 * Given an array of n elements which contains elements from 1 to n-1,
 * with any of these numbers appearing at most twice. Find these
 * repeating numbers in O(n) and using only constant memory space.
 * For example, let n be 7 and array be {1, 2, 3, 1, 3, 6, 6}, the
 * answer should be 1, 3 and 6.
 */
auto FindDuplicates_Inplace(ArrayType values) {
    ArrayType output;

    for (const auto elem : values) {
        const auto abs_elem = abs(elem);
        auto &counter = values[abs_elem];
        if (counter > 0) {
            counter = -counter;
        } else {
            output.push_back(abs_elem);
        }
    }

    return output;
}


/** Duplicates in an array in O(n) and by using O(1) extra space | Set-2
 *
 * @reference   https://www.geeksforgeeks.org/duplicates-array-using-o1-extra-space-set-2/
 *
 * Given an array of n elements which contains elements from 0 to n-1,
 * with any of these numbers appearing any number of times. Find these
 * repeating numbers in O(n) and using only constant memory space.
 * For example, let n be 7 and array be {1, 2, 3, 1, 3, 6, 6}, the
 * answer should be 1, 3 and 6.
 */
auto FindDuplicates_Inplace2(ArrayType values) {
    TransformToInplaceCounterArray(values, values.size());

    ArrayType output;
    for (ArrayType::size_type i = 0ul; i < values.size(); ++i) {
        if ((values[i] / values.size()) > 1) {
            output.push_back(i);
        }
    }

    return output;
}

}//namespace


const ArrayType SAMPLE1 = {12, 10, 9, 45, 2, 10, 10, 45};
const ArrayType EXPECTED1 = {10, 45};
const ArrayType SAMPLE2 = {1, 1, 1, 1, 1};
const ArrayType EXPECTED2 = {1};


SIMPLE_BENCHMARK(FindRepeatedElements, SAMPLE1);

SIMPLE_TEST(FindRepeatedElements, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(FindRepeatedElements, TestSAMPLE2, EXPECTED2, SAMPLE2);


const ArrayType SAMPLE3 = {1, 2, 3, 1, 3, 6, 6};
const ArrayType EXPECTED3 = {1, 3, 6};


SIMPLE_BENCHMARK(FindDuplicates_Inplace, SAMPLE3);

SIMPLE_TEST(FindDuplicates_Inplace, TestSAMPLE1, EXPECTED3, SAMPLE3);


SIMPLE_BENCHMARK(FindDuplicates_Inplace2, SAMPLE3);

SIMPLE_TEST(FindDuplicates_Inplace2, TestSAMPLE1, EXPECTED3, SAMPLE3);
SIMPLE_TEST(FindDuplicates_Inplace2, TestSAMPLE2, EXPECTED2, SAMPLE2);
