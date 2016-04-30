#include "common_header.h"

typedef unsigned InputType;
/** The Tower of Hanoi
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 1.1.
 *
 * We are given a tower of eight disks, initially stacked in decreasing size on one of three pegs.
 * The objective is to transfer the entire tower to one of the other pegs, moving only one disk
 * at a time and never moving a larger one onto a smaller.
 */

/**
 * T(0) = 0;
 * T(n) = 2T(n - 1) + 1, for n > 0.
 */
unsigned long HanoiTowerRecursive(const InputType n) {
    if (n == 0) {
        return 0;
    } else {
        return (HanoiTowerRecursive(n - 1) << 1) + 1;
    }
}

/**
 * T(n) = 2^n - 1, for n >= 0.
 */
unsigned long HanoiTowerClosedform(const InputType n) {
    return ((unsigned long)1 << n) - 1;
}

/**
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 1, Exercises 2.
 *
 * Find the shortest sequence of moves that transfers a tower of n disks from the left peg A to the right peg B,
 * if direct moves between A and B are disallowed. (Each move must be to or from the middle peg.
 * As usual, a larger disk must never appear above a smaller one.)
 */

/**
 * T(0) = 0;
 * T(n) = 3T(n - 1) + 2, for n > 0.
 */
unsigned long IndirectHanoiTowerRecursive(const InputType n) {
    if (n == 0) {
        return 0;
    } else {
        return IndirectHanoiTowerRecursive(n - 1) * 3 + 2;
    }
}

/**
 * T(n) = 3^n - 1, for n > 0;
 */
unsigned long IndirectHanoiTowerClosedform(const InputType n) {
    return std::pow(double(3.0), n) - 1;
}

/** Double Hanoi Tower
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 1, Exercises 11.
 *
 * A Double Tower of Hanoi contains 2n disks of n different sizes, two of each size. 
 * As usual, we’re required to move only one disk at a time, without putting a larger one over a smaller one.
 *      a. How many moves does it take to transfer a double tower from one peg to another, 
 *      if disks of equal size are indistinguishable from each other?
 *      b. What if we are required to reproduce the original top-to-bottom order of all 
 *      the equal-size disks in the final arrangement? 
 */

/**
 * A(0) = 0;
 * A(n) = 2A(n - 1) + 2
 */
unsigned long DoubleHanoiTowerARecursive(const InputType n) {
    if (n == 0) {
        return 0;
    } else {
        return (DoubleHanoiTowerARecursive(n - 1) << 1) + 2;
    }
}

/**
 * A(n) = 2^(n+1) - 2
 */
unsigned long DoubleHanoiTowerAClosedform(const InputType n) {
    return (long(1) << (n + 1)) - 2;
}

/**
 * B(n) = 2^(n+2) - 5
 */
unsigned long DoubleHanoiTowerBClosedform(const InputType n) {
    return (long(1) << (n + 2)) - 5;
}

const InputType LOWER = 0;
constexpr InputType UPPER = LONG_BITS_NUM - 1;
const InputType SAMPLE = 8;

SIMPLE_BENCHMARK(HanoiTowerRecursive, LOWER);
SIMPLE_BENCHMARK(HanoiTowerRecursive, UPPER);
SIMPLE_BENCHMARK(HanoiTowerRecursive, SAMPLE);
RANDOM_BENCHMARK(HanoiTowerRecursive, LOWER, UPPER);

SIMPLE_BENCHMARK(HanoiTowerClosedform, LOWER);
SIMPLE_BENCHMARK(HanoiTowerClosedform, UPPER);
SIMPLE_BENCHMARK(HanoiTowerClosedform, SAMPLE);
RANDOM_BENCHMARK(HanoiTowerClosedform, LOWER, UPPER);

SIMPLE_TEST(HanoiTowerRecursive, LOWER, 0);                                         
SIMPLE_TEST(HanoiTowerRecursive, UPPER, ULONG_MAX / 2);                                         
SIMPLE_TEST(HanoiTowerRecursive, SAMPLE, 255);

SIMPLE_TEST(HanoiTowerClosedform, LOWER, 0);                                         
SIMPLE_TEST(HanoiTowerClosedform, UPPER, ULONG_MAX / 2);                                         
SIMPLE_TEST(HanoiTowerClosedform, SAMPLE, 255);

MUTUAL_TEST(HanoiTowerRecursive, HanoiTowerClosedform, LOWER, UPPER);


constexpr InputType IndirectHanoiTowerUPPER = LONG_BITS_NUM / 3;

SIMPLE_BENCHMARK(IndirectHanoiTowerRecursive, LOWER);
SIMPLE_BENCHMARK(IndirectHanoiTowerRecursive, IndirectHanoiTowerUPPER);
SIMPLE_BENCHMARK(IndirectHanoiTowerRecursive, SAMPLE);
RANDOM_BENCHMARK(IndirectHanoiTowerRecursive, LOWER, IndirectHanoiTowerUPPER);

SIMPLE_BENCHMARK(IndirectHanoiTowerClosedform, LOWER);
SIMPLE_BENCHMARK(IndirectHanoiTowerClosedform, IndirectHanoiTowerUPPER);
SIMPLE_BENCHMARK(IndirectHanoiTowerClosedform, SAMPLE);
RANDOM_BENCHMARK(IndirectHanoiTowerClosedform, LOWER, IndirectHanoiTowerUPPER);

SIMPLE_TEST(IndirectHanoiTowerRecursive, LOWER, 0);                                         
SIMPLE_TEST(IndirectHanoiTowerRecursive, IndirectHanoiTowerUPPER, 10460353202);                                         
SIMPLE_TEST(IndirectHanoiTowerRecursive, SAMPLE, 6560);

SIMPLE_TEST(IndirectHanoiTowerClosedform, LOWER, 0);                                         
SIMPLE_TEST(IndirectHanoiTowerClosedform, IndirectHanoiTowerUPPER, 10460353202);                                         
SIMPLE_TEST(IndirectHanoiTowerClosedform, SAMPLE, 6560);

MUTUAL_TEST(IndirectHanoiTowerRecursive, IndirectHanoiTowerClosedform, LOWER, IndirectHanoiTowerUPPER);

const InputType DoubleHanoiTowerUPPER = UPPER - 2;

SIMPLE_BENCHMARK(DoubleHanoiTowerARecursive, LOWER);
SIMPLE_BENCHMARK(DoubleHanoiTowerARecursive, DoubleHanoiTowerUPPER);
SIMPLE_BENCHMARK(DoubleHanoiTowerARecursive, SAMPLE);
RANDOM_BENCHMARK(DoubleHanoiTowerARecursive, LOWER, DoubleHanoiTowerUPPER);

SIMPLE_BENCHMARK(DoubleHanoiTowerAClosedform, LOWER);
SIMPLE_BENCHMARK(DoubleHanoiTowerAClosedform, DoubleHanoiTowerUPPER);
SIMPLE_BENCHMARK(DoubleHanoiTowerAClosedform, SAMPLE);
RANDOM_BENCHMARK(DoubleHanoiTowerAClosedform, LOWER, DoubleHanoiTowerUPPER);

const InputType DoubleHanoiTowerBLOWER = 1;

SIMPLE_BENCHMARK(DoubleHanoiTowerBClosedform, DoubleHanoiTowerBLOWER);
SIMPLE_BENCHMARK(DoubleHanoiTowerBClosedform, DoubleHanoiTowerUPPER);
SIMPLE_BENCHMARK(DoubleHanoiTowerBClosedform, SAMPLE);
RANDOM_BENCHMARK(DoubleHanoiTowerBClosedform, LOWER, DoubleHanoiTowerUPPER);

SIMPLE_TEST(DoubleHanoiTowerARecursive, LOWER, 0);                                         
SIMPLE_TEST(DoubleHanoiTowerARecursive, DoubleHanoiTowerUPPER, 4611686018427387902);                                         
SIMPLE_TEST(DoubleHanoiTowerARecursive, SAMPLE, 510);

SIMPLE_TEST(DoubleHanoiTowerAClosedform, LOWER, 0);                                         
SIMPLE_TEST(DoubleHanoiTowerAClosedform, DoubleHanoiTowerUPPER, 4611686018427387902);                                         
SIMPLE_TEST(DoubleHanoiTowerAClosedform, SAMPLE, 510);

MUTUAL_TEST(DoubleHanoiTowerARecursive, DoubleHanoiTowerAClosedform, LOWER, DoubleHanoiTowerUPPER);

SIMPLE_TEST(DoubleHanoiTowerBClosedform, DoubleHanoiTowerBLOWER, 3);                                         
SIMPLE_TEST(DoubleHanoiTowerBClosedform, DoubleHanoiTowerUPPER, 9223372036854775803);                                         
SIMPLE_TEST(DoubleHanoiTowerBClosedform, SAMPLE, 1019);
