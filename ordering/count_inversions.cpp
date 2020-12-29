#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Count Inversions in an array | Set 1 (Using Merge Sort)
 *
 * @reference   Count Inversions in an array | Set 1 (Using Merge Sort)
 *              https://www.geeksforgeeks.org/counting-inversions/
 * @reference   https://www.cp.eng.chula.ac.th/~prabhas//teaching/algo/algo2008/count-inv.htm
 * @reference   C/C++ Program to Count Inversions in an array | Set 1 (Using Merge Sort)
 *              https://www.geeksforgeeks.org/c-program-for-count-inversions-in-an-array-set-1-using-merge-sort/
 *
 * Inversion Count for an array indicates – how far (or close) the array is from being sorted.
 * If array is already sorted then inversion count is 0. If array is sorted in reverse order
 * that inversion count is the maximum.
 * Formally speaking, two elements a[i] and a[j] form an inversion if a[i] > a[j] and i < j
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
    unsigned inversion_count = 0u;
    for (; (L_iter != L.cend()) and (R_iter != R.cend()); ++iter) {
        if (*L_iter <= *R_iter) {
            *iter = *L_iter;
            ++L_iter;
        } else {
            *iter = *R_iter;
            ++R_iter;
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
        const auto middle = n >> 1; //floor(n/2)
        const auto middle_begin = begin + middle;
        const auto left_inversion_count = MergeSort(begin, middle);
        const auto right_inversion_count = MergeSort(middle_begin, n - middle);
        return left_inversion_count +
               right_inversion_count +
               Merge(begin, middle_begin, begin + n);
    }
    return 0u;
}

auto CountInversions_MergeSort(ArrayType values) {
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

    if (not values.empty()) {
        auto iter = values.cbegin();
        std::multiset<ArrayType::value_type> visited_nodes = {*iter++};

        for (; iter != values.cend(); ++iter) {
            visited_nodes.emplace(*iter);
            inversion_count +=
                std::distance(visited_nodes.upper_bound(*iter), visited_nodes.cend());
        }
    }

    return inversion_count;
}

}//namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {1};
const ArrayType VALUES3 = {1, 2};
const ArrayType VALUES4 = {2, 3, 1};
const ArrayType VALUES5 = {4, 3, 2, 1};
const ArrayType VALUES6 = {1, 20, 6, 4, 5};
const ArrayType VALUES7 = {2, 4, 1, 3, 5};


SIMPLE_BENCHMARK(CountInversions_MergeSort, Sample1, VALUES6);

SIMPLE_TEST(CountInversions_MergeSort, TestSAMPLE1, 0u, VALUES1);
SIMPLE_TEST(CountInversions_MergeSort, TestSAMPLE2, 0u, VALUES2);
SIMPLE_TEST(CountInversions_MergeSort, TestSAMPLE3, 0u, VALUES3);
SIMPLE_TEST(CountInversions_MergeSort, TestSAMPLE4, 2u, VALUES4);
SIMPLE_TEST(CountInversions_MergeSort, TestSAMPLE5, 6u, VALUES5);
SIMPLE_TEST(CountInversions_MergeSort, TestSAMPLE6, 5u, VALUES6);
SIMPLE_TEST(CountInversions_MergeSort, TestSAMPLE7, 3u, VALUES7);


SIMPLE_BENCHMARK(CountInversions_Multiset, Sample1, VALUES6);

SIMPLE_TEST(CountInversions_Multiset, TestSAMPLE1, 0u, VALUES1);
SIMPLE_TEST(CountInversions_Multiset, TestSAMPLE2, 0u, VALUES2);
SIMPLE_TEST(CountInversions_Multiset, TestSAMPLE3, 0u, VALUES3);
SIMPLE_TEST(CountInversions_Multiset, TestSAMPLE4, 2u, VALUES4);
SIMPLE_TEST(CountInversions_Multiset, TestSAMPLE5, 6u, VALUES5);
SIMPLE_TEST(CountInversions_Multiset, TestSAMPLE6, 5u, VALUES6);
SIMPLE_TEST(CountInversions_Multiset, TestSAMPLE7, 3u, VALUES7);
