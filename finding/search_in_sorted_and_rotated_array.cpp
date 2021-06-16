#include "common_header.h"

#include "finding.h"


namespace {

using ArrayType = std::vector<int>;

/** Search an element in a sorted and rotated array
 *
 * @reference   https://www.geeksforgeeks.org/search-an-element-in-a-sorted-and-pivoted-array/
 * @reference   Search an element in a sorted and rotated array with duplicates
 *              https://www.geeksforgeeks.org/search-an-element-in-a-sorted-and-rotated-array-with-duplicates/
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 11.3.
 *
 * Given a sorted array of n integers that has been rotated an unknown number of times,
 * write code to find an element in the array. You may assume that the array was
 * originally sorted in increasing order.
 */
auto SearchRotatedArray(const ArrayType &elements, const ArrayType::value_type key,
                        const int left, const int right) {
    if (left > right) {
        return NOT_FOUND;
    }

    const auto mid = (left + right) / 2;

    if (elements[mid] == key) {
        return mid;
    }

    if (elements[left] == elements[mid] and elements[mid] == elements[right]) {
        return SearchRotatedArray(elements, key, left + 1, right - 1);
    }

    if (elements[left] <= elements[mid]) {
        if (key >= elements[left] and key <= elements[mid]) {
            return SearchRotatedArray(elements, key, left, mid - 1);
        } else {
            return SearchRotatedArray(elements, key, mid + 1, right);
        }
    }

    if (key >= elements[mid] and key <= elements[right]) {
        return SearchRotatedArray(elements, key, mid + 1, right);
    }

    return SearchRotatedArray(elements, key, left, mid - 1);
}

inline auto
SearchRotatedArray(const ArrayType &elements, const ArrayType::value_type key) {
    return SearchRotatedArray(elements, key, 0, elements.size() - 1);
}

}//namespace


const ArrayType SAMPLE1 = {5, 6, 7, 8, 9, 10, 1, 2, 3};
const ArrayType SAMPLE2 = {4, 5, 6, 7, 8, 9, 10, 1, 2, 3};
const ArrayType SAMPLE3 = {30, 40, 50, 10, 20};
const ArrayType SAMPLE4 = {3, 3, 3, 1, 2, 3};
const ArrayType SAMPLE5 = {3, 3, 1, 2, 3, 3};


THE_BENCHMARK(SearchRotatedArray, SAMPLE1, 3);

SIMPLE_TEST(SearchRotatedArray, TestSAMPLE1, 8, SAMPLE1, 3);
SIMPLE_TEST(SearchRotatedArray, TestSAMPLE2, 2, SAMPLE2, 6);
SIMPLE_TEST(SearchRotatedArray, TestSAMPLE3, NOT_FOUND, SAMPLE2, 30);
SIMPLE_TEST(SearchRotatedArray, TestSAMPLE4, 3, SAMPLE3, 10);
SIMPLE_TEST(SearchRotatedArray, TestSAMPLE5, 2, SAMPLE4, 3);
SIMPLE_TEST(SearchRotatedArray, TestSAMPLE6, NOT_FOUND, SAMPLE4, 11);
SIMPLE_TEST(SearchRotatedArray, TestSAMPLE7, 4, SAMPLE5, 3);
