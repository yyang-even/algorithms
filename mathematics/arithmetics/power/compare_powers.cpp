#include "common_header.h"


namespace {

/** Comparing X^Y and Y^X for very large values of X and Y
 *
 * @reference   https://www.geeksforgeeks.org/comparing-xy-and-yx-for-very-large-values-of-x-and-y/
 */
template <typename Compare>
inline constexpr auto
ComparePowers(const double base1, const double exp1,
              const Compare compare,
              const double base2, const double exp2) {
    return compare(exp1 * std::log(base1),
                   exp2 * std::log(base2));
}

inline constexpr auto ComparePowersX_YLessThanY_X(const int x, const int y) {
    return ComparePowers(x, y, std::less<double> {}, y, x);
}

}//namespace


THE_BENCHMARK(ComparePowersX_YLessThanY_X, 2, 3);

SIMPLE_TEST(ComparePowersX_YLessThanY_X, TestSAMPLE1, true, 2, 3);
SIMPLE_TEST(ComparePowersX_YLessThanY_X, TestSAMPLE2, false, 4, 5);
