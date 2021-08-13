#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;
using TwoDimensionalArrayType =
    std::unordered_map<std::size_t, std::unordered_map<std::size_t, ArrayType::size_type>>;

inline void
ToMatrixChainStringWithParenthesis(const ArrayType::size_type i,
                                   const ArrayType::size_type j,
                                   TwoDimensionalArrayType &break_points,
                                   std::stringstream &out) {
    if (i == j) {
        out << 'A' << i;
        return;
    }

    out << '(';
    ToMatrixChainStringWithParenthesis(i, break_points[i][j], break_points, out);
    ToMatrixChainStringWithParenthesis(break_points[i][j] + 1, j, break_points, out);
    out << ')';
}

/** Matrix-chain Multiplication (Minimum)
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 15.2.
 * @reference   Matrix Chain Multiplication | DP-8
 *              https://www.geeksforgeeks.org/matrix-chain-multiplication-dp-8/
 * @reference   C Program for Matrix Chain Multiplication | DP-8
 *              https://www.geeksforgeeks.org/c-program-for-matrix-chain-multiplication-dp-8/
 *
 * Given a sequence of matrices, find the most efficient way to multiply these matrices
 * together. The problem is not actually to perform the multiplications, but merely to
 * decide in which order to perform the multiplications.
 *
 * @reference   Matrix-chain Multiplication (Maximum)
 *              Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 15.3-3.
 */
auto MatrixChainMultiplication(const ArrayType &dimensions,
                               TwoDimensionalArrayType *const break_points = nullptr) {
    assert(not dimensions.empty());

    const auto total_chain_size = dimensions.size() - 1;
    ArrayType::value_type min_costs[dimensions.size()][dimensions.size()] = {};

    for (ArrayType::size_type chain_length = 2;
         chain_length < dimensions.size();
         ++chain_length) {
        for (ArrayType::size_type i = 1; i <= dimensions.size() - chain_length; ++i) {
            const auto j = i + chain_length - 1;
            min_costs[i][j] = std::numeric_limits<ArrayType::value_type>::max();
            for (auto k = i; k < j; ++k) {
                const auto cost = min_costs[i][k] +
                                  min_costs[k + 1][j] +
                                  dimensions[i - 1] * dimensions[k] * dimensions[j];
                if (cost < min_costs[i][j]) {
                    min_costs[i][j] = cost;
                    if (break_points) {
                        (*break_points)[i][j] = k;
                    }
                }
            }
        }
    }

    return min_costs[1][total_chain_size];
}


/**
 * @reference   Printing brackets in Matrix Chain Multiplication Problem
 *              https://www.geeksforgeeks.org/printing-brackets-matrix-chain-multiplication-problem/
 */
inline auto
MatrixChainMultiplicationString(const ArrayType &dimensions) {
    TwoDimensionalArrayType break_points;
    MatrixChainMultiplication(dimensions, &break_points);

    std::stringstream out;
    ToMatrixChainStringWithParenthesis(1, dimensions.size() - 1, break_points, out);

    return out.str();
}


/**
 * @reference   Printing Matrix Chain Multiplication (A Space Optimized Solution)
 *              https://www.geeksforgeeks.org/printing-matrix-chain-multiplication-a-space-optimized-solution/
 *
 * @note    This solution use the lower triangular part of the same matrix (that is not
 *  used) for storing brackets.
 */


/**
 * @reference   Matrix Chain Multiplication (A O(N^2) Solution)
 *              https://www.geeksforgeeks.org/matrix-chain-multiplication-a-on2-solution/
 *
 * @note    This solution does not work for many cases.
 */

}//namespace


const ArrayType SAMPLE1 = {5, 10, 3, 12, 5, 50, 6};
const ArrayType SAMPLE2 = {40, 20, 30, 10, 30};
const ArrayType SAMPLE3 = {10, 20, 30, 40, 30};
const ArrayType SAMPLE4 = {10, 20, 30};


THE_BENCHMARK(MatrixChainMultiplication, SAMPLE1);

SIMPLE_TEST(MatrixChainMultiplication, TestSAMPLE1, 2010, SAMPLE1);
SIMPLE_TEST(MatrixChainMultiplication, TestSAMPLE2, 26000, SAMPLE2);
SIMPLE_TEST(MatrixChainMultiplication, TestSAMPLE3, 30000, SAMPLE3);
SIMPLE_TEST(MatrixChainMultiplication, TestSAMPLE4, 6000, SAMPLE4);


THE_BENCHMARK(MatrixChainMultiplicationString, SAMPLE1);

SIMPLE_TEST(MatrixChainMultiplicationString, TestSAMPLE2, "((A1(A2A3))A4)", SAMPLE2);
SIMPLE_TEST(MatrixChainMultiplicationString, TestSAMPLE3, "(((A1A2)A3)A4)", SAMPLE3);
SIMPLE_TEST(MatrixChainMultiplicationString, TestSAMPLE4, "(A1A2)", SAMPLE4);
