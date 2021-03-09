#include "common_header.h"


namespace {

using MatrixType = std::vector<std::vector<bool>>;

/** Count all possible paths from top left to bottom right of a mXn matrix
 *
 * @reference   https://www.geeksforgeeks.org/count-possible-paths-top-left-bottom-right-nxm-matrix/
 *
 * The problem is to count all the possible paths from top left to bottom right of a mXn
 * matrix with the constraints that from each cell you can either move only to right or
 * down.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 9.2.
 */
auto CountPossiblePaths_DP(const unsigned M, const unsigned N) {
    assert(M > 0);
    assert(N > 0);

    unsigned counts[M][N] = {};
    for (unsigned i = 0; i < M; ++i) {
        counts[i][0] = 1;
    }

    for (unsigned j = 0; j < N; ++j) {
        counts[0][j] = 1;
    }

    for (unsigned i = 1; i < M; ++i) {
        for (unsigned j = 1; j < N; ++j) {
            counts[i][j] = counts[i - 1][j] + counts[i][j - 1];
        }
    }

    return counts[M - 1][N - 1];
}

auto CountPossiblePaths_SpaceOptimized_DP(const unsigned M, const unsigned N) {
    assert(M > 0);
    assert(N > 0);

    unsigned counts[N] = {1};

    for (unsigned i = 0; i < M; ++i) {
        for (unsigned j = 1; j < N; ++j) {
            counts[j] += counts[j - 1];
        }
    }

    return counts[N - 1];
}

auto CountPossiblePaths_Combinatorics(const unsigned M, const unsigned N) {
    assert(M > 0);
    assert(N > 0);

    unsigned result = 1;
    for (auto i = N; i < (M + N - 1); ++i) {
        result *= i;
        result /= (i - N + 1);
    }

    return result;
}


/**
 * @reference   Unique paths in a Grid with Obstacles
 *              https://www.geeksforgeeks.org/unique-paths-in-a-grid-with-obstacles/
 *
 * Given a grid of size m * n, let us assume you are starting at (1, 1) and your goal
 * is to reach (m, n). At any instance, if you are on (x, y), you can either go to
 * (x, y + 1) or (x + 1, y). Now consider if some obstacles are added to the grids.
 * How many unique paths would there be? An obstacle and empty space are marked as 1
 * and 0 respectively in the grid.
 */
auto CountPossiblePathsWithObstacle(const MatrixType &maze) {
    assert(not maze.empty());
    assert(not maze.front().empty());

    const auto M = maze.size();
    const auto N = maze.front().size();

    unsigned counts[M][N] = {not maze[0][0]};
    for (unsigned i = 1; i < M; ++i) {
        if (not maze[i][0]) {
            counts[i][0] = counts[i - 1][0];
        }
    }

    for (unsigned j = 1; j < N; ++j) {
        if (not maze[0][j]) {
            counts[0][j] = counts[0][j - 1];
        }
    }

    for (unsigned i = 1; i < M; ++i) {
        for (unsigned j = 1; j < N; ++j) {
            if (not maze[i][j]) {
                counts[i][j] = counts[i - 1][j] + counts[i][j - 1];
            }
        }
    }

    return counts[M - 1][N - 1];
}

}//namespace


THE_BENCHMARK(CountPossiblePaths_DP, 2, 2);

SIMPLE_TEST(CountPossiblePaths_DP, TestSAMPLE1, 2, 2, 2);
SIMPLE_TEST(CountPossiblePaths_DP, TestSAMPLE2, 3, 2, 3);
SIMPLE_TEST(CountPossiblePaths_DP, TestSAMPLE3, 6, 3, 3);


THE_BENCHMARK(CountPossiblePaths_SpaceOptimized_DP, 2, 2);

SIMPLE_TEST(CountPossiblePaths_SpaceOptimized_DP, TestSAMPLE1, 2, 2, 2);
SIMPLE_TEST(CountPossiblePaths_SpaceOptimized_DP, TestSAMPLE2, 3, 2, 3);
SIMPLE_TEST(CountPossiblePaths_SpaceOptimized_DP, TestSAMPLE3, 6, 3, 3);


THE_BENCHMARK(CountPossiblePaths_Combinatorics, 2, 2);

SIMPLE_TEST(CountPossiblePaths_Combinatorics, TestSAMPLE1, 2, 2, 2);
SIMPLE_TEST(CountPossiblePaths_Combinatorics, TestSAMPLE2, 3, 2, 3);
SIMPLE_TEST(CountPossiblePaths_Combinatorics, TestSAMPLE3, 6, 3, 3);


const MatrixType SAMPLE1 = {
    { 0, 0, 0 },
    { 0, 1, 0 },
    { 0, 0, 0 }
};

const MatrixType SAMPLE2 = {
    { 0, 0, 0 },
    { 1, 1, 0 },
    { 0, 0, 0 }
};


THE_BENCHMARK(CountPossiblePathsWithObstacle, SAMPLE1);

SIMPLE_TEST(CountPossiblePathsWithObstacle, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(CountPossiblePathsWithObstacle, TestSAMPLE2, 1, SAMPLE2);
