#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

/** Maximal Square
 *
 * @reference   https://leetcode.com/problems/maximal-square/
 *
 * Given an m x n binary matrix filled with 0's and 1's, find the largest square
 * containing only 1's and return its area.
 */
auto MaxSquare(const MatrixType &grid) {
    int dp[grid.size() + 1][grid.front().size() + 1] = {};

    int max_square_length = 0;
    for (std::size_t i = 1; i <= grid.size(); ++i) {
        for (std::size_t j = 1; j <= grid.front().size(); ++j) {
            if (grid[i - 1][j - 1] == '1') {
                dp[i][j] = std::min(std::min(dp[i][j - 1], dp[i - 1][j]),
                                    dp[i - 1][j - 1]) + 1;
                max_square_length = std::max(max_square_length, dp[i][j]);
            }
        }
    }

    return max_square_length * max_square_length;
}


auto MaxSquare_DP_On(const MatrixType &grid) {
    int dp[grid.front().size() + 1] = {};
    int max_square_length = 0;
    int prev = 0;

    for (std::size_t i = 1; i <= grid.size(); ++i) {
        for (std::size_t j = 1; j <= grid.front().size(); ++j) {
            const auto temp = dp[j];
            if (grid[i - 1][j - 1] == '1') {
                dp[j] = std::min(std::min(dp[j - 1], prev), dp[j]) + 1;
                max_square_length = std::max(max_square_length, dp[j]);
            } else {
                dp[j] = 0;
            }
            prev = temp;
        }
    }

    return max_square_length * max_square_length;
}


/**
 * @reference   Maximal Rectangle
 *              https://leetcode.com/problems/maximal-rectangle/
 *
 * Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle
 * containing only 1's and return its area.
 */
auto MaxRectangle(const MatrixType &grid) {
    const auto M = grid.size();
    const auto N = grid.front().size();

    int adjecent_1s_on_left[M + 1][N + 1] = {};
    for (std::size_t i = 1; i <= M; ++i) {
        for (std::size_t j = 1; j <= N; ++j) {
            if (grid[i - 1][j - 1] == '1') {
                adjecent_1s_on_left[i][j] = 1 + adjecent_1s_on_left[i][j - 1];
            }
        }
    }

    int result = 0;
    for (std::size_t i = 1; i <= M; ++i) {
        for (std::size_t j = 1; j <= N; ++j) {
            int width = adjecent_1s_on_left[i][j];
            int k = i - 1;
            int height = 1;
            result = std::max(result, width * height);

            while (k > 0 and adjecent_1s_on_left[k][j] > 0) {
                ++height;
                width = std::min(width, adjecent_1s_on_left[k--][j]);
                result = std::max(width * height, result);
            }
        }
    }

    return result;
}

auto MaxRectangle_MonotonicStack(const std::vector<int> &dp) {
    std::stack<int> s;
    s.push(-1);

    int max_area = 0;
    for (std::size_t i = 0; i <= dp.size(); ++i) {
        const auto v = (i == dp.size()) ? -1 : dp[i];
        while (s.top() != -1 and dp[s.top()] > v) {
            const auto height = dp[s.top()];
            s.pop();
            const int width = i - s.top() - 1;
            max_area = std::max(max_area, width * height);
        }
        s.push(i);
    }

    return max_area;
}

auto MaxRectangle_MonotonicStack(const MatrixType &grid) {
    const auto M = grid.size();
    const auto N = grid.front().size();

    std::vector dp(N, 0);
    int result = 0;
    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            if (grid[i][j] == '0') {
                dp[j] = 0;
            } else {
                ++(dp[j]);
            }
        }

        result = std::max(result, MaxRectangle_MonotonicStack(dp));
    }

    return result;
}

}//namespace


const MatrixType SAMPLE1 = {
    {'1', '0', '1', '0', '0'},
    {'1', '0', '1', '1', '1'},
    {'1', '1', '1', '1', '1'},
    {'1', '0', '0', '1', '0'}
};

const MatrixType SAMPLE2 = {
    {'0', '1'},
    {'1', '0'}
};

const MatrixType SAMPLE3 = {
    {'0'}
};

const MatrixType SAMPLE4 = {
    {'1'}
};


THE_BENCHMARK(MaxSquare, SAMPLE1);

SIMPLE_TEST(MaxSquare, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(MaxSquare, TestSAMPLE2, 1, SAMPLE2);
SIMPLE_TEST(MaxSquare, TestSAMPLE3, 0, SAMPLE3);


THE_BENCHMARK(MaxSquare_DP_On, SAMPLE1);

SIMPLE_TEST(MaxSquare_DP_On, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(MaxSquare_DP_On, TestSAMPLE2, 1, SAMPLE2);
SIMPLE_TEST(MaxSquare_DP_On, TestSAMPLE3, 0, SAMPLE3);


THE_BENCHMARK(MaxRectangle, SAMPLE1);

SIMPLE_TEST(MaxRectangle, TestSAMPLE1, 6, SAMPLE1);
SIMPLE_TEST(MaxRectangle, TestSAMPLE2, 1, SAMPLE2);
SIMPLE_TEST(MaxRectangle, TestSAMPLE3, 0, SAMPLE3);
SIMPLE_TEST(MaxRectangle, TestSAMPLE4, 1, SAMPLE4);


THE_BENCHMARK(MaxRectangle_MonotonicStack, SAMPLE1);

SIMPLE_TEST(MaxRectangle_MonotonicStack, TestSAMPLE1, 6, SAMPLE1);
SIMPLE_TEST(MaxRectangle_MonotonicStack, TestSAMPLE2, 1, SAMPLE2);
SIMPLE_TEST(MaxRectangle_MonotonicStack, TestSAMPLE3, 0, SAMPLE3);
SIMPLE_TEST(MaxRectangle_MonotonicStack, TestSAMPLE4, 1, SAMPLE4);
