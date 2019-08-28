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

}//namespace


SIMPLE_BENCHMARK(RemoveDuplicates, "geeksforgeeks");

SIMPLE_TEST(RemoveDuplicates, TestSAMPLE1, "geksfor", "geeksforgeeks");
SIMPLE_TEST(RemoveDuplicates, TestSAMPLE2, "chartes", "characters");


SIMPLE_BENCHMARK(RemoveDuplicates_Bits, "geeksforgeeks");

SIMPLE_TEST(RemoveDuplicates_Bits, TestSAMPLE1, "geksfor", "geeksforgeeks");
SIMPLE_TEST(RemoveDuplicates_Bits, TestSAMPLE2, "chartes", "characters");
