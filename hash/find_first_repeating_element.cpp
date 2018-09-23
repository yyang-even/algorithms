#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

using ArrayType = std::vector<int>;

/** Find the first repeating element in an array of integers
 *
 * @reference   https://www.geeksforgeeks.org/find-first-repeating-element-array-integers/
 *
 * Given an array of integers, find the first repeating element in it.
 * We need to find the element that occurs more than once and whose
 * index of first occurrence is smallest.
 */
auto FindFirstRepeatingElement(const ArrayType &elements) {
    std::unordered_set<ArrayType::value_type> counters;
    ArrayType::value_type first_repeated = -1;

    for (auto iter = elements.crbegin(); iter != elements.crend(); ++iter) {
        if (counters.find(*iter) != counters.cend()) {
            first_repeated = *iter;
        } else {
            counters.insert(*iter);
        }
    }

    return first_repeated;
}


/** Given a string, find its first non-repeating character
 *
 * @reference   https://www.geeksforgeeks.org/given-a-string-find-its-first-non-repeating-character/
 *
 * Given a string, find the first non-repeating character in it. For example, if the
 * input string is “GeeksforGeeks”, then output should be ‘f’ and if input string is
 * “GeeksQuiz”, then output should be ‘G’.
 */
auto FindFirstNonrepeatingChar(const std::string &input) {
    std::unordered_set<std::string::value_type> counters;
    std::string::value_type first_nonrepeated = -1;

    for (auto iter = input.crbegin(); iter != input.crend(); ++iter) {
        if (counters.find(*iter) == counters.cend()) {
            first_nonrepeated = *iter;
        }
        counters.insert(*iter);
    }

    return first_nonrepeated;
}


const ArrayType SAMPLE1 = {10, 5, 3, 4, 3, 5, 6};
const ArrayType SAMPLE2 = {6, 10, 5, 4, 9, 120, 4, 6, 10};

SIMPLE_BENCHMARK(FindFirstRepeatingElement, SAMPLE1);

SIMPLE_TEST(FindFirstRepeatingElement, TestSAMPLE1, 5, SAMPLE1);
SIMPLE_TEST(FindFirstRepeatingElement, TestSAMPLE2, 6, SAMPLE2);


SIMPLE_BENCHMARK(FindFirstNonrepeatingChar, std::string("GeeksforGeeks"));

SIMPLE_TEST(FindFirstNonrepeatingChar, TestSAMPLE1, 'f', std::string("GeeksforGeeks"));
SIMPLE_TEST(FindFirstNonrepeatingChar, TestSAMPLE2, 'G', std::string("GeeksQuiz"));
