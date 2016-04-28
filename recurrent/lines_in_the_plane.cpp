#include "common_header.h"

#include <cmath>

typedef unsigned InputType;
/** Lines in The Plane
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 1.2.
 *
 * How many slices of pizza can a person obtain by making n straight cuts with a pizza knife?
 * What is the maximum number of regions defined by n lines in the plane?
 */
unsigned long PlaneLinesRecursive(const InputType n) {
    if (n == 0) {
        return 1;
    } else {
        return PlaneLinesRecursive(n - 1) + n;
    }
}

unsigned long PlaneLinesClosedform(const InputType n) {
    return n * (n + 1) / 2 + 1;
}

/** Bent Lines in The Plane
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 1.2.
 *
 * Suppose that instead of straight lines we use bent lines, each containing one "zig."
 * What is the maximum number of regions determined by n such bent lines in the plane?
 */
unsigned long PlaneBentLinesClosedform(const InputType n) {
    return ((n * n) << 1) - n + 1;
}

const InputType LOWER = 0;
constexpr InputType UPPER = HYPOTHETIC_MAX_STACK_DEPTH;
const InputType SAMPLE = 14;
std::uniform_int_distribution<InputType> distribution(LOWER, UPPER);

BENCHMARK_SUIT(PlaneLinesRecursive);
BENCHMARK_SUIT(PlaneLinesClosedform);
BENCHMARK_SUIT(PlaneBentLinesClosedform);

SIMPLE_TEST_SUIT(PlaneLinesRecursive, 1, 8390657, 106);
SIMPLE_TEST_SUIT(PlaneLinesClosedform, 1, 8390657, 106);
SIMPLE_TEST_SUIT(PlaneBentLinesClosedform, 1, 33550337, 379);
MUTUAL_TEST(PlaneLinesRecursive, PlaneLinesClosedform);
