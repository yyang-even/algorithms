#include "common_header.h"

#include "rectangle.h"


namespace {

using PointType = std::vector<int>;
using ArrayType = std::vector<PointType>;

/**
 * @reference   Find the Number of Ways to Place People I
 *              https://leetcode.com/problems/find-the-number-of-ways-to-place-people-i/
 *
 * You are given a 2D array points of size n x 2 representing integer coordinates of some points on a 2D
 * plane, where points[i] = [xi, yi].
 * Count the number of pairs of points (A, B), where:
 *  A is on the upper left side of B, and
 *  there are no other points in the rectangle (or line) they make (including the border).
 * Return the count.
 *
 * @reference   Find the Number of Ways to Place People II
 *              https://leetcode.com/problems/find-the-number-of-ways-to-place-people-ii/
 *
 * You are given a 2D array points of size n x 2 representing integer coordinates of some points on a
 * 2D-plane, where points[i] = [xi, yi].
 * We define the right direction as positive x-axis (increasing x-coordinate) and the left direction as
 * negative x-axis (decreasing x-coordinate). Similarly, we define the up direction as positive y-axis
 * (increasing y-coordinate) and the down direction as negative y-axis (decreasing y-coordinate)
 * You have to place n people, including Alice and Bob, at these points such that there is exactly one
 * person at every point. Alice wants to be alone with Bob, so Alice will build a rectangular fence with
 * Alice's position as the upper left corner and Bob's position as the lower right corner of the fence
 * (Note that the fence might not enclose any area, i.e. it can be a line). If any person other than
 * Alice and Bob is either inside the fence or on the fence, Alice will be sad.
 * Return the number of pairs of points where you can place Alice and Bob, such that Alice does not
 * become sad on building the fence.
 * Note that Alice can only build a fence with Alice's position as the upper left corner, and Bob's
 * position as the lower right corner. For example, Alice cannot build either of the fences in the
 * picture below with four corners (1, 1), (1, 3), (3, 1), and (3, 3), because:
 *  With Alice at (3, 3) and Bob at (1, 1), Alice's position is not the upper left corner and Bob's
 *      position is not the lower right corner of the fence.
 *  With Alice at (1, 3) and Bob at (1, 1), Bob's position is not the lower right corner of the fence.
 * All points[i] are distinct.
 *
 * @tags    #geometry #rectangle #sorting #min-max-element
 */
auto NumberOfValidPairs(ArrayType points) {
    const auto Compare = [](const auto &one, const auto &another) {
        if (one[0] == another[0]) {
            return one[1] > another[1];
        }

        return one[0] < another[0];
    };

    std::sort(points.begin(), points.end(), Compare);

    const int N = points.size();
    int result = 0;
    for (int i = 0; i < N - 1; ++i) {
        const auto &left = points[i];
        int y_min = INT_MIN;
        const int y_max = left[1] + 1;

        for (int j = i + 1; j < N; ++j) {
            const auto &right = points[j];
            if (right[1] > y_min and right[1] < y_max) {
                ++result;
                y_min = right[1];
            }
        }
    }

    return result;
}

} //namespace


constexpr Rectangle SAMPLE_R1 = {0, 10, 8, 0};
constexpr Point SAMPLE_P1 = {1, 5};
constexpr Rectangle SAMPLE_R2 = {4, 2, 3, -1};
constexpr Point SAMPLE_P2 = {0, 4};


THE_BENCHMARK(Contains, SAMPLE_R1, SAMPLE_P1);

SIMPLE_TEST(Contains, TestSAMPLE1, true, SAMPLE_R1, SAMPLE_P1);
SIMPLE_TEST(Contains, TestSAMPLE2, false, SAMPLE_R2, SAMPLE_P2);


const ArrayType SAMPLE1P = {{1, 1}, {2, 2}, {3, 3}};
const ArrayType SAMPLE2P = {{6, 2}, {4, 4}, {2, 6}};
const ArrayType SAMPLE3P = {{3, 1}, {1, 3}, {1, 1}};
const ArrayType SAMPLE4P = {{0, 1}, {1, 3}, {6, 1}};


THE_BENCHMARK(NumberOfValidPairs, SAMPLE1P);

SIMPLE_TEST(NumberOfValidPairs, TestSAMPLE1, 0, SAMPLE1P);
SIMPLE_TEST(NumberOfValidPairs, TestSAMPLE2, 2, SAMPLE2P);
SIMPLE_TEST(NumberOfValidPairs, TestSAMPLE3, 2, SAMPLE3P);
SIMPLE_TEST(NumberOfValidPairs, TestSAMPLE4, 2, SAMPLE4P);
