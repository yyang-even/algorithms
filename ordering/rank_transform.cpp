#include "common_header.h"

#include "data_structure/disjoint_set.h"
#include "mathematics/matrix/matrix.h"


namespace {

using ArrayType = std::vector<int>;
using StrArray = std::vector<std::string_view>;

/** Rank Transform of an Array
 *
 * @reference   https://leetcode.com/problems/rank-transform-of-an-array/
 *
 * Given an array of integers arr, replace each element with its rank.
 *
 * The rank represents how large the element is. The rank has the following rules:
 *  Rank is an integer starting from 1.
 *  The larger the element, the larger the rank. If two elements are equal, their rank must be the same.
 *  Rank should be as small as possible.
 */
auto RankTransformArray(ArrayType elements) {
    std::vector<std::pair<int, int>> value_index_array;
    const auto N = elements.size();
    for (std::size_t i = 0; i < N; ++i) {
        value_index_array.emplace_back(elements[i], i);
    }

    std::sort(value_index_array.begin(), value_index_array.end());

    int previous = INT_MIN;
    int rank = 0;
    for (const auto &[value, index] : value_index_array) {
        if (value != previous) {
            ++rank;
        }
        previous = value;
        elements[index] = rank;
    }

    return elements;
}


/**
 * @reference   Rank Transform of a Matrix
 *              https://leetcode.com/problems/rank-transform-of-a-matrix/
 *
 * Given an m x n matrix, return a new matrix answer where answer[row][col] is the rank of
 * matrix[row][col]. The rank is an integer that represents how large an element is compared to other
 * elements. It is calculated using the following rules: The rank is an integer starting from 1.
 *  If two elements p and q are in the same row or column, then:
 *      If p < q then rank(p) < rank(q)
 *      If p == q then rank(p) == rank(q)
 *      If p > q then rank(p) > rank(q)
 *  The rank should be as small as possible.
 * It is guaranteed that answer is unique under the given rules.
 * 1 <= m, n <= 500
 */
auto RankTransformMatrix(MatrixType a_matrix) {
    std::map<int, std::vector<std::pair<int, int>>> value_coordi_map;
    const auto M = a_matrix.size();
    const auto N = a_matrix.front().size();
    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            value_coordi_map[a_matrix[i][j]].emplace_back(i, j);
        }
    }

    int row_ranks[M] = {};
    int column_ranks[N] = {};
    for (const auto &[value, coordinates] : value_coordi_map) {
        DisjointSet_Array disjoint_set(M + N);
        for (const auto &[x, y] : coordinates) {
            disjoint_set.Union(x, y + M);
        }

        std::unordered_map<int, int> group_rank_map;
        for (const auto &[x, y] : coordinates) {
            const auto rank = std::max(row_ranks[x], column_ranks[y]);
            const auto group = disjoint_set.Find(x);
            group_rank_map[group] = std::max(group_rank_map[group], rank);
        }

        for (const auto &[x, y] : coordinates) {
            const auto group = disjoint_set.Find(x);
            const auto rank = group_rank_map[group] + 1;
            a_matrix[x][y] = rank;
            row_ranks[x] = rank;
            column_ranks[y] = rank;
        }
    }

    return a_matrix;
}


inline constexpr int find(int disjoint_set[], const int x) {
    if (disjoint_set[x] == x) {
        return x;
    }
    return disjoint_set[x] = find(disjoint_set, disjoint_set[x]);
}

auto RankTransformMatrix_Optimized(MatrixType a_matrix) {
    const auto M = a_matrix.size();
    const auto N = a_matrix.front().size();

    std::map<int, std::vector<std::pair<int, int>>> value_coordi_map;
    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            value_coordi_map[a_matrix[i][j]].emplace_back(i, j);
        }
    }

    int row_ranks[M] = {};
    int column_ranks[N] = {};
    int max_ranks[M + N] = {};
    int disjoint_set[M + N] = {};
    for (const auto &[value, coordinates] : value_coordi_map) {
        for (const auto &[x, y] : coordinates) {
            disjoint_set[x] = x;
            max_ranks[x] = row_ranks[x];
            disjoint_set[y + M] = y + M;
            max_ranks[y + M] = column_ranks[y];
        }

        for (const auto &[x, y] : coordinates) {
            const auto x_set = find(disjoint_set, x);
            const auto y_set = find(disjoint_set, y + M);
            if (x_set != y_set) {
                disjoint_set[x_set] = y_set;
                max_ranks[y_set] = std::max(max_ranks[x_set], max_ranks[y_set]);
            }
        }

        for (const auto &[x, y] : coordinates) {
            const auto group = find(disjoint_set, x);
            const auto rank = max_ranks[group] + 1;
            a_matrix[x][y] = rank;
            row_ranks[x] = rank;
            column_ranks[y] = rank;
        }
    }

    return a_matrix;
}


/**
 * @reference   Satisfiability of Equality Equations
 *              https://leetcode.com/problems/satisfiability-of-equality-equations/
 *
 * You are given an array of strings equations that represent relationships between variables where each
 * string equations[i] is of length 4 and takes one of two different forms: "xi==yi" or "xi!=yi".Here,
 * xi and yi are lowercase letters (not necessarily different) that represent one-letter variable names.
 * Return true if it is possible to assign integers to variable names so as to satisfy all the given
 * equations, or false otherwise.
 */
auto EquationsPossible(const StrArray &equations) {
    DisjointSet_Array disjoint_set(26);

    for (const auto e : equations) {
        if (e[1] == '=') {
            disjoint_set.Union(e[0] - 'a', e[3] - 'a');
        }
    }

    for (const auto e : equations) {
        if (e[1] == '!' and disjoint_set.Find(e[0] - 'a') == disjoint_set.Find(e[3] - 'a')) {
            return false;
        }
    }

    return true;
}

} //namespace


const ArrayType SAMPLE1 = {40, 10, 20, 30};
const ArrayType EXPECTED1 = {4, 1, 2, 3};

const ArrayType SAMPLE2 = {100, 100, 100};
const ArrayType EXPECTED2 = {1, 1, 1};

const ArrayType SAMPLE3 = {37, 12, 28, 9, 100, 56, 80, 5, 12};
const ArrayType EXPECTED3 = {5, 3, 4, 2, 8, 6, 7, 1, 3};


THE_BENCHMARK(RankTransformArray, SAMPLE1);

SIMPLE_TEST(RankTransformArray, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(RankTransformArray, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(RankTransformArray, TestSAMPLE3, EXPECTED3, SAMPLE3);


// clang-format off
const MatrixType SAMPLE1M = {
    {1, 2},
    {3, 4}
};
const MatrixType EXPECTED1M = {
    {1, 2},
    {2, 3}
};

const MatrixType SAMPLE2M = {
    {7, 7},
    {7, 7}
};
const MatrixType EXPECTED2M = {
    {1, 1},
    {1, 1}
};

const MatrixType SAMPLE3M = {
    {20, -21, 14},
    {-19, 4, 19},
    {22, -47, 24},
    {-19, 4, 19}
};
const MatrixType EXPECTED3M = {
    {4, 2, 3},
    {1, 3, 4},
    {5, 1, 6},
    {1, 3, 4}
};

const MatrixType SAMPLE4M = {
    {7, 3, 6},
    {1, 4, 5},
    {9, 8, 2}
};
const MatrixType EXPECTED4M = {
    {5, 1, 4},
    {1, 2, 3},
    {6, 3, 1}
};

const MatrixType SAMPLE5M = {
    {-37, -50, -3, 44},
    {-37, 46, 13, -32},
    {47, -42, -3, -40},
    {-17, -22, -39, 24}
};
const MatrixType EXPECTED5M = {
    {2, 1, 4, 6},
    {2, 6, 5, 4},
    {5, 2, 4, 3},
    {4, 3, 1, 5}
};
// clang-format on


THE_BENCHMARK(RankTransformMatrix, SAMPLE1M);

SIMPLE_TEST(RankTransformMatrix, TestSAMPLE1, EXPECTED1M, SAMPLE1M);
SIMPLE_TEST(RankTransformMatrix, TestSAMPLE2, EXPECTED2M, SAMPLE2M);
SIMPLE_TEST(RankTransformMatrix, TestSAMPLE3, EXPECTED3M, SAMPLE3M);
SIMPLE_TEST(RankTransformMatrix, TestSAMPLE4, EXPECTED4M, SAMPLE4M);
SIMPLE_TEST(RankTransformMatrix, TestSAMPLE5, EXPECTED5M, SAMPLE5M);


THE_BENCHMARK(RankTransformMatrix_Optimized, SAMPLE1M);

SIMPLE_TEST(RankTransformMatrix_Optimized, TestSAMPLE1, EXPECTED1M, SAMPLE1M);
SIMPLE_TEST(RankTransformMatrix_Optimized, TestSAMPLE2, EXPECTED2M, SAMPLE2M);
SIMPLE_TEST(RankTransformMatrix_Optimized, TestSAMPLE3, EXPECTED3M, SAMPLE3M);
SIMPLE_TEST(RankTransformMatrix_Optimized, TestSAMPLE4, EXPECTED4M, SAMPLE4M);
SIMPLE_TEST(RankTransformMatrix_Optimized, TestSAMPLE5, EXPECTED5M, SAMPLE5M);


const StrArray SAMPLE1E = {"e==d", "e==a", "f!=d", "b!=c", "a==b"};
const StrArray SAMPLE2E = {"e==e", "d!=e", "c==d", "d!=e"};
const StrArray SAMPLE3E = {"f==b", "c==b", "c==b", "e!=f"};
const StrArray SAMPLE4E = {"c==c", "f!=a", "f==b", "b==c"};
const StrArray SAMPLE5E = {"b==a", "a==b"};
const StrArray SAMPLE6E = {"a==b", "b!=a"};


THE_BENCHMARK(EquationsPossible, SAMPLE1E);

SIMPLE_TEST(EquationsPossible, TestSAMPLE1, true, SAMPLE1E);
SIMPLE_TEST(EquationsPossible, TestSAMPLE2, true, SAMPLE2E);
SIMPLE_TEST(EquationsPossible, TestSAMPLE3, true, SAMPLE3E);
SIMPLE_TEST(EquationsPossible, TestSAMPLE4, true, SAMPLE4E);
SIMPLE_TEST(EquationsPossible, TestSAMPLE5, true, SAMPLE5E);
SIMPLE_TEST(EquationsPossible, TestSAMPLE6, false, SAMPLE6E);
