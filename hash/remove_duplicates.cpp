#include "common_header.h"

#include "hash.h"
#include "count_frequencies_of_all_elements.h"
#include "text/remove_characters.h"


namespace {

using ArrayType = std::vector<int>;
using ListType = std::forward_list<int>;

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
inline auto RemoveDuplicates(std::string input) {
    std::unordered_set<std::string::value_type> hash_table;

    return RemoveCharacters_TwoPointers(std::move(input), [&hash_table](const auto c) {
        return hash_table.emplace(c).second;
    });
}


/** Remove duplicates from a string in O(1) extra space
 *
 * @reference   https://www.geeksforgeeks.org/remove-duplicates-from-a-string-in-o1-extra-space/
 *
 * Given a string str of lowercase characters, the task is to remove duplicates and return
 * a resultant string without modifying the order of characters in the original string.
 */
inline auto RemoveDuplicates_Bits(std::string input) {
    std::bitset < 'z' - 'a' > hash_table;

    return RemoveCharacters_TwoPointers(std::move(input), [&hash_table](const auto c) {
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
inline auto RemoveDuplicates_Sorted(std::string sorted_input) {
    if (sorted_input.empty()) {
        return sorted_input;
    }

    std::string::value_type previous_element = sorted_input.front() + 1;
    return RemoveCharacters_TwoPointers(std::move(sorted_input),
    [&previous_element](const auto c) {
        const auto result = (previous_element != c);
        previous_element = c;
        return result;
    });
}


/**
 * @reference   Remove Duplicates from Sorted Array
 *              https://leetcode.com/problems/remove-duplicates-from-sorted-array/
 */
auto RemoveDuplicates_Sorted_Better(std::string sorted_input) {
    assert(std::is_sorted(sorted_input.cbegin(), sorted_input.cend()));

    if (sorted_input.empty()) {
        return sorted_input;
    }

    std::size_t last = 0;
    const auto N = sorted_input.size();
    for (std::size_t i = 1; i < N; ++i) {
        if (sorted_input[last] != sorted_input[i]) {
            sorted_input[++last] = sorted_input[i];
        }
    }
    sorted_input.resize(last + 1);

    return sorted_input;
}


/**
 * @reference   Duplicates Removal in Array using BST
 *              https://www.geeksforgeeks.org/duplicates-removal-in-array-using-bst/
 * @reference   Remove duplicates from unsorted array using Set data structure
 *              https://www.geeksforgeeks.org/remove-duplicates-from-unsorted-array-using-set-data-structure/
 */


/** Remove duplicates from an unsorted linked list
 *
 * @reference   https://www.geeksforgeeks.org/remove-duplicates-from-an-unsorted-linked-list/
 *
 * Write a removeDuplicates() function which takes a list and deletes any duplicate nodes
 * from the list. The list is not sorted.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 2.1.
 *
 * @reference   Remove duplicates from an unsorted doubly linked list
 *              https://www.geeksforgeeks.org/remove-duplicates-unsorted-doubly-linked-list/
 */
auto RemoveDuplicates_UnsortedLinkedList(ListType a_list) {
    std::unordered_set<ListType::value_type> seen_values;
    auto previous = a_list.cbefore_begin();
    for (auto current = a_list.cbegin(); current != a_list.cend();) {
        if (not seen_values.insert(*(current++)).second) {
            current = a_list.erase_after(previous);
        } else {
            ++previous;
        }
    }

    return a_list;
}


/**
 * @reference   Remove duplicates from a sorted linked list
 *              https://www.geeksforgeeks.org/remove-duplicates-from-a-sorted-linked-list/
 *
 * @reference   Remove duplicates from a sorted doubly linked list
 *              https://www.geeksforgeeks.org/remove-duplicates-sorted-doubly-linked-list/
 *
 * @reference   Remove Duplicates from Sorted List
 *              https://leetcode.com/problems/remove-duplicates-from-sorted-list/
 */
auto RemoveDuplicates_SortedLinkedList(ListType a_list) {
    assert(std::is_sorted(a_list.cbegin(), a_list.cend()));

    for (auto current = a_list.cbegin();
         isThereMoreThanOneElements(current, a_list.cend());) {
        if (*current == *std::next(current)) {
            a_list.erase_after(current);
        } else {
            ++current;
        }
    }

    return a_list;
}


inline void
RemoveDuplicates_SortedLinkedList_Recursive_Helper(ListType &a_list,
                                                   const ListType::const_iterator current) {
    if (isThereMoreThanOneElements(current, a_list.cend())) {
        if (*current == *std::next(current)) {
            a_list.erase_after(current);
            RemoveDuplicates_SortedLinkedList_Recursive_Helper(a_list, current);
        } else {
            RemoveDuplicates_SortedLinkedList_Recursive_Helper(a_list, std::next(current));
        }
    }
}

inline auto RemoveDuplicates_SortedLinkedList_Recursive(ListType a_list) {
    assert(std::is_sorted(a_list.cbegin(), a_list.cend()));
    RemoveDuplicates_SortedLinkedList_Recursive_Helper(a_list, a_list.cbegin());
    return a_list;
}


/**
 * @reference   Remove duplicates from a sorted linked list using recursion
 *              https://www.geeksforgeeks.org/remove-duplicates-sorted-linked-list-using-recursion/
 */


inline auto
RemoveDuplicates_UnsortedLinkedList_Sort(
    ListType a_list,
    const std::function<ListType(ListType)> remove_consecutive_duplicates) {
    a_list.sort();
    return remove_consecutive_duplicates(std::move(a_list));
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
 * @reference   Remove all occurrences of duplicates from a sorted Linked List
 *              https://www.geeksforgeeks.org/remove-occurrences-duplicates-sorted-linked-list/
 *
 * Given a sorted linked list, delete all nodes that have duplicate numbers (all
 * occurrences), leaving only numbers that appear once in the original list.
 *
 * @reference   Remove Duplicates from Sorted List II
 *              https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
 *
 * Given the head of a sorted linked list, delete all nodes that have duplicate numbers,
 * leaving only distinct numbers from the original list. Return the linked list sorted
 * as well.
 */
auto RemoveAllDuplicates_SortedLinkedList(ListType a_list) {
    assert(std::is_sorted(a_list.cbegin(), a_list.cend()));

    if (a_list.empty()) {
        return a_list;
    }

    auto before_current = a_list.cbefore_begin();
    for (auto current = std::next(before_current); current != a_list.cend();) {
        int count = 0;
        for (; std::next(current) != a_list.cend() and * current == *std::next(current);
             ++current) {
            ++count;
        }

        ++current;
        if (count) {
            a_list.erase_after(before_current, current);
        } else {
            ++before_current;
        }
    }

    return a_list;
}


/**
 * @reference   Count minimum frequency elements in a linked list
 *              https://www.geeksforgeeks.org/count-minimum-frequency-elements-in-a-linked-list/
 *
 * Given a linked list containing duplicate elements. The task is to find the count of
 * all minimum occurring elements in the given linked list. That is the count of all
 * such elements whose frequency is minimum in the matrix.
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
 * @reference   Count duplicates in a given linked list
 *              https://www.geeksforgeeks.org/count-duplicates-in-a-given-linked-list/
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
        auto &count = counters.find(elem)->second;
        if (count > 1) {
            count = 0;
            output.push_back(elem);
        }
    }

    return output;
}


/**
 * @reference   Find Duplicates of array using bit array
 *              https://www.geeksforgeeks.org/find-duplicates-of-array-using-bit-array/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 10.4.
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
 * @reference   Print all the duplicates in the input string
 *              https://www.geeksforgeeks.org/print-all-the-duplicates-in-the-input-string/
 *
 * Write an efficient C program to print all the duplicates and their counts in the input
 * string.
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
    const auto N = values.size();
    TransformToInplaceCounterArray(values, N);

    ArrayType output;
    for (ArrayType::size_type i = 0; i < N; ++i) {
        if ((values[i] / N) > 1) {
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


THE_BENCHMARK(RemoveDuplicates, "geeksforgeeks");

SIMPLE_TEST(RemoveDuplicates, TestSAMPLE1, "geksfor", "geeksforgeeks");
SIMPLE_TEST(RemoveDuplicates, TestSAMPLE2, "chartes", "characters");


THE_BENCHMARK(RemoveDuplicates_Bits, "geeksforgeeks");

SIMPLE_TEST(RemoveDuplicates_Bits, TestSAMPLE1, "geksfor", "geeksforgeeks");
SIMPLE_TEST(RemoveDuplicates_Bits, TestSAMPLE2, "chartes", "characters");


THE_BENCHMARK(RemoveDuplicates_Sorted, "122344455");

SIMPLE_TEST(RemoveDuplicates_Sorted, TestSAMPLE1, "12345", "122344455");
SIMPLE_TEST(RemoveDuplicates_Sorted, TestSAMPLE2, "12", "112");
SIMPLE_TEST(RemoveDuplicates_Sorted, TestSAMPLE3, "01234", "0011122334");
SIMPLE_TEST(RemoveDuplicates_Sorted, TestSAMPLE4, "Geks for geks", "Geeks for geeks");
SIMPLE_TEST(RemoveDuplicates_Sorted, TestSAMPLE5, "ab", "aaaaabbbbbb");


THE_BENCHMARK(RemoveDuplicates_Sorted_Better, "122344455");

SIMPLE_TEST(RemoveDuplicates_Sorted_Better, TestSAMPLE1, "12345", "122344455");
SIMPLE_TEST(RemoveDuplicates_Sorted_Better, TestSAMPLE2, "12", "112");
SIMPLE_TEST(RemoveDuplicates_Sorted_Better, TestSAMPLE3, "01234", "0011122334");


const ListType SAMPLE_L1 = {12, 11, 12, 21, 41, 43, 21};
const ListType EXPECTED_L1 = {12, 11, 21, 41, 43};
const ListType EXPECTED_SL1 = {11, 12, 21, 41, 43};

const ListType SAMPLE_L2 = {10, 12, 11, 11, 12, 11, 10};
const ListType EXPECTED_L2 = {10, 12, 11};
const ListType EXPECTED_SL2 = {10, 11, 12};


THE_BENCHMARK(RemoveDuplicates_UnsortedLinkedList, SAMPLE_L1);

SIMPLE_TEST(RemoveDuplicates_UnsortedLinkedList, TestSAMPLE1, EXPECTED_L1, SAMPLE_L1);
SIMPLE_TEST(RemoveDuplicates_UnsortedLinkedList, TestSAMPLE2, EXPECTED_L2, SAMPLE_L2);


SIMPLE_BENCHMARK(RemoveDuplicates_UnsortedLinkedList_Sort, BM_SAMPLE1, SAMPLE_L1,
                 RemoveDuplicates_SortedLinkedList);

SIMPLE_TEST(RemoveDuplicates_UnsortedLinkedList_Sort, TestSAMPLE1, EXPECTED_SL1,
            SAMPLE_L1, RemoveDuplicates_SortedLinkedList);
SIMPLE_TEST(RemoveDuplicates_UnsortedLinkedList_Sort, TestSAMPLE2, EXPECTED_SL2,
            SAMPLE_L2, RemoveDuplicates_SortedLinkedList);


SIMPLE_BENCHMARK(RemoveDuplicates_UnsortedLinkedList_Sort, BM_SAMPLE2, SAMPLE_L1,
                 RemoveDuplicates_SortedLinkedList_Recursive);

SIMPLE_TEST(RemoveDuplicates_UnsortedLinkedList_Sort, TestSAMPLE3, EXPECTED_SL1,
            SAMPLE_L1, RemoveDuplicates_SortedLinkedList_Recursive);
SIMPLE_TEST(RemoveDuplicates_UnsortedLinkedList_Sort, TestSAMPLE4, EXPECTED_SL2,
            SAMPLE_L2, RemoveDuplicates_SortedLinkedList_Recursive);


const ArrayType SAMPLE1 = {12, 10, 9, 45, 2, 10, 10, 45};
const ArrayType EXPECTED1 = {10, 45};

const ArrayType SAMPLE2 = {1, 1, 1, 1, 1};
const ArrayType EXPECTED2 = {1};


THE_BENCHMARK(FindRepeatedElements, SAMPLE1);

SIMPLE_TEST(FindRepeatedElements, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(FindRepeatedElements, TestSAMPLE2, EXPECTED2, SAMPLE2);


const ArrayType SAMPLE3 = {1, 2, 3, 1, 3, 6, 6};
const ArrayType EXPECTED3 = {1, 3, 6};


THE_BENCHMARK(FindDuplicates_Inplace_Sign, SAMPLE3);

SIMPLE_TEST(FindDuplicates_Inplace_Sign, TestSAMPLE1, EXPECTED3, SAMPLE3);


THE_BENCHMARK(FindDuplicates_Inplace_Mod, SAMPLE3);

SIMPLE_TEST(FindDuplicates_Inplace_Mod, TestSAMPLE1, EXPECTED3, SAMPLE3);
SIMPLE_TEST(FindDuplicates_Inplace_Mod, TestSAMPLE2, EXPECTED2, SAMPLE2);


const ArrayType SAMPLE4 = {0, 3, 1, 3, 0};
const ArrayType EXPECTED4 = {3, 0};


THE_BENCHMARK(FindDuplicates_Inplace_Mod_SecondOccurrence, SAMPLE3);

SIMPLE_TEST(FindDuplicates_Inplace_Mod_SecondOccurrence, TestSAMPLE1,
            EXPECTED4, SAMPLE4);
SIMPLE_TEST(FindDuplicates_Inplace_Mod_SecondOccurrence, TestSAMPLE2,
            EXPECTED2, SAMPLE2);
SIMPLE_TEST(FindDuplicates_Inplace_Mod_SecondOccurrence, TestSAMPLE3,
            EXPECTED3, SAMPLE3);


const ArrayType SAMPLE5 = {1, 5, 1, 10, 12, 10};
const ArrayType EXPECTED5 = {1, 10};

const ArrayType SAMPLE6 = {50, 40, 50};
const ArrayType EXPECTED6 = {50};


THE_BENCHMARK(FindAllDuplicates_BitArray, SAMPLE5);

SIMPLE_TEST(FindAllDuplicates_BitArray, TestSample1, EXPECTED5, SAMPLE5);
SIMPLE_TEST(FindAllDuplicates_BitArray, TestSample2, EXPECTED6, SAMPLE6);


const ListType SAMPLE_L3 = {23, 28, 28, 35, 49, 49, 53, 53};
const ListType EXPECTED_L3 = {23, 35};

const ListType SAMPLE_L4 = {11, 11, 11, 11, 75, 75};
const ListType EXPECTED_L4 = {};

const ListType SAMPLE_L5 = {1, 2, 3, 3, 4, 4, 5};
const ListType EXPECTED_L5 = {1, 2, 5};

const ListType SAMPLE_L6 = {1, 1, 1, 2, 3};
const ListType EXPECTED_L6 = {2, 3};


THE_BENCHMARK(RemoveAllDuplicates_SortedLinkedList, SAMPLE_L1);

SIMPLE_TEST(RemoveAllDuplicates_SortedLinkedList, TestSAMPLE1, EXPECTED_SL1,
            EXPECTED_SL1);
SIMPLE_TEST(RemoveAllDuplicates_SortedLinkedList, TestSAMPLE2, EXPECTED_SL2,
            EXPECTED_SL2);
SIMPLE_TEST(RemoveAllDuplicates_SortedLinkedList, TestSAMPLE3, EXPECTED_L3, SAMPLE_L3);
SIMPLE_TEST(RemoveAllDuplicates_SortedLinkedList, TestSAMPLE4, EXPECTED_L4, SAMPLE_L4);
SIMPLE_TEST(RemoveAllDuplicates_SortedLinkedList, TestSAMPLE5, EXPECTED_L5, SAMPLE_L5);
SIMPLE_TEST(RemoveAllDuplicates_SortedLinkedList, TestSAMPLE6, EXPECTED_L6, SAMPLE_L6);
