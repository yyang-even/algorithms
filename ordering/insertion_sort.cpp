#include "common_header.h"

namespace {

#include "insertion_sort.h"

using ArrayType = std::vector<int>;

/** Insertion Sort
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 2.1.
 *
 *              http://www.geeksforgeeks.org/insertion-sort/
 *
 * @complexity: O(n^2)
 */
/** Sort 3 numbers
 *
 * @reference   https://www.geeksforgeeks.org/sort-3-numbers/
 *
 * Given three numbers, how to sort them?
 * How to write our own sort function that does minimum comparison and does not use extra variables?
 * The idea is to use insertion sort as insertion sort works best for small arrays.
 */
auto InsertionSort(ArrayType values) {
    return InsertionSort(values, std::greater<ArrayType::value_type> {});
}


/** Recursive Insertion Sort
 *
 * @reference   http://www.geeksforgeeks.org/recursive-insertion-sort/
 *
 * @complexity: O(n^2)
 */
void InsertionSortRecursive(ArrayType &values, const int n) {
    if (n > 1) {
        const auto key_index = n - 1;
        InsertionSortRecursive(values, key_index);
        auto key_value = std::move(values[key_index]);
        auto i = key_index - 1;
        for (; (i >= 0) and (values[i] > key_value); --i) {
            values[i + 1] = std::move(values[i]);
        }
        values[i + 1] = std::move(key_value);
    }
}
auto InsertionSortRecursive(ArrayType values) {
    InsertionSortRecursive(values, values.size());
    return values;
}


/** Binary Insertion Sort
 *
 * @reference   http://www.geeksforgeeks.org/binary-insertion-sort/
 *
 * @complexity: O(n^2)
 */
auto BinarySearch(const int target, const ArrayType::const_iterator begin,
                  const ArrayType::size_type n) {
    if (n > 1) {
        const auto middle = n >> 1;
        const auto middle_value = *(begin + middle);

        if (target == middle_value) {
            return begin + middle + 1;
        } else if (target < middle_value) {
            return BinarySearch(target, begin, middle);
        } else {
            return BinarySearch(target, begin + middle, n - middle);
        }
    } else {
        return (target > *begin) ? begin + 1 : begin;
    }
}
auto BinaryInsertionSort(ArrayType values) {
    for (ArrayType::size_type j = 1; j < values.size(); ++j) {
        auto key_value = std::move(values[j]);
        ArrayType::difference_type i = j - 1;

        const auto location = BinarySearch(key_value, values.cbegin(), j) - values.cbegin();
        while (i >= location) {
            values[i + 1] = std::move(values[i]);
            --i;
        }
        values[i + 1] = std::move(key_value);
    }

    return values;
}

}//namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {1};
const ArrayType VALUES3 = {1, 2};
const ArrayType VALUES4 = {2, 3, 1};
const ArrayType EXPECTED4 = {1, 2, 3};
const ArrayType VALUES5 = {4, 3, 2, 1};
const ArrayType EXPECTED5 = {1, 2, 3, 4};
const ArrayType VALUES6 = {1, 2, 3, 1, 2, 2};
const ArrayType EXPECTED6 = {1, 1, 2, 2, 2, 3};

SIMPLE_TEST(InsertionSort, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(InsertionSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(InsertionSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(InsertionSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(InsertionSort, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(InsertionSort, TestSAMPLE6, EXPECTED6, VALUES6);

SIMPLE_TEST(InsertionSortRecursive, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(InsertionSortRecursive, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(InsertionSortRecursive, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(InsertionSortRecursive, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(InsertionSortRecursive, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(InsertionSortRecursive, TestSAMPLE6, EXPECTED6, VALUES6);

SIMPLE_TEST(BinaryInsertionSort, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(BinaryInsertionSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(BinaryInsertionSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(BinaryInsertionSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(BinaryInsertionSort, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(BinaryInsertionSort, TestSAMPLE6, EXPECTED6, VALUES6);
