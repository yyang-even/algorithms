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
unsigned long HanoiTowerRecursive(const InputType n) {
    if (n == 0) {
        return 0;
    } else {
        return (HanoiTowerRecursive(n - 1) << 1) + 1;
    }
}

unsigned long HanoiTowerClosedform(const InputType n) {
    return ((unsigned long)1 << n) - 1;
}

const InputType LOWER = 0;
constexpr InputType UPPER = LONG_BITS_NUM - 1;
const InputType SAMPLE = 8;
std::uniform_int_distribution<InputType> distribution(LOWER, UPPER);

BENCHMARK_SUIT(HanoiTowerRecursive);
BENCHMARK_SUIT(HanoiTowerClosedform);

SIMPLE_TEST_SUIT(HanoiTowerRecursive, 0, ULONG_MAX / 2, 255);
SIMPLE_TEST_SUIT(HanoiTowerClosedform, 0, ULONG_MAX / 2, 255);
MUTUAL_TEST(HanoiTowerRecursive, HanoiTowerClosedform);
