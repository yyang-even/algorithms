#include "common_header.h"

typedef unsigned InputType;
/** Lines in The Plane
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 1.2.
 *
 * How many slices of pizza can a person obtain by making n straight cuts with a pizza knife?
 * What is the maximum number of regions defined by n lines in the plane?
 */

/**
 * L(0) = 1;
 * L(n) = L(n - 1) + n, for n > 0.
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

/**
 * Z(n) = 2n^2 - n + 1, for n >= 0.
 */
unsigned long PlaneBentLinesClosedform(const InputType n) {
    return ((n * n) << 1) - n + 1;
}

const InputType LOWER = 0;
constexpr InputType UPPER = HYPOTHETIC_MAX_STACK_DEPTH;
const InputType SAMPLE = 14;

SIMPLE_BENCHMARK(PlaneLinesRecursive, LOWER);
SIMPLE_BENCHMARK(PlaneLinesRecursive, UPPER);
SIMPLE_BENCHMARK(PlaneLinesRecursive, SAMPLE);
RANDOM_BENCHMARK(PlaneLinesRecursive, LOWER, UPPER);

SIMPLE_BENCHMARK(PlaneLinesClosedform, LOWER);
SIMPLE_BENCHMARK(PlaneLinesClosedform, UPPER);
SIMPLE_BENCHMARK(PlaneLinesClosedform, SAMPLE);
RANDOM_BENCHMARK(PlaneLinesClosedform, LOWER, UPPER);

SIMPLE_BENCHMARK(PlaneBentLinesClosedform, LOWER);
SIMPLE_BENCHMARK(PlaneBentLinesClosedform, UPPER);
SIMPLE_BENCHMARK(PlaneBentLinesClosedform, SAMPLE);
RANDOM_BENCHMARK(PlaneBentLinesClosedform, LOWER, UPPER);

SIMPLE_TEST(PlaneLinesRecursive, LOWER, 1);                                         
SIMPLE_TEST(PlaneLinesRecursive, UPPER, 8390657);                                         
SIMPLE_TEST(PlaneLinesRecursive, SAMPLE, 106);

SIMPLE_TEST(PlaneLinesClosedform, LOWER, 1);                                         
SIMPLE_TEST(PlaneLinesClosedform, UPPER, 8390657);                                         
SIMPLE_TEST(PlaneLinesClosedform, SAMPLE, 106);

SIMPLE_TEST(PlaneBentLinesClosedform, LOWER, 1);                                         
SIMPLE_TEST(PlaneBentLinesClosedform, UPPER, 33550337);                                         
SIMPLE_TEST(PlaneBentLinesClosedform, SAMPLE, 379);

MUTUAL_TEST(PlaneLinesRecursive, PlaneLinesClosedform, LOWER, UPPER);
