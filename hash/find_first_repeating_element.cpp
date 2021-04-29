#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Find the first repeating element in an array of integers
 *
 * @reference   https://www.geeksforgeeks.org/find-first-repeating-element-array-integers/
 * @reference   Find repeated character present first in a string
 *              https://www.geeksforgeeks.org/find-repeated-character-present-first-string/
 * @reference   Repeated Character Whose First Appearance is Leftmost
 *              https://www.geeksforgeeks.org/repeated-character-whose-first-appearance-is-leftmost/
 * @reference   Find the first repeated word in a string
 *              https://www.geeksforgeeks.org/find-first-repeated-word-string/
 *
 * Given an array of integers, find the first repeating element in it. We need to find
 * the element that occurs more than once and whose index of first occurrence is smallest.
 */
auto FindFirstRepeatingElement_FirstAppearance(const ArrayType &elements) {
    std::unordered_set<ArrayType::value_type> counters;
    ArrayType::value_type first_repeated = -1;

    for (auto iter = elements.crbegin(); iter != elements.crend(); ++iter) {
        if (not counters.insert(*iter).second) {
            first_repeated = *iter;
        }
    }

    return first_repeated;
}


/** Find the first repeated character in a string
 *
 * @reference   https://www.geeksforgeeks.org/find-the-first-repeated-character-in-a-string/
 *
 * Given a string, find the first repeated character in it. We need to find the character
 * that occurs more than once and whose index of second occurrence is smallest.
 *
 * @reference   Efficiently find first repeated character in a string without using any additional data structure in one traversal
 *              https://www.geeksforgeeks.org/efficiently-find-first-repeated-character-string-without-using-additional-data-structure-one-traversal/
 *
 * Implement a space efficient algorithm to check First repeated character in a string
 * without using any additional data structure in one traversal. Use additional data
 * structures like count array, hash, etc is not allowed.
 */
auto FindFirstRepeatingElement_SecondAppearance_Hash(const std::string &str) {
    std::unordered_set<ArrayType::value_type> counters;

    for (const auto c : str) {
        if (not counters.insert(c).second) {
            return c;
        }
    }

    return '\0';
}


auto FindFirstRepeatingElement_SecondAppearance_Bits(const std::string &str) {
    assert(std::all_of(str.cbegin(), str.cend(), islower));

    unsigned long counters = 0;

    for (const auto c : str) {
        const auto mask = 1u << (c - 'a');

        if (counters & mask) {
            return c;
        } else {
            counters |= mask;
        }
    }

    return '\0';
}


/** Find the first duplicate element in the linked list
 *
 * @reference   https://www.geeksforgeeks.org/find-the-first-duplicate-element-in-the-linked-list/
 *
 * Given a linked list. Find the first element from the left which appears more than once.
 * If all the elements are unique then print -1.
 */
auto FindFirstDuplicateElement_LinkedList_FirstAppearance(
    const std::forward_list<ArrayType::value_type> &l) {
    std::unordered_map<int, std::size_t> occurrence_map;

    std::size_t index = 0;
    auto min_index = std::numeric_limits<std::size_t>::max();
    int first_duplicate_element = -1;
    for (const auto element : l) {
        const auto [map_iter, inserted] = occurrence_map.emplace(element, index);
        if (not inserted and map_iter->second < min_index) {
            min_index = map_iter->second;
            first_duplicate_element = element;
        }
        ++index;
    }

    return first_duplicate_element;
}

}//namespace


using InitializerType = std::initializer_list<ArrayType::value_type>;

constexpr InitializerType EMPTY = {};
constexpr InitializerType SAMPLE1 = {10, 5, 3, 4, 3, 5, 6};
constexpr InitializerType SAMPLE2 = {6, 10, 5, 4, 9, 120, 4, 6, 10};


THE_BENCHMARK(FindFirstRepeatingElement_FirstAppearance, SAMPLE1);

SIMPLE_TEST(FindFirstRepeatingElement_FirstAppearance, TestSAMPLE1, 5, SAMPLE1);
SIMPLE_TEST(FindFirstRepeatingElement_FirstAppearance, TestSAMPLE2, 6, SAMPLE2);


THE_BENCHMARK(FindFirstRepeatingElement_SecondAppearance_Hash, "geeksforgeeks");

SIMPLE_TEST(FindFirstRepeatingElement_SecondAppearance_Hash, TestSAMPLE1, 'e',
            "geeksforgeeks");
SIMPLE_TEST(FindFirstRepeatingElement_SecondAppearance_Hash, TestSAMPLE2, 'l',
            "hello geeks");


THE_BENCHMARK(FindFirstRepeatingElement_SecondAppearance_Bits, "geeksforgeeks");

SIMPLE_TEST(FindFirstRepeatingElement_SecondAppearance_Bits, TestSAMPLE1, 'e',
            "geeksforgeeks");
SIMPLE_TEST(FindFirstRepeatingElement_SecondAppearance_Bits, TestSAMPLE2, 'a',
            "abcfdeacf");


THE_BENCHMARK(FindFirstDuplicateElement_LinkedList_FirstAppearance, SAMPLE1);

SIMPLE_TEST(FindFirstDuplicateElement_LinkedList_FirstAppearance, TestSAMPLE0, -1,
            EMPTY);
SIMPLE_TEST(FindFirstDuplicateElement_LinkedList_FirstAppearance, TestSAMPLE1, 5,
            SAMPLE1);
SIMPLE_TEST(FindFirstDuplicateElement_LinkedList_FirstAppearance, TestSAMPLE2, 6,
            SAMPLE2);
