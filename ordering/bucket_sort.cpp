#include "common_header.h"

#include "radix_sort.h"

#include "mathematics/numbers/count_digits_in_integer.h"


namespace {

#include "bucket_sort.h"

using ArrayType = std::vector<float>;

/** Bucket Sort
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 8.4.
 * @reference   https://www.geeksforgeeks.org/bucket-sort-2/
 *
 * Bucket sort is mainly useful when input is uniformly distributed over a range.
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 8.4-4.
 *
 * We are given n points in the unit circle, p(i) = (x(i), y(i)), such that
 * 0 < x(i) ^ 2 + y(i) ^ 2 <= 1 for i = 1, 2,..., n. Suppose that the points are
 * uniformly distributed; that is, the probability of finding a point in any region of
 * the circle is proportional to the area of the region. Design an algorithm with an
 * average-case running time of O(n) to sort the n points by their distances
 * d(i) = sqrt(x(i) ^ 2 + y(i) ^ 2) from the origin.
 *
 * @reference   How to sort a big array with many repetitions?
 *              https://www.geeksforgeeks.org/how-to-sort-a-big-array-with-many-repetitions/
 * @reference   Sort an array which contain 1 to n values
 *              https://www.geeksforgeeks.org/sort-array-contain-1-n-values/
 * @reference   Sort Linked List containing values from 1 to N
 *              https://www.geeksforgeeks.org/sort-linked-list-containing-values-from-1-to-n/
 * @reference   How to sort an Array using STL in C++?
 *              https://www.geeksforgeeks.org/how-to-sort-an-array-using-stl-in-c/
 */
auto BucketSort(ArrayType elements) {
    const auto N = elements.size();
    ArrayType buckets[N] = {};

    for (const auto elem : elements) {
        const ArrayType::size_type index = elem * N;
        buckets[index].push_back(std::move(elem));
    }

    auto iter = elements.begin();
    for (auto &b : buckets) {
        std::sort(b.begin(), b.end());
        iter = std::copy(std::make_move_iterator(b.begin()),
                         std::make_move_iterator(b.end()), iter);
    }

    return elements;
}


inline auto BucketSort_STL(const ArrayType &elements) {
    const auto size = elements.size();
    return BucketSort_STL(std::move(elements), [size](const auto & elem) {
        return elem * size;
    }, ToLambda(std::sort));
}


/** Bucket Sort To Sort an Array with Negative Numbers
 *
 * @reference   https://www.geeksforgeeks.org/bucket-sort-to-sort-an-array-with-negative-numbers/
 */
auto BucketSort_Mixed(ArrayType elements) {
    ArrayType positives, negatives;
    for (const auto elem : elements) {
        if (elem < 0) {
            negatives.push_back(-elem);
        } else {
            positives.push_back(elem);
        }
    }

    positives = BucketSort(std::move(positives));
    negatives = BucketSort(std::move(negatives));

    auto iter = elements.begin();
    iter = std::transform(std::make_move_iterator(negatives.rbegin()),
                          std::make_move_iterator(negatives.rend()), iter,
                          std::negate<ArrayType::value_type> {});
    std::copy(std::make_move_iterator(positives.begin()),
              std::make_move_iterator(positives.end()),
              iter);

    return elements;
}


/** Sorting variable-length items
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Problems 8-3.a.
 *
 * You are given an array of integers, where different integers may have different numbers
 * of digits, but the total number of digits over all the integers in the array is n. Show
 * how to sort the array in O(n) time.
 */
inline auto SortVariableLengthItems_Ints(std::vector<int> elements) {
    return BucketSort_STL(std::move(elements), CountDigits_Iterative,
    [](const auto begin, const auto end) {
        const auto sorted = RadixSort(std::vector<int>(begin, end));
        std::copy(sorted.cbegin(), sorted.cend(), begin);
    });
}

}//namespace


const ArrayType VALUES1 = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
const ArrayType EXPECTED1 = {0.1234, 0.3434, 0.565, 0.656, 0.665, 0.897};


THE_BENCHMARK(BucketSort, VALUES1);

SIMPLE_TEST(BucketSort, TestSAMPLE1, EXPECTED1, VALUES1);


THE_BENCHMARK(BucketSort_STL, VALUES1);

SIMPLE_TEST(BucketSort_STL, TestSAMPLE1, EXPECTED1, VALUES1);


const ArrayType VALUES2 = {-0.897, 0.565, 0.656, -0.1234, 0, 0.3434};
const ArrayType EXPECTED2 = {-0.897, -0.1234, 0, 0.3434, 0.565, 0.656};


THE_BENCHMARK(BucketSort_Mixed, VALUES2);

SIMPLE_TEST(BucketSort_Mixed, TestSAMPLE1, EXPECTED1, VALUES1);
SIMPLE_TEST(BucketSort_Mixed, TestSAMPLE2, EXPECTED2, VALUES2);


const std::vector<int> VALUES3 = {6666, 999, 888, 11, 22, 33, 7, 0};
const std::vector<int> EXPECTED3 = {0, 7, 11, 22, 33, 888, 999, 6666};


THE_BENCHMARK(SortVariableLengthItems_Ints, VALUES3);

SIMPLE_TEST(SortVariableLengthItems_Ints, TestSAMPLE3, EXPECTED3, VALUES3);
