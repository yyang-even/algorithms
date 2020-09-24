#include "common_header.h"

#include "mathematics/numbers/gcd/gcd.h"


namespace {

using ArrayType = std::vector<int>;

/** Modular Linear Equations
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 31.4.
 *
 * ax = b (mod n)
 */
auto SolutionsToModularLinearEquation(const int a, const int b, const int n) {
    int x = 0;
    int y = 0;
    const auto gcd = gcd_Extended(a, n, &x, &y);

    ArrayType results;
    if (b % gcd == 0) {
        const auto x0 = ((x * (b / gcd) % n) + n) % n;
        for (int i = 0; i < gcd; ++i) {
            results.push_back((x0 + i * (n / gcd)) % n);
        }
    }

    return results;
}

}//namespace


const ArrayType EXPECTED1 = {95, 45};
const ArrayType EXPECTED2 = {6, 16, 26, 36, 46};


THE_BENCHMARK(SolutionsToModularLinearEquation, 14, 30, 100);

SIMPLE_TEST(SolutionsToModularLinearEquation, TestSample1, EXPECTED1, 14, 30, 100);
SIMPLE_TEST(SolutionsToModularLinearEquation, TestSample2, EXPECTED2, 35, 10, 50);
