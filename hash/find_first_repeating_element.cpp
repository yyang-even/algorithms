#include "common_header.h"


namespace {

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

}//namespace


const ArrayType SAMPLE1 = {10, 5, 3, 4, 3, 5, 6};
const ArrayType SAMPLE2 = {6, 10, 5, 4, 9, 120, 4, 6, 10};


SIMPLE_BENCHMARK(FindFirstRepeatingElement, SAMPLE1);

SIMPLE_TEST(FindFirstRepeatingElement, TestSAMPLE1, 5, SAMPLE1);
SIMPLE_TEST(FindFirstRepeatingElement, TestSAMPLE2, 6, SAMPLE2);
