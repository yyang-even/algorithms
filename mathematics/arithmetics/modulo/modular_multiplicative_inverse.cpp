#include "common_header.h"

#include "modular_multiplicative_inverse.h"


auto ModularMultiplicativeInverseFermatsLittleTheorem(const int a, const int m) {
    //assert(IsPrime(m));
    const auto exist = (std::gcd(a, m) == 1);
    return exist ? (static_cast<int>(pow(a, m - 2)) % m) : 0;
}


SIMPLE_BENCHMARK(ModularMultiplicativeInverse, 3, 11);

SIMPLE_TEST(ModularMultiplicativeInverse, TestSample1, 4, 3, 11);
SIMPLE_TEST(ModularMultiplicativeInverse, TestSample2, 12, 10, 17);


SIMPLE_BENCHMARK(ModularMultiplicativeInverseFermatsLittleTheorem, 3, 11);

SIMPLE_TEST(ModularMultiplicativeInverseFermatsLittleTheorem, TestSample1, 4, 3, 11);
