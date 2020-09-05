#include "common_header.h"


using ArrayType = std::vector<unsigned>;

/** Probability of a key K present in array
 *
 * @reference   https://www.geeksforgeeks.org/probability-of-a-key-k-present-in-array/
 *
 * Given an array A[] and size of array is N and one another key K.
 * The task is to find the probability that the Key K present in array.
 */
auto ProbabilityOfKinArray(const ArrayType &A, const ArrayType::value_type K) {
    const double count = std::count(A.cbegin(), A.cend(), K);
    return count / A.size();
}


const ArrayType SAMPLE1 = {4, 7, 2, 0, 8, 7, 5};
const ArrayType SAMPLE2 = {2, 3, 5, 1, 9, 8, 0, 7, 6, 5};


SIMPLE_BENCHMARK(ProbabilityOfKinArray, Sample1, SAMPLE2, 5);

SIMPLE_TEST(ProbabilityOfKinArray, TestSample1, 0, SAMPLE1, 3);
SIMPLE_TEST(ProbabilityOfKinArray, TestSample2, 0.2, SAMPLE2, 5);
