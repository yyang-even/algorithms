#include "common_header.h"


namespace {

/** Modular Exponentiation (Power in Modular Arithmetic)
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 31.6.
 * @reference   https://www.geeksforgeeks.org/modular-exponentiation-power-in-modular-arithmetic/
 *
 * Given three numbers x, y and p, compute (x^y) % p.
 * (ab) mod p = ( (a mod p) (b mod p) ) mod p
 *
 * @reference   Modular exponentiation (Recursive)
 *              https://www.geeksforgeeks.org/modular-exponentiation-recursive/
 *
 * Now why do "% c" after exponentiation, because ab will be really large even for
 * relatively small values of a, b and that is a problem because the data type of the
 * language that we try to code the problem, will most probably not let us store such
 * a large number.
 *
 * If we have to return the mod of a negative number x whose absolute value is less
 * than y: then (x + y) % y will do the trick
 */
constexpr inline auto
ModularExponentiation(const int x, const unsigned y, const int p) {
    return static_cast<long>(pow(x, y)) % p;
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 31.6-2.
 */
constexpr auto
ModularExponentiation_Iterative(int x, unsigned y, const int p) {

    long results = 1;
    for (x %= p; y; y >>= 1) {
        if (y & 1) {
            results = (results * x) % p;
        }
        x = (x * x) % p;
    }

    return results;
}


constexpr long
ModularExponentiation_Recursive_Helper(const int x, const unsigned y, const int p) {
    assert(x % p == x);

    if (x == 0) {
        return 0;
    }
    if (y == 0) {
        return 1;
    }

    long result = x;
    if (y % 2 == 0) {
        result = ModularExponentiation_Recursive_Helper(x, y / 2, p);
        result = (result * result) % p;
    } else {
        result = (result * ModularExponentiation_Recursive_Helper(x, y - 1, p) % p) % p;
    }

    return (result + p) % p;
}

constexpr inline auto
ModularExponentiation_Recursive(const int x, const unsigned y, const int p) {
    return ModularExponentiation_Recursive_Helper(x % p, y, p);
}

}//namespace


THE_BENCHMARK(ModularExponentiation, 2, 3, 5);

SIMPLE_TEST(ModularExponentiation, TestSAMPLE1, 3, 2, 3, 5);
SIMPLE_TEST(ModularExponentiation, TestSAMPLE2, 6, 2, 5, 13);


THE_BENCHMARK(ModularExponentiation_Iterative, 2, 3, 5);

SIMPLE_TEST(ModularExponentiation_Iterative, TestSAMPLE1, 3, 2, 3, 5);
SIMPLE_TEST(ModularExponentiation_Iterative, TestSAMPLE2, 6, 2, 5, 13);


THE_BENCHMARK(ModularExponentiation_Recursive, 2, 3, 5);

SIMPLE_TEST(ModularExponentiation_Recursive, TestSAMPLE1, 3, 2, 3, 5);
SIMPLE_TEST(ModularExponentiation_Recursive, TestSAMPLE2, 6, 2, 5, 13);
