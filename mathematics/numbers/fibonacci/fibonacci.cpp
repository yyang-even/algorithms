#include "common_header.h"


namespace {

typedef unsigned InputType;

/** Mathematics of Rabbit Breeding
 *
 * @reference   Jan Gullberg. Mathematics: From the Birth of Numbers. Chapter 8.5.
 *
 * A pair of newly born rabbits, male and female, were placed in a hutch. In two months these rabbits
 * began their breeding cycle and produced one pair of rabbits, one male and one female. The original
 * rabbits and their offspring continued to breed in their manner, that is, the first pair of
 * offspring appearing at the parental age of two months and then a new pair every month thereafter
 * ------ always one male and one female. All rabbits survived the first year.
 *  What then is the total number of pairs of rabbits at the beginning of each month during the first
 *  year?
 *
 *  1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377,...
 */
/**
 * @reference   C/C++ Program for n-th Fibonacci number
 *              https://www.geeksforgeeks.org/c-program-for-n-th-fibonacci-number/
 * @reference   Program to print first n Fibonacci Numbers | Set 1
 *              https://www.geeksforgeeks.org/program-to-print-first-n-fibonacci-numbers/
 *
 * The Fibonacci numbers are the numbers in the following integer sequence.
 *      0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, ……..
 * In mathematical terms, the sequence Fn of Fibonacci numbers is defined by the recurrence relation
 *      Fn = Fn-1 + Fn-2
 * with seed values
 *      F0 = 0 and F1 = 1.
 */
/**
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 7.1.
 *
 * How many ways T(n) are there to completely cover a 2*n rectangle with 2*1 dominoes?
 *
 *      T(n) = F(n+1)
 *
 *  1, 1, 2, 3, 5,...
 */
/**
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 6.6.
 *
 * How many ways a(n) are there for light rays to pass through or be reflected after changing direction
 * n times?
 *
 *      a(n) = F(n+2)
 */
/**
 * @reference   Count number of possible paths up ladder
 *              https://stackoverflow.com/questions/12255193/count-number-of-possible-paths-up-ladder
 *
 * A ladder has n steps, one can climb the ladder using any combination of steps of 1 or steps of 2.
 * How many possible ways are there for one to climb the ladder?
 *
 *      L(n) = F(n+1)
 *
 * 1, 1, 2, 3, 5,...
 */
/**Spans-of-fans
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 7.3.
 *              https://en.wikipedia.org/wiki/Spanning_tree
 *
 * A fan of order n is a graph on the vertices {0, 1,..., n} with 2n-1 edges defined as follows: Vertex
 * 0 is connected by an edge to each of the order n vertices, and vertex k is connected by an edge to
 * vertex k+1, for 1 <= k < n.
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
 * When we take any two successive (one after the other) Fibonacci Numbers,
 * their ratio is very close to the Golden Ratio.
 */
const double GOLDEN_RATIO = 1.61803;
unsigned long Fibonacci_GoldenRatio(const InputType n) {
    if (n < 2) {
        return n;
    } else if (n == 2) {
        return 1;
    } else {
        unsigned long ret = 1;
        for (InputType i = 2; i < n; ++i) {
            ret = ret * GOLDEN_RATIO + 0.5;
        }
        return ret;
    }
}


/**
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 6.6.
 * @reference   Print first n Fibonacci Numbers using direct formula
 *              https://www.geeksforgeeks.org/print-first-n-fibonacci-numbers-using-direct-formula/
 *
 * Note: It may not work perfect due to floating point precision errors.
 */
unsigned long Fibonacci_GoldenRatioClosedForm(const InputType n) {
    constexpr double square_root_of_5 = std::sqrt(5.0);
    constexpr double phi = (1.0 + square_root_of_5) / 2.0;
    constexpr double phi_hat = (1.0 - square_root_of_5) / 2.0;

    return (std::pow(phi, n) - std::pow(phi_hat, n)) / square_root_of_5;
}


/** Sum of Fibonacci Numbers
 *
 * @reference   https://www.geeksforgeeks.org/sum-fibonacci-numbers/
 *
 * Given a number positive number n, find value of f0 + f1 + f2 + … + fn where fi indicates i’th Fibonacci number.
 */
auto SumOfFibonacci(const InputType n) {
    return  Fibonacci_GoldenRatioClosedForm(n + 2) - 1;
}

}//namespace


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr InputType UPPER = HYPOTHETIC_MAX_STACK_DEPTH;


SIMPLE_BENCHMARK(Fibonacci_GoldenRatio, LOWER);
SIMPLE_BENCHMARK(Fibonacci_GoldenRatio, UPPER);
RANDOM_BENCHMARK(Fibonacci_GoldenRatio, LOWER, UPPER);

SIMPLE_TEST(Fibonacci_GoldenRatio, TestLOWER, 0u, LOWER);
SIMPLE_TEST(Fibonacci_GoldenRatio, TestSAMPLE1, 1u, 1);
SIMPLE_TEST(Fibonacci_GoldenRatio, TestSAMPLE2, 144u, 12);


SIMPLE_BENCHMARK(Fibonacci_GoldenRatioClosedForm, LOWER);
SIMPLE_BENCHMARK(Fibonacci_GoldenRatioClosedForm, UPPER);
RANDOM_BENCHMARK(Fibonacci_GoldenRatioClosedForm, LOWER, UPPER);

SIMPLE_TEST(Fibonacci_GoldenRatioClosedForm, TestLOWER, 0u, LOWER);
SIMPLE_TEST(Fibonacci_GoldenRatioClosedForm, TestSAMPLE1, 1u, 1);
SIMPLE_TEST(Fibonacci_GoldenRatioClosedForm, TestSAMPLE2, 144u, 12);


SIMPLE_BENCHMARK(SumOfFibonacci, 4);

SIMPLE_TEST(SumOfFibonacci, TestSAMPLE1, 4u, 3);
SIMPLE_TEST(SumOfFibonacci, TestSAMPLE2, 7u, 4);
