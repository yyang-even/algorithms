#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Total Cost to Hire K Workers
 *
 * @reference   https://leetcode.com/problems/total-cost-to-hire-k-workers/
 *
 * You are given a 0-indexed integer array costs where costs[i] is the cost of hiring the ith worker.
 * You are also given two integers k and candidates. We want to hire exactly k workers according to the
 * following rules:
 *  You will run k sessions and hire exactly one worker in each session.
 *  In each hiring session, choose the worker with the lowest cost from either the first candidates
 *  workers or the last candidates workers. Break the tie by the smallest index.
 *      For example, if costs = [3,2,7,7,1,2] and candidates = 2, then in the first hiring session, we
 *      will choose the 4th worker because they have the lowest cost [3,2,7,7,1,2].
 *      In the second hiring session, we will choose 1st worker because they have the same lowest cost
 *      as 4th worker but they have the smallest index [3,2,7,7,2]. Please note that the indexing may be
 *      changed in the process.
 *  If there are fewer than candidates workers remaining, choose the worker with the lowest cost among
 *  them. Break the tie by the smallest index.
 *  A worker can only be chosen once.
 * Return the total cost to hire exactly k workers.
 * 1 <= k, candidates <= costs.length
 */
auto TotalCostToHire(const ArrayType &costs, const int k, const int candidates) {
    const int size = costs.size();
    int left = 0;
    int right = size - 1;

    std::priority_queue<int, std::vector<int>, std::greater<int>> left_heap;
    for (; left < candidates; ++left) {
        left_heap.push(costs[left]);
    }

    std::priority_queue<int, std::vector<int>, std::greater<int>> right_heap;
    for (; right >= std::max(left, size - candidates); --right) {
        right_heap.push(costs[right]);
    }

    long long result = 0;
    for (int i = 0; i++ < k;) {
        if (right_heap.empty() or
            ((not left_heap.empty()) and left_heap.top() <= right_heap.top())) {
            result += left_heap.top();
            left_heap.pop();
            if (left <= right) {
                left_heap.push(costs[left++]);
            }
        } else {
            result += right_heap.top();
            right_heap.pop();
            if (left <= right) {
                right_heap.push(costs[right--]);
            }
        }
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {17, 12, 10, 2, 7, 2, 11, 20, 8};
const ArrayType SAMPLE2 = {1, 2, 4, 1};
const ArrayType SAMPLE3 = {57, 33, 26, 76, 14, 67, 24, 90, 72, 37, 30};


THE_BENCHMARK(TotalCostToHire, SAMPLE1, 3, 4);

SIMPLE_TEST(TotalCostToHire, TestSAMPLE1, 11, SAMPLE1, 3, 4);
SIMPLE_TEST(TotalCostToHire, TestSAMPLE2, 4, SAMPLE2, 3, 3);
SIMPLE_TEST(TotalCostToHire, TestSAMPLE3, 526, SAMPLE3, 11, 2);
