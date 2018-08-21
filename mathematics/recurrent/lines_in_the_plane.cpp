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
 * z(0) = 1;
 * Z(n) = Z(n - 1) + 4n -3, for n > 0.
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

/** Zig-zag Lines in The Plane
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 1, Exercises 13.
 *
 * What’s the maximum number of regions definable by n zig-zag lines, ZZ(2) = 12,
 * each of which consists of two parallel infinite half-lines joined by a straight segment?
 */

/**
 * ZZ(0) = 1;
 * ZZ(n) = ZZ(n - 1) + 9n - 8, for n > 0.
 */
InputType PlaneZigzagLinesRecursive(const InputType n) {
    if (n == 0) {
        return 1;
    } else {
        return PlaneZigzagLinesRecursive(n - 1) + (9 * n) - 8;
    }
}

/**
 * ZZ(n) = (9n^2 - 7n)/2 + 1, for n >= 0.
 */
InputType PlaneZigzagLinesClosedform(const InputType n) {
    return (9 * n * n - 7 * n) / 2 + 1;
}

constexpr InputType LOWER = std::numeric_limits<InputType>::min();
constexpr InputType UPPER = HYPOTHETIC_MAX_STACK_DEPTH;
constexpr InputType SAMPLE = 14;

constexpr InputType BITS_NUM = Bits_Number<InputType>();
constexpr InputType UPPER2 = InputType(1) << ((LONG_BITS_NUM / 2) - 1);

constexpr InputType BoundedRegionsPlaneLinesLOWER = 1;

SIMPLE_BENCHMARK(PlaneLinesRecursive, LOWER);
SIMPLE_BENCHMARK(PlaneLinesRecursive, UPPER);
SIMPLE_BENCHMARK(PlaneLinesRecursive, SAMPLE);
RANDOM_BENCHMARK(PlaneLinesRecursive, LOWER, UPPER);

SIMPLE_TEST(PlaneLinesRecursive, TestLOWER, 1, LOWER);
SIMPLE_TEST(PlaneLinesRecursive, TestUPPER, 8390657, UPPER);
SIMPLE_TEST(PlaneLinesRecursive, TestSAMPLE, 106, SAMPLE);

SIMPLE_BENCHMARK(PlaneLinesClosedform, LOWER);
SIMPLE_BENCHMARK(PlaneLinesClosedform, UPPER2);
SIMPLE_BENCHMARK(PlaneLinesClosedform, SAMPLE);
RANDOM_BENCHMARK(PlaneLinesClosedform, LOWER, UPPER2);

SIMPLE_TEST(PlaneLinesClosedform, TestLOWER, 1, LOWER);
SIMPLE_TEST(PlaneLinesClosedform, TestUPPER2, 2305843010287435777, UPPER2);
SIMPLE_TEST(PlaneLinesClosedform, TestSAMPLE, 106, SAMPLE);

MUTUAL_RANDOM_TEST(PlaneLinesRecursive, PlaneLinesClosedform, LOWER, UPPER);

SIMPLE_BENCHMARK(PlaneBentLinesRecursive, LOWER);
SIMPLE_BENCHMARK(PlaneBentLinesRecursive, UPPER);
SIMPLE_BENCHMARK(PlaneBentLinesRecursive, SAMPLE);
RANDOM_BENCHMARK(PlaneBentLinesRecursive, LOWER, UPPER);

SIMPLE_TEST(PlaneBentLinesRecursive, TestLOWER, 1, LOWER);
SIMPLE_TEST(PlaneBentLinesRecursive, TestUPPER, 33550337, UPPER);
SIMPLE_TEST(PlaneBentLinesRecursive, TestSAMPLE, 379, SAMPLE);

SIMPLE_BENCHMARK(PlaneBentLinesClosedform, LOWER);
SIMPLE_BENCHMARK(PlaneBentLinesClosedform, UPPER2);
SIMPLE_BENCHMARK(PlaneBentLinesClosedform, SAMPLE);
RANDOM_BENCHMARK(PlaneBentLinesClosedform, LOWER, UPPER2);

SIMPLE_TEST(PlaneBentLinesClosedform, TestLOWER, 1, LOWER);
SIMPLE_TEST(PlaneBentLinesClosedform, TestUPPER2, 9223372034707292161, UPPER2);
SIMPLE_TEST(PlaneBentLinesClosedform, TestSAMPLE, 379, SAMPLE);

MUTUAL_RANDOM_TEST(PlaneBentLinesRecursive, PlaneBentLinesClosedform, LOWER, UPPER);

SIMPLE_BENCHMARK(PlaneZigzagLinesRecursive, LOWER);
SIMPLE_BENCHMARK(PlaneZigzagLinesRecursive, UPPER);
SIMPLE_BENCHMARK(PlaneZigzagLinesRecursive, SAMPLE);
RANDOM_BENCHMARK(PlaneZigzagLinesRecursive, LOWER, UPPER);

SIMPLE_TEST(PlaneZigzagLinesRecursive, TestLOWER, 1, LOWER);
SIMPLE_TEST(PlaneZigzagLinesRecursive, TestUPPER, 75483137, UPPER);
SIMPLE_TEST(PlaneZigzagLinesRecursive, TestSAMPLE, 834, SAMPLE);

constexpr InputType PlaneZigzagLinesClosedformUPPER = InputType(1) << ((LONG_BITS_NUM / 2) - 2);

SIMPLE_BENCHMARK(PlaneZigzagLinesClosedform, LOWER);
SIMPLE_BENCHMARK(PlaneZigzagLinesClosedform, PlaneZigzagLinesClosedformUPPER);
SIMPLE_BENCHMARK(PlaneZigzagLinesClosedform, SAMPLE);
RANDOM_BENCHMARK(PlaneZigzagLinesClosedform, LOWER, PlaneZigzagLinesClosedformUPPER);

SIMPLE_TEST(PlaneZigzagLinesClosedform, TestLOWER, 1, LOWER);
SIMPLE_TEST(PlaneZigzagLinesClosedform, TestPlaneZigzagLinesClosedformUPPER, 5188146766972715009,
            PlaneZigzagLinesClosedformUPPER);
SIMPLE_TEST(PlaneZigzagLinesClosedform, TestSAMPLE, 834, SAMPLE);

MUTUAL_RANDOM_TEST(PlaneZigzagLinesRecursive, PlaneZigzagLinesClosedform, LOWER, UPPER);

SIMPLE_BENCHMARK(BoundedRegionsPlaneLinesClosedform, BoundedRegionsPlaneLinesLOWER);
SIMPLE_BENCHMARK(BoundedRegionsPlaneLinesClosedform, UPPER2);
SIMPLE_BENCHMARK(BoundedRegionsPlaneLinesClosedform, SAMPLE);
RANDOM_BENCHMARK(BoundedRegionsPlaneLinesClosedform, LOWER, UPPER2);

SIMPLE_TEST(BoundedRegionsPlaneLinesClosedform, TestBoundedRegionsPlaneLinesLOWER, 0,
            BoundedRegionsPlaneLinesLOWER);
SIMPLE_TEST(BoundedRegionsPlaneLinesClosedform, TestUPPER2, 2305843005992468481, UPPER2);
SIMPLE_TEST(BoundedRegionsPlaneLinesClosedform, TestSAMPLE, 78, SAMPLE);
