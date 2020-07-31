#include "common_header.h"

#include "text/remove_characters.h"


namespace {

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


/** Find sum of non-repeating (distinct) elements in an array
 *
 * @reference   https://www.geeksforgeeks.org/find-sum-non-repeating-distinct-elements-array/
 */

}//namespace


SIMPLE_BENCHMARK(RemoveDuplicates, "geeksforgeeks");

SIMPLE_TEST(RemoveDuplicates, TestSAMPLE1, "geksfor", "geeksforgeeks");
SIMPLE_TEST(RemoveDuplicates, TestSAMPLE2, "chartes", "characters");


SIMPLE_BENCHMARK(RemoveDuplicates_Bits, "geeksforgeeks");

SIMPLE_TEST(RemoveDuplicates_Bits, TestSAMPLE1, "geksfor", "geeksforgeeks");
SIMPLE_TEST(RemoveDuplicates_Bits, TestSAMPLE2, "chartes", "characters");


SIMPLE_BENCHMARK(RemoveDuplicates_Sorted, "122344455");

SIMPLE_TEST(RemoveDuplicates_Sorted, TestSAMPLE1, "12345", "122344455");
SIMPLE_TEST(RemoveDuplicates_Sorted, TestSAMPLE2, "Geks for geks", "Geeks for geeks");
