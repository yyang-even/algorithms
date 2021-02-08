#include "common_header.h"

#include "hash.h"
#include "count_frequencies_of_all_elements.h"
#include "text/remove_characters.h"


namespace {

using ArrayType = std::vector<int>;

/** Remove duplicates from a given string
 *
 * @reference   https://www.geeksforgeeks.org/remove-duplicates-from-a-given-string/
 * @reference   Remove duplicate elements in an Array using STL in C++
 *              https://www.geeksforgeeks.org/remove-duplicate-elements-in-an-array-using-stl-in-c/
 * @reference   Remove duplicates from unsorted array
 *              https://www.geeksforgeeks.org/remove-duplicates-from-unsorted-array/
 * @reference   Remove duplicates from unsorted array
 *              https://www.geeksforgeeks.org/remove-duplicates-from-unsorted-array-2/
 * @reference   Remove duplicates from unsorted array using Map data structure
 *              https://www.geeksforgeeks.org/remove-duplicates-from-unsorted-array-using-map-data-structure/
 *
 * @reference   Print All Distinct Elements of a given integer array
 *              https://www.geeksforgeeks.org/print-distinct-elements-given-integer-array/
 *
 * Given an integer array, print all distinct elements in array. The given array may
 * contain duplicates and the output should print every element only once. The given
 * array is not sorted.
 *
 * @complexity  O(n)
 */
auto RemoveDuplicates(const std::string &input) {
    std::unordered_set<std::string::value_type> hash_table;

    return RemoveCharacters_TwoPointers(input, [&hash_table](const auto c) {
        if (hash_table.find(c) == hash_table.cend()) {
            hash_table.emplace(c);
            return true;
        }
        return false;
    });
}


/** Remove duplicates from a string in O(1) extra space
 *
 * @reference   https://www.geeksforgeeks.org/remove-duplicates-from-a-string-in-o1-extra-space/
 *
 * Given a string str of lowercase characters, the task is to remove duplicates and return
 * a resultant string without modifying the order of characters in the original string.
 */
auto RemoveDuplicates_Bits(const std::string &input) {
    std::bitset < 'z' - 'a' > hash_table;

    return RemoveCharacters_TwoPointers(input, [&hash_table](const auto c) {
        const auto index = c - 'a';
        if (not hash_table.test(index)) {
            hash_table.set(index);
            return true;
        }
        return false;
    });
}


/**
 * @reference   Remove duplicates from sorted array
 *              https://www.geeksforgeeks.org/remove-duplicates-sorted-array/
 * @reference   Remove duplicates from a sorted array using STL in C++
 *              https://www.geeksforgeeks.org/remove-duplicates-from-a-sorted-array-using-stl-in-c/
 *
 * @reference   Remove duplicates from an unsorted array using STL in C++
 *              https://www.geeksforgeeks.org/remove-duplicates-from-an-unsorted-array-using-stl-in-c/
 *
 * @reference   Remove duplicates from a string using STL in C++
 *              https://www.geeksforgeeks.org/remove-duplicates-from-a-string-using-stl-in-c/
 * @reference   Remove all consecutive duplicates from a string using STL in C++
 *              https://www.geeksforgeeks.org/remove-all-consecutive-duplicates-from-the-string-using-stl-in-c/
 */
auto RemoveDuplicates_Sorted(const std::string &sorted_input) {
    if (sorted_input.empty()) {
        return sorted_input;
    }

    std::string::value_type previous_element = sorted_input.front() + 1;
    return RemoveCharacters_TwoPointers(sorted_input, [&previous_element](const auto c) {
        const auto result = (previous_element != c);
        previous_element = c;
        return result;
    });
}


/**
 * @reference   Duplicates Removal in Array using BST
 *              https://www.geeksforgeeks.org/duplicates-removal-in-array-using-bst/
 * @reference   Remove duplicates from unsorted array using Set data structure
 *              https://www.geeksforgeeks.org/remove-duplicates-from-unsorted-array-using-set-data-structure/
 */


/**
 * @reference   Find sum of non-repeating (distinct) elements in an array
 *              https://www.geeksforgeeks.org/find-sum-non-repeating-distinct-elements-array/
 *
 * @reference   Sum of distinct elements when elements are in range 1 to n
 *              https://www.geeksforgeeks.org/sum-distinct-elements-elements-range-1-n/
 *
 * Given an array of n elements such that every element of array is an integer in the
 * range 1 to n, find the sum of all the distinct elements of the array.
 */


/**
 * @reference   Product of non-repeating (distinct) elements in an Array
 *              https://www.geeksforgeeks.org/product-of-non-repeating-distinct-elements-in-an-array/
 */


/**
 * @reference   Count distinct elements in an array
 *              https://www.geeksforgeeks.org/count-distinct-elements-in-an-array/
 */


/** Array elements that appear more than once
 *
 * @reference   https://www.geeksforgeeks.org/array-elements-that-appear-more-than-once/
 * @reference   Find duplicates in a given array when elements are not limited to a range
 *              https://www.geeksforgeeks.org/find-duplicates-given-array-elements-not-limited-range/
 *
 * Given an integer array, print all repeating elements (Elements that appear more than
 * once) in array. The output should contain elements according to their first occurrences.
 *
 * @complexity  O(n)
 */
auto FindRepeatedElements(const ArrayType &values) {
    auto counters = ToFrequencyHashTable(values);

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


/**
 * @reference   Find Duplicates of array using bit array
 *              https://www.geeksforgeeks.org/find-duplicates-of-array-using-bit-array/
 *
 * You have an array of N numbers, where N is at most 32,000. The array may have
 * duplicates entries and you do not know what N is. With only 4 Kilobytes of memory
 * available, how would print all duplicates elements in the array?
 *
 * @complexity  O(n)
 */
auto FindAllDuplicates_BitArray(const ArrayType &elements) {
    std::vector<bool> counters(elements.size(), false);

    ArrayType output;
    for (const auto elem : elements) {
        if (counters[elem]) {
            output.push_back(elem);
        } else {
            counters[elem] = true;
        }
    }

    return output;
}


/**
 * @reference   Find unique elements in linked list
 *              https://www.geeksforgeeks.org/find-unique-elements-linked-list/
 *
 * Given a linked list. We need to find unique elements in the linked list i.e, those
 * elements which are not repeated in the linked list or those elements whose frequency
 * is 1. If No such elements are present in list so Print "No Unique Elements".
 */


/**
 * @reference   Count minimum frequency elements in a linked list
 *              https://www.geeksforgeeks.org/count-minimum-frequency-elements-in-a-linked-list/
 *
 * Given a linked list containing duplicate elements. The task is to find the count of
 * all minimum occurring elements in the given linked list. That is the count of all
 * such elements whose frequency is minimum in the matrix.
 */


/**
 * @reference   Print all the duplicates in the input string
 *              https://www.geeksforgeeks.org/print-all-the-duplicates-in-the-input-string/
 *
 * Write an efficient C program to print all the duplicates and their counts in the
 * input string.
 */


/** Find duplicates in O(n) time and O(1) extra space | Set 1
 *
 * @reference   https://www.geeksforgeeks.org/find-duplicates-in-on-time-and-constant-extra-space/
 *
 * Given an array of n elements which contains elements from 1 to n-1, with any of these
 * numbers appearing at most twice. Find these repeating numbers in O(n) and using only
 * constant memory space. For example, let n be 7 and array be {1, 2, 3, 1, 3, 6, 6},
 * the answer should be 1, 3 and 6.
 */
auto FindDuplicates_Inplace_Sign(ArrayType values) {
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


/**
 * @reference   Duplicates in an array in O(n) and by using O(1) extra space | Set-2
 *              https://www.geeksforgeeks.org/duplicates-array-using-o1-extra-space-set-2/
 */
auto FindDuplicates_Inplace_Mod(ArrayType values) {
    TransformToInplaceCounterArray(values, values.size());

    ArrayType output;
    for (ArrayType::size_type i = 0ul; i < values.size(); ++i) {
        if ((values[i] / values.size()) > 1) {
            output.push_back(i);
        }
    }

    return output;
}


/**
 * @reference   Duplicates in an array in O(n) time and by using O(1) extra space | Set-3
 *              https://www.geeksforgeeks.org/duplicates-in-an-array-in-on-time-and-by-using-o1-extra-space-set-3/
 *
 * Given an array of n elements which contains elements from 0 to n-1, with any of these
 * numbers appearing any number of times. Find these repeating numbers in O(n) and using
 * only constant memory space. It is required that the order in which elements repeat
 * should be maintained. If there is no repeating element present then print -1.
 */
auto FindDuplicates_Inplace_Mod_SecondOccurrence(ArrayType values) {
    assert(not values.empty());

    const long N = values.size();
    const auto TWO_TIMES_N = N * 2;

    ArrayType output;
    for (const auto number : values) {
        const auto original_number = number % N;
        if (values[original_number] >= N) {
            if (values[original_number] < TWO_TIMES_N) {
                output.push_back(original_number);
            }
        }

        values[original_number] += N;
    }

    return output;
}

}//namespace


SIMPLE_BENCHMARK(RemoveDuplicates, Sample1, "geeksforgeeks");

SIMPLE_TEST(RemoveDuplicates, TestSAMPLE1, "geksfor", "geeksforgeeks");
SIMPLE_TEST(RemoveDuplicates, TestSAMPLE2, "chartes", "characters");


SIMPLE_BENCHMARK(RemoveDuplicates_Bits, Sample1, "geeksforgeeks");

SIMPLE_TEST(RemoveDuplicates_Bits, TestSAMPLE1, "geksfor", "geeksforgeeks");
SIMPLE_TEST(RemoveDuplicates_Bits, TestSAMPLE2, "chartes", "characters");


SIMPLE_BENCHMARK(RemoveDuplicates_Sorted, Sample1, "122344455");

SIMPLE_TEST(RemoveDuplicates_Sorted, TestSAMPLE1, "12345", "122344455");
SIMPLE_TEST(RemoveDuplicates_Sorted, TestSAMPLE2, "Geks for geks", "Geeks for geeks");


const ArrayType SAMPLE1 = {12, 10, 9, 45, 2, 10, 10, 45};
const ArrayType EXPECTED1 = {10, 45};
const ArrayType SAMPLE2 = {1, 1, 1, 1, 1};
const ArrayType EXPECTED2 = {1};


SIMPLE_BENCHMARK(FindRepeatedElements, Sample1, SAMPLE1);

SIMPLE_TEST(FindRepeatedElements, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(FindRepeatedElements, TestSAMPLE2, EXPECTED2, SAMPLE2);


const ArrayType SAMPLE3 = {1, 2, 3, 1, 3, 6, 6};
const ArrayType EXPECTED3 = {1, 3, 6};


SIMPLE_BENCHMARK(FindDuplicates_Inplace_Sign, Sample1, SAMPLE3);

SIMPLE_TEST(FindDuplicates_Inplace_Sign, TestSAMPLE1, EXPECTED3, SAMPLE3);


SIMPLE_BENCHMARK(FindDuplicates_Inplace_Mod, Sample1, SAMPLE3);

SIMPLE_TEST(FindDuplicates_Inplace_Mod, TestSAMPLE1, EXPECTED3, SAMPLE3);
SIMPLE_TEST(FindDuplicates_Inplace_Mod, TestSAMPLE2, EXPECTED2, SAMPLE2);


const ArrayType SAMPLE4 = {0, 3, 1, 3, 0};
const ArrayType EXPECTED4 = {3, 0};


SIMPLE_BENCHMARK(FindDuplicates_Inplace_Mod_SecondOccurrence, Sample1, SAMPLE3);

SIMPLE_TEST(FindDuplicates_Inplace_Mod_SecondOccurrence, TestSAMPLE1, EXPECTED4,
            SAMPLE4);
SIMPLE_TEST(FindDuplicates_Inplace_Mod_SecondOccurrence, TestSAMPLE2, EXPECTED2,
            SAMPLE2);
SIMPLE_TEST(FindDuplicates_Inplace_Mod_SecondOccurrence, TestSAMPLE3, EXPECTED3,
            SAMPLE3);


const ArrayType SAMPLE5 = {1, 5, 1, 10, 12, 10};
const ArrayType EXPECTED5 = {1, 10};
const ArrayType SAMPLE6 = {50, 40, 50};
const ArrayType EXPECTED6 = {50};


SIMPLE_BENCHMARK(FindAllDuplicates_BitArray, Sample1, SAMPLE5);

SIMPLE_TEST(FindAllDuplicates_BitArray, TestSample1, EXPECTED5, SAMPLE5);
SIMPLE_TEST(FindAllDuplicates_BitArray, TestSample2, EXPECTED6, SAMPLE6);
