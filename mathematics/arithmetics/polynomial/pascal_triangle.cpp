#include "common_header.h"


namespace {

using ArrayType = std::vector<std::vector<int>>;

/**
 * @reference   Pascal's Triangle
 *              https://leetcode.com/problems/pascals-triangle/
 * @reference   Pascal’s Triangle
 *              https://www.geeksforgeeks.org/pascal-triangle/
 *
 * Pascal's triangle is a triangular array of the binomial coefficients. Write a function that takes an
 * integer value n as input and prints first n lines of the Pascal's triangle.
 *
 * @tags    #pascals-triangle
 */
auto PascalTriangle(const unsigned num_rows) {
    assert(num_rows >= 1 and num_rows <= 30);

    ArrayType results {{1}};
    for (unsigned i = 2; i <= num_rows; ++i) {
        results.emplace_back(1, 1);
        const auto &prev_row = results[i - 2];
        auto &new_row = results.back();
        for (std::size_t k = 1; k < prev_row.size(); ++k) {
            new_row.push_back(prev_row[k - 1] + prev_row[k]);
        }
        new_row.push_back(1);
    }

    return results;
}


auto PascalTriangle_Coefficient(const unsigned num_rows) {
    assert(num_rows >= 1 and num_rows <= 30);

    ArrayType results {{1}};
    for (unsigned line = 2; line <= num_rows; ++line) {
        results.emplace_back();
        auto &new_row = results.back();
        unsigned long C = 1;
        for (unsigned i = 1; i <= line; ++i) {
            new_row.push_back(C);
            C = C * (line - i) / i;
        }
    }

    return results;
}


/**
 * @reference   Find the Nth row in Pascal's Triangle
 *              https://www.geeksforgeeks.org/find-the-nth-row-in-pascals-triangle/
 * @reference   Pascal's Triangle II
 *              https://leetcode.com/problems/pascals-triangle-ii/
 *
 * Given an integer rowIndex, return the rowIndexth (0-indexed) row of the Pascal's triangle.
 * In Pascal's triangle, each number is the sum of the two numbers directly above it.
 * Follow up: Could you optimize your algorithm to use only O(rowIndex) extra space?
 *
 * @tags    #pascals-triangle
 */
auto NthPascalTriangle(const int nth) {
    std::vector<int> results {1};
    for (int i = 1; i <= nth; ++i) {
        auto prev = 1;
        for (int k = 1; k < i; ++k) {
            const auto current = results[k] + prev;
            prev = results[k];
            results[k] = current;
        }
        results.push_back(1);
    }

    return results;
}


auto NthPascalTriangle_ClosedForm(const int nth) {
    std::vector<int> results {1};
    int prev = 1;

    for (int i = 1; i <= nth; ++i) {
        const auto current = (prev * (nth - i + 1)) / i;
        results.push_back(current);
        prev = current;
    }

    return results;
}


/**
 * @reference   Find Triangular Sum of an Array
 *              https://leetcode.com/problems/find-triangular-sum-of-an-array/
 *
 * You are given a 0-indexed integer array nums, where nums[i] is a digit between 0 and 9 (inclusive).
 * The triangular sum of nums is the value of the only element present in nums after the following
 * process terminates:
 *  Let nums comprise of n elements. If n == 1, end the process. Otherwise, create a new 0-indexed
 *      integer array newNums of length n - 1.
 *  For each index i, where 0 <= i < n - 1, assign the value of newNums[i] as (nums[i] + nums[i+1]) %
 *      10, where % denotes modulo operator.
 *  Replace the array nums with newNums.
 *  Repeat the entire process starting from step 1.
 * Return the triangular sum of nums.
 *
 * @tags    #pascals-triangle
 */

} //namespace


const ArrayType EXPECTED1 = {{1}};
// clang-format off
const ArrayType EXPECTED2 = {
    {1},
    {1, 1},
    {1, 2, 1},
    {1, 3, 3, 1},
    {1, 4, 6, 4, 1}
};
// clang-format on


THE_BENCHMARK(PascalTriangle, 6);

SIMPLE_TEST(PascalTriangle, TestSAMPLE1, EXPECTED1, 1);
SIMPLE_TEST(PascalTriangle, TestSAMPLE2, EXPECTED2, 5);


THE_BENCHMARK(PascalTriangle_Coefficient, 6);

SIMPLE_TEST(PascalTriangle_Coefficient, TestSAMPLE1, EXPECTED1, 1);
SIMPLE_TEST(PascalTriangle_Coefficient, TestSAMPLE2, EXPECTED2, 5);


THE_BENCHMARK(NthPascalTriangle, 6);

SIMPLE_TEST(NthPascalTriangle, TestSAMPLE1, EXPECTED2[0], 0);
SIMPLE_TEST(NthPascalTriangle, TestSAMPLE2, EXPECTED2[2], 2);
SIMPLE_TEST(NthPascalTriangle, TestSAMPLE3, EXPECTED2[4], 4);


THE_BENCHMARK(NthPascalTriangle_ClosedForm, 6);

SIMPLE_TEST(NthPascalTriangle_ClosedForm, TestSAMPLE1, EXPECTED2[0], 0);
SIMPLE_TEST(NthPascalTriangle_ClosedForm, TestSAMPLE2, EXPECTED2[2], 2);
SIMPLE_TEST(NthPascalTriangle_ClosedForm, TestSAMPLE3, EXPECTED2[4], 4);
