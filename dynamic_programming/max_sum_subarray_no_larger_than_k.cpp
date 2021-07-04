#include "common_header.h"

#include "mathematics/matrix/matrix.h"
#include "mathematics/arithmetics/sum/largest_sum_contiguous_subarray.h"


namespace {

using ArrayType = std::vector<int>;

/** Maximum sum subarray having sum less than or equal to given sum
 *
 * @reference   https://www.geeksforgeeks.org/maximum-sum-subarray-sum-less-equal-given-sum/
 *
 * Given an array of integers and a sum. We have to find sum of subarray having maximum
 * sum less than or equal to given sum in array.
 */
auto MaxSumSubarrayNoLargerThanK_NoNegative(const ArrayType &elements,
                                            const ArrayType::value_type K) {
    ArrayType::value_type current_sum = 0;
    ArrayType::value_type max_sum = INT_MIN;
    ArrayType::size_type left = 0;

    for (std::size_t i = 0; i < elements.size(); ++i) {
        current_sum += elements[i];
        while (current_sum > K and left <= i) {
            current_sum -= elements[left++];
        }

        if (current_sum == K) {
            return K;
        }
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
    }

    return max_sum;
}


/**
 * @reference   Maximum sum subarray having sum less than or equal to given sum using Set
 *              https://www.geeksforgeeks.org/maximum-sum-subarray-having-sum-less-than-or-equal-to-given-sum-using-set/
 */
auto MaxSumSubarrayNoLargerThanK_Set(const ArrayType &elements,
                                     const ArrayType::value_type K) {
    std::set<ArrayType::value_type> prefix_sums;
    ArrayType::value_type current_prefix_sum = 0;
    prefix_sums.insert(current_prefix_sum);
    ArrayType::value_type max_sum = INT_MIN;

    for (const auto a_number : elements) {
        current_prefix_sum += a_number;

        const auto iter = prefix_sums.lower_bound(current_prefix_sum - K);
        if (iter != prefix_sums.cend()) {
            max_sum = std::max(max_sum, current_prefix_sum - *iter);
            if (max_sum == K) {
                return K;
            }
        }

        prefix_sums.insert(current_prefix_sum);
    }

    return max_sum;
}


/**
 * @reference   Max Sum of Rectangle No Larger Than K
 *              https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/
 *
 * Given an m x n matrix matrix and an integer k, return the max sum of a rectangle in
 * the matrix such that its sum is no larger than k. It is guaranteed that there will be
 * a rectangle with a sum no larger than k.
 */
auto MaxSumRectangleNoLargerThanK_Set(const MatrixType &a_matrix, const int K) {
    int max_sum = INT_MIN;
    for (std::size_t left = 0; left < a_matrix.front().size(); ++left) {
        std::vector temp(a_matrix.size(), 0);
        for (auto right = left; right < a_matrix.front().size(); ++right) {
            for (std::size_t i = 0; i < a_matrix.size(); ++i) {
                temp[i] += a_matrix[i][right];
            }

            const auto result = MaxSumSubarrayNoLargerThanK_Set(temp, K);

            if (result == K) {
                return K;
            }
            max_sum = std::max(result, max_sum);
        }
    }

    return max_sum;
}


auto MaxSumRectangleNoLargerThanK_Kadane(const MatrixType &a_matrix, const int K) {
    int max_sum = INT_MIN;
    for (std::size_t top = 0; top < a_matrix.size(); ++top) {
        std::vector temp(a_matrix.front().size(), 0);
        for (auto bottom = top; bottom < a_matrix.size(); ++bottom) {
            for (std::size_t i = 0; i < a_matrix.front().size(); ++i) {
                temp[i] += a_matrix[bottom][i];
            }

            const auto max_subarray_sum = LargestSumContiguousSubarray_Kadane(temp);
            if (max_subarray_sum <= K) {
                max_sum = std::max(max_subarray_sum, max_sum);
            } else {
                const auto result = MaxSumSubarrayNoLargerThanK_Set(temp, K);
                max_sum = std::max(result, max_sum);
            }
            if (max_sum == K) {
                return K;
            }
        }
    }

    return max_sum;
}

}//namespace


const ArrayType SAMPLE1 = {1, 2, 3, 4, 5};
const ArrayType SAMPLE2 = {2, 4, 6, 8, 10};
const ArrayType SAMPLE3 = {6, 8, 9};
const ArrayType SAMPLE4 = {1, 2, 2};


THE_BENCHMARK(MaxSumSubarrayNoLargerThanK_NoNegative, SAMPLE1, 11);

SIMPLE_TEST(MaxSumSubarrayNoLargerThanK_NoNegative, TestSAMPLE1, 10, SAMPLE1, 11);
SIMPLE_TEST(MaxSumSubarrayNoLargerThanK_NoNegative, TestSAMPLE2, 6, SAMPLE2, 7);
SIMPLE_TEST(MaxSumSubarrayNoLargerThanK_NoNegative, TestSAMPLE3, 17, SAMPLE3, 20);
SIMPLE_TEST(MaxSumSubarrayNoLargerThanK_NoNegative, TestSAMPLE4, 4, SAMPLE4, 4);


const ArrayType SAMPLE5 = {-1, 2, 2};
const ArrayType SAMPLE6 = {5, -2, 6, 3, -5};


THE_BENCHMARK(MaxSumSubarrayNoLargerThanK_Set, SAMPLE1, 11);

SIMPLE_TEST(MaxSumSubarrayNoLargerThanK_Set, TestSAMPLE1, 10, SAMPLE1, 11);
SIMPLE_TEST(MaxSumSubarrayNoLargerThanK_Set, TestSAMPLE2, 6, SAMPLE2, 7);
SIMPLE_TEST(MaxSumSubarrayNoLargerThanK_Set, TestSAMPLE3, 17, SAMPLE3, 20);
SIMPLE_TEST(MaxSumSubarrayNoLargerThanK_Set, TestSAMPLE4, 4, SAMPLE4, 4);
SIMPLE_TEST(MaxSumSubarrayNoLargerThanK_Set, TestSAMPLE5, 4, SAMPLE5, 4);
SIMPLE_TEST(MaxSumSubarrayNoLargerThanK_Set, TestSAMPLE6, 12, SAMPLE6, 15);


const MatrixType SAMPLE7 = {
    {1, 0, 1},
    {0, -2, 3}
};

const MatrixType SAMPLE8 = {
    {2, 2, -1}
};


THE_BENCHMARK(MaxSumRectangleNoLargerThanK_Set, SAMPLE7, 2);

SIMPLE_TEST(MaxSumRectangleNoLargerThanK_Set, TestSAMPLE7, 2, SAMPLE7, 2);
SIMPLE_TEST(MaxSumRectangleNoLargerThanK_Set, TestSAMPLE8, 3, SAMPLE8, 3);


THE_BENCHMARK(MaxSumRectangleNoLargerThanK_Kadane, SAMPLE7, 2);

SIMPLE_TEST(MaxSumRectangleNoLargerThanK_Kadane, TestSAMPLE7, 2, SAMPLE7, 2);
SIMPLE_TEST(MaxSumRectangleNoLargerThanK_Kadane, TestSAMPLE8, 3, SAMPLE8, 3);
