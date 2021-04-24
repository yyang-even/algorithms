#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Print the last occurrence of elements in array in relative order
 *
 * @reference   https://www.geeksforgeeks.org/print-the-last-occurrence-of-elements-in-array-in-relative-order/
 *
 * Given an array of N elements, print the elements in the same relative order as given
 * by removing all the occurrences of elements except the last occurrence.
 */
auto LastOccurrenceOfElementsInRelativeOrder(const ArrayType &elements) {
    std::unordered_map<ArrayType::value_type, ArrayType::size_type> counters;

    for (ArrayType::size_type i = 0; i < elements.size(); ++i) {
        counters[elements[i]] = i;
    }

    ArrayType output;
    for (ArrayType::size_type i = 0; i < elements.size(); ++i) {
        if (i == counters[elements[i]]) {
            output.push_back(elements[i]);
        }
    }

    return output;
}

}//namespace


const ArrayType SAMPLE1 = {1, 5, 5, 1, 6, 1};
const ArrayType EXPECTED1 = {5, 6, 1};
const ArrayType SAMPLE2 = {2, 5, 5, 2};
const ArrayType EXPECTED2 = {5, 2};


THE_BENCHMARK(LastOccurrenceOfElementsInRelativeOrder, SAMPLE1);

SIMPLE_TEST(LastOccurrenceOfElementsInRelativeOrder, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(LastOccurrenceOfElementsInRelativeOrder, TestSAMPLE2, EXPECTED2, SAMPLE2);
