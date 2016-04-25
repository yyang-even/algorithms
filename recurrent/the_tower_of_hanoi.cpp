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
unsigned long HanoiTower_recursive(const InputType n) {
    if (n == 0) {
        return 0;
    } else {
        return (HanoiTower_recursive(n - 1) << 1) + 1;
    }
}

unsigned long HanoiTower_closedform(const InputType n) {
    return ((unsigned long)1 << n) - 1;
}

const InputType LOWER_BOUND = 0;
constexpr InputType UPPER_BOUND = LONG_BITS_NUM - 1;
const InputType SAMPLE = 8;
std::uniform_int_distribution<InputType> distribution(LOWER_BOUND, UPPER_BOUND);

BENCHMARK_SUIT(HanoiTower_recursive);
BENCHMARK_SUIT(HanoiTower_closedform);
