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
unsigned long PlaneLines_recursive(const InputType n) {
    if (n == 0) {
        return 1;
    } else {
        return PlaneLines_recursive(n - 1) + n;
    }
}

unsigned long PlaneLines_closedform(const InputType n) {
    return n * (n + 1) / 2 + 1;
}

/** Bent Lines in The Plane
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 1.2.
 *
 * Suppose that instead of straight lines we use bent lines, each containing one "zig."
 * What is the maximum number of regions determined by n such bent lines in the plane?
 */
unsigned long PlaneBentLines_closedform(const InputType n) {
    return ((n * n) << 1) - n + 1;
}

const InputType LOWER_BOUND = 0;
constexpr InputType UPPER_BOUND = std::sqrt(static_cast<double>((~InputType(0)) / 2));
const InputType SAMPLE = 14;
std::uniform_int_distribution<InputType> distribution(LOWER_BOUND, UPPER_BOUND);

BENCHMARK_SUIT(PlaneLines_recursive);
BENCHMARK_SUIT(PlaneLines_closedform);
BENCHMARK_SUIT(PlaneBentLines_closedform);
