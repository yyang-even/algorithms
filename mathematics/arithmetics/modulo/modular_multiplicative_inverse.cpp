#include "common_header.h"

#include "modular_multiplicative_inverse.h"
#include "mathematics/numbers/prime/is_prime.h"


namespace {

inline constexpr auto
ModularMultiplicativeInverse_FermatsLittleTheorem(const int a, const int m) {
    assert(IsPrime_OptimizedSchoolMethod(m));
    const auto exist = (std::gcd(a, m) == 1);
    return exist ? (static_cast<int>(pow(a, m - 2)) % m) : 0;
}

}//namespace


THE_BENCHMARK(ModularMultiplicativeInverse, 3, 11);

SIMPLE_TEST(ModularMultiplicativeInverse, TestSample1, 4, 3, 11);
SIMPLE_TEST(ModularMultiplicativeInverse, TestSample2, 12, 10, 17);


THE_BENCHMARK(ModularMultiplicativeInverse_FermatsLittleTheorem, 3, 11);

SIMPLE_TEST(ModularMultiplicativeInverse_FermatsLittleTheorem, TestSample1, 4, 3, 11);
