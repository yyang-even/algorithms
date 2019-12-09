#include "common_header.h"

#include "median.h"


namespace {

using ArrayType = std::vector<int>;

/** Program for Mean and median of an unsorted array
 *
 * @reference   https://www.geeksforgeeks.org/program-for-mean-and-median-of-an-unsorted-array/
 *
 * Median of a sorted array of size n is defined as below:
 * It is middle element when n is odd and average of middle two elements when n is even.
 *
 * @reference   Median and Mode using Counting Sort
 *              https://www.geeksforgeeks.org/median-and-mode-using-counting-sort/
 * @reference   Median
 *              https://www.geeksforgeeks.org/median/
 */
double Median(const ArrayType &sorted_array) {
    assert(not sorted_array.empty());
    assert(std::is_sorted(sorted_array.cbegin(), sorted_array.cend()));

    return Median_Sorted(sorted_array.cbegin(), sorted_array.size());
}

inline auto Median_Unsorted(ArrayType values) {
    std::sort(values.begin(), values.end());
    return Median(values);
}


/** Finding Median in a Sorted Linked List
 *
 * @reference   https://www.geeksforgeeks.org/finding-median-in-a-sorted-linked-list/
 */
double Median_SinglyList_TwoPointers(const std::forward_list<ArrayType::value_type> &sorted_list) {
    assert(not sorted_list.empty());
    assert(std::is_sorted(sorted_list.cbegin(), sorted_list.cend()));

    auto fast_ptr = sorted_list.cbegin();
    auto slow_ptr = sorted_list.cbegin();
    auto prev_slow = sorted_list.cbefore_begin();

    while (fast_ptr != sorted_list.cend() and std::next(fast_ptr) != sorted_list.cend()) {
        fast_ptr = std::next(fast_ptr, 2);
        ++slow_ptr;
        ++prev_slow;
    }

    if (fast_ptr != sorted_list.cend()) {
        return *slow_ptr;
    } else {
        return (*slow_ptr + *prev_slow) / 2.0;
    }
}

inline auto Median_Unsorted_List(std::forward_list<ArrayType::value_type> values) {
    values.sort();
    return Median_SinglyList_TwoPointers(values);
}

}//namespace


using InitializerType = std::initializer_list<ArrayType::value_type>;

const InitializerType VALUES1 = {1};
const InitializerType VALUES2 = {1, 2};
const InitializerType VALUES3 = {2, 3, 1};
const InitializerType VALUES4 = {1, 3, 4, 2, 6, 5, 8, 7};
const InitializerType VALUES5 = {4, 4, 4, 4, 4};


SIMPLE_BENCHMARK(Median, VALUES5);

SIMPLE_DOUBLE_TEST(Median_Unsorted, TestSAMPLE1, 1, VALUES1);
SIMPLE_DOUBLE_TEST(Median_Unsorted, TestSAMPLE2, 1.5, VALUES2);
SIMPLE_DOUBLE_TEST(Median_Unsorted, TestSAMPLE3, 2, VALUES3);
SIMPLE_DOUBLE_TEST(Median_Unsorted, TestSAMPLE4, 4.5, VALUES4);
SIMPLE_DOUBLE_TEST(Median_Unsorted, TestSAMPLE5, 4, VALUES5);


SIMPLE_BENCHMARK(Median_SinglyList_TwoPointers, VALUES5);

SIMPLE_DOUBLE_TEST(Median_Unsorted_List, TestSAMPLE1, 1, VALUES1);
SIMPLE_DOUBLE_TEST(Median_Unsorted_List, TestSAMPLE2, 1.5, VALUES2);
SIMPLE_DOUBLE_TEST(Median_Unsorted_List, TestSAMPLE3, 2, VALUES3);
SIMPLE_DOUBLE_TEST(Median_Unsorted_List, TestSAMPLE4, 4.5, VALUES4);
SIMPLE_DOUBLE_TEST(Median_Unsorted_List, TestSAMPLE5, 4, VALUES5);


SIMPLE_BENCHMARK(Median_Unsorted_QuickSelect, VALUES5);

SIMPLE_DOUBLE_TEST(Median_Unsorted_QuickSelect, TestSAMPLE1, 1, VALUES1);
SIMPLE_DOUBLE_TEST(Median_Unsorted_QuickSelect, TestSAMPLE2, 1.5, VALUES2);
SIMPLE_DOUBLE_TEST(Median_Unsorted_QuickSelect, TestSAMPLE3, 2, VALUES3);
SIMPLE_DOUBLE_TEST(Median_Unsorted_QuickSelect, TestSAMPLE4, 4.5, VALUES4);
SIMPLE_DOUBLE_TEST(Median_Unsorted_QuickSelect, TestSAMPLE5, 4, VALUES5);
