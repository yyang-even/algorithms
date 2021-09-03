#include "common_header.h"


namespace {

using Point = std::pair<int, int>;
using ArrayType = std::vector<Point>;
using OutputType = std::set<Point>;

/** Erect the Fence
 *
 * @reference   https://leetcode.com/problems/erect-the-fence/
 *
 * You are given an array trees where trees[i] = [xi, yi] represents the location of a
 * tree in the garden. You are asked to fence the entire garden using the minimum length
 * of rope as it is expensive. The garden is well fenced only if all the trees are
 * enclosed. Return the coordinates of trees that are exactly located on the fence
 * perimeter.
 * All the given points are unique.
 */
inline constexpr auto
cross_product(const Point p, const Point q, const Point r) {
    return (p.first - q.first) * (r.second - q.second) -
           (p.second - q.second) * (r.first - q.first);
}

inline constexpr auto
inBetween(const Point p, const Point i, const Point q) {
    const auto a = (i.first >= p.first and i.first <= q.first) or
                   (i.first <= p.first and i.first >= q.first);
    const auto b = (i.second >= p.second and i.second <= q.second) or
                   (i.second <= p.second and i.second >= q.second);
    return a and b;
}

auto ConvexHull_Jarvis(const ArrayType &points) {
    const auto min_iter = std::min_element(points.cbegin(), points.cend());
    const std::size_t min_index = min_iter - points.cbegin();

    std::unordered_set<const Point *> selected = {&(*min_iter)};
    OutputType result = {*min_iter};

    std::size_t current = min_index;
    while (true) {
        std::size_t next = 0;
        for (std::size_t i = 1; i < points.size(); ++i) {
            if (i == current) {
                continue;
            }
            const auto orientation = cross_product(points[current], points[i], points[next]);
            if (next == current or orientation > 0 or
                (orientation == 0 and
                 not inBetween(points[current], points[i], points[next]))) {
                next = i;
            }
        }

        for (std::size_t i = 0; i < points.size(); ++i) {
            if (i != current and
                cross_product(points[current], points[i], points[next]) == 0) {
                if (selected.insert(&points[i]).second) {
                    result.insert(points[i]);
                }
            }
        }

        current = next;
        if (current == min_index) {
            break;
        }
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {{1, 1}, {2, 2}, {2, 0}, {2, 4}, {3, 3}, {4, 2}};
const OutputType EXPECTED1 = {{1, 1}, {2, 0}, {3, 3}, {2, 4}, {4, 2}};

const ArrayType SAMPLE2 = {{1, 2}, {2, 2}, {4, 2}};
const OutputType EXPECTED2 = {{4, 2}, {2, 2}, {1, 2}};


THE_BENCHMARK(ConvexHull_Jarvis, SAMPLE1);

SIMPLE_TEST(ConvexHull_Jarvis, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(ConvexHull_Jarvis, TestSAMPLE2, EXPECTED2, SAMPLE2);
