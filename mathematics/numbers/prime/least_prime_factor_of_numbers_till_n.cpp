#include "common_header.h"

#include "least_prime_factor_of_numbers_till_n.h"


const std::vector<unsigned> RESULT1 = {0, 1, 2, 3, 2, 5, 2, 7, 2, 3, 2};


THE_BENCHMARK(LeastPrimeFactorOfNumbers, 10);

SIMPLE_TEST(LeastPrimeFactorOfNumbers, TestSample1, RESULT1, 10);
