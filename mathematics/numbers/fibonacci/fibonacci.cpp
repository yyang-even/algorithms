#include "common_header.h"

typedef unsigned InputType;

/** Mathematics of Rabbit Breeding
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
 * @reference   Program for Fibonacci numbers
 *              http://www.geeksforgeeks.org/program-for-nth-fibonacci-number/
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
 *              http://stackoverflow.com/questions/12255193/count-number-of-possible-paths-up-ladder
 *
 * A ladder has n steps, one can climb the ladder using any combination of steps of 1 or steps of 2.
 * How many possible ways are there for one to climb the ladder?
 *
 *      L(n) = F(n+1)
 *
 * 1, 1, 2, 3, 5,...
 */

/** Golden Ratio
 * @reference   Nature, The Golden Ratio, and Fibonacci too ...
 *              http://www.mathsisfun.com/numbers/nature-golden-ratio-fibonacci.html
 *
 * When we take any two successive (one after the other) Fibonacci Numbers,
 * their ratio is very close to the Golden Ratio.
 */
const double GOLDEN_RATIO = 1.61803;
unsigned long FibonacciGoldenRatio(const InputType n) {
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
 */
unsigned long FibonacciGoldenRatioClosedForm(const InputType n) {
    constexpr double square_root_of_5 = std::sqrt(5.0);
    constexpr double phi = (1.0 + square_root_of_5) / 2.0;
    constexpr double phi_hat = (1.0 - square_root_of_5) / 2.0;

    return (std::pow(phi, n) - std::pow(phi_hat, n)) / square_root_of_5;
}


const InputType LOWER = 0;
constexpr InputType UPPER = HYPOTHETIC_MAX_STACK_DEPTH;

SIMPLE_BENCHMARK(FibonacciGoldenRatio, LOWER);
SIMPLE_BENCHMARK(FibonacciGoldenRatio, UPPER);
RANDOM_BENCHMARK(FibonacciGoldenRatio, LOWER, UPPER);

SIMPLE_TEST(FibonacciGoldenRatio, TestLOWER, 0, LOWER);
SIMPLE_TEST(FibonacciGoldenRatio, TestSAMPLE1, 1, 1);
SIMPLE_TEST(FibonacciGoldenRatio, TestSAMPLE2, 144, 12);

SIMPLE_BENCHMARK(FibonacciGoldenRatioClosedForm, LOWER);
SIMPLE_BENCHMARK(FibonacciGoldenRatioClosedForm, UPPER);
RANDOM_BENCHMARK(FibonacciGoldenRatioClosedForm, LOWER, UPPER);

SIMPLE_TEST(FibonacciGoldenRatioClosedForm, TestLOWER, 0, LOWER);
SIMPLE_TEST(FibonacciGoldenRatioClosedForm, TestSAMPLE1, 1, 1);
SIMPLE_TEST(FibonacciGoldenRatioClosedForm, TestSAMPLE2, 144, 12);
