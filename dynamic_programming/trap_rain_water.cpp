#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

using ArrayType = std::vector<int>;

/** Trapping Rain Water
 *
 * @reference   https://leetcode.com/problems/trapping-rain-water/
 *
 * Given n non-negative integers representing an elevation map where the width of each
 * bar is 1, compute how much water it can trap after raining.
 */
auto TrapRain_DP(const ArrayType &heights) {
    if (heights.empty()) {
        return 0;
    }

    int left_max[heights.size()] = {heights[0]};
    for (std::size_t i = 1; i < heights.size(); ++i) {
        left_max[i] = std::max(heights[i], left_max[i - 1]);
    }

    int right_max[heights.size()] = {};
    right_max[heights.size() - 1] = heights.back();
    for (int i = heights.size() - 2; i >= 0; --i) {
        right_max[i] = std::max(heights[i], right_max[i + 1]);
    }

    int result = 0;
    for (std::size_t i = 1; i < heights.size() - 1; ++i) {
        result += std::min(left_max[i], right_max[i]) - heights[i];
    }

    return result;
}


auto TrapRain_Stack(const ArrayType &heights) {
    int result = 0;
    std::stack<int> monotonic_stack;
    for (std::size_t i = 0; i < heights.size();) {
        while (not monotonic_stack.empty() and heights[i] > heights[monotonic_stack.top()]) {
            const auto top = monotonic_stack.top();
            monotonic_stack.pop();
            if (monotonic_stack.empty()) {
                break;
            }
            const int distance = i - monotonic_stack.top() - 1;
            const int bounded_height =
                std::min(heights[i], heights[monotonic_stack.top()]) - heights[top];
            result += distance * bounded_height;
        }
        monotonic_stack.push(i++);
    }

    return result;
}


auto TrapRain_TwoPointer(const ArrayType &heights) {
    int left = 0, right = heights.size() - 1;
    int left_max = 0, right_max = 0;
    int result = 0;
    while (left < right) {
        if (heights[left] < heights[right]) {
            if (heights[left] >= left_max) {
                left_max = heights[left];
            } else {
                result += (left_max - heights[left]);
            }
            ++left;
        } else {
            if (heights[right] >= right_max) {
                right_max = heights[right];
            } else {
                result += (right_max - heights[right]);
            }
            --right;
        }
    }
    return result;
}


/**
 * @reference   Trapping Rain Water II
 *              https://leetcode.com/problems/trapping-rain-water-ii/
 * @reference   https://www.cnblogs.com/grandyang/p/5928987.html
 *
 * Given an m x n integer matrix heightMap representing the height of each unit cell in
 * a 2D elevation map, return the volume of water it can trap after raining.
 */
using HeightRowColumn = std::tuple<int, int, int>;

auto TrapRain2D(const MatrixType &a_matrix) {
    if (a_matrix.empty()) {
        return 0;
    }

    const int M = a_matrix.size();
    const int N = a_matrix.front().size();
    std::priority_queue<HeightRowColumn, std::vector<HeightRowColumn>, std::greater<HeightRowColumn>>
            min_heap;
    std::vector visited(M, std::vector(N, false));
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == 0 or i == M - 1 or j == 0 or j == N - 1) {
                min_heap.emplace(a_matrix[i][j], i, j);
                visited[i][j] = true;
            }
        }
    }

    int level = INT_MIN;
    int result = 0;
    while (not min_heap.empty()) {
        const auto [height, row, column] = min_heap.top();
        min_heap.pop();
        level = std::max(level, height);
        ForEachDirection(M, N, row, column,
        [&a_matrix, &min_heap, &visited, level, &result](const auto x, const auto y) {
            if (not visited[x][y]) {
                visited[x][y] = true;
                if (a_matrix[x][y] < level) {
                    result += level - a_matrix[x][y];
                }
                min_heap.emplace(a_matrix[x][y], x, y);
            }
        });
    }

    return result;
}


/**
 * @reference   Container With Most Water
 *              https://leetcode.com/problems/container-with-most-water/
 *
 * You are given an integer array height of length n. There are n vertical lines drawn such
 * that the two endpoints of the ith line are (i, 0) and (i, height[i]).
 * Find two lines that together with the x-axis form a container, such that the container
 * contains the most water.
 * Return the maximum amount of water a container can store.
 * Notice that you may not slant the container.
 */
auto ContainerWithMostWater(const ArrayType &heights) {
    int result = 0;
    int left = 0;
    int right = heights.size() - 1;
    while (left < right) {
        result = std::max(result, (right - left) * std::min(heights[left], heights[right]));

        if (heights[left] < heights[right]) {
            ++left;
        } else {
            --right;
        }
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
const ArrayType SAMPLE2 = {4, 2, 0, 3, 2, 5};


THE_BENCHMARK(TrapRain_DP, SAMPLE1);

SIMPLE_TEST(TrapRain_DP, TestSAMPLE1, 6, SAMPLE1);
SIMPLE_TEST(TrapRain_DP, TestSAMPLE2, 9, SAMPLE2);


THE_BENCHMARK(TrapRain_Stack, SAMPLE1);

SIMPLE_TEST(TrapRain_Stack, TestSAMPLE1, 6, SAMPLE1);
SIMPLE_TEST(TrapRain_Stack, TestSAMPLE2, 9, SAMPLE2);


THE_BENCHMARK(TrapRain_TwoPointer, SAMPLE1);

SIMPLE_TEST(TrapRain_TwoPointer, TestSAMPLE1, 6, SAMPLE1);
SIMPLE_TEST(TrapRain_TwoPointer, TestSAMPLE2, 9, SAMPLE2);


const MatrixType SAMPLE1M = {
    {1, 4, 3, 1, 3, 2},
    {3, 2, 1, 3, 2, 4},
    {2, 3, 3, 2, 3, 1}
};

const MatrixType SAMPLE2M = {
    {3, 3, 3, 3, 3},
    {3, 2, 2, 2, 3},
    {3, 2, 1, 2, 3},
    {3, 2, 2, 2, 3},
    {3, 3, 3, 3, 3}
};


THE_BENCHMARK(TrapRain2D, SAMPLE1M);

SIMPLE_TEST(TrapRain2D, TestSAMPLE1, 4, SAMPLE1M);
SIMPLE_TEST(TrapRain2D, TestSAMPLE2, 10, SAMPLE2M);


const ArrayType SAMPLE1W = {1, 8, 6, 2, 5, 4, 8, 3, 7};
const ArrayType SAMPLE2W = {1, 1};


THE_BENCHMARK(ContainerWithMostWater, SAMPLE1W);

SIMPLE_TEST(ContainerWithMostWater, TestSAMPLE1, 49, SAMPLE1W);
SIMPLE_TEST(ContainerWithMostWater, TestSAMPLE2, 1, SAMPLE2W);
