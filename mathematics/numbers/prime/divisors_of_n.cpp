#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Find all divisors of a natural number
 *
 * @reference   Find all divisors of a natural number | Set 1
 *              https://www.geeksforgeeks.org/find-divisors-natural-number-set-1/
 * @reference   Find all divisors of a natural number | Set 2
 *              https://www.geeksforgeeks.org/find-all-divisors-of-a-natural-number-set-2/
 * @reference   Program to find all Factors of a Number using recursion
 *              https://www.geeksforgeeks.org/program-to-find-all-factors-of-a-number-using-recursion/
 * @reference   Program to print factors of a number in pairs
 *              https://www.geeksforgeeks.org/program-to-print-factors-of-a-number-in-pairs/
 */
auto DivisorsOfN_Pairs(const int N) {
    ArrayType divisors;
    for (int i = 1; i <= sqrt(N); ++i) {
        if (N % i == 0) {
            divisors.push_back(i);

            const auto second = N / i;
            if (second != i) {
                divisors.push_back(second);
            }
        }
    }

    std::sort(divisors.begin(), divisors.end());

    return divisors;
}

}//namespace


const ArrayType EXPECTED1 = {1, 2, 5, 10};
const ArrayType EXPECTED2 = {1, 2, 4, 5, 10, 20, 25, 50, 100};
const ArrayType EXPECTED3 = {1, 5, 25, 125};


SIMPLE_BENCHMARK(DivisorsOfN_Pairs, Sample1, 100);

SIMPLE_TEST(DivisorsOfN_Pairs, TestSAMPLE1, EXPECTED1, 10);
SIMPLE_TEST(DivisorsOfN_Pairs, TestSAMPLE2, EXPECTED2, 100);
SIMPLE_TEST(DivisorsOfN_Pairs, TestSAMPLE3, EXPECTED3, 125);
