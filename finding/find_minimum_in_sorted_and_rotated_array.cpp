#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

#include "find_minimum_in_sorted_and_rotated_array.h"


inline auto FindMinInSortedAndRotatedArray_Neighbor(const ArrayType &elements) {
    assert(not elements.empty());

    return *FindMinInSortedAndRotated_Neighbor(elements.cbegin(), elements.size());
}


/**
 * @reference   Find Minimum in Rotated Sorted Array
 *              https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
 *
 * Suppose an array of length n sorted in ascending order is rotated between 1 and n
 * times. For example, the array nums = [0,1,2,4,5,6,7] might become:
 *  [4,5,6,7,0,1,2] if it was rotated 4 times.
 *  [0,1,2,4,5,6,7] if it was rotated 7 times.
 * Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the
 * array [a[n-1], a[0], a[1], a[2], ..., a[n-2]]. Given the sorted rotated array nums of
 * unique elements, return the minimum element of this array. You must write an algorithm
 * that runs in O(log n) time.
 */
auto FindMinInSortedAndRotatedArray(const ArrayType &nums) {
    int left = 0, right = nums.size() - 1;
    while (left < right) {
        const auto mid = (left + right) / 2;
        if (nums[mid] < nums[right]) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return nums[left];
}


/**
 * @reference   Find Minimum in Rotated Sorted Array II
 *              https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/
 * @reference   https://www.cnblogs.com/grandyang/p/4040438.html
 *
 * Suppose an array of length n sorted in ascending order is rotated between 1 and n
 * times. For example, the array nums = [0,1,4,4,5,6,7] might become:
 *  [4,5,6,7,0,1,4] if it was rotated 4 times.
 *  [0,1,4,4,5,6,7] if it was rotated 7 times.
 * Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the
 * array [a[n-1], a[0], a[1], a[2], ..., a[n-2]]. Given the sorted rotated array nums
 * that may contain duplicates, return the minimum element of this array. You must
 * decrease the overall operation steps as much as possible.
 * Follow up: This problem is similar to Find Minimum in Rotated Sorted Array, but nums
 * may contain duplicates. Would this affect the runtime complexity? How and why?
 */
auto FindMinInSortedAndRotatedWithDuplicates(const ArrayType &nums) {
    int left = 0, right = nums.size() - 1;
    while (left < right) {
        const int mid = (left + right) / 2;
        if (nums[mid] > nums[right]) {
            left = mid + 1;
        } else if (nums[mid] < nums[right]) {
            right = mid;
        } else {
            --right;
        }
    }

    return nums[right];
}


/** Maximum element in a sorted and rotated array
 *
 * @reference   https://www.geeksforgeeks.org/maximum-element-in-a-sorted-and-rotated-array/
 */


/** Sort a Rotated Sorted Array
 *
 * @reference   https://www.geeksforgeeks.org/sort-rotated-sorted-array/
 */

}//namespace


const ArrayType VALUES_EVEN = {5, 6, 1, 2, 3, 4};
const ArrayType VALUES_ODD = {2, 3, 4, 10, 40};


THE_BENCHMARK(FindMinInSortedAndRotatedArray_Neighbor, VALUES_EVEN);

THE_BENCHMARK(FindMinInSortedAndRotatedArray, VALUES_EVEN);


#ifdef WANT_TESTS
class FindMinInSortedAndRotatedArrayTest: public ::testing::Test {
protected:
    void TestAllCasesOf(const std::function<int(const ArrayType &)> min_element_finder,
                        ArrayType elements) const {
        std::sort(elements.begin(), elements.end());
        const auto minimum_element = elements.front();

        const auto N = elements.size();
        for (ArrayType::size_type i = 0; i < N; ++i) {
            auto sorted_elements = elements;
            std::rotate(
                sorted_elements.begin(), std::next(sorted_elements.begin(), i), sorted_elements.end());
            EXPECT_EQ_AND_PRINT_INPUTS(
                minimum_element, min_element_finder,
                sorted_elements);
        }
    }
};

#define DefineTestCase(testName, min_element_finder, sampleArray) namespace {   \
    TEST_F(FindMinInSortedAndRotatedArrayTest, min_element_finder##testName) {  \
        TestAllCasesOf(min_element_finder, sampleArray);                        \
    }                                                       \
}

DefineTestCase(TestOdd, FindMinInSortedAndRotatedArray_Neighbor, VALUES_ODD);
DefineTestCase(TestEven, FindMinInSortedAndRotatedArray_Neighbor, VALUES_EVEN);

DefineTestCase(TestOdd, FindMinInSortedAndRotatedArray, VALUES_ODD);
DefineTestCase(TestEven, FindMinInSortedAndRotatedArray, VALUES_EVEN);
#endif


const ArrayType SAMPLE1 = {2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 1, 2};
const ArrayType SAMPLE2 = {2, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2};
const ArrayType SAMPLE3 = {2, 2, 2, 0, 1};


THE_BENCHMARK(FindMinInSortedAndRotatedWithDuplicates, VALUES_EVEN);

SIMPLE_TEST(FindMinInSortedAndRotatedWithDuplicates, TestSAMPLE1, 0, SAMPLE1);
SIMPLE_TEST(FindMinInSortedAndRotatedWithDuplicates, TestSAMPLE2, 0, SAMPLE2);
SIMPLE_TEST(FindMinInSortedAndRotatedWithDuplicates, TestSAMPLE3, 0, SAMPLE3);
SIMPLE_TEST(FindMinInSortedAndRotatedWithDuplicates, TestSAMPLE4, 1, VALUES_EVEN);
SIMPLE_TEST(FindMinInSortedAndRotatedWithDuplicates, TestSAMPLE5, 2, VALUES_ODD);
