#include "common_header.h"


namespace {

#include "merge_two_sorted_arrays.h"

using ArrayType = std::vector<int>;

/** Merge two sorted arrays
 *
 * @reference   https://www.geeksforgeeks.org/merge-two-sorted-arrays/
 *
 * Given two sorted arrays, the task is to merge them in a sorted manner.
 *
 * @reference   Quickly merging two sorted arrays using std::merge() in C++ STL
 *              https://www.geeksforgeeks.org/quickly-merging-two-sorted-arrays-using-stdmerge-c-stl/
 */
auto MergeTwoSortedArrays(const ArrayType &L, const ArrayType &R) {
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
 * We are given two sorted array. We need to merge these two arrays such that the initial
 * numbers (after complete sorting) are in the first array and the remaining numbers are
 * in the second array. Extra space allowed in O(1).
 */
ArrayType::size_type nextGap(const ArrayType::size_type gap) {
    if (gap <= 1ul) {
        return 0;
    }
    return (gap / 2ul) + (gap % 2ul);
}

auto MergeTwoSortedArrays_InPlace(ArrayType L, ArrayType R) {
    for (auto gap = nextGap(L.size() + R.size()); gap; gap = nextGap(gap)) {
        ArrayType::size_type i = 0ul;
        ArrayType::size_type j = gap > L.size() ? gap - L.size() : 0ul;

        // comparing elements in the first array.
        for (auto i_plus_gap = i + gap; i_plus_gap < L.size(); ++i, ++i_plus_gap)
            if (L[i] > L[i_plus_gap]) {
                std::swap(L[i], L[i_plus_gap]);
            }

        //comparing elements in both arrays.
        for (; i < L.size() and j < R.size(); ++i, ++j)
            if (L[i] > R[j]) {
                std::swap(L[i], R[j]);
            }

        if (j < R.size()) {
            //comparing elements in the second array.
            j = 0ul;
            for (auto j_plus_gap = j + gap; j_plus_gap < R.size(); ++j, ++j_plus_gap) {
                if (R[j] > R[j_plus_gap]) {
                    std::swap(R[j], R[j_plus_gap]);
                }
            }
        }
    }

    return std::pair(L, R);
}


/**
 * @reference   Merge two sorted arrays in constant space using Min Heap
 *              https://www.geeksforgeeks.org/merge-two-sorted-arrays-in-constant-space-using-min-heap/
 */
auto MergeTwoSortedArrays_InPlace_Heap(ArrayType L, ArrayType R) {
    std::make_heap(R.begin(), R.end(), std::greater<ArrayType::value_type> {});
    for (auto &elem : L) {
        if (elem > R.front()) {
            std::pop_heap(R.begin(), R.end(), std::greater<ArrayType::value_type> {});
            std::swap(elem, R.back());
            std::push_heap(R.begin(), R.end(), std::greater<ArrayType::value_type> {});
        }
    }

    std::make_heap(R.begin(), R.end());
    sort_heap(R.begin(), R.end());

    return std::pair(L, R);
}


/** Sorted merge in one array
 *
 * @reference   https://www.geeksforgeeks.org/sorted-merge-one-array/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 11.1.
 *
 * Given two sorted arrays, A and B, where A has a large enough buffer at the end to hold
 * B. Merge B into A in sorted order.
 */
auto MergeTwoSortedArraysToOne(ArrayType L, const ArrayType &R) {
    MergeTwoSortedArrays(L.crbegin() + R.size(), L.crend(), R.crbegin(), R.crend(),
                         L.rbegin(), std::greater<ArrayType::value_type>());
    return L;
}


/** Merge an array of size n into another array of size m+n
 *
 * @reference   https://www.geeksforgeeks.org/merge-one-array-of-size-n-into-another-one-of-size-mn/
 *
 * There are two sorted arrays. First one is of size m+n containing only m elements.
 * Another one is of size n and contains n elements. Merge these two arrays into the
 * first array of size m+n such that the output is sorted.
 */
constexpr ArrayType::value_type NA = 0;
auto MergeTwoSortedArraysToOne_Partition(ArrayType L, const ArrayType &R) {
    std::stable_partition(L.begin(), L.end(), [](const auto v) {
        return v != NA;
    });
    return MergeTwoSortedArraysToOne(L, R);
}

}//namespace


const ArrayType SAMPLE1L = {1, 3, 5, 7};
const ArrayType SAMPLE1R = {2, 4, 6, 8};
const ArrayType EXPECTED1 = {1, 2, 3, 4, 5, 6, 7, 8};

const ArrayType SAMPLE2L = {5, 8, 9};
const ArrayType SAMPLE2R = {4, 7, 8};
const ArrayType EXPECTED2 = {4, 5, 7, 8, 8, 9};


THE_BENCHMARK(MergeTwoSortedArrays, SAMPLE1L, SAMPLE1R);

SIMPLE_TEST(MergeTwoSortedArrays, TestSAMPLE1, EXPECTED1, SAMPLE1L, SAMPLE1R);
SIMPLE_TEST(MergeTwoSortedArrays, TestSAMPLE2, EXPECTED2, SAMPLE2L, SAMPLE2R);


const std::pair<ArrayType, ArrayType> EXPECTED_PAIR1 = {{1, 2, 3, 4}, {5, 6, 7, 8}};
const ArrayType SAMPLE3L = {10};
const ArrayType SAMPLE3R = {2, 3};
const std::pair<ArrayType, ArrayType> EXPECTED_PAIR3 = {{2}, {3, 10}};

const ArrayType SAMPLE4L = {1, 5, 9, 10, 15, 20};
const ArrayType SAMPLE4R = {2, 3, 8, 13};
const std::pair<ArrayType, ArrayType> EXPECTED_PAIR4 = {{1, 2, 3, 5, 8, 9}, {10, 13, 15, 20}};


THE_BENCHMARK(MergeTwoSortedArrays_InPlace, SAMPLE1L, SAMPLE1R);

SIMPLE_TEST(MergeTwoSortedArrays_InPlace, TestSAMPLE1, EXPECTED_PAIR1,
            SAMPLE1L, SAMPLE1R);
SIMPLE_TEST(MergeTwoSortedArrays_InPlace, TestSAMPLE3, EXPECTED_PAIR3,
            SAMPLE3L, SAMPLE3R);
SIMPLE_TEST(MergeTwoSortedArrays_InPlace, TestSAMPLE4, EXPECTED_PAIR4,
            SAMPLE4L, SAMPLE4R);


THE_BENCHMARK(MergeTwoSortedArrays_InPlace_Heap, SAMPLE1L, SAMPLE1R);

SIMPLE_TEST(MergeTwoSortedArrays_InPlace_Heap, TestSAMPLE1, EXPECTED_PAIR1,
            SAMPLE1L, SAMPLE1R);
SIMPLE_TEST(MergeTwoSortedArrays_InPlace_Heap, TestSAMPLE3, EXPECTED_PAIR3,
            SAMPLE3L, SAMPLE3R);
SIMPLE_TEST(MergeTwoSortedArrays_InPlace_Heap, TestSAMPLE4, EXPECTED_PAIR4,
            SAMPLE4L, SAMPLE4R);


const ArrayType SAMPLE1LToOne = {1, 3, 5, 7, NA, NA, NA, NA};
const ArrayType SAMPLE2LToOne = {5, 8, 9, NA, NA, NA};
const ArrayType SAMPLE5LToOne = {10, 12, 13, 14, 18, NA, NA, NA, NA, NA};
const ArrayType SAMPLE5R = {16, 17, 19, 20, 22};
const ArrayType EXPECTED5 = {10, 12, 13, 14, 16, 17, 18, 19, 20, 22};


THE_BENCHMARK(MergeTwoSortedArraysToOne, SAMPLE1LToOne, SAMPLE1R);

SIMPLE_TEST(MergeTwoSortedArraysToOne, TestSAMPLE1, EXPECTED1, SAMPLE1LToOne, SAMPLE1R);
SIMPLE_TEST(MergeTwoSortedArraysToOne, TestSAMPLE2, EXPECTED2, SAMPLE2LToOne, SAMPLE2R);
SIMPLE_TEST(MergeTwoSortedArraysToOne, TestSAMPLE5, EXPECTED5, SAMPLE5LToOne, SAMPLE5R);


const ArrayType SAMPLE1LToOnePartition = {1, NA, 3, NA, 5, NA, 7, NA};
const ArrayType SAMPLE2LToOnePartition = {NA, 5, NA, 8, NA, 9};
const ArrayType SAMPLE5LToOnePartition = {10, 12, NA, NA, 13, 14, 18, NA, NA, NA};


THE_BENCHMARK(MergeTwoSortedArraysToOne_Partition, SAMPLE1LToOnePartition, SAMPLE1R);

SIMPLE_TEST(MergeTwoSortedArraysToOne_Partition, TestSAMPLE1, EXPECTED1,
            SAMPLE1LToOnePartition, SAMPLE1R);
SIMPLE_TEST(MergeTwoSortedArraysToOne_Partition, TestSAMPLE2, EXPECTED2,
            SAMPLE2LToOnePartition, SAMPLE2R);
SIMPLE_TEST(MergeTwoSortedArraysToOne_Partition, TestSAMPLE5, EXPECTED5,
            SAMPLE5LToOnePartition, SAMPLE5R);
