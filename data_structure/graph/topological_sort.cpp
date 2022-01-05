#include "common_header.h"

#include "graph.h"


using namespace graph;
using CourseArrayType = std::vector<std::pair<int, int>>;
using MemoType = std::vector<std::vector<int>>;

namespace {

#include "topological_sort.h"


inline auto TopologicalSort(const std::size_t number_vertices,
                            const DirectedEdgeArrayType &edges) {
    ArrayType results;
    GraphTraverse(number_vertices, edges,
    [&results](const auto & graph, const auto source, auto & visited_vertices) {
        TopologicalSort(graph, source, visited_vertices, results);
        return true;
    });

    std::reverse(results.begin(), results.end());
    return results;
}


inline auto TopologicalSort_Kahn(const std::size_t number_vertices,
                                 const DirectedEdgeArrayType &edges) {
    return AdjacencyListGraph(number_vertices, edges).Visit
           (ToLambda(TopologicalSort_Kahn)).second;
}


/**
 * @reference   Course Schedule
 *              https://leetcode.com/problems/course-schedule/
 *
 * There are a total of numCourses courses you have to take, labeled from 0 to
 * numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi]
 * indicates that you must take course bi first if you want to take course ai.
 *  For example, the pair [0, 1], indicates that to take course 0 you have to first take
 *  course 1.
 * Return true if you can finish all courses. Otherwise, return false.
 * All the pairs prerequisites[i] are unique.
 *
 * @reference   Course Schedule II
 *              https://leetcode.com/problems/course-schedule-ii/
 *
 * There are a total of numCourses courses you have to take, labeled from 0 to
 * numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi]
 * indicates that you must take course bi first if you want to take course ai.
 *  For example, the pair [0, 1], indicates that to take course 0 you have to first take
 *  course 1.
 * Return the ordering of courses you should take to finish all courses. If there are many
 * valid answers, return any of them. If it is impossible to finish all courses, return an
 * empty array.
 * All the pairs [ai, bi] are distinct.
 */


/**
 * @reference   All Topological Sorts of a Directed Acyclic Graph
 *              https://www.geeksforgeeks.org/all-topological-sorts-of-a-directed-acyclic-graph/
 */
void AllTopologicalSort(const AdjacencyListGraph::RepresentationType &graph,
                        std::vector<bool> &visited_vertices,
                        ArrayType &in_degrees,
                        ArrayType &one_result,
                        std::vector<ArrayType> &all_results) {
    bool complete = true;

    for (std::size_t i = 0; i < graph.size(); ++i) {
        if (in_degrees[i] == 0 and not visited_vertices[i]) {
            for (const auto adjacent_vertex : graph[i]) {
                --in_degrees[adjacent_vertex];
            }
            one_result.push_back(i);
            visited_vertices[i] = true;

            AllTopologicalSort(graph, visited_vertices, in_degrees, one_result, all_results);

            visited_vertices[i] = false;
            one_result.pop_back();
            for (const auto adjacent_vertex : graph[i]) {
                ++in_degrees[adjacent_vertex];
            }

            complete = false;
        }
    }

    if (complete) {
        all_results.push_back(one_result);
    }
}

inline auto AllTopologicalSort(const AdjacencyListGraph::RepresentationType &graph) {
    std::vector<bool> visited_vertices(graph.size(), false);
    auto in_degrees = InDegrees(graph);
    ArrayType one_result;
    std::vector<ArrayType> all_results;

    AllTopologicalSort(graph, visited_vertices, in_degrees, one_result, all_results);

    return all_results;
}

inline auto AllTopologicalSort(const std::size_t number_vertices,
                               const DirectedEdgeArrayType &edges) {
    return AdjacencyListGraph(number_vertices, edges).Visit(ToLambda(AllTopologicalSort));
}


/**
 * @reference   Minimum Height Trees
 *              https://leetcode.com/problems/minimum-height-trees/
 *
 * A tree is an undirected graph in which any two vertices are connected by exactly one
 * path. In other words, any connected graph without simple cycles is a tree. Given a
 * tree of n nodes labelled from 0 to n - 1, and an array of n - 1 edges where
 * edges[i] = [ai, bi] indicates that there is an undirected edge between the two nodes
 * ai and bi in the tree, you can choose any node of the tree as the root. When you
 * select a node x as the root, the result tree has height h. Among all possible rooted
 * trees, those with minimum height (i.e. min(h))  are called minimum height trees (MHTs).
 * Return a list of all MHTs' root labels. You can return the answer in any order. The
 * height of a rooted tree is the number of edges on the longest downward path between
 * the root and a leaf.
 * The given input is guaranteed to be a tree and there will be no repeated edges.
 */
auto MinimumHeightTrees(const AdjacencyListGraph::RepresentationType &graph) {
    auto degrees = OutDegrees(graph);

    std::queue<std::size_t> q;
    for (std::size_t i = 0; i < graph.size(); ++i) {
        if (degrees[i] <= 1) {
            q.push(i);
        }
    }

    ArrayType results;
    while (not q.empty()) {
        results.clear();
        for (int i = q.size(); i-- > 0;) {
            const auto vertex = q.front();
            q.pop();
            results.push_back(vertex);

            for (const auto adjacent_vertex : graph[vertex]) {
                if (--degrees[adjacent_vertex] == 1) {
                    q.push(adjacent_vertex);
                }
            }
        }
    }

    return results;
}

inline auto MinimumHeightTrees(const std::size_t number_vertices,
                               const UndirectedEdgeArrayType &edges) {
    return AdjacencyListGraph(number_vertices, edges).Visit(ToLambda(MinimumHeightTrees));
}


/**
 * @reference   Course Schedule III
 *              https://leetcode.com/problems/course-schedule-iii/
 *
 * There are n different online courses numbered from 1 to n. You are given an array
 * courses where courses[i] = [duration_i, lastDay_i] indicate that the ith course should
 * be taken continuously for duration_i days and must be finished before or on lastDay_i.
 * You will start on the 1st day and you cannot take two or more courses simultaneously.
 * Return the maximum number of courses that you can take.
 */
auto CourseSchedule_Memo(const CourseArrayType &courses, const std::size_t i,
                         const int time, MemoType &memo) {
    if (i == courses.size()) {
        return 0;
    }

    if (memo[i][time]) {
        return memo[i][time];
    }

    int taken = 0;
    if (time + courses[i].first <= courses[i].second) {
        taken = 1 + CourseSchedule_Memo(courses, i + 1, time + courses[i].first, memo);
    }
    const int not_taken = CourseSchedule_Memo(courses, i + 1, time, memo);

    return memo[i][time] = std::max(taken, not_taken);
}

inline auto CourseSchedule_Memo(CourseArrayType courses) {
    std::sort(courses.begin(), courses.end(), [](const auto one, const auto another) {
        return one.second < another.second;
    });

    std::vector memo(courses.size(), std::vector(courses.back().second + 1, 0));
    return CourseSchedule_Memo(courses, 0, 0, memo);
}


inline auto CourseSchedule_Heap(CourseArrayType courses) {
    std::sort(courses.begin(), courses.end(), [](const auto one, const auto another) {
        return one.second < another.second;
    });

    int time = 0;
    std::priority_queue<int> max_heap;
    for (const auto [duration, last_day] : courses) {
        if (time + duration <= last_day) {
            max_heap.push(duration);
            time += duration;
        } else if (not max_heap.empty() and max_heap.top() > duration) {
            time += duration - max_heap.top();
            max_heap.pop();
            max_heap.push(duration);
        }
    }

    return max_heap.size();
}

}//namespace


const DirectedEdgeArrayType SAMPLE1 = {{5, 2}, {5, 0}, {4, 0}, {4, 1}, {2, 3}, {3, 1}};
const ArrayType EXPECTED1 = {5, 4, 2, 3, 1, 0};

const DirectedEdgeArrayType SAMPLE2 = {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {2, 1}};
const ArrayType EXPECTED2 = {0, 2, 1, 3};


THE_BENCHMARK(TopologicalSort, 6, SAMPLE1);

SIMPLE_TEST(TopologicalSort, TestSAMPLE1, EXPECTED1, 6, SAMPLE1);
SIMPLE_TEST(TopologicalSort, TestSAMPLE2, EXPECTED2, 4, SAMPLE2);


const ArrayType EXPECTED1K = {4, 5, 2, 0, 3, 1};


THE_BENCHMARK(TopologicalSort_Kahn, 6, SAMPLE1);

SIMPLE_TEST(TopologicalSort_Kahn, TestSAMPLE1, EXPECTED1K, 6, SAMPLE1);
SIMPLE_TEST(TopologicalSort_Kahn, TestSAMPLE2, EXPECTED2, 4, SAMPLE2);


const std::vector<ArrayType> EXPECTED3 = {
    {4, 5, 0, 2, 3, 1},
    {4, 5, 2, 0, 3, 1},
    {4, 5, 2, 3, 0, 1},
    {4, 5, 2, 3, 1, 0},
    {5, 2, 3, 4, 0, 1},
    {5, 2, 3, 4, 1, 0},
    {5, 2, 4, 0, 3, 1},
    {5, 2, 4, 3, 0, 1},
    {5, 2, 4, 3, 1, 0},
    {5, 4, 0, 2, 3, 1},
    {5, 4, 2, 0, 3, 1},
    {5, 4, 2, 3, 0, 1},
    {5, 4, 2, 3, 1, 0}
};


THE_BENCHMARK(AllTopologicalSort, 6, SAMPLE1);

SIMPLE_TEST(AllTopologicalSort, TestSAMPLE1, EXPECTED3, 6, SAMPLE1);


const CourseArrayType SAMPLE1C = {{100, 200}, {200, 1300}, {1000, 1250}, {2000, 3200}};
const CourseArrayType SAMPLE2C = {{1, 2}};
const CourseArrayType SAMPLE3C = {{3, 2}, {4, 3}};


THE_BENCHMARK(CourseSchedule_Memo, SAMPLE1C);

SIMPLE_TEST(CourseSchedule_Memo, TestSAMPLE1, 3, SAMPLE1C);
SIMPLE_TEST(CourseSchedule_Memo, TestSAMPLE2, 1, SAMPLE2C);
SIMPLE_TEST(CourseSchedule_Memo, TestSAMPLE3, 0, SAMPLE3C);


THE_BENCHMARK(CourseSchedule_Heap, SAMPLE1C);

SIMPLE_TEST(CourseSchedule_Heap, TestSAMPLE1, 3, SAMPLE1C);
SIMPLE_TEST(CourseSchedule_Heap, TestSAMPLE2, 1, SAMPLE2C);
SIMPLE_TEST(CourseSchedule_Heap, TestSAMPLE3, 0, SAMPLE3C);


const UndirectedEdgeArrayType SAMPLE0T = {};
const ArrayType EXPECTED0T = {0};

const UndirectedEdgeArrayType SAMPLE1T = {{1, 0}, {1, 2}, {1, 3}};
const ArrayType EXPECTED1T = {1};

const UndirectedEdgeArrayType SAMPLE2T = {{3, 0}, {3, 1}, {3, 2}, {3, 4}, {5, 4}};
const ArrayType EXPECTED2T = {3, 4};


THE_BENCHMARK(MinimumHeightTrees, 6, SAMPLE2T);

SIMPLE_TEST(MinimumHeightTrees, TestSAMPLE0, EXPECTED0T, 1, SAMPLE0T);
SIMPLE_TEST(MinimumHeightTrees, TestSAMPLE1, EXPECTED1T, 4, SAMPLE1T);
SIMPLE_TEST(MinimumHeightTrees, TestSAMPLE2, EXPECTED2T, 6, SAMPLE2T);
