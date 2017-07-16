#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

/** Merge Sort
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 2.3.
 *
 *              http://www.geeksforgeeks.org/merge-sort/
 */
void Merge(const std::vector<int>::iterator begin, const std::vector<int>::iterator middle,
           const std::vector<int>::iterator end) {
    const auto L = std::vector<int>(begin, middle);
    const auto R = std::vector<int>(middle, end);

    auto iter = begin;
    auto L_iter = L.cbegin();
    auto R_iter = R.cbegin();
    for (; (L_iter != L.cend()) and (R_iter != R.cend()); ++iter) {
        if (*L_iter <= *R_iter) {
            *iter = *L_iter;
            ++L_iter;
        } else {
            *iter = *R_iter;
            ++R_iter;
        }
    }

    while (L_iter != L.cend()) {
        *iter++ = *L_iter++;
    }
    while (R_iter != R.cend()) {
        *iter++ = *R_iter++;
    }
}
void MergeSort(const std::vector<int>::iterator begin, const std::vector<int>::size_type n) {
    if (n > 1) {
        const auto middle = n >> 1; //floor(n/2)
        const auto middle_begin = begin + middle;
        MergeSort(begin, middle);
        MergeSort(middle_begin, n - middle);
        Merge(begin, middle_begin, begin + n);
    }
}
auto MergeSort(std::vector<int> values) {
    MergeSort(values.begin(), values.size());
    return values;
}


const std::vector<int> VALUES1 = {};
const std::vector<int> VALUES2 = {1};
const std::vector<int> VALUES3 = {1, 2};
const std::vector<int> VALUES4 = {2, 3, 1};
const std::vector<int> EXPECTED4 = {1, 2, 3};
const std::vector<int> VALUES5 = {4, 3, 2, 1};
const std::vector<int> EXPECTED5 = {1, 2, 3, 4};

SIMPLE_TEST(MergeSort, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(MergeSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(MergeSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(MergeSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(MergeSort, TestSAMPLE5, EXPECTED5, VALUES5);
