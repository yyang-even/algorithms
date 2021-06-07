#include "common_header.h"

#include "hash/hash.h"
#include "mathematics/numbers/prime/primes_below_n.h"


namespace {

using ArrayType = std::vector<int>;

/** Absolute Difference between the Sum of Non-Prime numbers and Prime numbers of an Array
 *
 * @reference   https://www.geeksforgeeks.org/absolute-difference-between-the-sum-of-non-prime-numbers-and-prime-numbers-of-an-array/
 *
 * Given an array of positive numbers, the task is to calculate the absolute difference
 * between sum of non-prime numbers and prime numbers. Note: 1 is neither prime nor
 * non-prime.
 */
auto DifferenceBetweenSumOfNonprimesAndPrimes(const ArrayType &numbers) {
    const auto max = *std::max_element(numbers.cbegin(), numbers.cend());
    const auto primes_hash = ToUnorderedSet(PrimesBelowN(max + 1));

    long difference = 0;
    for (const auto n : numbers) {
        if (primes_hash.find(n) != primes_hash.cend()) {
            difference += n;
        } else if (n != 1) {
            difference -= n;
        }
    }

    return abs(difference);
}


/** Absolute difference between the Product of Non-Prime numbers and Prime numbers of an Array
 *
 * @reference   https://www.geeksforgeeks.org/absolute-difference-between-the-product-of-non-prime-numbers-and-prime-numbers-of-an-array/
 *
 * Given an array of positive numbers, the task is to calculate the absolute difference
 * between product of non-prime numbers and prime numbers. Note: 1 is neither prime nor
 * non-prime.
 */
auto DifferenceBetweenProductOfNonprimesAndPrimes(const ArrayType &numbers) {
    const auto max = *std::max_element(numbers.cbegin(), numbers.cend());
    const auto primes_hash = ToUnorderedSet(PrimesBelowN(max + 1));

    long primes_product = 1, nonprimes_product = 1;
    for (const auto n : numbers) {
        if (primes_hash.find(n) != primes_hash.cend()) {
            primes_product *= n;
        } else {
            nonprimes_product *= n;
        }
    }

    return abs(primes_product - nonprimes_product);
}

}//namespace


const ArrayType SAMPLE1 = {1, 3, 5, 10, 15, 7};
const ArrayType SAMPLE2 = {1, 3, 5, 10, 15, 7, 17};


THE_BENCHMARK(DifferenceBetweenSumOfNonprimesAndPrimes, SAMPLE1);

SIMPLE_TEST(DifferenceBetweenSumOfNonprimesAndPrimes, TestSample1, 10, SAMPLE1);
SIMPLE_TEST(DifferenceBetweenSumOfNonprimesAndPrimes, TestSample2, 7, SAMPLE2);


const ArrayType SAMPLE3 = { -1, 3, 5, 10, 15, 7};


THE_BENCHMARK(DifferenceBetweenProductOfNonprimesAndPrimes, SAMPLE1);

SIMPLE_TEST(DifferenceBetweenProductOfNonprimesAndPrimes, TestSample1, 45, SAMPLE1);
SIMPLE_TEST(DifferenceBetweenProductOfNonprimesAndPrimes, TestSample3, 255, SAMPLE3);
