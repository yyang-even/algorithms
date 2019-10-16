#include "common_header.h"


namespace {

using ArrayType = std::vector<float>;

/** Bucket Sort
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 8.4.
 * @reference   https://www.geeksforgeeks.org/bucket-sort-2/
 *
 * Bucket sort is mainly useful when input is uniformly distributed over a range.
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 8.4-4.
 *
 * We are given n points in the unit circle, p(i) = (x(i), y(i)), such that 0 < x(i) ^ 2 + y(i) ^ 2 <= 1
 * for i = 1, 2,..., n. Suppose that the points are uniformly distributed; that is, the probability of
 * finding a point in any region of the circle is proportional to the area of the region. Design an
 * algorithm with an average-case running time of O(n) to sort the n points by their distances d(i) =
 * sqrt(x(i) ^ 2 + y(i) ^ 2) from the origin.
 */
auto BucketSort(ArrayType elements) {
    ArrayType buckets[elements.size()] = {};

    for (const auto elem : elements) {
        const ArrayType::size_type index = elem * elements.size();
        buckets[index].push_back(elem);
    }

    auto iter = elements.begin();
    for (auto &b : buckets) {
        std::sort(b.begin(), b.end());
        iter = std::copy(std::make_move_iterator(b.cbegin()), std::make_move_iterator(b.cend()), iter);
    }

    return elements;
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
    iter = std::transform(std::make_move_iterator(negatives.crbegin()),
                          std::make_move_iterator(negatives.crend()), iter, std::negate<ArrayType::value_type> {});
    std::copy(std::make_move_iterator(positives.cbegin()), std::make_move_iterator(positives.cend()),
              iter);

    return elements;
}

}//namespace


const ArrayType VALUES1 = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
const ArrayType EXPECTED1 = {0.1234, 0.3434, 0.565, 0.656, 0.665, 0.897};


SIMPLE_BENCHMARK(BucketSort, VALUES1);

SIMPLE_TEST(BucketSort, TestSAMPLE1, EXPECTED1, VALUES1);


const ArrayType VALUES2 = {-0.897, 0.565, 0.656, -0.1234, 0, 0.3434};
const ArrayType EXPECTED2 = {-0.897, -0.1234, 0, 0.3434, 0.565, 0.656};


SIMPLE_BENCHMARK(BucketSort_Mixed, VALUES2);

SIMPLE_TEST(BucketSort_Mixed, TestSAMPLE1, EXPECTED1, VALUES1);
SIMPLE_TEST(BucketSort_Mixed, TestSAMPLE2, EXPECTED2, VALUES2);
