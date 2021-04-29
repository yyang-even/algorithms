#include "common_header.h"

#include "median.h"


namespace {

using ArrayType = std::vector<int>;
using ListType = std::forward_list<ArrayType::value_type>;

/** Program for Mean and median of an unsorted array
 *
 * @reference   https://www.geeksforgeeks.org/program-for-mean-and-median-of-an-unsorted-array/
 * @reference   Finding Median of unsorted Array in linear time using C++ STL
 *              https://www.geeksforgeeks.org/finding-median-of-unsorted-array-in-linear-time-using-c-stl/
 * @reference   Median of an unsorted array using Quick Select Algorithm
 *              https://www.geeksforgeeks.org/median-of-an-unsorted-array-in-liner-time-on/
 *
 * Median of a sorted array of size n is defined as below:
 * It is middle element when n is odd and average of middle two elements when n is even.
 *
 * @reference   Median and Mode using Counting Sort
 *              https://www.geeksforgeeks.org/median-and-mode-using-counting-sort/
 * @reference   Median
 *              https://www.geeksforgeeks.org/median/
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 9.3-9.
 *
 * Professor Olay is consulting for an oil company, which is planning a large pipeline
 * running east to west through an oil field of n wells, The company wants to connect a
 * spur pipeline from each well directly to the main pipeline along a shortest route
 * (either north or south). Given the x- and y-coordinate of the wells, how should the
 * professor pick the optimal location of the main pipeline, which would be the one that
 * minimizes the total length of the spurs? Show how to determine the optimal location
 * in linear time.
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
double Median_SinglyList_TwoPointers(const ListType &sorted_list) {
    assert(not sorted_list.empty());
    assert(std::is_sorted(sorted_list.cbegin(), sorted_list.cend()));

    auto fast_ptr = sorted_list.cbegin();
    auto slow_ptr = sorted_list.cbegin();
    auto prev_slow = sorted_list.cbefore_begin();

    while (isThereMoreThanOneElements(fast_ptr, sorted_list.cend())) {
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

inline auto Median_Unsorted_List(ListType values) {
    values.sort();
    return Median_SinglyList_TwoPointers(values);
}

}//namespace


using InitializerType = std::initializer_list<ArrayType::value_type>;

constexpr InitializerType VALUES1 = {1};
constexpr InitializerType VALUES2 = {1, 2};
constexpr InitializerType VALUES3 = {2, 3, 1};
constexpr InitializerType VALUES4 = {1, 3, 4, 2, 6, 5, 8, 7};
constexpr InitializerType VALUES5 = {4, 4, 4, 4, 4};


THE_BENCHMARK(Median, VALUES5);

SIMPLE_DOUBLE_TEST(Median_Unsorted, TestSAMPLE1, 1, VALUES1);
SIMPLE_DOUBLE_TEST(Median_Unsorted, TestSAMPLE2, 1.5, VALUES2);
SIMPLE_DOUBLE_TEST(Median_Unsorted, TestSAMPLE3, 2, VALUES3);
SIMPLE_DOUBLE_TEST(Median_Unsorted, TestSAMPLE4, 4.5, VALUES4);
SIMPLE_DOUBLE_TEST(Median_Unsorted, TestSAMPLE5, 4, VALUES5);


THE_BENCHMARK(Median_SinglyList_TwoPointers, VALUES5);

SIMPLE_DOUBLE_TEST(Median_Unsorted_List, TestSAMPLE1, 1, VALUES1);
SIMPLE_DOUBLE_TEST(Median_Unsorted_List, TestSAMPLE2, 1.5, VALUES2);
SIMPLE_DOUBLE_TEST(Median_Unsorted_List, TestSAMPLE3, 2, VALUES3);
SIMPLE_DOUBLE_TEST(Median_Unsorted_List, TestSAMPLE4, 4.5, VALUES4);
SIMPLE_DOUBLE_TEST(Median_Unsorted_List, TestSAMPLE5, 4, VALUES5);


THE_BENCHMARK(Median_Unsorted_QuickSelect, VALUES5);

SIMPLE_DOUBLE_TEST(Median_Unsorted_QuickSelect, TestSAMPLE1, 1, VALUES1);
SIMPLE_DOUBLE_TEST(Median_Unsorted_QuickSelect, TestSAMPLE2, 1.5, VALUES2);
SIMPLE_DOUBLE_TEST(Median_Unsorted_QuickSelect, TestSAMPLE3, 2, VALUES3);
SIMPLE_DOUBLE_TEST(Median_Unsorted_QuickSelect, TestSAMPLE4, 4.5, VALUES4);
SIMPLE_DOUBLE_TEST(Median_Unsorted_QuickSelect, TestSAMPLE5, 4, VALUES5);
