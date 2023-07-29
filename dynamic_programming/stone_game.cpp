#include "common_header.h"

#include "mathematics/arithmetics/sum/prefix_sum_array.h"
#include "mathematics/arithmetics/sum/range_sum_queries.h"
#include "mathematics/matrix/matrix.h"


namespace {

using ArrayType = std::vector<int>;
using MemoType = MatrixType;

/** Stone Game
 *
 * @reference   https://leetcode.com/problems/stone-game/
 *
 * Alice and Bob play a game with piles of stones. There are an even number of piles arranged in a row,
 * and each pile has a positive integer number of stones piles[i].
 * The objective of the game is to end with the most stones. The total number of stones across all the
 * piles is odd, so there are no ties.
 * Alice and Bob take turns, with Alice starting first. Each turn, a player takes the entire pile of
 * stones either from the beginning or from the end of the row. This continues until there are no more
 * piles left, at which point the person with the most stones wins.
 * Assuming Alice and Bob play optimally, return true if Alice wins the game, or false if Bob wins.
 */
inline auto StoneGameEvenPiles(const ArrayType &) {
    return true;
}


auto StoneGameEvenPiles_DP(const ArrayType &piles) {
    assert(piles.size() % 2 == 0);

    const auto N = piles.size();

    int dp[N + 2][N + 2] = {};
    for (std::size_t size = 1; size <= N; ++size) {
        for (int i = 0; i + size <= N; ++i) {
            int j = i + size - 1;
            const bool alex_turn = (j + i) % 2;
            if (alex_turn == 1) {
                dp[i + 1][j + 1] = std::max(dp[i + 2][j + 1] + piles[i], dp[i + 1][j] + piles[j]);
            } else {
                dp[i + 1][j + 1] = std::min(dp[i + 2][j + 1] - piles[i], dp[i + 1][j] - piles[j]);
            }
        }
    }

    return dp[1][N] > 0;
}


/**
 * @reference   Predict the Winner
 *              https://leetcode.com/problems/predict-the-winner/
 *
 * You are given an integer array nums. Two players are playing a game with this array: player 1 and
 * player 2.
 * Player 1 and player 2 take turns, with player 1 starting first. Both players start the game with a
 * score of 0. At each turn, the player takes one of the numbers from either end of the array (i.e.,
 * nums[0] or nums[nums.length - 1]) which reduces the size of the array by 1. The player adds the
 * chosen number to their score. The game ends when there are no more elements in the array.
 * Return true if Player 1 can win the game. If the scores of both players are equal, then player 1 is
 * still the winner, and you should also return true. You may assume that both players are playing
 * optimally.
 */
auto PredictTheWinner(const ArrayType &nums) {
    if (nums.size() % 2 == 0) {
        return true;
    }

    const int N = nums.size();
    auto dp = nums;
    for (int size = 1; size < N; ++size) {
        for (int left = 0; left < N - size; ++left) {
            const auto right = left + size;
            dp[left] = std::max(nums[left] - dp[left + 1], nums[right] - dp[left]);
        }
    }

    return dp[0] >= 0;
}


/**
 * @reference   Stone Game II
 *              https://leetcode.com/problems/stone-game-ii/
 * @reference   https://www.cnblogs.com/grandyang/p/14899090.html
 *
 * Alice and Bob continue their games with piles of stones.  There are a number of piles arranged in a
 * row, and each pile has a positive integer number of stones piles[i].  The objective of the game is to
 * end with the most stones.
 * Alice and Bob take turns, with Alice starting first.  Initially, M = 1.
 * On each player's turn, that player can take all the stones in the first X remaining piles, where 1 <=
 * X <= 2M.  Then, we set M = max(M, X).
 * The game continues until all the stones have been taken.
 * Assuming Alice and Bob play optimally, return the maximum number of stones Alice can get.
 */
auto StoneGameII_Memo(const ArrayType &suffix_sums,
                      const std::size_t i,
                      const std::size_t m,
                      MemoType &memo) {
    if (i + 2 * m >= suffix_sums.size()) {
        return suffix_sums[i];
    }

    if (memo[i][m] > 0) {
        return memo[i][m];
    }

    int result = 0;
    for (std::size_t x = 1; x <= 2 * m; ++x) {
        const auto current = suffix_sums[i] - suffix_sums[i + x];
        result = std::max(result,
                          current + suffix_sums[i + x] -
                              StoneGameII_Memo(suffix_sums, i + x, std::max(x, m), memo));
    }
    return memo[i][m] = result;
}

inline auto StoneGameII_Memo(const ArrayType &piles) {
    auto suffix_sums = piles;
    for (int i = piles.size() - 2; i >= 0; --i) {
        suffix_sums[i] += suffix_sums[i + 1];
    }
    MemoType memo(piles.size(), std::vector(piles.size(), 0));
    return StoneGameII_Memo(suffix_sums, 0, 1, memo);
}


auto StoneGameII_DP(const ArrayType &piles) {
    const int N = piles.size();
    auto suffix_sums = piles;
    for (int i = N - 2; i >= 0; --i) {
        suffix_sums[i] += suffix_sums[i + 1];
    }

    int dp[N + 1][N + 1] = {};
    for (int i = 0; i < N; ++i) {
        dp[i][N] = suffix_sums[i];
    }

    for (int i = N - 1; i >= 0; --i) {
        for (int m = N - 1; m >= 1; --m) {
            for (int x = 1; x <= 2 * m and i + x <= N; ++x) {
                dp[i][m] = std::max(dp[i][m], suffix_sums[i] - dp[i + x][std::max(m, x)]);
            }
        }
    }

    return dp[0][1];
}


/**
 * @reference   Stone Game III
 *              https://leetcode.com/problems/stone-game-iii/
 * @reference   https://walkccc.me/LeetCode/problems/1406/
 *
 * Alice and Bob continue their games with piles of stones. There are several stones arranged in a row,
 * and each stone has an associated value which is an integer given in the array stoneValue.
 * Alice and Bob take turns, with Alice starting first. On each player's turn, that player can take 1,
 * 2, or 3 stones from the first remaining stones in the row.
 * The score of each player is the sum of the values of the stones taken. The score of each player is 0
 * initially.
 * The objective of the game is to end with the highest score, and the winner is the player with the
 * highest score and there could be a tie. The game continues until all the stones have been taken.
 * Assume Alice and Bob play optimally.
 * Return "Alice" if Alice will win, "Bob" if Bob will win, or "Tie" if they will end the game with the
 * same score.
 */
inline constexpr auto toResult(const int score) {
    if (score > 0) {
        return "Alice";
    } else if (score < 0) {
        return "Bob";
    }
    return "Tie";
}

auto StoneGame3_Memo(const ArrayType &values, const std::size_t i, ArrayType &memo) {
    if (i == values.size()) {
        return 0;
    }

    if (memo[i] > INT_MIN) {
        return memo[i];
    }

    int sum = 0;
    for (auto j = i; j < i + 3 and j < values.size(); ++j) {
        sum += values[j];
        memo[i] = std::max(memo[i], sum - StoneGame3_Memo(values, j + 1, memo));
    }

    return memo[i];
}

inline auto StoneGame3_Memo(const ArrayType &values) {
    std::vector memo(values.size(), INT_MIN);
    const auto score = StoneGame3_Memo(values, 0, memo);
    return toResult(score);
}


auto StoneGame3_DP(const ArrayType &values) {
    std::vector dp(values.size() + 1, INT_MIN / 2);
    dp.back() = 0;

    for (int i = values.size() - 1; i >= 0; --i) {
        int sum = 0;
        for (std::size_t j = i; j < i + 3u and j < values.size(); ++j) {
            sum += values[j];
            dp[i] = std::max(dp[i], sum - dp[j + 1]);
        }
    }

    return toResult(dp[0]);
}


/**
 * @reference   Stone Game IV
 *              https://leetcode.com/problems/stone-game-iv/
 *
 * Alice and Bob take turns playing a game, with Alice starting first.
 * Initially, there are n stones in a pile. On each player's turn, that player makes a move consisting
 * of removing any non-zero square number of stones in the pile.
 * Also, if a player cannot make a move, he/she loses the game.
 * Given a positive integer n, return true if and only if Alice wins the game otherwise return false,
 * assuming both players play optimally.
 */
auto StoneGame4_Memo(const int n, std::unordered_map<int, bool> &memo) {
    const auto [iter, inserted] = memo.emplace(n, false);
    if (not inserted) {
        return iter->second;
    }

    for (int i = 1; i <= std::sqrt(n); ++i) {
        if (not StoneGame4_Memo(n - i * i, memo)) {
            iter->second = true;
            return true;
        }
    }

    return false;
}

inline auto StoneGame4_Memo(const int n) {
    std::unordered_map<int, bool> memo = {{0, false}};
    return StoneGame4_Memo(n, memo);
}


inline constexpr auto StoneGame4_DP(const int n) {
    bool dp[n + 1] = {};

    for (int i = 0; i <= n; ++i) {
        for (int k = 1; k * k <= i; ++k) {
            if (dp[i - k * k] == false) {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[n];
}


/**
 * @reference   Stone Game V
 *              https://leetcode.com/problems/stone-game-v/
 *
 * There are several stones arranged in a row, and each stone has an associated value which is an
 * integer given in the array stoneValue.
 * In each round of the game, Alice divides the row into two non-empty rows (i.e. left row and right
 * row), then Bob calculates the value of each row which is the sum of the values of all the stones in
 * this row. Bob throws away the row which has the maximum value, and Alice's score increases by the
 * value of the remaining row. If the value of the two rows are equal, Bob lets Alice decide which row
 * will be thrown away. The next round starts with the remaining row.
 * The game ends when there is only one stone remaining. Alice's is initially zero.
 * Return the maximum score that Alice can obtain.
 */
auto StoneGame5_Memo(const ArrayType &prefix_sum,
                     const int left,
                     const int right,
                     MemoType &memo) {
    if (left == right) {
        return 0;
    }

    if (memo[left][right]) {
        return memo[left][right];
    }

    int maximum = 0;
    for (auto i = left; i < right; ++i) {
        const auto left_sum = RangeSum(prefix_sum, left, i);
        const auto right_sum = RangeSum(prefix_sum, i + 1, right);

        int total = 0;
        if (left_sum > right_sum) {
            total = right_sum + StoneGame5_Memo(prefix_sum, i + 1, right, memo);
        } else if (left_sum < right_sum) {
            total = left_sum + StoneGame5_Memo(prefix_sum, left, i, memo);
        } else {
            total = left_sum + std::max(StoneGame5_Memo(prefix_sum, left, i, memo),
                                        StoneGame5_Memo(prefix_sum, i + 1, right, memo));
        }
        maximum = std::max(maximum, total);
    }

    memo[left][right] = maximum;
    return maximum;
}

inline auto StoneGame5_Memo(ArrayType values) {
    const auto N = values.size();
    const auto prefix_sum = PrefixSumArray(std::move(values));
    MemoType memo = std::vector(N, std::vector(N, 0));
    return StoneGame5_Memo(prefix_sum, 0, N - 1, memo);
}


auto StoneGame5_DP_Optimized(const ArrayType &values) {
    const int N = values.size();
    int dp[N][N] = {};
    int max[N][N] = {};
    for (int i = 0; i < N; ++i) {
        max[i][i] = values[i];
    }

    for (int j = 1; j < N; ++j) {
        int mid = j, sum = values[j], right_half = 0;
        for (int i = j - 1; i >= 0; --i) {
            sum += values[i];
            while ((right_half + values[mid]) * 2 <= sum) {
                right_half += values[mid--];
            }
            dp[i][j] = right_half * 2 == sum ? max[i][mid] : (mid == i ? 0 : max[i][mid - 1]);
            dp[i][j] = std::max(dp[i][j], mid == j ? 0 : max[j][mid + 1]);
            max[i][j] = std::max(max[i][j - 1], dp[i][j] + sum);
            max[j][i] = std::max(max[j][i + 1], dp[i][j] + sum);
        }
    }

    return dp[0][N - 1];
}


/**
 * @reference   Stone Game VI
 *              https://leetcode.com/problems/stone-game-vi/
 *
 * Alice and Bob take turns playing a game, with Alice starting first.
 * There are n stones in a pile. On each player's turn, they can remove a stone from the pile and
 * receive points based on the stone's value. Alice and Bob may value the stones differently.
 * You are given two integer arrays of length n, aliceValues and bobValues. Each aliceValues[i] and
 * bobValues[i] represents how Alice and Bob, respectively, value the ith stone.
 * The winner is the person with the most points after all the stones are chosen. If both players have
 * the same amount of points, the game results in a draw. Both players will play optimally.  Both
 * players know the other's values.
 * Determine the result of the game, and:
 *  If Alice wins, return 1.
 *  If Bob wins, return -1.
 *  If the game results in a draw, return 0.
 */
auto StoneGame6(const ArrayType &alice_values, const ArrayType &bob_values) {
    assert(alice_values.size() == bob_values.size());

    ArrayType stones;
    for (std::size_t i = 0; i < alice_values.size(); ++i) {
        stones.push_back(i);
    }

    std::sort(stones.begin(),
              stones.end(),
              [&alice_values, &bob_values](const auto lhs, const auto rhs) {
                  return alice_values[lhs] + bob_values[lhs] >
                         alice_values[rhs] + bob_values[rhs];
              });

    bool alice_turn = true;
    int score = 0;
    for (const auto index : stones) {
        if (alice_turn) {
            score += alice_values[index];
        } else {
            score -= bob_values[index];
        }

        alice_turn = !alice_turn;
    }

    if (score) {
        return score > 0 ? 1 : -1;
    }
    return score;
}


auto StoneGame6_O1(ArrayType alice_values, const ArrayType &bob_values) {
    int diff = 0;
    const auto N = alice_values.size();
    for (std::size_t i = 0; i < N; ++i) {
        alice_values[i] += bob_values[i];
        diff -= bob_values[i];
    }

    std::sort(alice_values.begin(), alice_values.end());

    for (int i = alice_values.size() - 1; i >= 0; i -= 2) {
        diff += alice_values[i];
    }

    if (diff) {
        return diff > 0 ? 1 : -1;
    }
    return diff;
}


/**
 * @reference   Stone Game VII
 *              https://leetcode.com/problems/stone-game-vii/
 *
 * Alice and Bob take turns playing a game, with Alice starting first.
 * There are n stones arranged in a row. On each player's turn, they can remove either the leftmost
 * stone or the rightmost stone from the row and receive points equal to the sum of the remaining
 * stones' values in the row. The winner is the one with the higher score when there are no stones left
 * to remove.
 * Bob found that he will always lose this game (poor Bob, he always loses), so he decided to minimize
 * the score's difference. Alice's goal is to maximize the difference in the score.
 * Given an array of integers stones where stones[i] represents the value of the ith stone from the
 * left, return the difference in Alice and Bob's score if they both play optimally.
 */
auto StoneGame7_Memo(const ArrayType &prefix_sum,
                     const int left,
                     const int right,
                     MemoType &memo) {
    if (left > right) {
        return 0;
    }

    if (memo[left][right]) {
        return memo[left][right];
    }

    const auto left_score = RangeSum(prefix_sum, left + 1, right) -
                            StoneGame7_Memo(prefix_sum, left + 1, right, memo);
    const auto right_score = RangeSum(prefix_sum, left, right - 1) -
                             StoneGame7_Memo(prefix_sum, left, right - 1, memo);

    memo[left][right] = std::max(left_score, right_score);
    return memo[left][right];
}

inline auto StoneGame7_Memo(ArrayType stones) {
    const auto N = stones.size();
    const auto prefix_sum = PrefixSumArray(std::move(stones));
    MemoType memo = std::vector(N, std::vector(N, 0));
    return StoneGame7_Memo(prefix_sum, 0, N - 1, memo);
}


auto StoneGame7_DP(const ArrayType &stones) {
    int dp[stones.size()] = {};
    for (int i = stones.size() - 2; i >= 0; --i) {
        auto total = stones[i];
        for (std::size_t j = i + 1; j < stones.size(); ++j) {
            total += stones[j];
            dp[j] = std::max(total - stones[i] - dp[j], total - stones[j] - dp[j - 1]);
        }
    }

    return dp[stones.size() - 1];
}


/**
 * @reference   Stone Game VIII
 *              https://leetcode.com/problems/stone-game-viii/
 *
 * Alice and Bob take turns playing a game, with Alice starting first.
 * There are n stones arranged in a row. On each player's turn, while the number of stones is more than
 * one, they will do the following:
 *  Choose an integer x > 1, and remove the leftmost x stones from the row.
 *  Add the sum of the removed stones' values to the player's score.
 *  Place a new stone, whose value is equal to that sum, on the left side of the row.
 * The game stops when only one stone is left in the row.
 * The score difference between Alice and Bob is (Alice's score - Bob's score). Alice's goal is to
 * maximize the score difference, and Bob's goal is the minimize the score difference.
 * Given an integer array stones of length n where stones[i] represents the value of the ith stone from
 * the left, return the score difference between Alice and Bob if they both play optimally.
 */
auto StoneGame8_DP(ArrayType stones) {
    const auto N = stones.size();
    for (std::size_t i = 1; i < N; ++i) {
        stones[i] += stones[i - 1];
    }

    int dp = stones.back();
    for (int i = stones.size() - 2; i > 0; --i) {
        dp = std::max(dp, stones[i] - dp);
    }

    return dp;
}

} //namespace


const ArrayType SAMPLE1 = {5, 3, 4, 5};


THE_BENCHMARK(StoneGameEvenPiles, SAMPLE1);

SIMPLE_TEST(StoneGameEvenPiles, TestSAMPLE1, true, SAMPLE1);


THE_BENCHMARK(StoneGameEvenPiles_DP, SAMPLE1);

SIMPLE_TEST(StoneGameEvenPiles_DP, TestSAMPLE1, true, SAMPLE1);


const ArrayType SAMPLE2 = {2, 7, 9, 4, 4};
const ArrayType SAMPLE3 = {1, 2, 3, 4, 5, 100};


THE_BENCHMARK(StoneGameII_Memo, SAMPLE2);

SIMPLE_TEST(StoneGameII_Memo, TestSAMPLE2, 10, SAMPLE2);
SIMPLE_TEST(StoneGameII_Memo, TestSAMPLE3, 104, SAMPLE3);


THE_BENCHMARK(StoneGameII_DP, SAMPLE2);

SIMPLE_TEST(StoneGameII_DP, TestSAMPLE2, 10, SAMPLE2);
SIMPLE_TEST(StoneGameII_DP, TestSAMPLE3, 104, SAMPLE3);


const ArrayType SAMPLE4 = {1, 2, 3, 7};
const ArrayType SAMPLE5 = {1, 2, 3, -9};
const ArrayType SAMPLE6 = {1, 2, 3, 6};
const ArrayType SAMPLE7 = {1, 2, 3, -1, -2, -3, 7};
const ArrayType SAMPLE8 = {-1, -2, -3};


THE_BENCHMARK(StoneGame3_Memo, SAMPLE7);

SIMPLE_TEST(StoneGame3_Memo, TestSAMPLE4, "Bob", SAMPLE4);
SIMPLE_TEST(StoneGame3_Memo, TestSAMPLE5, "Alice", SAMPLE5);
SIMPLE_TEST(StoneGame3_Memo, TestSAMPLE6, "Tie", SAMPLE6);
SIMPLE_TEST(StoneGame3_Memo, TestSAMPLE7, "Alice", SAMPLE7);
SIMPLE_TEST(StoneGame3_Memo, TestSAMPLE8, "Tie", SAMPLE8);


THE_BENCHMARK(StoneGame3_DP, SAMPLE7);

SIMPLE_TEST(StoneGame3_DP, TestSAMPLE4, "Bob", SAMPLE4);
SIMPLE_TEST(StoneGame3_DP, TestSAMPLE5, "Alice", SAMPLE5);
SIMPLE_TEST(StoneGame3_DP, TestSAMPLE6, "Tie", SAMPLE6);
SIMPLE_TEST(StoneGame3_DP, TestSAMPLE7, "Alice", SAMPLE7);
SIMPLE_TEST(StoneGame3_DP, TestSAMPLE8, "Tie", SAMPLE8);


THE_BENCHMARK(StoneGame4_Memo, 17);

SIMPLE_TEST(StoneGame4_Memo, TestSAMPLE1, true, 1);
SIMPLE_TEST(StoneGame4_Memo, TestSAMPLE2, false, 2);
SIMPLE_TEST(StoneGame4_Memo, TestSAMPLE3, true, 4);
SIMPLE_TEST(StoneGame4_Memo, TestSAMPLE4, false, 7);
SIMPLE_TEST(StoneGame4_Memo, TestSAMPLE5, false, 17);


THE_BENCHMARK(StoneGame4_DP, 17);

SIMPLE_TEST(StoneGame4_DP, TestSAMPLE1, true, 1);
SIMPLE_TEST(StoneGame4_DP, TestSAMPLE2, false, 2);
SIMPLE_TEST(StoneGame4_DP, TestSAMPLE3, true, 4);
SIMPLE_TEST(StoneGame4_DP, TestSAMPLE4, false, 7);
SIMPLE_TEST(StoneGame4_DP, TestSAMPLE5, false, 17);


const ArrayType SAMPLE9 = {6, 2, 3, 4, 5, 5};
const ArrayType SAMPLE10 = {7, 7, 7, 7, 7, 7, 7};
const ArrayType SAMPLE11 = {4};


THE_BENCHMARK(StoneGame5_Memo, SAMPLE9);

SIMPLE_TEST(StoneGame5_Memo, TestSAMPLE9, 18, SAMPLE9);
SIMPLE_TEST(StoneGame5_Memo, TestSAMPLE10, 28, SAMPLE10);
SIMPLE_TEST(StoneGame5_Memo, TestSAMPLE11, 0, SAMPLE11);


THE_BENCHMARK(StoneGame5_DP_Optimized, SAMPLE9);

SIMPLE_TEST(StoneGame5_DP_Optimized, TestSAMPLE9, 18, SAMPLE9);
SIMPLE_TEST(StoneGame5_DP_Optimized, TestSAMPLE10, 28, SAMPLE10);
SIMPLE_TEST(StoneGame5_DP_Optimized, TestSAMPLE11, 0, SAMPLE11);


const ArrayType SAMPLE1A = {1, 3};
const ArrayType SAMPLE1B = {2, 1};

const ArrayType SAMPLE2A = {1, 2};
const ArrayType SAMPLE2B = {3, 1};

const ArrayType SAMPLE3A = {2, 4, 3};
const ArrayType SAMPLE3B = {1, 6, 7};


THE_BENCHMARK(StoneGame6, SAMPLE1A, SAMPLE1B);

SIMPLE_TEST(StoneGame6, TestSAMPLE1, 1, SAMPLE1A, SAMPLE1B);
SIMPLE_TEST(StoneGame6, TestSAMPLE2, 0, SAMPLE2A, SAMPLE2B);
SIMPLE_TEST(StoneGame6, TestSAMPLE3, -1, SAMPLE3A, SAMPLE3B);


THE_BENCHMARK(StoneGame6_O1, SAMPLE1A, SAMPLE1B);

SIMPLE_TEST(StoneGame6_O1, TestSAMPLE1, 1, SAMPLE1A, SAMPLE1B);
SIMPLE_TEST(StoneGame6_O1, TestSAMPLE2, 0, SAMPLE2A, SAMPLE2B);
SIMPLE_TEST(StoneGame6_O1, TestSAMPLE3, -1, SAMPLE3A, SAMPLE3B);


const ArrayType SAMPLE12 = {5, 3, 1, 4, 2};
const ArrayType SAMPLE13 = {7, 90, 5, 1, 100, 10, 10, 2};


THE_BENCHMARK(StoneGame7_Memo, SAMPLE12);

SIMPLE_TEST(StoneGame7_Memo, TestSAMPLE12, 6, SAMPLE12);
SIMPLE_TEST(StoneGame7_Memo, TestSAMPLE13, 122, SAMPLE13);


THE_BENCHMARK(StoneGame7_DP, SAMPLE12);

SIMPLE_TEST(StoneGame7_DP, TestSAMPLE12, 6, SAMPLE12);
SIMPLE_TEST(StoneGame7_DP, TestSAMPLE13, 122, SAMPLE13);


const ArrayType SAMPLE14 = {-1, 2, -3, 4, -5};
const ArrayType SAMPLE15 = {7, -6, 5, 10, 5, -2, -6};
const ArrayType SAMPLE16 = {-10, -12};


THE_BENCHMARK(StoneGame8_DP, SAMPLE14);

SIMPLE_TEST(StoneGame8_DP, TestSAMPLE14, 5, SAMPLE14);
SIMPLE_TEST(StoneGame8_DP, TestSAMPLE15, 13, SAMPLE15);
SIMPLE_TEST(StoneGame8_DP, TestSAMPLE16, -22, SAMPLE16);


const ArrayType SAMPLE1N = {1, 5, 2};
const ArrayType SAMPLE2N = {1, 5, 233, 7};
const ArrayType SAMPLE3N = {1, 5, 2, 4, 6};


THE_BENCHMARK(PredictTheWinner, SAMPLE1N);

SIMPLE_TEST(PredictTheWinner, TestSAMPLE1, false, SAMPLE1N);
SIMPLE_TEST(PredictTheWinner, TestSAMPLE2, true, SAMPLE2N);
SIMPLE_TEST(PredictTheWinner, TestSAMPLE3, true, SAMPLE3N);
