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


/**
 * @reference   Degree of an Array
 *              https://leetcode.com/problems/degree-of-an-array/
 *
 * Given a non-empty array of non-negative integers nums, the degree of this array is
 * defined as the maximum frequency of any one of its elements. Your task is to find the
 * smallest possible length of a (contiguous) subarray of nums, that has the same degree
 * as nums.
 * nums[i] will be an integer between 0 and 49,999.
 */
auto DegreeOfArray(const ArrayType &nums) {
    std::pair<int, std::size_t> count_first_map[50000] = {};

    int max_count = 1;
    std::size_t min_length = INT_MAX;
    for (std::size_t i = 0; i < nums.size(); ++i) {
        const auto n = nums[i];
        auto &[count, first] = count_first_map[n];
        if (count++ == 0) {
            first = i;
        }

        if (count == max_count) {
            min_length = std::min(min_length, i - first + 1);
        } else if (count > max_count) {
            max_count = count;
            min_length = i - first + 1;
        }
    }

    return min_length;
}

}//namespace


const ArrayType SAMPLE1 = {1, 5, 5, 1, 6, 1};
const ArrayType EXPECTED1 = {5, 6, 1};

const ArrayType SAMPLE2 = {2, 5, 5, 2};
const ArrayType EXPECTED2 = {5, 2};


THE_BENCHMARK(LastOccurrenceOfElementsInRelativeOrder, SAMPLE1);

SIMPLE_TEST(LastOccurrenceOfElementsInRelativeOrder, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(LastOccurrenceOfElementsInRelativeOrder, TestSAMPLE2, EXPECTED2, SAMPLE2);


const ArrayType SAMPLE3 = {1, 2, 2, 3, 1};
const ArrayType SAMPLE4 = {1, 2, 2, 3, 1, 4, 2};
const ArrayType SAMPLE5 = {2, 1, 1, 2, 1, 3, 3, 3, 1, 3, 1, 3, 2};


THE_BENCHMARK(DegreeOfArray, SAMPLE4);

SIMPLE_TEST(DegreeOfArray, TestSAMPLE3, 2, SAMPLE3);
SIMPLE_TEST(DegreeOfArray, TestSAMPLE4, 6, SAMPLE4);
SIMPLE_TEST(DegreeOfArray, TestSAMPLE5, 7, SAMPLE5);
