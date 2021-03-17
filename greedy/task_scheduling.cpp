#include "common_header.h"


namespace {

struct Job {
    char id{};
    int deadline{};
    int profit{};
};

using ArrayType = std::vector<Job>;

inline auto &operator<<(std::ostream &out, const Job &a_job) {
    return out << "(" << a_job.id << ", " << a_job.deadline << ", " << a_job.profit << ")";
}

/** Task-scheduling Problem
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 16.5. Problems 16-4.
 * @reference   Job Sequencing Problem
 *              https://www.geeksforgeeks.org/job-sequencing-problem/
 *
 * Given an array of jobs where every job has a deadline and associated profit if the job
 * is finished before the deadline. It is also given that every job takes single unit of
 * time, so the minimum possible deadline for any job is 1. How to maximize total profit
 * if only one job can be scheduled at a time.
 */
auto TaskScheduling(ArrayType jobs) {
    std::sort(jobs.begin(), jobs.end(), [](const auto & lhs, const auto & rhs) {
        return lhs.profit > rhs.profit;
    });

    std::vector<int> slots(jobs.size(), -1);

    for (ArrayType::size_type i = 0; i < jobs.size(); ++i) {
        for (int j = std::min(static_cast<int>(jobs.size()), jobs[i].deadline) - 1;
             j >= 0;
             --j) {
            if (slots[j] < 0) {
                slots[j] = i;
                break;
            }
        }
    }

    std::string selected_jobs;
    for (const auto one_slot : slots) {
        if (one_slot >= 0) {
            selected_jobs.push_back(jobs[one_slot].id);
        }
    }

    return selected_jobs;
}

}//namespace


const ArrayType SAMPLE1 = {{'a', 2, 100}, {'b', 1, 19}, {'c', 2, 27}, {'d', 1, 25}, {'e', 3, 15}};
const std::string EXPECTED1 = "cae";

const ArrayType SAMPLE2 = {{'a', 4, 20}, {'b', 1, 10}, {'c', 1, 40}, {'d', 1, 30}};
const std::string EXPECTED2 = "ca";


THE_BENCHMARK(TaskScheduling, SAMPLE1);

SIMPLE_TEST(TaskScheduling, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(TaskScheduling, TestSAMPLE2, EXPECTED2, SAMPLE2);
