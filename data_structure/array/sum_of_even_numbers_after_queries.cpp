#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;
using QueryArray = std::vector<std::pair<int, int>>;

/** Sum of Even Numbers After Queries
 *
 * @reference   https://leetcode.com/problems/sum-of-even-numbers-after-queries/
 *
 * You are given an integer array nums and an array queries where queries[i] = [vali, indexi].
 * For each query i, first, apply nums[indexi] = nums[indexi] + vali, then print the sum of the even
 * values of nums.
 * Return an integer array answer where answer[i] is the answer to the ith query.
 */
auto SumOfEvenNumsAfterQueries(ArrayType nums, const QueryArray &queries) {
    int sum = 0;
    for (const auto n : nums) {
        if (n % 2 == 0) {
            sum += n;
        }
    }

    ArrayType result;
    for (const auto &[v, i] : queries) {
        if (nums[i] % 2 == 0) {
            sum -= nums[i];
        }

        nums[i] += v;

        if (nums[i] % 2 == 0) {
            sum += nums[i];
        }

        result.push_back(sum);
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1N = {1, 2, 3, 4};
const QueryArray SAMPLE1Q = {{1, 0}, {-3, 1}, {-4, 0}, {2, 3}};
const ArrayType EXPECTED1 = {8, 6, 2, 4};

const ArrayType SAMPLE2N = {1};
const QueryArray SAMPLE2Q = {{4, 0}};
const ArrayType EXPECTED2 = {0};


THE_BENCHMARK(SumOfEvenNumsAfterQueries, SAMPLE1N, SAMPLE1Q);

SIMPLE_TEST(SumOfEvenNumsAfterQueries, TestSAMPLE1, EXPECTED1, SAMPLE1N, SAMPLE1Q);
SIMPLE_TEST(SumOfEvenNumsAfterQueries, TestSAMPLE2, EXPECTED2, SAMPLE2N, SAMPLE2Q);
