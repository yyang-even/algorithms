#include "common_header.h"

#include "hash/hash.h"


namespace {

/** Reorganize String
 *
 * @reference   https://leetcode.com/problems/reorganize-string/
 *
 * Given a string s, rearrange the characters of s so that any two adjacent characters are not the same.
 * Return any possible rearrangement of s or return "" if not possible.
 */
std::string ReorganizeStr(const std::string_view s) {
    auto counts = ToFrequencyHashTable(s);

    auto max_iter = counts.cbegin();
    for (auto iter = counts.cbegin(); iter != counts.cend(); ++iter) {
        if (iter->second > max_iter->second) {
            max_iter = iter;
        }
    }

    const int size = s.size();
    if (max_iter->second > (size + 1) / 2) {
        return {};
    }

    std::string result(size, max_iter->first);
    std::size_t i = max_iter->second * 2;
    counts.erase(max_iter);

    for (const auto &[c, n] : counts) {
        for (int j = 0; j++ < n;) {
            if (i >= result.size()) {
                i = 1;
            }

            result[i] = c;
            i += 2;
        }
    }

    return result;
}


/**
 * @reference   Task Scheduler
 *              https://leetcode.com/problems/task-scheduler/
 *
 * You are given an array of CPU tasks, each represented by letters A to Z, and a cooling time, n. Each
 * cycle or interval allows the completion of one task. Tasks can be completed in any order, but there's
 * a constraint: identical tasks must be separated by at least n intervals due to cooling time.
 * Return the minimum number of intervals required to complete all tasks.
 */
auto TaskScheduler(const std::string_view tasks, const int n) {
    const auto counts = ToFrequencyHashTable(tasks);

    int max_count = 0;
    int num_max_count = 0;
    for (const auto &[i, c] : counts) {
        if (max_count < c) {
            max_count = c;
            num_max_count = 1;
        } else if (max_count == c) {
            ++num_max_count;
        }
    }

    const std::size_t total = (max_count - 1) * (n + 1) + num_max_count;

    return std::max(tasks.size(), total);
}


/**
 * @reference   Task Scheduler II
 *              https://leetcode.com/problems/task-scheduler-ii/
 *
 * You are given a 0-indexed array of positive integers tasks, representing tasks that need to be
 * completed in order, where tasks[i] represents the type of the ith task.
 * You are also given a positive integer space, which represents the minimum number of days that must
 * pass after the completion of a task before another task of the same type can be performed.
 * Each day, until all tasks have been completed, you must either:
 *  Complete the next task from tasks, or
 *  Take a break.
 * Return the minimum number of days needed to complete all tasks.
 */

} //namespace


THE_BENCHMARK(ReorganizeStr, "aab");

SIMPLE_TEST(ReorganizeStr, TestSAMPLE1, "aba", "aab");
SIMPLE_TEST(ReorganizeStr, TestSAMPLE2, "", "aaab");


THE_BENCHMARK(TaskScheduler, "AAABBB", 2);

SIMPLE_TEST(TaskScheduler, TestSAMPLE1, 8, "AAABBB", 2);
SIMPLE_TEST(TaskScheduler, TestSAMPLE2, 6, "ACABDB", 1);
SIMPLE_TEST(TaskScheduler, TestSAMPLE3, 10, "AAABBB", 3);
SIMPLE_TEST(TaskScheduler, TestSAMPLE4, 4, "AAB", 2);
