#include "common_header.h"


namespace {

using StartFinishPair = std::pair<unsigned, unsigned>;
using ArrayType = std::vector<StartFinishPair>;
using OutputType = std::vector<ArrayType::size_type>;

/** Activity Selection Problem
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 16.1.
 * @reference   Activity Selection Problem | Greedy Algo-1
 *              https://www.geeksforgeeks.org/activity-selection-problem-greedy-algo-1/
 * @reference   C Program for Activity Selection Problem | Greedy Algo-1
 *              https://www.geeksforgeeks.org/c-program-for-activity-selection-problem-greedy-algo-1/
 * @reference   Greedy approach vs Dynamic programming
 *              https://www.geeksforgeeks.org/greedy-approach-vs-dynamic-programming/
 *
 * You are given n activities with their start and finish times. Select the maximum number
 * of activities that can be performed by a single person, assuming that a person can only
 * work on a single activity at a time.
 */
void ActivitySelection_Recursive(const ArrayType &activities, const ArrayType::size_type i,
                                 OutputType &selected_activities) {
    auto j = i + 1;
    for (; j < activities.size() and activities[j].first < activities[i].second; ++j);

    if (j < activities.size()) {
        selected_activities.push_back(j);
        ActivitySelection_Recursive(activities, j, selected_activities);
    }
}

auto ActivitySelection_Recursive(const ArrayType &activities) {
    assert(std::is_sorted(activities.cbegin(), activities.cend(),
    [](const auto & lhs, const auto & rhs) {
        return lhs.second < rhs.second;
    }));

    OutputType selected_activities = {0};
    ActivitySelection_Recursive(activities, selected_activities.front(), selected_activities);
    return selected_activities;
}


auto ActivitySelection_Iterative(const ArrayType &activities) {
    assert(std::is_sorted(activities.cbegin(), activities.cend(),
    [](const auto & lhs, const auto & rhs) {
        return lhs.second < rhs.second;
    }));

    ArrayType::size_type i = 0;
    OutputType selected_activities = {i};

    for (auto j = i + 1; j < activities.size(); ++j) {
        if (activities[j].first >= activities[i].second) {
            selected_activities.push_back(j);
            i = j;
        }
    }

    return selected_activities;
}

}//namespace


const ArrayType SAMPLE1 = {{10, 20}, {12, 25}, {20, 30}};
const OutputType EXPECTED1 = {0, 2};

const ArrayType SAMPLE2 = {{1, 2}, {3, 4}, {0, 6}, {5, 7}, {8, 9}, {5, 9}};
const OutputType EXPECTED2 = {0, 1, 3, 4};

const ArrayType SAMPLE3 =
{{1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 9}, {5, 9}, {6, 10}, {8, 11}, {8, 12}, {2, 14}, {12, 16}};
const OutputType EXPECTED3 = {0, 3, 7, 10};


SIMPLE_BENCHMARK(ActivitySelection_Recursive, SAMPLE1);

SIMPLE_TEST(ActivitySelection_Recursive, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(ActivitySelection_Recursive, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(ActivitySelection_Recursive, TestSAMPLE3, EXPECTED3, SAMPLE3);


SIMPLE_BENCHMARK(ActivitySelection_Iterative, SAMPLE1);

SIMPLE_TEST(ActivitySelection_Iterative, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(ActivitySelection_Iterative, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(ActivitySelection_Iterative, TestSAMPLE3, EXPECTED3, SAMPLE3);
