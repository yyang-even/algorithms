#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Number of Students Unable to Eat Lunch
 *
 * @reference   https://leetcode.com/problems/number-of-students-unable-to-eat-lunch/
 *
 * The school cafeteria offers circular and square sandwiches at lunch break, referred to
 * by numbers 0 and 1 respectively. All students stand in a queue. Each student either
 * prefers square or circular sandwiches.
 * The number of sandwiches in the cafeteria is equal to the number of students. The
 * sandwiches are placed in a stack. At each step:
 *  If the student at the front of the queue prefers the sandwich on the top of the stack,
 *      they will take it and leave the queue.
 *  Otherwise, they will leave it and go to the queue's end.
 * This continues until none of the queue students want to take the top sandwich and are
 * thus unable to eat.
 * You are given two integer arrays students and sandwiches where sandwiches[i] is the
 * type of the ith sandwich in the stack (i = 0 is the top of the stack) and students[j]
 * is the preference of the jth student in the initial queue (j = 0 is the front of the
 * queue). Return the number of students that are unable to eat.
 * students.length == sandwiches.length
 */
int CountStudents(const ArrayType &students, const ArrayType &sandwiches) {
    int counts[2] = {};
    for (const auto n : students) {
        ++counts[n];
    }

    int eat = 0;
    for (const auto n : sandwiches) {
        if (counts[n]-- == 0) {
            break;
        }
        ++eat;
    }

    return students.size() - eat;
}

}//namespace


const ArrayType SAMPLE1S = {1, 1, 0, 0};
const ArrayType SAMPLE1W = {0, 1, 0, 1};

const ArrayType SAMPLE2S = {1, 1, 1, 0, 0, 1};
const ArrayType SAMPLE2W = {1, 0, 0, 0, 1, 1};


THE_BENCHMARK(CountStudents, SAMPLE1S, SAMPLE1W);

SIMPLE_TEST(CountStudents, TestSAMPLE1, 0, SAMPLE1S, SAMPLE1W);
SIMPLE_TEST(CountStudents, TestSAMPLE2, 3, SAMPLE2S, SAMPLE2W);
