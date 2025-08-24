#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Maximal Square
 *              https://leetcode.com/problems/maximal-square/
 *
 * Given an m x n binary matrix filled with 0's and 1's, find the largest square containing only 1's and
 * return its area.
 *
 * @tags    #DP #matrix
 */
auto MaxSquare(const MatrixType &grid) {
    int dp[grid.size() + 1][grid.front().size() + 1] = {};

    int max_square_length = 0;
    for (std::size_t i = 1; i <= grid.size(); ++i) {
        for (std::size_t j = 1; j <= grid.front().size(); ++j) {
            if (grid[i - 1][j - 1] == '1') {
                dp[i][j] = std::min({dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]}) + 1;
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
                dp[j] = std::min({dp[j - 1], prev, dp[j]}) + 1;
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
 * @reference   Count Square Submatrices with All Ones
 *              https://leetcode.com/problems/count-square-submatrices-with-all-ones/
 *
 * Given a m * n matrix of ones and zeros, return how many square submatrices have all ones.
 *
 * @tags    #DP #matrix
 */
auto CountSquares(const MatrixType &a_matrix) {
    const int M = a_matrix.size();
    const int N = a_matrix[0].size();

    std::vector dp(M + 1, std::vector(N + 1, 0));

    int result = 0;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (a_matrix[i][j]) {
                dp[i + 1][j + 1] = std::min({dp[i][j + 1], dp[i + 1][j], dp[i][j]}) + 1;
                result += dp[i + 1][j + 1];
            }
        }
    }

    return result;
}


/**
 * @reference   Maximal Rectangle
 *              https://leetcode.com/problems/maximal-rectangle/
 *
 * Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only
 * 1's and return its area.
 *
 * @tags    #DP #matrix
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


/**
 * @reference   Count Submatrices With All Ones
 *              https://leetcode.com/problems/count-submatrices-with-all-ones/
 *
 * Given an m x n binary matrix mat, return the number of submatrices that have all ones.
 *
 * @tags    #DP #matrix
 */
auto CountRectangle(const MatrixType &grid) {
    const auto M = grid.size();
    const auto N = grid.front().size();

    std::vector adjecent_1s_on_left(M + 1, std::vector(N + 1, 0));
    int result = 0;
    for (std::size_t i = 1; i <= M; ++i) {
        for (std::size_t j = 1; j <= N; ++j) {
            if (grid[i - 1][j - 1]) {
                adjecent_1s_on_left[i][j] = 1 + adjecent_1s_on_left[i][j - 1];

                int width = adjecent_1s_on_left[i][j];
                for (int k = i; width;) {
                    width = std::min(width, adjecent_1s_on_left[k--][j]);
                    result += width;
                }
            }
        }
    }

    return result;
}


/**
 * @reference   Largest Rectangle in Histogram
 *              https://leetcode.com/problems/largest-rectangle-in-histogram/
 *
 * Given an array of integers heights representing the histogram's bar height where the width of each
 * bar is 1, return the area of the largest rectangle in the histogram.
 */
auto MaxRectangleInHistogram(const ArrayType &dp) {
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

    ArrayType dp(N, 0);
    int result = 0;
    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            if (grid[i][j] == '0') {
                dp[j] = 0;
            } else {
                ++(dp[j]);
            }
        }

        result = std::max(result, MaxRectangleInHistogram(dp));
    }

    return result;
}


/**
 * @reference   Largest Submatrix With Rearrangements
 *              https://leetcode.com/problems/largest-submatrix-with-rearrangements/
 *
 * You are given a binary matrix matrix of size m x n, and you are allowed to rearrange the columns of
 * the matrix in any order.
 * Return the area of the largest submatrix within matrix where every element of the submatrix is 1
 * after reordering the columns optimally.
 */
auto LargestSubmatrixWithRearrangements(const MatrixType &a_matrix) {
    const int N = a_matrix[0].size();

    int result = 0;
    std::vector prev_row(N, 0);
    for (auto current_row : a_matrix) {
        for (int column = 0; column < N; ++column) {
            if (current_row[column]) {
                current_row[column] += prev_row[column];
            }
        }
        prev_row = current_row;

        std::sort(current_row.begin(), current_row.end(), std::greater<int>());
        for (int i = 0; i < N; i++) {
            result = std::max(result, current_row[i] * (i + 1));
        }
    }

    return result;
}


/**
 * @reference   Maximum Score of a Good Subarray
 *              https://leetcode.com/problems/maximum-score-of-a-good-subarray/
 *
 * You are given an array of integers nums (0-indexed) and an integer k.
 * The score of a subarray (i, j) is defined as min(nums[i], nums[i+1], ..., nums[j]) * (j - i + 1). A
 * good subarray is a subarray where i <= k <= j.
 * Return the maximum possible score of a good subarray.
 */
auto MaxScoreOfGoodSubarray_TwoPointer(const ArrayType &nums, const int k) {
    auto result = nums[k];
    auto minimum = result;
    auto i = k;
    auto j = k;
    const int N = nums.size();

    while (i > 0 or j < N - 1) {
        if ((i > 0 ? nums[i - 1] : 0) < (j < N - 1 ? nums[j + 1] : 0)) {
            minimum = std::min(minimum, nums[++j]);
        } else {
            minimum = std::min(minimum, nums[--i]);
        }
        result = std::max(result, minimum * (j - i + 1));
    }

    return result;
}


/**
 * @reference   Sum of Subarray Minimums
 *              https://leetcode.com/problems/sum-of-subarray-minimums/
 *
 * Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous)
 * subarray of arr. Since the answer may be large, return the answer modulo 10^9 + 7.
 */
int SumOfSubarrayMins_MonotonicStack(const ArrayType &nums) {
    std::stack<long> s;

    long result = 0;
    for (std::size_t i = 0; i <= nums.size(); ++i) {
        while (not s.empty() and (i == nums.size() or nums[s.top()] >= nums[i])) {
            const long mid = s.top();
            s.pop();
            const long left = s.empty() ? -1 : s.top();
            const long right = i;

            const auto count = (mid - left) * (right - mid) % LARGE_PRIME;

            result = (result + (count * nums[mid])) % LARGE_PRIME;
        }
        s.push(i);
    }

    return result;
}

} //namespace


// clang-format off
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
// clang-format on

const MatrixType SAMPLE3 = {{'0'}};

const MatrixType SAMPLE4 = {{'1'}};


THE_BENCHMARK(MaxSquare, SAMPLE1);

SIMPLE_TEST(MaxSquare, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(MaxSquare, TestSAMPLE2, 1, SAMPLE2);
SIMPLE_TEST(MaxSquare, TestSAMPLE3, 0, SAMPLE3);


THE_BENCHMARK(MaxSquare_DP_On, SAMPLE1);

SIMPLE_TEST(MaxSquare_DP_On, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(MaxSquare_DP_On, TestSAMPLE2, 1, SAMPLE2);
SIMPLE_TEST(MaxSquare_DP_On, TestSAMPLE3, 0, SAMPLE3);


// clang-format off
const MatrixType SAMPLE1CS = {
    {0, 1, 1, 1},
    {1, 1, 1, 1},
    {0, 1, 1, 1}
};

const MatrixType SAMPLE2CS = {
    {1, 0, 1},
    {1, 1, 0},
    {1, 1, 0}
};

const MatrixType SAMPLE3CS = {
    {0, 1, 1, 1},
    {1, 1, 0, 1},
    {1, 1, 1, 1},
    {1, 0, 1, 0}
};

const MatrixType SAMPLE4CS = {
    {0, 1, 1, 0},
    {0, 1, 1, 1},
    {1, 1, 1, 0}
};
// clang-format on


THE_BENCHMARK(CountSquares, SAMPLE1CS);

SIMPLE_TEST(CountSquares, TestSAMPLE1, 15, SAMPLE1CS);
SIMPLE_TEST(CountSquares, TestSAMPLE2, 7, SAMPLE2CS);
SIMPLE_TEST(CountSquares, TestSAMPLE3, 13, SAMPLE3CS);


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


THE_BENCHMARK(CountRectangle, SAMPLE4CS);

SIMPLE_TEST(CountRectangle, TestSAMPLE2, 13, SAMPLE2CS);
SIMPLE_TEST(CountRectangle, TestSAMPLE4, 24, SAMPLE4CS);


// clang-format off
const MatrixType SAMPLE1L = {
    {0, 0, 1},
    {1, 1, 1},
    {1, 0, 1}
};

const MatrixType SAMPLE2L = {{1, 0, 1, 0, 1}};

const MatrixType SAMPLE3L = {
    {1, 1, 0},
    {1, 0, 1}
};
// clang-format on


THE_BENCHMARK(LargestSubmatrixWithRearrangements, SAMPLE1L);

SIMPLE_TEST(LargestSubmatrixWithRearrangements, TestSAMPLE1, 4, SAMPLE1L);
SIMPLE_TEST(LargestSubmatrixWithRearrangements, TestSAMPLE2, 3, SAMPLE2L);
SIMPLE_TEST(LargestSubmatrixWithRearrangements, TestSAMPLE3, 2, SAMPLE3L);


const ArrayType SAMPLE1H = {2, 1, 5, 6, 2, 3};
const ArrayType SAMPLE2H = {2, 4};


THE_BENCHMARK(MaxRectangleInHistogram, SAMPLE1H);

SIMPLE_TEST(MaxRectangleInHistogram, TestSAMPLE1, 10, SAMPLE1H);
SIMPLE_TEST(MaxRectangleInHistogram, TestSAMPLE2, 4, SAMPLE2H);


const ArrayType SAMPLE1S = {1, 4, 3, 7, 4, 5};
const ArrayType SAMPLE2S = {5, 5, 4, 5, 4, 1, 1, 1};


THE_BENCHMARK(MaxScoreOfGoodSubarray_TwoPointer, SAMPLE1S, 3);

SIMPLE_TEST(MaxScoreOfGoodSubarray_TwoPointer, TestSAMPLE1, 15, SAMPLE1S, 3);
SIMPLE_TEST(MaxScoreOfGoodSubarray_TwoPointer, TestSAMPLE2, 20, SAMPLE2S, 0);


const ArrayType SAMPLE1M = {3, 1, 2, 4};
const ArrayType SAMPLE2M = {11, 81, 94, 43, 3};


THE_BENCHMARK(SumOfSubarrayMins_MonotonicStack, SAMPLE1M);

SIMPLE_TEST(SumOfSubarrayMins_MonotonicStack, TestSAMPLE1, 17, SAMPLE1M);
SIMPLE_TEST(SumOfSubarrayMins_MonotonicStack, TestSAMPLE2, 444, SAMPLE2M);
