#include "common_header.h"

#include "hash/hash.h"
#include "mathematics/matrix/matrix.h"


namespace {

using ArrayType = std::vector<int>;

/** Length of the Longest Consecutive 1s in Binary Representation
 *
 * @reference   https://www.geeksforgeeks.org/length-longest-consecutive-1s-binary-representation/
 *
 * The idea is based on the concept that if we AND a bit sequence with a shifted version
 * of itself, we're effectively removing the trailing 1 from every sequence of
 * consecutive 1s.
 */
constexpr auto LengthOfLongestConsecutive1s(unsigned number) {
    unsigned length = 0;
    while (number) {
        number &= (number << 1);
        ++length;
    }

    return length;
}


/** Length of longest consecutive zeroes in the binary representation of a number.
 *
 * @reference   https://www.geeksforgeeks.org/length-of-longest-consecutive-zeroes-in-the-binary-representation-of-a-number/
 */


/**
 * @reference   Maximum consecutive one’s (or zeros) in a binary array
 *              https://www.geeksforgeeks.org/maximum-consecutive-ones-or-zeros-in-a-binary-array/
 *
 * Given binary array, find count of maximum number of consecutive 1’s present in the array.
 *
 * @reference   Max Consecutive Ones
 *              https://leetcode.com/problems/max-consecutive-ones/
 */
auto LengthOfLongestConsecutive1s_Array(const ArrayType &number) {
    int count = 0;
    int max_count = 0;
    for (const auto a_digit : number) {
        if (a_digit) {
            if (++count > max_count) {
                max_count = count;
            }
        } else {
            count = 0;
        }
    }

    return max_count;
}


/**
 * @reference   Max Consecutive Ones II
 *              https://www.lintcode.com/problem/883/
 *
 * Given a binary array, find the maximum number of consecutive 1s in this array if you
 * can flip at most one 0.
 */
auto LengthOfLongestConsecutive1s_1Flip_Array(const ArrayType &number) {
    unsigned current_count = 0;
    unsigned prev_count = 0;
    unsigned max_count = 0;

    for (const auto digit : number) {
        if (digit == 0) {
            prev_count = current_count;
            current_count = 0;
        } else {
            ++current_count;
        }

        const auto total = current_count + prev_count + 1;
        if (total > max_count) {
            max_count = total;
        }
    }

    return std::min(max_count, static_cast<unsigned>(number.size()));
}


/**
 * @reference   Max Consecutive Ones III
 *              https://leetcode.com/problems/max-consecutive-ones-iii/
 *
 * Given a binary array nums and an integer k, return the maximum number of consecutive
 * 1's in the array if you can flip at most k 0's.
 */
auto LengthOfLongestConsecutive1s_KFlip_Array(const ArrayType &number, const int K) {
    ArrayType::size_type left = 0;
    int flipped_zeros = 0;
    ArrayType::size_type max_count = 0;

    for (ArrayType::size_type right = 0; right < number.size(); ++right) {
        if (number[right] == 0) {
            ++flipped_zeros;
        }

        while (flipped_zeros > K) {
            if (number[left++] == 0) {
                --flipped_zeros;
            }
        }

        const auto total = right - left + 1;
        if (total > max_count) {
            max_count = total;
        }
    }

    return max_count;
}


/**
 * @reference   Making A Large Island
 *              https://leetcode.com/problems/making-a-large-island/
 *
 * You are given an n x n binary matrix grid. You are allowed to change at most one 0 to
 * be 1. Return the size of the largest island in grid after applying this operation. An
 * island is a 4-directionally connected group of 1s.
 */
int checkIslandSize_Iterative(const MatrixType &grid,
                              const std::pair<int, int> start_point) {
    const int N = grid.size();
    std::stack<std::pair<int, int>> s;
    s.push(start_point);
    std::unordered_set<std::pair<int, int>, PairHash> visited;
    visited.insert(start_point);

    while (not s.empty()) {
        const auto [row, column] = s.top();
        s.pop();

        for (const auto [row_delta, column_delta] : DIRECTIONS) {
            const auto i = row + row_delta;
            const auto j = column + column_delta;
            if (i >= 0 and i < N and j >= 0 and j < N and grid[i][j] == 1) {
                if (visited.emplace(i, j).second) {
                    s.emplace(i, j);
                }
            }
        }
    }

    return visited.size();
}

int MakeLargeIsland_Naive(MatrixType grid) {
    const auto N = grid.size();
    assert(N == grid.front().size());

    int result = 0;
    bool has_zero = false;
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            if (grid[i][j] == 0) {
                has_zero = true;
                grid[i][j] = 1;
                result = std::max(result,
                                  checkIslandSize_Iterative(grid, std::pair<int, int>(i, j)));
                grid[i][j] = 0;
            }
        }
    }

    return has_zero ? result : N * N;
}


int checkIslandSize_Recursive(MatrixType &grid, const int row, const int column,
                              const int island_index) {
    const int N = grid.size();
    grid[row][column] = island_index;

    int result = 1;
    for (const auto [row_delta, column_delta] : DIRECTIONS) {
        const auto i = row + row_delta;
        const auto j = column + column_delta;
        if (i >= 0 and i < N and j >= 0 and j < N and grid[i][j] == 1) {
            result += checkIslandSize_Recursive(grid, i, j, island_index);
        }
    }

    return result;
}

int findTotalArea(const MatrixType &grid, const int row, const int column,
                  const std::unordered_map<int, int> &areas) {
    const int N = grid.size();

    int result = 1;
    std::unordered_set<int> visited_island;
    for (const auto [row_delta, column_delta] : DIRECTIONS) {
        const auto i = row + row_delta;
        const auto j = column + column_delta;
        if (i >= 0 and i < N and j >= 0 and j < N and grid[i][j] != 0) {
            if (visited_island.insert(grid[i][j]).second) {
                result += areas.at(grid[i][j]);
            }
        }
    }

    return result;
}

int MakeLargeIsland_UnionFind(MatrixType grid) {
    const auto N = grid.size();
    assert(N == grid.front().size());

    std::unordered_map<int, int> areas;
    int island_index = 2;
    int result = 0;
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            if (grid[i][j] == 1) {
                ++island_index;
                areas[island_index] = checkIslandSize_Recursive(grid, i, j, island_index);
                result = std::max(result, areas[island_index]);
            }
        }
    }

    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            if (grid[i][j] == 0) {
                result = std::max(result, findTotalArea(grid, i, j, areas));
            }
        }
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1};
const ArrayType SAMPLE2 = {0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
const ArrayType SAMPLE3 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};


THE_BENCHMARK(LengthOfLongestConsecutive1s, 14);

SIMPLE_TEST(LengthOfLongestConsecutive1s, TestSAMPLE1, 3, 14);
SIMPLE_TEST(LengthOfLongestConsecutive1s, TestSAMPLE2, 4, 222);
SIMPLE_TEST(LengthOfLongestConsecutive1s, TestSAMPLE3, 4, 0b110010101111);
SIMPLE_TEST(LengthOfLongestConsecutive1s, TestSAMPLE4, 1, 0b00101010101);


THE_BENCHMARK(LengthOfLongestConsecutive1s_Array, SAMPLE1);

SIMPLE_TEST(LengthOfLongestConsecutive1s_Array, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(LengthOfLongestConsecutive1s_Array, TestSAMPLE2, 1, SAMPLE2);
SIMPLE_TEST(LengthOfLongestConsecutive1s_Array, TestSAMPLE3, SAMPLE3.size(), SAMPLE3);


const ArrayType SAMPLE4 = {1, 0, 1, 1, 0};


THE_BENCHMARK(LengthOfLongestConsecutive1s_1Flip_Array, SAMPLE1);

SIMPLE_TEST(LengthOfLongestConsecutive1s_1Flip_Array, TestSAMPLE1, 6, SAMPLE1);
SIMPLE_TEST(LengthOfLongestConsecutive1s_1Flip_Array, TestSAMPLE2, 3, SAMPLE2);
SIMPLE_TEST(LengthOfLongestConsecutive1s_1Flip_Array, TestSAMPLE3, SAMPLE3.size(),
            SAMPLE3);
SIMPLE_TEST(LengthOfLongestConsecutive1s_1Flip_Array, TestSAMPLE4, 4, SAMPLE4);


const ArrayType SAMPLE6 = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
const ArrayType SAMPLE7 = {0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1};


THE_BENCHMARK(LengthOfLongestConsecutive1s_KFlip_Array, SAMPLE1, 1);

SIMPLE_TEST(LengthOfLongestConsecutive1s_KFlip_Array, TestSAMPLE1, 6, SAMPLE1, 1);
SIMPLE_TEST(LengthOfLongestConsecutive1s_KFlip_Array, TestSAMPLE2, 3, SAMPLE2, 1);
SIMPLE_TEST(LengthOfLongestConsecutive1s_KFlip_Array, TestSAMPLE3, SAMPLE3.size(),
            SAMPLE3, 1);
SIMPLE_TEST(LengthOfLongestConsecutive1s_KFlip_Array, TestSAMPLE4, 4, SAMPLE4, 1);
SIMPLE_TEST(LengthOfLongestConsecutive1s_KFlip_Array, TestSAMPLE5, SAMPLE4.size(),
            SAMPLE4, 2);
SIMPLE_TEST(LengthOfLongestConsecutive1s_KFlip_Array, TestSAMPLE6, 6, SAMPLE6, 2);
SIMPLE_TEST(LengthOfLongestConsecutive1s_KFlip_Array, TestSAMPLE7, 10, SAMPLE7, 3);


const MatrixType SAMPLE1M = {
    {1, 0},
    {0, 1}
};

const MatrixType SAMPLE2M = {
    {1, 1},
    {0, 1}
};

const MatrixType SAMPLE3M = {
    {1, 1},
    {1, 1}
};


THE_BENCHMARK(MakeLargeIsland_Naive, SAMPLE1M);

SIMPLE_TEST(MakeLargeIsland_Naive, TestSAMPLE1, 3, SAMPLE1M);
SIMPLE_TEST(MakeLargeIsland_Naive, TestSAMPLE2, 4, SAMPLE2M);
SIMPLE_TEST(MakeLargeIsland_Naive, TestSAMPLE3, 4, SAMPLE3M);


THE_BENCHMARK(MakeLargeIsland_UnionFind, SAMPLE1M);

SIMPLE_TEST(MakeLargeIsland_UnionFind, TestSAMPLE1, 3, SAMPLE1M);
SIMPLE_TEST(MakeLargeIsland_UnionFind, TestSAMPLE2, 4, SAMPLE2M);
SIMPLE_TEST(MakeLargeIsland_UnionFind, TestSAMPLE3, 4, SAMPLE3M);
