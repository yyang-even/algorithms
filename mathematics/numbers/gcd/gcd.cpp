#include "common_header.h"

#include "gcd.h"
#include "mathematics/numbers/binary/count_trailing_zeros.h"


namespace {

/** Stein’s Algorithm for finding GCD
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Problems 31-1.
 * @reference   https://www.geeksforgeeks.org/steins-algorithm-for-finding-gcd/
 *
 * Stein's algorithm or binary GCD algorithm is an algorithm that computes the greatest
 * common divisor of two non-negative integers. Stein's algorithm replaces division with
 * arithmetic shifts, comparisons, and subtraction.
 *
 * @reference   Euclid’s Algorithm when % and / operations are costly
 *              https://www.geeksforgeeks.org/euclids-algorithm-when-and-operations-are-costly/
 */
constexpr auto Gcd_Stein_Iterative(unsigned a, unsigned b) {
    if (a == 0) {
        return b;
    }
    if (b == 0) {
        return a;
    }

    const auto k = CountTrailingZeros_Linear(a | b);
    a >>= k;
    b >>= k;

    while (not(a & 1)) {
        a >>= 1;
    }

    do {
        while (not(b & 1)) {
            b >>= 1;
        }
        if (a > b) {
            std::swap(a, b);
        }

        b -= a;

    } while (b != 0);

    return a << k;
}


constexpr auto Gcd_Stein_Recursive(const unsigned a, const unsigned b) {
    if (a == b) {
        return a;
    }

    if (a == 0) {
        return b;
    }
    if (b == 0) {
        return a;
    }

    if (not(a & 1)) {
        if (b & 1) {
            return Gcd_Stein_Recursive(a >> 1, b);
        } else {
            return Gcd_Stein_Recursive(a >> 1, b >> 1) << 1;
        }
    } else if (not(b & 1)) {
        return Gcd_Stein_Recursive(a, b >> 1);
    }

    return a > b ?
           Gcd_Stein_Recursive((a - b) >> 1, b) :
           Gcd_Stein_Recursive((b - a) >> 1, a);
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 31.2-4.
 */
constexpr unsigned gcd_Euclid_Iterative(unsigned m, unsigned n) {
    if (m > n) {
        std::swap(m, n);
    }

    while (m > 0) {
        const auto original_m = m;
        m = n % m;
        n = original_m;
    }

    return n;
}


/**
 * @reference   Find Greatest Common Divisor of Array
 *              https://leetcode.com/problems/find-greatest-common-divisor-of-array/
 *
 * Given an integer array nums, return the greatest common divisor of the smallest number
 * and largest number in nums.
 * The greatest common divisor of two numbers is the largest positive integer that evenly
 * divides both numbers.
 * 2 <= nums.length <= 1000
 */


/**
 * @reference   Count Operations to Obtain Zero
 *              https://leetcode.com/problems/count-operations-to-obtain-zero/
 *
 * You are given two non-negative integers num1 and num2.
 * In one operation, if num1 >= num2, you must subtract num2 from num1, otherwise subtract
 * num1 from num2.
 *  For example, if num1 = 5 and num2 = 4, subtract num2 from num1, thus obtaining num1 = 1
 *      and num2 = 4. However, if num1 = 4 and num2 = 5, after one operation, num1 = 4 and
 *      num2 = 1.
 * Return the number of operations required to make either num1 = 0 or num2 = 0.
 */
constexpr auto CountOperations(int num1, int num2) {
    if (num1 < num2) {
        std::swap(num1, num2);
    }

    int result = 0;
    while (num2) {
        result += num1 / num2;
        num1 %= num2;
        std::swap(num1, num2);
    }

    return result;
}

}//namespace


SIMPLE_BENCHMARK(gcd, Sample1, 12, 18);
SIMPLE_BENCHMARK(gcd, Sample2, 18, 12);

SIMPLE_TEST(gcd, Test1, 6, 12, 18);
SIMPLE_TEST(gcd, Test2, 6, 18, 12);
SIMPLE_TEST(gcd, Test3, 5, 10, 15);
SIMPLE_TEST(gcd, Test4, 5, 35, 10);
SIMPLE_TEST(gcd, Test5, 1, 31, 2);


SIMPLE_BENCHMARK(gcd_Euclid_Iterative, Sample1, 12, 18);
SIMPLE_BENCHMARK(gcd_Euclid_Iterative, Sample2, 18, 12);

SIMPLE_TEST(gcd_Euclid_Iterative, Test1, 6, 12, 18);
SIMPLE_TEST(gcd_Euclid_Iterative, Test2, 6, 18, 12);
SIMPLE_TEST(gcd_Euclid_Iterative, Test3, 5, 10, 15);
SIMPLE_TEST(gcd_Euclid_Iterative, Test4, 5, 35, 10);
SIMPLE_TEST(gcd_Euclid_Iterative, Test5, 1, 31, 2);


constexpr auto EXPECTED1 = std::make_tuple(10, 1, -1);
constexpr auto EXPECTED2 = std::make_tuple(5, 1, -2);


THE_BENCHMARK(gcd_Extended, 18, 12);

SIMPLE_TEST(gcd_Extended, TestSample1, EXPECTED1, 30, 20);
SIMPLE_TEST(gcd_Extended, TestSample2, EXPECTED2, 35, 15);


THE_BENCHMARK(Gcd_Stein_Iterative, 18, 12);

SIMPLE_TEST(Gcd_Stein_Iterative, Test1, 6, 12, 18);
SIMPLE_TEST(Gcd_Stein_Iterative, Test2, 6, 18, 12);
SIMPLE_TEST(Gcd_Stein_Iterative, Test3, 5, 10, 15);
SIMPLE_TEST(Gcd_Stein_Iterative, Test4, 5, 35, 10);
SIMPLE_TEST(Gcd_Stein_Iterative, Test5, 1, 31, 2);
SIMPLE_TEST(Gcd_Stein_Iterative, Test6, 17, 17, 34);
SIMPLE_TEST(Gcd_Stein_Iterative, Test7, 1, 50, 49);


THE_BENCHMARK(Gcd_Stein_Recursive, 18, 12);

SIMPLE_TEST(Gcd_Stein_Recursive, Test1, 6, 12, 18);
SIMPLE_TEST(Gcd_Stein_Recursive, Test2, 6, 18, 12);
SIMPLE_TEST(Gcd_Stein_Recursive, Test3, 5, 10, 15);
SIMPLE_TEST(Gcd_Stein_Recursive, Test4, 5, 35, 10);
SIMPLE_TEST(Gcd_Stein_Recursive, Test5, 1, 31, 2);
SIMPLE_TEST(Gcd_Stein_Recursive, Test6, 17, 17, 34);
SIMPLE_TEST(Gcd_Stein_Recursive, Test7, 1, 50, 49);


THE_BENCHMARK(CountOperations, 2, 3);

SIMPLE_TEST(CountOperations, TestSample1, 3, 2, 3);
SIMPLE_TEST(CountOperations, TestSample2, 3, 3, 2);
SIMPLE_TEST(CountOperations, TestSample3, 1, 10, 10);
