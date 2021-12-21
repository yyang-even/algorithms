#include "common_header.h"

#include "graph.h"


using namespace graph;

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
