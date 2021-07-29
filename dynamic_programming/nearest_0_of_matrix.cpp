#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

/** 01 Matrix
 *
 * @reference   https://leetcode.com/problems/01-matrix/
 *
 * Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.
 * The distance between two adjacent cells is 1.
 */
auto Nearest0_BFS(const MatrixType &a_matrix) {
    const int M = a_matrix.size();
    const int N = a_matrix.front().size();

    MatrixType results(M, std::vector(N, -1));

    std::queue<std::pair<int, int>> q;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (a_matrix[i][j] == 0) {
                results[i][j] = 0;
                q.emplace(i, j);
            }
        }
    }

    while (not q.empty()) {
        const auto [i, j] = q.front();
        q.pop();

        if (i != 0 and results[i - 1][j] < 0) {
            results[i - 1][j] = results[i][j] + 1;
            q.emplace(i - 1, j);
        }

        if (i != M - 1 and results[i + 1][j] < 0) {
            results[i + 1][j] = results[i][j] + 1;
            q.emplace(i + 1, j);
        }

        if (j != 0 and results[i][j - 1] < 0) {
            results[i][j - 1] = results[i][j] + 1;
            q.emplace(i, j - 1);
        }

        if (j != N - 1 and results[i][j + 1] < 0) {
            results[i][j + 1] = results[i][j] + 1;
            q.emplace(i, j + 1);
        }
    }

    return results;
}


auto Nearest0_DP(const MatrixType &a_matrix) {
    const int M = a_matrix.size();
    const int N = a_matrix.front().size();

    MatrixType results(M, std::vector(N, M + N));

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (a_matrix[i][j] == 0) {
                results[i][j] = 0;
            } else {
                if (i > 0) {
                    results[i][j] = std::min(results[i][j], results[i - 1][j] + 1);
                }
                if (j > 0) {
                    results[i][j] = std::min(results[i][j], results[i][j - 1] + 1);
                }
            }
        }
    }

    for (int i = M - 1; i >= 0; --i) {
        for (int j = N - 1; j >= 0; --j) {
            if (i < M - 1) {
                results[i][j] = std::min(results[i][j], results[i + 1][j] + 1);
            }
            if (j < N - 1) {
                results[i][j] = std::min(results[i][j], results[i][j + 1] + 1);
            }
        }
    }

    return results;
}

}//namespace


const MatrixType SAMPLE1 = {
    {0, 0, 0},
    {0, 1, 0},
    {0, 0, 0},
};

const MatrixType SAMPLE2 = {
    {0, 0, 0},
    {0, 1, 0},
    {1, 1, 1},
};

const MatrixType EXPECTED2 = {
    {0, 0, 0},
    {0, 1, 0},
    {1, 2, 1},
};


THE_BENCHMARK(Nearest0_BFS, SAMPLE1);

SIMPLE_TEST(Nearest0_BFS, TestSAMPLE1, SAMPLE1, SAMPLE1);
SIMPLE_TEST(Nearest0_BFS, TestSAMPLE2, EXPECTED2, SAMPLE2);


THE_BENCHMARK(Nearest0_DP, SAMPLE1);

SIMPLE_TEST(Nearest0_DP, TestSAMPLE1, SAMPLE1, SAMPLE1);
SIMPLE_TEST(Nearest0_DP, TestSAMPLE2, EXPECTED2, SAMPLE2);
