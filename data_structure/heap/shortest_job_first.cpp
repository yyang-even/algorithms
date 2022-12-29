#include "common_header.h"


namespace {

using ArrayType = std::vector<std::pair<int, int>>;

/** Single-Threaded CPU
 *
 * @reference   https://leetcode.com/problems/single-threaded-cpu/description/
 *
 * You are given n tasks labeled from 0 to n - 1 represented by a 2D integer array tasks, where tasks[i]
 * = [enqueueTimei, processingTimei] means that the ith task will be available to process at
 * enqueueTimei and will take processingTimei to finish processing.
 * You have a single-threaded CPU that can process at most one task at a time and will act in the
 * following way:
 *  If the CPU is idle and there are no available tasks to process, the CPU remains idle.
 *  If the CPU is idle and there are available tasks, the CPU will choose the one with the shortest
 *      processing time. If multiple tasks have the same shortest processing time, it will choose the
 *      task with the smallest index.
 *  Once a task is started, the CPU will process the entire task without stopping.
 *  The CPU can finish a task then start a new one instantly.
 * Return the order in which the CPU will process the tasks.
 */
auto ShortestJobFirst(const ArrayType &tasks) {
    std::vector indices(tasks.size(), 0);
    std::iota(indices.begin(), indices.end(), 0);
    std::sort(indices.begin(), indices.end(), [&tasks](const auto left, const auto right) {
        return tasks[left].first < tasks[right].first;
    });

    const auto compare = [&tasks](const auto left, const auto right) {
        if (tasks[left].second == tasks[right].second) {
            return left > right;
        }
        return tasks[left].second > tasks[right].second;
    };

    std::priority_queue<int, std::vector<int>, decltype(compare)> q(compare);
    std::vector<int> result;
    long time = 0;
    for (std::size_t i = 0; i < indices.size() or not q.empty();) {
        for (; i < indices.size() and tasks[indices[i]].first <= time; ++i) {
            q.push(indices[i]);
        }

        if (q.empty()) {
            time = tasks[indices[i]].first;
        } else {
            const auto top = q.top();
            q.pop();
            time += tasks[top].second;
            result.push_back(top);
        }
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {{1, 2}, {2, 4}, {3, 2}, {4, 1}};
const std::vector EXPECTED1 = {0, 2, 3, 1};

const ArrayType SAMPLE2 = {{7, 10}, {7, 12}, {7, 5}, {7, 4}, {7, 2}};
const std::vector EXPECTED2 = {4, 3, 2, 0, 1};


THE_BENCHMARK(ShortestJobFirst, SAMPLE1);

SIMPLE_TEST(ShortestJobFirst, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(ShortestJobFirst, TestSAMPLE2, EXPECTED2, SAMPLE2);
