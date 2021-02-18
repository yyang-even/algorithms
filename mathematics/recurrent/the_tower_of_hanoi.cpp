#include "common_header.h"


namespace {

typedef unsigned InputType;

/** The Tower of Hanoi
 *
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Section 1.1.
 *
 * We are given a tower of eight disks, initially stacked in decreasing size on one of
 * three pegs. The objective is to transfer the entire tower to one of the other pegs,
 * moving only one disk at a time and never moving a larger one onto a smaller.
 *
 * @reference   Recursive Functions
 *              https://www.geeksforgeeks.org/recursive-functions/
 * @reference   Program for Tower of Hanoi
 *              https://www.geeksforgeeks.org/c-program-for-tower-of-hanoi/
 * @reference   Time Complexity Analysis | Tower Of Hanoi (Recursion)
 *              https://www.geeksforgeeks.org/time-complexity-analysis-tower-hanoi-recursion/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 3.4.
 */

/**
 * T(0) = 0;
 * T(n) = 2T(n - 1) + 1, for n > 0.
 */
unsigned long HanoiTower_Recursive(const InputType n) {
    if (n == 0) {
        return 0;
    } else {
        return (HanoiTower_Recursive(n - 1) << 1) + 1;
    }
}


/**
 * T(n) = 2^n - 1, for n >= 0.
 */
unsigned long HanoiTower_Closedform(const InputType n) {
    return (1ul << n) - 1;
}


/** Iterative Tower of Hanoi
 *
 * @reference   https://www.geeksforgeeks.org/iterative-tower-of-hanoi/
 */


/**
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Section 1, Exercises 2.
 *
 * Find the shortest sequence of moves that transfers a tower of n disks from the left
 * peg A to the right peg B, if direct moves between A and B are disallowed. (Each move
 * must be to or from the middle peg.  As usual, a larger disk must never appear above
 * a smaller one.)
 *
 * @reference   Twisted Tower of Hanoi Problem
 *              https://www.geeksforgeeks.org/twisted-tower-of-hanoi-problem/
 */

/**
 * T(0) = 0;
 * T(n) = 3T(n - 1) + 2, for n > 0.
 */
unsigned long IndirectHanoiTower_Recursive(const InputType n) {
    if (n == 0) {
        return 0;
    } else {
        return IndirectHanoiTower_Recursive(n - 1) * 3 + 2;
    }
}


/**
 * T(n) = 3^n - 1, for n > 0;
 */
unsigned long IndirectHanoiTower_Closedform(const InputType n) {
    return static_cast<unsigned long>(std::pow(double(3.0), n)) - 1;
}


/** Double Hanoi Tower
 *
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Section 1, Exercises 11.
 *
 * A Double Tower of Hanoi contains 2n disks of n different sizes, two of each size.
 * As usual, we're required to move only one disk at a time, without putting a larger
 * one over a smaller one.
 *  a. How many moves does it take to transfer a double tower from one peg to another,
 *  if disks of equal size are indistinguishable from each other?
 *  b. What if we are required to reproduce the original top-to-bottom order of all the
 *  equal-size disks in the final arrangement?
 */

/**
 * A(0) = 0;
 * A(n) = 2A(n - 1) + 2
 */
unsigned long DoubleHanoiTower_A_Recursive(const InputType n) {
    if (n == 0) {
        return 0;
    } else {
        return (DoubleHanoiTower_A_Recursive(n - 1) << 1) + 2;
    }
}


/**
 * A(n) = 2^(n+1) - 2
 */
unsigned long DoubleHanoiTower_A_Closedform(const InputType n) {
    return (1ul << (n + 1)) - 2;
}


/**
 * B(n) = 2^(n+2) - 5
 */
unsigned long DoubleHanoiTower_B_Closedform(const InputType n) {
    return (1ul << (n + 2)) - 5;
}


/** Recursive Tower of Hanoi using 4 pegs / rods
 *
 * @reference   https://www.geeksforgeeks.org/recursive-tower-hanoi-using-4-pegs-rods/
 */
unsigned long HanoiTower_4Rods_Recursive(const InputType n) {
    if (n < 2) {
        return n;
    } else {
        return (HanoiTower_4Rods_Recursive(n - 2) << 1) + 3;
    }
}

}//namespace


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr auto OUTPUT_NUMBER_BITS = BitsNumber<decltype(HanoiTower_Closedform(LOWER))>;
constexpr auto UPPER = OUTPUT_NUMBER_BITS - 1;
constexpr InputType SAMPLE = 8;


SIMPLE_BENCHMARK(HanoiTower_Recursive, Sample1, LOWER);
SIMPLE_BENCHMARK(HanoiTower_Recursive, Sample2, UPPER);
SIMPLE_BENCHMARK(HanoiTower_Recursive, Sample3, SAMPLE);


SIMPLE_BENCHMARK(HanoiTower_Closedform, Sample1, LOWER);
SIMPLE_BENCHMARK(HanoiTower_Closedform, Sample2, UPPER);
SIMPLE_BENCHMARK(HanoiTower_Closedform, Sample3, SAMPLE);


SIMPLE_TEST(HanoiTower_Recursive, TestLOWER, 0u, LOWER);
SIMPLE_TEST(HanoiTower_Recursive, TestUPPER,
            std::numeric_limits<unsigned long>::max() / 2, UPPER);
SIMPLE_TEST(HanoiTower_Recursive, TestSAMPLE, 255u, SAMPLE);


SIMPLE_TEST(HanoiTower_Closedform, TestLOWER, 0u, LOWER);
SIMPLE_TEST(HanoiTower_Closedform, TestUPPER,
            std::numeric_limits<unsigned long>::max() / 2, UPPER);
SIMPLE_TEST(HanoiTower_Closedform, TestSAMPLE, 255u, SAMPLE);

MUTUAL_RANDOM_TEST(HanoiTower_Recursive, HanoiTower_Closedform, LOWER, UPPER);


constexpr InputType IndirectHanoiTowerUPPER = OUTPUT_NUMBER_BITS / 3;


SIMPLE_BENCHMARK(IndirectHanoiTower_Recursive, Sample1, LOWER);
SIMPLE_BENCHMARK(IndirectHanoiTower_Recursive, Sample2, IndirectHanoiTowerUPPER);
SIMPLE_BENCHMARK(IndirectHanoiTower_Recursive, Sample3, SAMPLE);


SIMPLE_BENCHMARK(IndirectHanoiTower_Closedform, Sample1, LOWER);
SIMPLE_BENCHMARK(IndirectHanoiTower_Closedform, Sample2, IndirectHanoiTowerUPPER);
SIMPLE_BENCHMARK(IndirectHanoiTower_Closedform, Sample3, SAMPLE);


SIMPLE_TEST(IndirectHanoiTower_Recursive, TestLOWER, 0u, LOWER);
SIMPLE_TEST(IndirectHanoiTower_Recursive, TestIndirectHanoiTowerUPPER, 10460353202ul,
            IndirectHanoiTowerUPPER);
SIMPLE_TEST(IndirectHanoiTower_Recursive, TestSAMPLE, 6560u, SAMPLE);


SIMPLE_TEST(IndirectHanoiTower_Closedform, TestLOWER, 0u, LOWER);
SIMPLE_TEST(IndirectHanoiTower_Closedform, TestIndirectHanoiTowerUPPER, 10460353202ul,
            IndirectHanoiTowerUPPER);
SIMPLE_TEST(IndirectHanoiTower_Closedform, TestSAMPLE, 6560u, SAMPLE);

MUTUAL_RANDOM_TEST(IndirectHanoiTower_Recursive, IndirectHanoiTower_Closedform, LOWER,
                   IndirectHanoiTowerUPPER);


const InputType DoubleHanoiTowerUPPER = UPPER - 2;


SIMPLE_BENCHMARK(DoubleHanoiTower_A_Recursive, Sample1, LOWER);
SIMPLE_BENCHMARK(DoubleHanoiTower_A_Recursive, Sample2, DoubleHanoiTowerUPPER);
SIMPLE_BENCHMARK(DoubleHanoiTower_A_Recursive, Sample3, SAMPLE);


SIMPLE_BENCHMARK(DoubleHanoiTower_A_Closedform, Sample1, LOWER);
SIMPLE_BENCHMARK(DoubleHanoiTower_A_Closedform, Sample2, DoubleHanoiTowerUPPER);
SIMPLE_BENCHMARK(DoubleHanoiTower_A_Closedform, Sample3, SAMPLE);


const InputType DoubleHanoiTowerBLOWER = 1;


SIMPLE_BENCHMARK(DoubleHanoiTower_B_Closedform, Sample1, DoubleHanoiTowerBLOWER);
SIMPLE_BENCHMARK(DoubleHanoiTower_B_Closedform, Sample2, DoubleHanoiTowerUPPER);
SIMPLE_BENCHMARK(DoubleHanoiTower_B_Closedform, Sample3, SAMPLE);


SIMPLE_TEST(DoubleHanoiTower_A_Recursive, TestLOWER, 0u, LOWER);
SIMPLE_TEST(DoubleHanoiTower_A_Recursive, TestDoubleHanoiTowerUPPER,
            4611686018427387902ull, DoubleHanoiTowerUPPER);
SIMPLE_TEST(DoubleHanoiTower_A_Recursive, TestSAMPLE, 510u, SAMPLE);


SIMPLE_TEST(DoubleHanoiTower_A_Closedform, TestLOWER, 0u, LOWER);
SIMPLE_TEST(DoubleHanoiTower_A_Closedform, TestDoubleHanoiTowerUPPER,
            4611686018427387902ull, DoubleHanoiTowerUPPER);
SIMPLE_TEST(DoubleHanoiTower_A_Closedform, TestSAMPLE, 510u, SAMPLE);

MUTUAL_RANDOM_TEST(DoubleHanoiTower_A_Recursive, DoubleHanoiTower_A_Closedform,
                   LOWER, DoubleHanoiTowerUPPER);


SIMPLE_TEST(DoubleHanoiTower_B_Closedform, TestDoubleHanoiTowerBLOWER, 3,
            DoubleHanoiTowerBLOWER);
SIMPLE_TEST(DoubleHanoiTower_B_Closedform, TestDoubleHanoiTowerUPPER,
            9223372036854775803ull, DoubleHanoiTowerUPPER);
SIMPLE_TEST(DoubleHanoiTower_B_Closedform, TestSAMPLE, 1019, SAMPLE);


SIMPLE_BENCHMARK(HanoiTower_4Rods_Recursive, Sample1, 3);

SIMPLE_TEST(HanoiTower_4Rods_Recursive, TestSample1, 5u, 3);
SIMPLE_TEST(HanoiTower_4Rods_Recursive, TestSample2, 9u, 4);
SIMPLE_TEST(HanoiTower_4Rods_Recursive, TestSample3, 13u, 5);
