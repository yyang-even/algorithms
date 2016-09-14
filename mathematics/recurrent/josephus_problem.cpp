#include "common_header.h"

typedef unsigned long InputType;
/** Josephus Problem
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 1.3.
 *
 * A variant of Josephus Problem. Start with n people numbered 1 to n around a circle,
 * and we eliminate every second remaining person until only one survives. For n = 10,
 * the elimination order is 2, 4, 6, 8, 10, 3, 7, 1, 9, so 5 survives.
 * The problem: Determine the survivor’s number, J(n).
 */

/**
 * J(1) = 1;
 * J(2n) = 2J(n) - 1,      for n >= 1;
 * J(2n + 1) = 2J(n) + 1,  for n >= 1.
 */
InputType JosephusProblem2Recursive(const InputType n) {
    if (n == 1) {
        return 1;
    } else if ((n & 1) == 1) {  //odd
        return (JosephusProblem2Recursive(n / 2) << 1) + 1;
    } else { //even
        return (JosephusProblem2Recursive(n / 2) << 1) - 1;
    }
}

/**
 * J(2^m + l) = 2l + 1, for m >= 0 and 0 <= l < 2^m.
 */
InputType JosephusProblem2Closedform(const InputType n) {
    const auto bit_length = sizeof(n) * CHAR_BIT;
    InputType m = InputType(1) << (bit_length - 1);

    while (m and !(m & n)) {
        m /= 2;
    }
    return ((m ^ n) << 1) + 1;
}

/** Penultimate Survivor
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 1, Exercises 15.
 *
 * Josephus had a friend who was saved by getting into the next-to-last position.
 * What is I(n), the number of the penultimate survivor when every second person is executed?
 */

/**
 * I(n) = I(3*2^m + l) = 2l + 1.
 */
InputType PenultimateSurvivorClosedform(const InputType n) {
    if (n == 2) {
        return 2;
    }
    const auto bit_length = sizeof(n) * CHAR_BIT;
    InputType m = InputType(3) << (bit_length - 2);

    while (n < m) {
        m /= 2;
    }
    return ((n - m) << 1) + 1;
}

/** Authentic Josephus Problem
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 3.3.
 *
 *  Authentic Josephus Problem in which every third person is eliminated, instead of every second.
 */
InputType JosephusProblem3(const InputType n) {
    double D = 1.0;
    const double BOUND = n * 2.0;
    while (D <= BOUND) {
        D = std::ceil(1.5 * D);
    }
    return 3 * n + 1 - static_cast<InputType>(D);
}

/** Kth Josephus problem
 * @reference http://www.geeksforgeeks.org/josephus-problem-set-1-a-on-solution/
 *
 * There are n people standing in a circle waiting to be executed. The counting out begins at some
 * point in the circle and proceeds around the circle in a fixed direction. In each step,
 * a certain number of people are skipped and the next person is executed. The elimination proceeds
 * around the circle (which is becoming smaller and smaller as the executed people are removed),
 * until only the last person remains, who is given freedom. Given the total number of persons n
 * and a number k which indicates that k-1 persons are skipped and kth person is killed in circle.
 * The task is to choose the place in the initial circle so that you are the last one remaining and so survive.
 */

/**
 * josephus(n, k) = (josephus(n - 1, k) + k-1) % n + 1;
 * josephus(1, k) = 1.
 *
 * After the first person (kth from begining) is killed, n-1 persons are left. So we call josephus(n - 1, k)
 * to get the position with n-1 persons. But the position returned by josephus(n - 1, k) will consider
 * the position starting from k%n + 1. So, we must make adjustments to the position returned by josephus(n - 1, k).
 */
InputType JosephusKRecursive(const InputType n, const InputType k) {
    if (n == 1) {
        return 1;
    } else {
        return (JosephusKRecursive(n - 1, k) + k - 1) % n + 1;
    }
}

/**
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 3.3.
 */
InputType JosephusKClosedform(const InputType n, const InputType k) {
    double D = 1.0;
    const double K_MINUS_ONE = static_cast<double>(k - 1);
    const double BOUND = n * K_MINUS_ONE;
    while (D <= BOUND) {
        D = std::ceil(k / K_MINUS_ONE * D);
    }
    return k * n + 1 - static_cast<InputType>(D);
}


const InputType LOWER = 1;
constexpr InputType UPPER = ~InputType(0);
const InputType SAMPLE = 15;

SIMPLE_BENCHMARK(JosephusProblem2Recursive, LOWER);
SIMPLE_BENCHMARK(JosephusProblem2Recursive, UPPER);
SIMPLE_BENCHMARK(JosephusProblem2Recursive, SAMPLE);
RANDOM_BENCHMARK(JosephusProblem2Recursive, LOWER, UPPER);

SIMPLE_TEST(JosephusProblem2Recursive, TestLOWER, 1, LOWER);
SIMPLE_TEST(JosephusProblem2Recursive, TestUPPER, UPPER, UPPER);
SIMPLE_TEST(JosephusProblem2Recursive, TestSAMPLE, 15, SAMPLE);

SIMPLE_BENCHMARK(JosephusProblem2Closedform, LOWER);
SIMPLE_BENCHMARK(JosephusProblem2Closedform, UPPER);
SIMPLE_BENCHMARK(JosephusProblem2Closedform, SAMPLE);
RANDOM_BENCHMARK(JosephusProblem2Closedform, LOWER, UPPER);

SIMPLE_TEST(JosephusProblem2Closedform, TestLOWER, 1, LOWER);
SIMPLE_TEST(JosephusProblem2Closedform, TestUPPER, UPPER, UPPER);
SIMPLE_TEST(JosephusProblem2Closedform, TestSAMPLE, 15, SAMPLE);

MUTUAL_RANDOM_TEST(JosephusProblem2Recursive, JosephusProblem2Closedform, LOWER, UPPER);

const InputType LOWER2 = 2;

SIMPLE_BENCHMARK(PenultimateSurvivorClosedform, LOWER2);
SIMPLE_BENCHMARK(PenultimateSurvivorClosedform, UPPER);
SIMPLE_BENCHMARK(PenultimateSurvivorClosedform, SAMPLE);
RANDOM_BENCHMARK(PenultimateSurvivorClosedform, LOWER2, UPPER);

SIMPLE_TEST(PenultimateSurvivorClosedform, TestLOWER2, 2, LOWER2);
SIMPLE_TEST(PenultimateSurvivorClosedform, TestUPPER, UPPER / 2, UPPER);
SIMPLE_TEST(PenultimateSurvivorClosedform, TestSAMPLE, 7, SAMPLE);

constexpr InputType UPPER3 = ~InputType(0) / 4;

SIMPLE_BENCHMARK(JosephusProblem3, LOWER);
SIMPLE_BENCHMARK(JosephusProblem3, UPPER3);
SIMPLE_BENCHMARK(JosephusProblem3, SAMPLE);
RANDOM_BENCHMARK(JosephusProblem3, LOWER, UPPER3);

SIMPLE_TEST(JosephusProblem3, TestLOWER, 1, LOWER);
SIMPLE_TEST(JosephusProblem3, TestUPPER3, 2565990286715650046, UPPER3);
SIMPLE_TEST(JosephusProblem3, TestSAMPLE, 5, SAMPLE);

const InputType UPPER_K = HYPOTHETIC_MAX_STACK_DEPTH;

SIMPLE_BENCHMARK(JosephusKRecursive, LOWER, UPPER_K);
SIMPLE_BENCHMARK(JosephusKRecursive, LOWER, 2);
SIMPLE_BENCHMARK(JosephusKRecursive, UPPER_K, UPPER_K);
SIMPLE_BENCHMARK(JosephusKRecursive, UPPER_K, 2);
SIMPLE_BENCHMARK(JosephusKRecursive, SAMPLE, UPPER_K);
SIMPLE_BENCHMARK(JosephusKRecursive, SAMPLE, 2);

SIMPLE_TEST(JosephusKRecursive, TestLOWER2, 1, LOWER, 2);
SIMPLE_TEST(JosephusKRecursive, TestSAMPLE2, 15, SAMPLE, 2);
SIMPLE_TEST(JosephusKRecursive, TestLOWER3, 1, LOWER, 3);
SIMPLE_TEST(JosephusKRecursive, TestSAMPLE3, 5, SAMPLE, 3);

SIMPLE_BENCHMARK(JosephusKClosedform, LOWER, UPPER_K);
SIMPLE_BENCHMARK(JosephusKClosedform, LOWER, 2);
SIMPLE_BENCHMARK(JosephusKClosedform, UPPER_K, UPPER_K);
SIMPLE_BENCHMARK(JosephusKClosedform, UPPER_K, 2);
SIMPLE_BENCHMARK(JosephusKClosedform, SAMPLE, UPPER_K);
SIMPLE_BENCHMARK(JosephusKClosedform, SAMPLE, 2);

SIMPLE_TEST(JosephusKClosedform, TestLOWER2, 1, LOWER, 2);
SIMPLE_TEST(JosephusKClosedform, TestSAMPLE2, 15, SAMPLE, 2);
SIMPLE_TEST(JosephusKClosedform, TestLOWER3, 1, LOWER, 3);
SIMPLE_TEST(JosephusKClosedform, TestSAMPLE3, 5, SAMPLE, 3);
