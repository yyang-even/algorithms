#include "common_header.h"

typedef unsigned long InputType;
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
InputType PlaneLinesRecursive(const InputType n) {
    if (n == 0) {
        return 1;
    } else {
        return PlaneLinesRecursive(n - 1) + n;
    }
}

InputType PlaneLinesClosedform(const InputType n) {
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
 * Z(n) = Z(n - 1) + 4n -3
 */
InputType PlaneBentLinesRecursive(const InputType n) {
    if (n == 0) {
        return 1;
    } else {
        return PlaneBentLinesRecursive(n - 1) + (n << 2) - 3;
    }
}

/**
 * Z(n) = 2n^2 - n + 1, for n >= 0.
 */
InputType PlaneBentLinesClosedform(const InputType n) {
    return ((n * n) << 1) - n + 1;
}

/** Bounded Regions in The Plane
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 1, Exercises 6.
 *
 * Some of the regions defined by n lines in the plane are infinite, while others are bounded. What’s the maximum possible number of bounded regions?
 */

/**
 * Z(n) = (n-2)(n-1)/2, for n > 0;
 */
InputType BoundedRegionsPlaneLinesClosedform(const InputType n) {
    return ((n - 2) * (n - 1)) / 2;
}

const InputType LOWER = 0;
constexpr InputType UPPER = HYPOTHETIC_MAX_STACK_DEPTH;
const InputType SAMPLE = 14;

SIMPLE_BENCHMARK(PlaneLinesRecursive, LOWER);
SIMPLE_BENCHMARK(PlaneLinesRecursive, UPPER);
SIMPLE_BENCHMARK(PlaneLinesRecursive, SAMPLE);
RANDOM_BENCHMARK(PlaneLinesRecursive, LOWER, UPPER);

constexpr InputType BITS_NUM = (sizeof(InputType) * CHAR_BIT);
constexpr InputType UPPER2 = InputType(1) << ((LONG_BITS_NUM / 2) - 1);

SIMPLE_BENCHMARK(PlaneLinesClosedform, LOWER);
SIMPLE_BENCHMARK(PlaneLinesClosedform, UPPER2);
SIMPLE_BENCHMARK(PlaneLinesClosedform, SAMPLE);
RANDOM_BENCHMARK(PlaneLinesClosedform, LOWER, UPPER2);

SIMPLE_BENCHMARK(PlaneBentLinesRecursive, LOWER);
SIMPLE_BENCHMARK(PlaneBentLinesRecursive, UPPER);
SIMPLE_BENCHMARK(PlaneBentLinesRecursive, SAMPLE);
RANDOM_BENCHMARK(PlaneBentLinesRecursive, LOWER, UPPER);

SIMPLE_BENCHMARK(PlaneBentLinesClosedform, LOWER);
SIMPLE_BENCHMARK(PlaneBentLinesClosedform, UPPER2);
SIMPLE_BENCHMARK(PlaneBentLinesClosedform, SAMPLE);
RANDOM_BENCHMARK(PlaneBentLinesClosedform, LOWER, UPPER2);

constexpr InputType BoundedRegionsPlaneLinesLOWER = 1;

SIMPLE_BENCHMARK(BoundedRegionsPlaneLinesClosedform, BoundedRegionsPlaneLinesLOWER);
SIMPLE_BENCHMARK(BoundedRegionsPlaneLinesClosedform, UPPER2);
SIMPLE_BENCHMARK(BoundedRegionsPlaneLinesClosedform, SAMPLE);
RANDOM_BENCHMARK(BoundedRegionsPlaneLinesClosedform, LOWER, UPPER2);

SIMPLE_TEST(PlaneLinesRecursive, LOWER, 1);
SIMPLE_TEST(PlaneLinesRecursive, UPPER, 8390657);
SIMPLE_TEST(PlaneLinesRecursive, SAMPLE, 106);

SIMPLE_TEST(PlaneLinesClosedform, LOWER, 1);
SIMPLE_TEST(PlaneLinesClosedform, UPPER2, 2305843010287435777);
SIMPLE_TEST(PlaneLinesClosedform, SAMPLE, 106);

MUTUAL_TEST(PlaneLinesRecursive, PlaneLinesClosedform, LOWER, UPPER);

SIMPLE_TEST(PlaneBentLinesRecursive, LOWER, 1);
SIMPLE_TEST(PlaneBentLinesRecursive, UPPER, 33550337);
SIMPLE_TEST(PlaneBentLinesRecursive, SAMPLE, 379);

SIMPLE_TEST(PlaneBentLinesClosedform, LOWER, 1);
SIMPLE_TEST(PlaneBentLinesClosedform, UPPER2, 9223372034707292161);
SIMPLE_TEST(PlaneBentLinesClosedform, SAMPLE, 379);

MUTUAL_TEST(PlaneBentLinesRecursive, PlaneBentLinesClosedform, LOWER, UPPER);

SIMPLE_TEST(BoundedRegionsPlaneLinesClosedform, BoundedRegionsPlaneLinesLOWER, 0);
SIMPLE_TEST(BoundedRegionsPlaneLinesClosedform, UPPER2, 2305843005992468481);
SIMPLE_TEST(BoundedRegionsPlaneLinesClosedform, SAMPLE, 78);
