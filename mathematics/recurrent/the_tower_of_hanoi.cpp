#include "common_header.h"


namespace {

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
    return (long(1) << (n + 1)) - 2;
}


/**
 * B(n) = 2^(n+2) - 5
 */
unsigned long DoubleHanoiTower_B_Closedform(const InputType n) {
    return (long(1) << (n + 2)) - 5;
}

}//namespace


constexpr auto LOWER = std::numeric_limits<InputType>::min();
constexpr InputType UPPER = LONG_BITS_NUM - 1;
constexpr InputType SAMPLE = 8;


SIMPLE_BENCHMARK(HanoiTower_Recursive, LOWER);
SIMPLE_BENCHMARK(HanoiTower_Recursive, UPPER);
SIMPLE_BENCHMARK(HanoiTower_Recursive, SAMPLE);
RANDOM_BENCHMARK(HanoiTower_Recursive, LOWER, UPPER);


SIMPLE_BENCHMARK(HanoiTower_Closedform, LOWER);
SIMPLE_BENCHMARK(HanoiTower_Closedform, UPPER);
SIMPLE_BENCHMARK(HanoiTower_Closedform, SAMPLE);
RANDOM_BENCHMARK(HanoiTower_Closedform, LOWER, UPPER);


SIMPLE_TEST(HanoiTower_Recursive, TestLOWER, 0u, LOWER);
SIMPLE_TEST(HanoiTower_Recursive, TestUPPER, std::numeric_limits<unsigned long>::max() / 2, UPPER);
SIMPLE_TEST(HanoiTower_Recursive, TestSAMPLE, 255u, SAMPLE);


SIMPLE_TEST(HanoiTower_Closedform, TestLOWER, 0u, LOWER);
SIMPLE_TEST(HanoiTower_Closedform, TestUPPER, std::numeric_limits<unsigned long>::max() / 2, UPPER);
SIMPLE_TEST(HanoiTower_Closedform, TestSAMPLE, 255u, SAMPLE);

MUTUAL_RANDOM_TEST(HanoiTower_Recursive, HanoiTower_Closedform, LOWER, UPPER);


constexpr InputType IndirectHanoiTowerUPPER = LONG_BITS_NUM / 3;


SIMPLE_BENCHMARK(IndirectHanoiTower_Recursive, LOWER);
SIMPLE_BENCHMARK(IndirectHanoiTower_Recursive, IndirectHanoiTowerUPPER);
SIMPLE_BENCHMARK(IndirectHanoiTower_Recursive, SAMPLE);
RANDOM_BENCHMARK(IndirectHanoiTower_Recursive, LOWER, IndirectHanoiTowerUPPER);


SIMPLE_BENCHMARK(IndirectHanoiTower_Closedform, LOWER);
SIMPLE_BENCHMARK(IndirectHanoiTower_Closedform, IndirectHanoiTowerUPPER);
SIMPLE_BENCHMARK(IndirectHanoiTower_Closedform, SAMPLE);
RANDOM_BENCHMARK(IndirectHanoiTower_Closedform, LOWER, IndirectHanoiTowerUPPER);


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


SIMPLE_BENCHMARK(DoubleHanoiTower_A_Recursive, LOWER);
SIMPLE_BENCHMARK(DoubleHanoiTower_A_Recursive, DoubleHanoiTowerUPPER);
SIMPLE_BENCHMARK(DoubleHanoiTower_A_Recursive, SAMPLE);
RANDOM_BENCHMARK(DoubleHanoiTower_A_Recursive, LOWER, DoubleHanoiTowerUPPER);


SIMPLE_BENCHMARK(DoubleHanoiTower_A_Closedform, LOWER);
SIMPLE_BENCHMARK(DoubleHanoiTower_A_Closedform, DoubleHanoiTowerUPPER);
SIMPLE_BENCHMARK(DoubleHanoiTower_A_Closedform, SAMPLE);
RANDOM_BENCHMARK(DoubleHanoiTower_A_Closedform, LOWER, DoubleHanoiTowerUPPER);


const InputType DoubleHanoiTowerBLOWER = 1;


SIMPLE_BENCHMARK(DoubleHanoiTower_B_Closedform, DoubleHanoiTowerBLOWER);
SIMPLE_BENCHMARK(DoubleHanoiTower_B_Closedform, DoubleHanoiTowerUPPER);
SIMPLE_BENCHMARK(DoubleHanoiTower_B_Closedform, SAMPLE);
RANDOM_BENCHMARK(DoubleHanoiTower_B_Closedform, LOWER, DoubleHanoiTowerUPPER);


SIMPLE_TEST(DoubleHanoiTower_A_Recursive, TestLOWER, 0u, LOWER);
SIMPLE_TEST(DoubleHanoiTower_A_Recursive, TestDoubleHanoiTowerUPPER, 4611686018427387902ull,
            DoubleHanoiTowerUPPER);
SIMPLE_TEST(DoubleHanoiTower_A_Recursive, TestSAMPLE, 510u, SAMPLE);


SIMPLE_TEST(DoubleHanoiTower_A_Closedform, TestLOWER, 0u, LOWER);
SIMPLE_TEST(DoubleHanoiTower_A_Closedform, TestDoubleHanoiTowerUPPER, 4611686018427387902ull,
            DoubleHanoiTowerUPPER);
SIMPLE_TEST(DoubleHanoiTower_A_Closedform, TestSAMPLE, 510u, SAMPLE);

MUTUAL_RANDOM_TEST(DoubleHanoiTower_A_Recursive, DoubleHanoiTower_A_Closedform, LOWER,
                   DoubleHanoiTowerUPPER);


SIMPLE_TEST(DoubleHanoiTower_B_Closedform, TestDoubleHanoiTowerBLOWER, 3u, DoubleHanoiTowerBLOWER);
SIMPLE_TEST(DoubleHanoiTower_B_Closedform, TestDoubleHanoiTowerUPPER, 9223372036854775803ull,
            DoubleHanoiTowerUPPER);
SIMPLE_TEST(DoubleHanoiTower_B_Closedform, TestSAMPLE, 1019u, SAMPLE);
