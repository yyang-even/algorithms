#include "common_header.h"


namespace {

using ClassType = std::vector<int>;
using ArrayType = std::vector<ClassType>;

/**
 * @reference   Maximum Average Pass Ratio
 *              https://leetcode.com/problems/maximum-average-pass-ratio/
 *
 * There is a school that has classes of students and each class will be having a final exam. You are
 * given a 2D integer array classes, where classes[i] = [passi, totali]. You know beforehand that in the
 * ith class, there are totali total students, but only passi number of students will pass the exam.
 * You are also given an integer extraStudents. There are another extraStudents brilliant students that
 * are guaranteed to pass the exam of any class they are assigned to. You want to assign each of the
 * extraStudents students to a class in a way that maximizes the average pass ratio across all the
 * classes.
 * The pass ratio of a class is equal to the number of students of the class that will pass the exam
 * divided by the total number of students of the class. The average pass ratio is the sum of pass
 * ratios of all the classes divided by the number of the classes.
 * Return the maximum possible average pass ratio after assigning the extraStudents students. Answers
 * within 10-5 of the actual answer will be accepted.
 *
 * @tags    #greedy #priority-queue
 */
double gain(const ClassType &c) {
    return (c[1] - c[0]) / ((c[1] + 1.0) * c[1]);
}

double MaxAveragePassRatio(ArrayType classes, const int extraStudents) {
    std::priority_queue<std::pair<double, int>> max_heap;

    for (std::size_t i = 0; i < classes.size(); ++i) {
        if (classes[i][0] != classes[i][1]) {
            max_heap.emplace(gain(classes[i]), i);
        }
    }

    if (max_heap.empty()) {
        return 1.0;
    }

    for (int i = 0; i < extraStudents; ++i) {
        const auto [_, c] = max_heap.top();
        max_heap.pop();
        ++(classes[c][0]);
        ++(classes[c][1]);

        max_heap.emplace(gain(classes[c]), c);
    }

    double result = 0;
    for (const auto &c : classes) {
        result += static_cast<double>(c[0]) / c[1];
    }

    return result / classes.size();
}

} //namespace


const ArrayType SAMPLE1 = {{1, 2}, {3, 5}, {2, 2}};
const ArrayType SAMPLE2 = {{2, 4}, {3, 9}, {4, 5}, {2, 10}};
const ArrayType SAMPLE3 = {{4, 4}, {10, 10}};


THE_BENCHMARK(MaxAveragePassRatio, SAMPLE1, 2);

SIMPLE_DOUBLE_TEST(MaxAveragePassRatio, TestSAMPLE1, 0.78333333333333333, SAMPLE1, 2);
SIMPLE_DOUBLE_TEST(MaxAveragePassRatio, TestSAMPLE2, 0.53484848484848491, SAMPLE2, 4);
SIMPLE_DOUBLE_TEST(MaxAveragePassRatio, TestSAMPLE3, 1.0, SAMPLE3, 6);
