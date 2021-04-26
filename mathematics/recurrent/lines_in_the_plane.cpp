#include "common_header.h"


namespace {

using InputType = unsigned long;

/** Lines in The Plane
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Section 1.2.
 *
 * How many slices of pizza can a person obtain by making n straight cuts with a pizza
 * knife? What is the maximum number of regions defined by n lines in the plane?
 */

/**
 * L(0) = 1;
 * L(n) = L(n - 1) + n, for n > 0.
 */
InputType PlaneLines_Recursive(const InputType n) {
    if (n == 0) {
        return 1;
    } else {
        return PlaneLines_Recursive(n - 1) + n;
    }
}


InputType PlaneLines_Closedform(const InputType n) {
    return n * (n + 1) / 2 + 1;
}


/** Bent Lines in The Plane
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Section 1.2.
 *
 * Suppose that instead of straight lines we use bent lines, each containing one "zig."
 * What is the maximum number of regions determined by n such bent lines in the plane?
 */

/**
 * z(0) = 1;
 * Z(n) = Z(n - 1) + 4n -3, for n > 0.
 */
InputType PlaneBentLines_Recursive(const InputType n) {
    if (n == 0) {
        return 1;
    } else {
        return PlaneBentLines_Recursive(n - 1) + (n << 2) - 3;
    }
}


/**
 * Z(n) = 2n^2 - n + 1, for n >= 0.
 */
InputType PlaneBentLines_Closedform(const InputType n) {
    return ((n * n) << 1) - n + 1;
}


/** Bounded Regions in The Plane
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Section 1, Exercises 6.
 *
 * Some of the regions defined by n lines in the plane are infinite, while others are
 * bounded. What’s the maximum possible number of bounded regions?
 */

/**
 * Z(n) = (n-2)(n-1)/2, for n > 0;
 */
InputType BoundedRegionsPlaneLines_Closedform(const InputType n) {
    return ((n - 2) * (n - 1)) / 2;
}


/** Zig-zag Lines in The Plane
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Section 1, Exercises 13.
 *
 * What's the maximum number of regions definable by n zig-zag lines, ZZ(2) = 12, each of
 * which consists of two parallel infinite half-lines joined by a straight segment?
 */

/**
 * ZZ(0) = 1;
 * ZZ(n) = ZZ(n - 1) + 9n - 8, for n > 0.
 */
InputType PlaneZigzagLines_Recursive(const InputType n) {
    if (n == 0) {
        return 1;
    } else {
        return PlaneZigzagLines_Recursive(n - 1) + (9 * n) - 8;
    }
}


/**
 * ZZ(n) = (9n^2 - 7n)/2 + 1, for n >= 0.
 */
InputType PlaneZigzagLines_Closedform(const InputType n) {
    return (9 * n * n - 7 * n) / 2 + 1;
}

}//namespace


constexpr InputType LOWER = std::numeric_limits<InputType>::min();
constexpr InputType UPPER = HYPOTHETIC_MAX_STACK_DEPTH;
constexpr InputType SAMPLE = 14;

constexpr InputType UPPER2 = InputType(1) << ((BitsNumber<InputType> / 2) - 1);

constexpr InputType BoundedRegionsPlaneLinesLOWER = 1;


SIMPLE_BENCHMARK(PlaneLines_Recursive, Sample1, LOWER);
SIMPLE_BENCHMARK(PlaneLines_Recursive, Sample2, UPPER);
SIMPLE_BENCHMARK(PlaneLines_Recursive, Sample3, SAMPLE);

SIMPLE_TEST(PlaneLines_Recursive, TestLOWER, 1, LOWER);
SIMPLE_TEST(PlaneLines_Recursive, TestUPPER, 8390657, UPPER);
SIMPLE_TEST(PlaneLines_Recursive, TestSAMPLE, 106, SAMPLE);


SIMPLE_BENCHMARK(PlaneLines_Closedform, Sample1, LOWER);
SIMPLE_BENCHMARK(PlaneLines_Closedform, Sample2, UPPER2);
SIMPLE_BENCHMARK(PlaneLines_Closedform, Sample3, SAMPLE);

SIMPLE_TEST(PlaneLines_Closedform, TestLOWER, 1, LOWER);
SIMPLE_TEST(PlaneLines_Closedform, TestUPPER2, 2305843010287435777, UPPER2);
SIMPLE_TEST(PlaneLines_Closedform, TestSAMPLE, 106, SAMPLE);

MUTUAL_RANDOM_TEST(PlaneLines_Recursive, PlaneLines_Closedform, LOWER, UPPER);


SIMPLE_BENCHMARK(PlaneBentLines_Recursive, Sample1, LOWER);
SIMPLE_BENCHMARK(PlaneBentLines_Recursive, Sample2, UPPER);
SIMPLE_BENCHMARK(PlaneBentLines_Recursive, Sample3, SAMPLE);

SIMPLE_TEST(PlaneBentLines_Recursive, TestLOWER, 1, LOWER);
SIMPLE_TEST(PlaneBentLines_Recursive, TestUPPER, 33550337, UPPER);
SIMPLE_TEST(PlaneBentLines_Recursive, TestSAMPLE, 379, SAMPLE);


SIMPLE_BENCHMARK(PlaneBentLines_Closedform, Sample1, LOWER);
SIMPLE_BENCHMARK(PlaneBentLines_Closedform, Sample2, UPPER2);
SIMPLE_BENCHMARK(PlaneBentLines_Closedform, Sample3, SAMPLE);

SIMPLE_TEST(PlaneBentLines_Closedform, TestLOWER, 1, LOWER);
SIMPLE_TEST(PlaneBentLines_Closedform, TestUPPER2, 9223372034707292161, UPPER2);
SIMPLE_TEST(PlaneBentLines_Closedform, TestSAMPLE, 379, SAMPLE);

MUTUAL_RANDOM_TEST(PlaneBentLines_Recursive, PlaneBentLines_Closedform, LOWER, UPPER);


SIMPLE_BENCHMARK(PlaneZigzagLines_Recursive, Sample1, LOWER);
SIMPLE_BENCHMARK(PlaneZigzagLines_Recursive, Sample2, UPPER);
SIMPLE_BENCHMARK(PlaneZigzagLines_Recursive, Sample3, SAMPLE);

SIMPLE_TEST(PlaneZigzagLines_Recursive, TestLOWER, 1, LOWER);
SIMPLE_TEST(PlaneZigzagLines_Recursive, TestUPPER, 75483137, UPPER);
SIMPLE_TEST(PlaneZigzagLines_Recursive, TestSAMPLE, 834, SAMPLE);


constexpr InputType PlaneZigzagLinesClosedformUPPER =
    InputType(1) << ((BitsNumber<InputType> / 2) - 2);


SIMPLE_BENCHMARK(PlaneZigzagLines_Closedform, Sample1, LOWER);
SIMPLE_BENCHMARK(PlaneZigzagLines_Closedform, Sample2, PlaneZigzagLinesClosedformUPPER);
SIMPLE_BENCHMARK(PlaneZigzagLines_Closedform, Sample3, SAMPLE);

SIMPLE_TEST(PlaneZigzagLines_Closedform, TestLOWER, 1, LOWER);
SIMPLE_TEST(PlaneZigzagLines_Closedform, TestPlaneZigzagLinesClosedformUPPER,
            5188146766972715009, PlaneZigzagLinesClosedformUPPER);
SIMPLE_TEST(PlaneZigzagLines_Closedform, TestSAMPLE, 834, SAMPLE);

MUTUAL_RANDOM_TEST(PlaneZigzagLines_Recursive, PlaneZigzagLines_Closedform,
                   LOWER, UPPER);


SIMPLE_BENCHMARK(BoundedRegionsPlaneLines_Closedform, Sample1,
                 BoundedRegionsPlaneLinesLOWER);
SIMPLE_BENCHMARK(BoundedRegionsPlaneLines_Closedform, Sample2, UPPER2);
SIMPLE_BENCHMARK(BoundedRegionsPlaneLines_Closedform, Sample3, SAMPLE);

SIMPLE_TEST(BoundedRegionsPlaneLines_Closedform, TestBoundedRegionsPlaneLinesLOWER, 0,
            BoundedRegionsPlaneLinesLOWER);
SIMPLE_TEST(BoundedRegionsPlaneLines_Closedform, TestUPPER2, 2305843005992468481,
            UPPER2);
SIMPLE_TEST(BoundedRegionsPlaneLines_Closedform, TestSAMPLE, 78, SAMPLE);
