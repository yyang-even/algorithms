#include "common_header.h"

#include "mathematics/matrix/matrix.h"
#include "mathematics/arithmetics/sum/largest_sum_contiguous_subarray.h"


namespace {

/** Maximum sum rectangle in a 2D matrix | DP-27
 *
 * @reference   https://www.geeksforgeeks.org/maximum-sum-rectangle-in-a-2d-matrix-dp-27/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 18.12.
 *
 * This problem is mainly an extension of Largest Sum Contiguous Subarray for 1D array.
 */
auto MaxSumRectangle(const MatrixType &a_matrix) {
    assert(not a_matrix.empty());

    auto max_sum = std::numeric_limits<int>::min();
    for (std::size_t left = 0; left < a_matrix.front().size(); ++left) {
        auto temp = std::vector(a_matrix.size(), 0);
        for (auto right = left; right < a_matrix.front().size(); ++right) {
            for (std::size_t i = 0; i < a_matrix.size(); ++i) {
                temp[i] += a_matrix[i][right];
            }

            const auto sum = LargestSumContiguousSubarray_Kadane(temp);

            if (sum > max_sum) {
                max_sum = sum;
            }
        }
    }

    return max_sum;
}

}//namespace


const MatrixType SAMPLE1 = {
    { 1, 2, -1, -4, -20 },
    { -8, -3, 4, 2, 1 },
    { 3, 8, 10, 1, 3 },
    { -4, -1, 1, 7, -6 }
};


THE_BENCHMARK(MaxSumRectangle, SAMPLE1);

SIMPLE_TEST(MaxSumRectangle, TestSAMPLE1, 29, SAMPLE1);
