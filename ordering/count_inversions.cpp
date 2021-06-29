#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;
using IndexValueArray =
    std::vector<std::pair<ArrayType::size_type, ArrayType::value_type>>;

/** Count Inversions in an array | Set 1 (Using Merge Sort)
 *
 * @reference   Count Inversions in an array | Set 1 (Using Merge Sort)
 *              https://www.geeksforgeeks.org/counting-inversions/
 * @reference   https://www.cp.eng.chula.ac.th/~prabhas//teaching/algo/algo2008/count-inv.htm
 * @reference   C/C++ Program to Count Inversions in an array | Set 1 (Using Merge Sort)
 *              https://www.geeksforgeeks.org/c-program-for-count-inversions-in-an-array-set-1-using-merge-sort/
 *
 * Inversion Count for an array indicates - how far (or close) the array is from being
 * sorted. If array is already sorted then inversion count is 0. If array is sorted in
 * reverse order that inversion count is the maximum. Formally speaking, two elements
 * a[i] and a[j] form an inversion if a[i] > a[j] and i < j.
 *
 * Example:
 * The sequence 2, 4, 1, 3, 5 has three inversions (2, 1), (4, 1), (4, 3).
 *
 * @complexity: O(n*lgn)
 */
auto Merge(const ArrayType::iterator begin, const ArrayType::iterator middle,
           const ArrayType::iterator end) {
    const auto L = ArrayType(begin, middle);
    const auto R = ArrayType(middle, end);

    auto iter = begin;
    auto L_iter = L.cbegin();
    auto R_iter = R.cbegin();
    unsigned inversion_count = 0;
    for (; (L_iter != L.cend()) and (R_iter != R.cend()); ++iter) {
        if (*L_iter <= *R_iter) {
            *iter = *L_iter++;
        } else {
            *iter = *R_iter++;
            inversion_count += (L.cend() - L_iter);
        }
    }

    while (L_iter != L.cend()) {
        *iter++ = *L_iter++;
    }
    while (R_iter != R.cend()) {
        *iter++ = *R_iter++;
    }
    return inversion_count;
}

unsigned MergeSort(const ArrayType::iterator begin, const ArrayType::size_type n) {
    if (n > 1) {
        const auto middle = n >> 1;
        const auto middle_begin = begin + middle;
        const auto left_inversion_count = MergeSort(begin, middle);
        const auto right_inversion_count = MergeSort(middle_begin, n - middle);
        return left_inversion_count +
               right_inversion_count +
               Merge(begin, middle_begin, begin + n);
    }
    return 0;
}

inline auto CountInversions_MergeSort(ArrayType values) {
    return MergeSort(values.begin(), values.size());
}


/**
 * @reference   Count inversions in an array | Set 2 (Using Self-Balancing BST)
 *              https://www.geeksforgeeks.org/count-inversions-in-an-array-set-2-using-self-balancing-bst/
 * @reference   Counting Inversions using Set in C++ STL
 *              https://www.geeksforgeeks.org/counting-inversions-using-set-in-c-stl/
 */
auto CountInversions_Multiset(const ArrayType &values) {
    unsigned inversion_count = 0;

    std::multiset<ArrayType::value_type> counters;
    for (int i = values.size() - 1; i >= 0; --i) {
        counters.insert(values[i]);
        const auto lower = counters.lower_bound(values[i]);
        inversion_count += std::distance(counters.cbegin(), lower);
    }

    return inversion_count;
}


/**
 * @reference   Count of Smaller Numbers After Self
 *              https://leetcode.com/problems/count-of-smaller-numbers-after-self/
 * @reference   Count smaller elements on right side using Set in C++ STL
 *              https://www.geeksforgeeks.org/count-smaller-elements-right-side-using-set-c-stl/
 *
 * You are given an integer array nums and you have to return a new counts array. The
 * counts array has the property where counts[i] is the number of smaller elements to
 * the right of nums[i].
 */


/**
 * @reference   Count smaller elements on right side
 *              https://www.geeksforgeeks.org/count-smaller-elements-on-right-side/
 *
 * @hint    A Self Balancing Binary Search Tree (AVL, Red Black,.. etc) can be used to
 *  get this solution in O(nLogn) time complexity. See Method 2 for more details.
 */
struct Node {
    using PointerType = std::unique_ptr<Node>;

    int value;
    int count_smaller;
    PointerType left;
    PointerType right;

    Node(const int v, const int c): value(v), count_smaller(c) {
    }
};

auto insert(Node::PointerType &root, const int value, const int count_smaller) {
    if (not root) {
        root = std::make_unique<Node>(value, 0);
        return count_smaller;
    }
    if (root->value < value) {
        return root->count_smaller + insert(root->right, value, count_smaller + 1);
    } else {
        root->count_smaller++;
        return insert(root->left, value, count_smaller);
    }
}

auto CountInversionsArray_BST(const ArrayType &nums) {
    Node::PointerType root;
    ArrayType results(nums.size(), 0);
    for (int i = nums.size() - 1; i >= 0; --i) {
        results[i] = insert(root, nums[i], 0);
    }

    return results;
}


/**
 * @reference   Count of smaller elements on right side of each element in an Array using Merge sort
 *              https://www.geeksforgeeks.org/count-of-smaller-elements-on-right-side-of-each-element-in-an-array-using-merge-sort/
 */
void merge(IndexValueArray &index_value_array,
           const int start, const int mid, const int last,
           ArrayType &results) {
    IndexValueArray left(index_value_array.cbegin() + start,
                         index_value_array.cbegin() + mid + 1);
    IndexValueArray right(index_value_array.cbegin() + mid + 1,
                          index_value_array.cbegin() + last + 1);

    std::size_t first_i = 0, right_i = 0, k = start;
    int offset = 0;
    while (first_i < left.size() and right_i < right.size()) {
        const auto [first_index, first_value] = left[first_i];
        const auto [right_index, right_value] = right[right_i];
        if (first_value <= right_value) {
            results[first_index] += offset;
            index_value_array[k++] = left[first_i++];
        } else {
            ++offset;
            index_value_array[k++] = right[right_i++];
        }
    }

    while (first_i < left.size()) {
        results[left[first_i].first] += offset;
        index_value_array[k++] = left[first_i++];
    }

    while (right_i < right.size()) {
        index_value_array[k++] = right[right_i++];
    }
}

inline void
CountInversionsArray_MergeSort(IndexValueArray &index_value_array,
                               const int low, const int high,
                               ArrayType &results) {
    if (low >= high) {
        return;
    }

    const int mid = (low + high) / 2;
    CountInversionsArray_MergeSort(index_value_array, low, mid, results);
    CountInversionsArray_MergeSort(index_value_array, mid + 1, high, results);
    merge(index_value_array, low, mid, high, results);
}

auto CountInversionsArray_MergeSort(const ArrayType &nums) {
    IndexValueArray index_value_array;
    for (std::size_t i = 0; i < nums.size(); ++i) {
        index_value_array.emplace_back(i, nums[i]);
    }

    ArrayType results(nums.size(), 0);
    CountInversionsArray_MergeSort(index_value_array, 0, nums.size() - 1, results);

    return results;
}

}//namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {1};
const ArrayType VALUES3 = {1, 2};
const ArrayType VALUES4 = {2, 3, 1};
const ArrayType VALUES5 = {4, 3, 2, 1};
const ArrayType VALUES6 = {1, 20, 6, 4, 5};
const ArrayType VALUES7 = {2, 4, 1, 3, 5};
const ArrayType VALUES8 = {12, 1, 2, 3, 0, 11, 4};
const ArrayType VALUES9 = {5, 4, 3, 2, 1};


THE_BENCHMARK(CountInversions_MergeSort, VALUES6);

SIMPLE_TEST(CountInversions_MergeSort, TestSAMPLE1, 0, VALUES1);
SIMPLE_TEST(CountInversions_MergeSort, TestSAMPLE2, 0, VALUES2);
SIMPLE_TEST(CountInversions_MergeSort, TestSAMPLE3, 0, VALUES3);
SIMPLE_TEST(CountInversions_MergeSort, TestSAMPLE4, 2, VALUES4);
SIMPLE_TEST(CountInversions_MergeSort, TestSAMPLE5, 6, VALUES5);
SIMPLE_TEST(CountInversions_MergeSort, TestSAMPLE6, 5, VALUES6);
SIMPLE_TEST(CountInversions_MergeSort, TestSAMPLE7, 3, VALUES7);


THE_BENCHMARK(CountInversions_Multiset, VALUES6);

SIMPLE_TEST(CountInversions_Multiset, TestSAMPLE1, 0, VALUES1);
SIMPLE_TEST(CountInversions_Multiset, TestSAMPLE2, 0, VALUES2);
SIMPLE_TEST(CountInversions_Multiset, TestSAMPLE3, 0, VALUES3);
SIMPLE_TEST(CountInversions_Multiset, TestSAMPLE4, 2, VALUES4);
SIMPLE_TEST(CountInversions_Multiset, TestSAMPLE5, 6, VALUES5);
SIMPLE_TEST(CountInversions_Multiset, TestSAMPLE6, 5, VALUES6);
SIMPLE_TEST(CountInversions_Multiset, TestSAMPLE7, 3, VALUES7);
SIMPLE_TEST(CountInversions_Multiset, TestSAMPLE8, 10, VALUES8);
SIMPLE_TEST(CountInversions_Multiset, TestSAMPLE9, 10, VALUES9);


const ArrayType EXPECTED8 = {6, 1, 1, 1, 0, 1, 0};
const ArrayType EXPECTED9 = {4, 3, 2, 1, 0};

const ArrayType VALUES10 = {1, 2, 3, 4, 5};
const ArrayType EXPECTED10 = {0, 0, 0, 0, 0};


THE_BENCHMARK(CountInversionsArray_BST, VALUES6);

SIMPLE_TEST(CountInversionsArray_BST, TestSAMPLE8, EXPECTED8, VALUES8);
SIMPLE_TEST(CountInversionsArray_BST, TestSAMPLE9, EXPECTED9, VALUES9);
SIMPLE_TEST(CountInversionsArray_BST, TestSAMPLE10, EXPECTED10, VALUES10);


THE_BENCHMARK(CountInversionsArray_MergeSort, VALUES6);

SIMPLE_TEST(CountInversionsArray_MergeSort, TestSAMPLE8, EXPECTED8, VALUES8);
SIMPLE_TEST(CountInversionsArray_MergeSort, TestSAMPLE9, EXPECTED9, VALUES9);
SIMPLE_TEST(CountInversionsArray_MergeSort, TestSAMPLE10, EXPECTED10, VALUES10);
