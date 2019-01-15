#include "common_header.h"

#include "prime_factors_of_n.h"

#include "least_prime_factor_of_numbers_till_n.h"

typedef unsigned InputType;


std::string PrintAllPrimeFactors(const InputType N) {
    std::string output;
    const auto prime_factors = PrimeFactorsOf(N);
    for (const auto factor : prime_factors) {
        output.append(std::to_string(factor));
    }
    return output;
}


auto PrimeFactorsOfNSieve(unsigned N) {
    const auto smallest_prime_factors = LeastPrimeFactorOfNumbers(N);

    std::vector<unsigned> output;
    while (N != 1) {
        output.push_back(smallest_prime_factors[N]);
        N /= smallest_prime_factors[N];
    }

    return output;
}


constexpr InputType LOWER = 1;
constexpr InputType SAMPLE1 = 12;
constexpr InputType SAMPLE2 = 315;

SIMPLE_BENCHMARK(PrintAllPrimeFactors, LOWER);
SIMPLE_BENCHMARK(PrintAllPrimeFactors, SAMPLE1);
RANDOM_BENCHMARK(PrintAllPrimeFactors, LOWER, std::numeric_limits<InputType>::max());

SIMPLE_TEST(PrintAllPrimeFactors, TestLOWER, "", LOWER);
SIMPLE_TEST(PrintAllPrimeFactors, TestSAMPLE1, "223", SAMPLE1);
SIMPLE_TEST(PrintAllPrimeFactors, TestSAMPLE2, "3357", SAMPLE2);
SIMPLE_TEST(PrintAllPrimeFactors, TestSAMPLE3, "11", 11);
SIMPLE_TEST(PrintAllPrimeFactors, TestSAMPLE4, "311", 33);


const std::vector<unsigned> EXPECTED2 = {3, 5, 7};

SIMPLE_BENCHMARK(UniquePrimeFactorsOf, SAMPLE2);

SIMPLE_TEST(UniquePrimeFactorsOf, TestSAMPLE2, EXPECTED2, SAMPLE2);


const std::vector<unsigned> EXPECTED3 = {3, 3, 5, 7};
const std::vector<unsigned> EXPECTED4 = {2, 3, 13, 157};

SIMPLE_BENCHMARK(PrimeFactorsOfNSieve, 12246);

SIMPLE_TEST(PrimeFactorsOfNSieve, TestSAMPLE3, EXPECTED3, SAMPLE2);
SIMPLE_TEST(PrimeFactorsOfNSieve, TestSAMPLE4, EXPECTED4, 12246);
