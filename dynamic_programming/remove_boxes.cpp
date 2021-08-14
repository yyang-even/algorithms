#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;
using MemoType = std::vector<std::vector<std::vector<int>>>;

/** Remove Boxes
 *
 * @reference   https://leetcode.com/problems/remove-boxes/
 * @reference   https://www.cnblogs.com/grandyang/p/6850657.html
 *
 * You are given several boxes with different colors represented by different positive
 * numbers. You may experience several rounds to remove boxes until there is no box left.
 * Each time you can choose some continuous boxes with the same color (i.e., composed of
 * k boxes, k >= 1), remove them and get k * k points. Return the maximum points you can
 * get.
 */
auto RemoveBoxes_Memo(const ArrayType &boxes, const int left, int right,
                      int k, MemoType &memo)  {
    if (left > right) {
        return 0;
    }

    if (memo[left][right][k] != 0) {
        return memo[left][right][k];
    }

    while (right > left and boxes[right] == boxes[right - 1]) {
        --right;
        ++k;
    }
    memo[left][right][k] = RemoveBoxes_Memo(boxes, left, right - 1, 0,
                                            memo) + (k + 1) * (k + 1);

    for (int i = left; i < right; ++i) {
        if (boxes[i] == boxes[right]) {
            memo[left][right][k] = std::max(memo[left][right][k],
                                            RemoveBoxes_Memo(boxes, left, i, k + 1, memo) + RemoveBoxes_Memo(boxes, i + 1,
                                                    right - 1, 0, memo));
        }
    }

    return memo[left][right][k];
}

inline auto RemoveBoxes_Memo(const ArrayType &boxes) {
    MemoType memo(boxes.size(), std::vector(boxes.size(), std::vector(boxes.size(), 0)));
    return RemoveBoxes_Memo(boxes, 0, boxes.size() - 1, 0, memo);
}


inline auto RemoveBoxes_DP(const ArrayType &boxes) {
    int dp[boxes.size()][boxes.size()][boxes.size()] = {};

    for (std::size_t i = 0; i < boxes.size(); ++i) {
        for (std::size_t k = 0; k <= i; ++k) {
            dp[i][i][k] = (1 + k) * (1 + k);
        }
    }

    for (std::size_t t = 1; t < boxes.size(); ++t) {
        for (std::size_t j = t; j < boxes.size(); ++j) {
            const auto i = j - t;
            for (std::size_t k = 0; k <= i; ++k) {
                int result = (1 + k) * (1 + k) + dp[i + 1][j][0];
                for (std::size_t m = i + 1; m <= j; ++m) {
                    if (boxes[m] == boxes[i]) {
                        result = std::max(result, dp[i + 1][m - 1][0] + dp[m][j][k + 1]);
                    }
                }
                dp[i][j][k] = result;
            }
        }
    }

    return boxes.size() == 0 ? 0 : dp[0][boxes.size() - 1][0];
}

}//namespace


const ArrayType SAMPLE1 = {1, 3, 2, 2, 2, 3, 4, 3, 1};
const ArrayType SAMPLE2 = {1, 1, 1};
const ArrayType SAMPLE3 = {1};


THE_BENCHMARK(RemoveBoxes_Memo, SAMPLE1);

SIMPLE_TEST(RemoveBoxes_Memo, TestSAMPLE1, 23, SAMPLE1);
SIMPLE_TEST(RemoveBoxes_Memo, TestSAMPLE2, 9, SAMPLE2);
SIMPLE_TEST(RemoveBoxes_Memo, TestSAMPLE3, 1, SAMPLE3);


THE_BENCHMARK(RemoveBoxes_DP, SAMPLE1);

SIMPLE_TEST(RemoveBoxes_DP, TestSAMPLE1, 23, SAMPLE1);
SIMPLE_TEST(RemoveBoxes_DP, TestSAMPLE2, 9, SAMPLE2);
SIMPLE_TEST(RemoveBoxes_DP, TestSAMPLE3, 1, SAMPLE3);
