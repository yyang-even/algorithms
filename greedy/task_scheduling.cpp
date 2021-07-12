#include "common_header.h"

#include "data_structure/disjoint_set.h"


namespace {

struct Job {
    char id{};
    std::size_t deadline{};
    int profit{};
};

using ArrayType = std::vector<Job>;
using OutputType = std::multiset<char>;

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
    OutputType results;

    for (ArrayType::size_type i = 0; i < jobs.size(); ++i) {
        for (int j = std::min(jobs.size(), jobs[i].deadline) - 1; j >= 0; --j) {
            if (slots[j] < 0) {
                slots[j] = i;
                results.insert(jobs[i].id);
                break;
            }
        }
    }

    return results;
}


/**
 * @reference   Job Sequencing Problem | Set 2 (Using Disjoint Set)
 *              https://www.geeksforgeeks.org/job-sequencing-using-disjoint-set-union/
 */
auto TaskScheduling_DisjointSet(ArrayType jobs) {
    std::sort(jobs.begin(), jobs.end(), [](const auto & lhs, const auto & rhs) {
        return lhs.profit > rhs.profit;
    });

    // const auto max_deadline = std::min(std::max_element(jobs.cbegin(), jobs.cend(),
    //         [](const auto &lhs, const auto &rhs) {
    //             return lhs.deadline > rhs.deadline;
    //         })->deadline, jobs.size());
    DisjointSet_Array disjoint_set{jobs.size() + 1};
    OutputType results;

    for (const auto &a_job : jobs) {
        const auto available_slot = disjoint_set.Find(std::min(jobs.size(), a_job.deadline));
        std::cout << available_slot << std::endl;
        if (available_slot > 0) {
            disjoint_set.Adopt(disjoint_set.Find(available_slot - 1), available_slot);
            results.insert(a_job.id);
        }
    }

    return results;
}

}//namespace


const ArrayType SAMPLE1 = {{'a', 2, 100}, {'b', 1, 19}, {'c', 2, 27}, {'d', 1, 25}, {'e', 3, 15}};
const OutputType EXPECTED1 = {'c', 'a', 'e'};

const ArrayType SAMPLE2 = {{'a', 4, 20}, {'b', 1, 10}, {'c', 1, 40}, {'d', 1, 30}};
const OutputType EXPECTED2 = {'c', 'a'};


THE_BENCHMARK(TaskScheduling, SAMPLE1);

SIMPLE_TEST(TaskScheduling, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(TaskScheduling, TestSAMPLE2, EXPECTED2, SAMPLE2);


THE_BENCHMARK(TaskScheduling_DisjointSet, SAMPLE1);

SIMPLE_TEST(TaskScheduling_DisjointSet, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(TaskScheduling_DisjointSet, TestSAMPLE2, EXPECTED2, SAMPLE2);
