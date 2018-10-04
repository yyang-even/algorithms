#include "common_header.h"

#include "merge_two_sorted_arrays.h"

using ArrayType = std::vector<int>;

/** Merge two sorted arrays
 *
 * @reference   https://www.geeksforgeeks.org/merge-two-sorted-arrays/
 *
 * Given two sorted arrays, the task is to merge them in a sorted manner.
 */
auto MergeTwoSortedArrays(const ArrayType &L, const ArrayType &R){
    ArrayType output(L.size() + R.size(), 0);
    MergeTwoSortedArrays(L, R, output.begin());

    return output;
}


/** Efficiently merging two sorted arrays with O(1) extra space
 *
 * @reference   https://www.geeksforgeeks.org/efficiently-merging-two-sorted-arrays-with-o1-extra-space/
 * @reference   Merge two sorted arrays with O(1) extra space
 *              https://www.geeksforgeeks.org/merge-two-sorted-arrays-o1-extra-space/
 *
 * We are given two sorted array. We need to merge these two arrays such that the
 * initial numbers (after complete sorting) are in the first array and the
 * remaining numbers are in the second array. Extra space allowed in O(1).
 */
ArrayType::size_type nextGap(const ArrayType::size_type gap) 
{ 
    if (gap <= 1ul) 
        return 0; 
    return (gap / 2ul) + (gap % 2ul); 
} 
auto MergeTwoSortedArraysInPlace(ArrayType L, ArrayType R){
    for(auto gap = nextGap(L.size() + R.size()); gap; gap = nextGap(gap)){
        ArrayType::size_type i = 0ul;
        ArrayType::size_type j = gap > L.size() ? gap - L.size() : 0ul;

        // comparing elements in the first array. 
        for (auto i_plus_gap = i + gap; i_plus_gap < L.size(); ++i, ++i_plus_gap) 
            if (L[i] > L[i_plus_gap]) 
                std::swap(L[i], L[i_plus_gap]); 

        //comparing elements in both arrays. 
        for (; i < L.size() and j < R.size(); ++i, ++j) 
            if (L[i] > R[j]) 
                std::swap(L[i], R[j]); 

        if(j < R.size()){
            //comparing elements in the second array.
            j = 0ul;
            for(auto j_plus_gap = j + gap; j_plus_gap < R.size(); ++j, ++j_plus_gap){
                if (R[j] > R[j_plus_gap]) 
                    std::swap(R[j], R[j_plus_gap]); 
            }
        }
    }

    return std::make_pair(L, R);
}


const ArrayType SAMPLE1L = {1, 3, 5, 7};
const ArrayType SAMPLE1R = {2, 4, 6, 8};
const ArrayType EXPECTED1 = {1, 2, 3, 4, 5, 6, 7, 8};

const ArrayType SAMPLE2L = {5, 8, 9};
const ArrayType SAMPLE2R = {4, 7, 8};
const ArrayType EXPECTED2 = {4, 5, 7, 8, 8, 9};

SIMPLE_BENCHMARK(MergeTwoSortedArrays, SAMPLE1L, SAMPLE1R);

SIMPLE_TEST(MergeTwoSortedArrays, TestSAMPLE1, EXPECTED1, SAMPLE1L, SAMPLE1R);
SIMPLE_TEST(MergeTwoSortedArrays, TestSAMPLE2, EXPECTED2, SAMPLE2L, SAMPLE2R);


const auto EXPECTED_PAIR1 = std::make_pair(ArrayType{1,2,3,4}, ArrayType{5,6,7,8});
const ArrayType SAMPLE3L = {10};
const ArrayType SAMPLE3R = {2, 3};
const auto EXPECTED_PAIR3 = std::make_pair(ArrayType{2}, ArrayType{3, 10});
const ArrayType SAMPLE4L = {1, 5, 9, 10, 15, 20};
const ArrayType SAMPLE4R = {2, 3, 8, 13};
const auto EXPECTED_PAIR4 = std::make_pair(ArrayType{1, 2, 3, 5, 8, 9}, ArrayType{10, 13, 15, 20});

SIMPLE_BENCHMARK(MergeTwoSortedArraysInPlace, SAMPLE1L, SAMPLE1R);

SIMPLE_TEST(MergeTwoSortedArraysInPlace, TestSAMPLE1, EXPECTED_PAIR1, SAMPLE1L, SAMPLE1R);
SIMPLE_TEST(MergeTwoSortedArraysInPlace, TestSAMPLE3, EXPECTED_PAIR3, SAMPLE3L, SAMPLE3R);
SIMPLE_TEST(MergeTwoSortedArraysInPlace, TestSAMPLE4, EXPECTED_PAIR4, SAMPLE4L, SAMPLE4R);
