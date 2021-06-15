#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Breaking a string
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Problems 15-9.
 *
 * Given a string S with n characters and an array L[1..m] containing the break points,
 * compute the lowest cost for a sequence of breaks, along with a sequence of breaks
 * that achieves this cost.
 */
unsigned BreakString(const unsigned start, const unsigned end,
                     const ArrayType &break_points,
                     const int i, const int j) {
    if (i > j) {
        return 0;
    }

    auto min_cost = std::numeric_limits<unsigned>::max();
    for (auto k = i; k <= j; ++k) {
        const auto cost = end - start + 1 +
                          BreakString(start, break_points[k], break_points, i, k - 1) +
                          BreakString(break_points[k] + 1, end, break_points, k + 1, j);

        if (cost < min_cost) {
            min_cost = cost;
        }
    }

    return min_cost;
}

inline auto
BreakString(const unsigned string_length, const ArrayType &break_points) {
    assert(std::is_sorted(break_points.cbegin(), break_points.cend()));

    return BreakString(1, string_length, break_points, 0, break_points.size() - 1);
}

}//namespace


const ArrayType SAMPLE1 = {2};
const ArrayType SAMPLE2 = {2, 8};
const ArrayType SAMPLE3 = {2, 8, 10};


THE_BENCHMARK(BreakString, 20, SAMPLE3);

SIMPLE_TEST(BreakString, TestSAMPLE1, 20, 20, SAMPLE1);
SIMPLE_TEST(BreakString, TestSAMPLE2, 28, 20, SAMPLE2);
SIMPLE_TEST(BreakString, TestSAMPLE3, 38, 20, SAMPLE3);
