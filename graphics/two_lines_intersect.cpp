#include "common_header.h"

#include "line.h"


namespace {

/** Two lines intersect
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 7.3.
 *
 * Given two lines on a Cartesian plane, determine whether the two lines would intersect.
 */
inline constexpr auto
WouldTwoLinesIntersect(const Line &a_line, const Line &another_line) {
    return std::abs(a_line.slope - another_line.slope) >
           std::numeric_limits<double>::epsilon() or
           std::abs(a_line.intercept - another_line.intercept) <
           std::numeric_limits<double>::epsilon();
}

}//namespace


constexpr Line SAMPLE1 = {0.5, 3};
constexpr Line SAMPLE2 = {1, 5};
constexpr Line SAMPLE3 = {0.5, 1};


THE_BENCHMARK(WouldTwoLinesIntersect, SAMPLE1, SAMPLE2);

SIMPLE_TEST(WouldTwoLinesIntersect, TestSAMPLE1, true, SAMPLE1, SAMPLE2);
SIMPLE_TEST(WouldTwoLinesIntersect, TestSAMPLE2, true, SAMPLE1, SAMPLE1);
SIMPLE_TEST(WouldTwoLinesIntersect, TestSAMPLE3, false, SAMPLE1, SAMPLE3);
