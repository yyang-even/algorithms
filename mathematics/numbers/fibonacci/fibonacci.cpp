#include "common_header.h"


namespace {

/** Mathematics of Rabbit Breeding
 *
 * @reference   Jan Gullberg. Mathematics: From the Birth of Numbers. Section 8.5.
 *
 * A pair of newly born rabbits, male and female, were placed in a hutch. In two months
 * these rabbits began their breeding cycle and produced one pair of rabbits, one male
 * and one female. The original rabbits and their offspring continued to breed in their
 * manner, that is, the first pair of offspring appearing at the parental age of two
 * months and then a new pair every month thereafter ----- always one male and one
 * female. All rabbits survived the first year. What then is the total number of pairs
 * of rabbits at the beginning of each month during the first year?
 *
 *  1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377,...
 */
/**
 * @reference   C/C++ Program for n-th Fibonacci number
 *              https://www.geeksforgeeks.org/c-program-for-n-th-fibonacci-number/
 * @reference   Program to print first n Fibonacci Numbers | Set 1
 *              https://www.geeksforgeeks.org/program-to-print-first-n-fibonacci-numbers/
 * @reference   Program for Fibonacci numbers
 *              https://www.geeksforgeeks.org/program-for-nth-fibonacci-number/
 * @reference   C++ Program to print Fibonacci Series using Class template
 *              https://www.geeksforgeeks.org/c-program-to-print-fibonacci-series-using-class-template/
 * @reference   TCS Coding Practice Question | Fibonacci Series
 *              https://www.geeksforgeeks.org/tcs-coding-practice-question-fibonacci-series/
 * @reference   C Program for Fibonacci numbers
 *              https://www.geeksforgeeks.org/c-program-for-fibonacci-numbers/
 *
 * The Fibonacci numbers are the numbers in the following integer sequence.
 *      0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, ......
 * In mathematical terms, the sequence Fn of Fibonacci numbers is defined by the
 * recurrence relation
 *      Fn = Fn-1 + Fn-2
 * with seed values
 *      F0 = 0 and F1 = 1.
 *
 * @reference   Time complexity of recursive Fibonacci program
 *              https://www.geeksforgeeks.org/time-complexity-recursive-fibonacci-program/
 */
/**
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Section 7.1.
 *
 * How many ways T(n) are there to completely cover a 2*n rectangle with 2*1 dominoes?
 *
 *      T(n) = F(n+1)
 *
 *  1, 1, 2, 3, 5,...
 */
/**
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Section 6.6.
 *
 * How many ways a(n) are there for light rays to pass through or be reflected after
 * changing direction n times?
 *
 *      a(n) = F(n+2)
 */
/**
 * @reference   Count ways to reach the n’th stair
 *              https://www.geeksforgeeks.org/count-ways-reach-nth-stair/
 * @reference   Count number of possible paths up ladder
 *              https://stackoverflow.com/questions/12255193/count-number-of-possible-paths-up-ladder
 *
 * A ladder has n steps, one can climb the ladder using any combination of steps of 1 or
 * steps of 2. How many possible ways are there for one to climb the ladder?
 *
 *      L(n) = F(n+1)
 *
 * 1, 1, 2, 3, 5,...
 */
/**Spans-of-fans
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Section 7.3.
 *              https://en.wikipedia.org/wiki/Spanning_tree
 *
 * A fan of order n is a graph on the vertices {0, 1,..., n} with 2n-1 edges defined as
 * follows: Vertex 0 is connected by an edge to each of the order n vertices, and vertex
 * k is connected by an edge to vertex k+1, for 1 <= k < n.
 * How many spanning trees f(n) are in such a graph?
 *
 * f(n) = f(n-1) + f(n-1) + f(n-2) + f(n-3) +...+ f(1) + 1
 *
 *      f(n) = F(2n), for n >= 0
 *
 * 0, 1, 3, 8,...
 */

/** Golden Ratio
 *
 * @reference   Nature, The Golden Ratio, and Fibonacci too ...
 *              https://www.mathsisfun.com/numbers/nature-golden-ratio-fibonacci.html
 * @reference   The Magic of Fibonacci Numbers
 *              https://www.geeksforgeeks.org/magic-fibonacci-numbers/
 *
 * When we take any two successive (one after the other) Fibonacci Numbers, their ratio
 * is very close to the Golden Ratio.
 */
const double GOLDEN_RATIO = 1.61803;

constexpr inline unsigned long NthFibonacci_GoldenRatio(const unsigned n) {
    if (n < 2) {
        return n;
    } else if (n == 2) {
        return 1;
    } else {
        unsigned long ret = 1;
        for (unsigned i = 2; i < n; ++i) {
            ret = ret * GOLDEN_RATIO + 0.5;
        }
        return ret;
    }
}


/**
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Section 6.6.
 * @reference   Print first n Fibonacci Numbers using direct formula
 *              https://www.geeksforgeeks.org/print-first-n-fibonacci-numbers-using-direct-formula/
 *
 * @note    It may not work perfect due to floating point precision errors.
 */
inline unsigned long NthFibonacci_GoldenRatioClosedForm(const unsigned n) {
    static constexpr double square_root_of_5 = std::sqrt(5.0);
    static constexpr double phi = (1.0 + square_root_of_5) / 2.0;
    static constexpr double phi_hat = (1.0 - square_root_of_5) / 2.0;

    return (std::pow(phi, n) - std::pow(phi_hat, n)) / square_root_of_5;
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 15.1-5.
 * @reference   Overlapping Subproblems Property in Dynamic Programming | DP-1
 *              https://www.geeksforgeeks.org/overlapping-subproblems-property-in-dynamic-programming-dp-1/
 * @reference   Optimal Substructure Property in Dynamic Programming | DP-2
 *              https://www.geeksforgeeks.org/optimal-substructure-property-in-dynamic-programming-dp-2/
 * @reference   How to solve a Dynamic Programming Problem ?
 *              https://www.geeksforgeeks.org/solve-dynamic-programming-problem/
 * @reference   Tabulation vs Memoization
 *              https://www.geeksforgeeks.org/tabulation-vs-memoization/
 */
inline auto NthFibonacci_DP(const unsigned n) {
    std::vector<unsigned> fibonaccis = {0, 1};
    for (unsigned i = 1; i < n; ++i) {
        fibonaccis.push_back(fibonaccis[i] + fibonaccis[i - 1]);
    }

    return fibonaccis[n];
}


constexpr auto NthFibonacci_DP_Optimized(const unsigned n) {
    unsigned f_n_minus_2 = 0, f_n_minus_1 = 1;
    if (n == 0) {
        return f_n_minus_2;
    }

    for (unsigned i = 1; i < n; ++i) {
        const auto f_n = f_n_minus_2 + f_n_minus_1;
        f_n_minus_2 = f_n_minus_1;
        f_n_minus_1 = f_n;
    }

    return f_n_minus_1;
}


/**
 * @reference   Tail Recursion for Fibonacci
 *              https://www.geeksforgeeks.org/tail-recursion-fibonacci/
 */
constexpr auto NthFibonacci_TailRecursion(const unsigned n, const unsigned a = 0,
                                          const unsigned b = 1) {
    if (n == 0) {
        return a;
    }
    if (n == 1) {
        return b;
    }
    return NthFibonacci_TailRecursion(n - 1, b, a + b);
}


/**
 * @reference   Print Fibonacci sequence using 2 variables
 *              https://www.geeksforgeeks.org/print-fibonacci-sequence-using-2-variables/
 */


/** Sum of Fibonacci Numbers
 *
 * @reference   https://www.geeksforgeeks.org/sum-fibonacci-numbers/
 *
 * Given a number positive number n, find value of f0 + f1 + f2 + ... + fn where fi
 * indicates i'th Fibonacci number.
 */
inline auto SumOfFibonacci(const unsigned n) {
    return  NthFibonacci_GoldenRatioClosedForm(n + 2) - 1;
}


/**
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 9.1.
 * @reference   Count ways to reach the nth stair using step 1, 2 or 3
 *              https://www.geeksforgeeks.org/count-ways-reach-nth-stair-using-step-1-2-3/
 *
 * A child is running up a staircase with n steps and can hop either 1 step, 2 steps, or
 * 3 steps at a time. Implement a method to count how many possible ways the child can
 * run up the stairs.
 */
constexpr auto FindWaysToRunUpStairs_DP(const unsigned n) {
    unsigned long f_n_minus_3 = 0;
    unsigned long f_n_minus_2 = 1;
    unsigned long f_n_minus_1 = 1;
    if (n < 2) {
        return f_n_minus_1;
    }

    for (unsigned i = 2; i <= n; ++i) {
        const auto f_n = f_n_minus_1 + f_n_minus_2 + f_n_minus_3;
        f_n_minus_3 = f_n_minus_2;
        f_n_minus_2 = f_n_minus_1;
        f_n_minus_1 = f_n;
    }

    return f_n_minus_1;
}

}//namespace


constexpr auto LOWER = std::numeric_limits<unsigned>::min();
constexpr unsigned UPPER = HYPOTHETIC_MAX_STACK_DEPTH;


SIMPLE_BENCHMARK(NthFibonacci_GoldenRatio, Sample1, LOWER);
SIMPLE_BENCHMARK(NthFibonacci_GoldenRatio, Sample2, UPPER);

SIMPLE_TEST(NthFibonacci_GoldenRatio, TestLOWER, 0, LOWER);
SIMPLE_TEST(NthFibonacci_GoldenRatio, TestSAMPLE1, 1, 1);
SIMPLE_TEST(NthFibonacci_GoldenRatio, TestSAMPLE2, 144, 12);


SIMPLE_BENCHMARK(NthFibonacci_GoldenRatioClosedForm, Sample1, LOWER);
SIMPLE_BENCHMARK(NthFibonacci_GoldenRatioClosedForm, Sample2, UPPER);

SIMPLE_TEST(NthFibonacci_GoldenRatioClosedForm, TestLOWER, 0, LOWER);
SIMPLE_TEST(NthFibonacci_GoldenRatioClosedForm, TestSAMPLE1, 1, 1);
SIMPLE_TEST(NthFibonacci_GoldenRatioClosedForm, TestSAMPLE2, 144, 12);


SIMPLE_BENCHMARK(NthFibonacci_DP, Sample1, LOWER);
SIMPLE_BENCHMARK(NthFibonacci_DP, Sample2, UPPER);

SIMPLE_TEST(NthFibonacci_DP, TestLOWER, 0, LOWER);
SIMPLE_TEST(NthFibonacci_DP, TestSAMPLE1, 1, 1);
SIMPLE_TEST(NthFibonacci_DP, TestSAMPLE2, 144, 12);


SIMPLE_BENCHMARK(NthFibonacci_DP_Optimized, Sample1, LOWER);
SIMPLE_BENCHMARK(NthFibonacci_DP_Optimized, Sample2, UPPER);

SIMPLE_TEST(NthFibonacci_DP_Optimized, TestLOWER, 0, LOWER);
SIMPLE_TEST(NthFibonacci_DP_Optimized, TestSAMPLE1, 1, 1);
SIMPLE_TEST(NthFibonacci_DP_Optimized, TestSAMPLE2, 144, 12);


SIMPLE_BENCHMARK(NthFibonacci_TailRecursion, Sample1, LOWER);
SIMPLE_BENCHMARK(NthFibonacci_TailRecursion, Sample2, UPPER);

SIMPLE_TEST(NthFibonacci_TailRecursion, TestLOWER, 0, LOWER);
SIMPLE_TEST(NthFibonacci_TailRecursion, TestSAMPLE1, 1, 1);
SIMPLE_TEST(NthFibonacci_TailRecursion, TestSAMPLE2, 144, 12);


THE_BENCHMARK(SumOfFibonacci, 4);

SIMPLE_TEST(SumOfFibonacci, TestSAMPLE1, 4, 3);
SIMPLE_TEST(SumOfFibonacci, TestSAMPLE2, 7, 4);


THE_BENCHMARK(FindWaysToRunUpStairs_DP, 4);

SIMPLE_TEST(FindWaysToRunUpStairs_DP, TestSAMPLE1, 7, 4);
SIMPLE_TEST(FindWaysToRunUpStairs_DP, TestSAMPLE2, 4, 3);
SIMPLE_TEST(FindWaysToRunUpStairs_DP, TestSAMPLE3, 1, 0);
SIMPLE_TEST(FindWaysToRunUpStairs_DP, TestSAMPLE4, 1, 1);
SIMPLE_TEST(FindWaysToRunUpStairs_DP, TestSAMPLE5, 2, 2);
