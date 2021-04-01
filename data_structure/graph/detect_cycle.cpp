#include "common_header.h"

#include "graph.h"
#include "topological_sort.h"


using namespace graph;

namespace {

/** Detect Cycle in a Directed Graph
 *
 * @reference   https://www.geeksforgeeks.org/detect-cycle-in-a-graph/
 * @reference   Detect Cycle in a directed graph using colors
 *              https://www.geeksforgeeks.org/detect-cycle-direct-graph-using-colors/
 * @reference   C Program to Detect Cycle in a Directed Graph
 *              https://www.geeksforgeeks.org/c-program-for-detect-cycle-in-a-directed-graph/
 */
bool DetectCycle_DFS(const AdjacencyListGraph::RepresentationType &graph,
                     const std::size_t source,
                     std::vector<bool> &visited_vertices,
                     std::vector<bool> &in_stack_vertices) {
    visited_vertices[source] = true;
    in_stack_vertices[source] = true;

    for (const auto adjacent_vertex : graph.at(source)) {
        if (not visited_vertices[adjacent_vertex] and
            DetectCycle_DFS(graph, adjacent_vertex, visited_vertices, in_stack_vertices)) {
            return true;
        } else if (in_stack_vertices[adjacent_vertex]) {
            return true;
        }
    }

    in_stack_vertices[source] = false;
    return false;
}

auto DetectCycle_DFS(const std::size_t number_vertices,
                     const DirectedEdgeArrayType &edges) {
    std::vector<bool> in_stack_vertices(number_vertices, false);
    bool result = false;

    GraphTraverse(number_vertices, edges,
                  [&in_stack_vertices, &result]
    (const auto & graph, const auto source, auto & visited_vertices) {
        result = DetectCycle_DFS(graph, source, visited_vertices, in_stack_vertices);
        return not result;
    });

    return result;
}


/**
 * @reference   Detect Cycle in a Directed Graph using BFS
 *              https://www.geeksforgeeks.org/detect-cycle-in-a-directed-graph-using-bfs/
 */
auto DetectCycle_Degrees(const std::size_t number_vertices,
                         const DirectedEdgeArrayType &edges) {
    return not AdjacencyListGraph(number_vertices, edges).Visit(TopologicalSort_Kahn).first;
}


/**
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 16.4.
 *
 * Design a class which provides a lock only if there are no possible deadlocks.
 */


/** Detect cycle in an undirected graph
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 22.4-3.
 * @reference   Detect cycle in an undirected graph
 *              https://www.geeksforgeeks.org/detect-cycle-undirected-graph/
 */
bool DetectCycle_Undirected_DFS(const AdjacencyListGraph::RepresentationType &graph,
                                const std::size_t source,
                                std::vector<bool> &visited_vertices,
                                const std::size_t parent = -1) {
    visited_vertices[source] = true;

    for (const auto adjacent_vertex : graph.at(source)) {
        if (not visited_vertices[adjacent_vertex]) {
            if (DetectCycle_Undirected_DFS(graph, adjacent_vertex, visited_vertices, source)) {
                return true;
            }
        } else if (adjacent_vertex != parent) {
            return true;
        }
    }

    return false;
}

auto DetectCycle_Undirected_DFS(const std::size_t number_vertices,
                                const UndirectedEdgeArrayType &edges) {
    bool result = false;

    GraphTraverse(number_vertices, edges,
    [&result](const auto & graph, const auto source, auto & visited_vertices) {
        result = DetectCycle_Undirected_DFS(graph, source, visited_vertices);
        return not result;
    });

    return result;
}


/**
 * @reference   Detect cycle in an undirected graph using BFS
 *              https://www.geeksforgeeks.org/detect-cycle-in-an-undirected-graph-using-bfs/
 */
bool DetectCycle_Undirected_BFS(const AdjacencyListGraph::RepresentationType &graph,
                                const std::size_t source,
                                std::vector<bool> &visited_vertices) {
    ArrayType parents(graph.size(), -1);
    std::queue<std::size_t> gray_vertex_queue;
    visited_vertices[source] = true;
    gray_vertex_queue.push(source);

    while (not gray_vertex_queue.empty()) {
        const auto vertex = gray_vertex_queue.front();
        gray_vertex_queue.pop();

        for (const auto adjacent_vertex : graph.at(vertex)) {
            if (not visited_vertices[adjacent_vertex]) {
                visited_vertices[adjacent_vertex] = true;
                gray_vertex_queue.push(adjacent_vertex);
                parents[adjacent_vertex] = vertex;
            } else if (parents[vertex] != adjacent_vertex) {
                return true;
            }
        }
    }

    return false;
}

auto DetectCycle_Undirected_BFS(const std::size_t number_vertices,
                                const UndirectedEdgeArrayType &edges) {
    bool result = false;

    GraphTraverse(number_vertices, edges,
    [&result](const auto & graph, const auto source, auto & visited_vertices) {
        result = DetectCycle_Undirected_BFS(graph, source, visited_vertices);
        return not result;
    });

    return result;
}


/**
 * @reference   Detect cycle in the graph using degrees of nodes of graph
 *              https://www.geeksforgeeks.org/detect-cycle-in-the-graph-using-degrees-of-nodes-of-graph/
 *
 * Given a graph, the task is to detect a cycle in the graph using degrees of the nodes
 * in the graph and print all the nodes that are involved in any of the cycles. If there
 * is no cycle in the graph then print -1.
 */
auto DetectCycle_Undirected_Degrees(
    const AdjacencyListGraph::RepresentationType &graph) {
    auto degrees = OutDegrees(graph);

    std::vector<bool> visited_vertices(graph.size(), false);

    std::queue<std::size_t> one_indegree_vertex_queue;
    for (std::size_t i = 0; i < graph.size(); ++i) {
        if (degrees[i] == 0) {
            visited_vertices[i] = true;
        } else if (degrees[i] == 1) {
            one_indegree_vertex_queue.push(i);
        }
    }

    while (not one_indegree_vertex_queue.empty()) {
        const auto vertex = one_indegree_vertex_queue.front();
        one_indegree_vertex_queue.pop();
        visited_vertices[vertex] = true;

        for (const auto adjacent_vertex : graph[vertex]) {
            if (--degrees[adjacent_vertex] == 1) {
                one_indegree_vertex_queue.push(adjacent_vertex);
            }
        }
    }

    ArrayType results;
    for (std::size_t i = 0; i < visited_vertices.size(); ++i) {
        if (not visited_vertices[i]) {
            results.push_back(i);
        }
    }

    return results;
}

auto DetectCycle_Undirected_Degrees(const std::size_t number_vertices,
                                    const UndirectedEdgeArrayType &edges) {
    return AdjacencyListGraph(number_vertices, edges).Visit
           (ToLambda(DetectCycle_Undirected_Degrees));
}

}//namespace


const DirectedEdgeArrayType SAMPLE1 = {{0, 1}, {0, 2}, {1, 2}, {2, 0}, {2, 3}, {3, 3}};
const DirectedEdgeArrayType SAMPLE2 = {{0, 1}, {0, 2}, {1, 2}, {2, 3}};
const DirectedEdgeArrayType SAMPLE5 = {{1, 2}, {2, 3}, {3, 4}, {1, 3}, {3, 5}, {7, 5}, {5, 9}, {9, 2}};


THE_BENCHMARK(DetectCycle_DFS, 4, SAMPLE1);

SIMPLE_TEST(DetectCycle_DFS, TestSAMPLE1, true, 4, SAMPLE1);
SIMPLE_TEST(DetectCycle_DFS, TestSAMPLE2, false, 4, SAMPLE2);
SIMPLE_TEST(DetectCycle_DFS, TestSAMPLE5, true, 10, SAMPLE5);


THE_BENCHMARK(DetectCycle_Degrees, 4, SAMPLE1);

SIMPLE_TEST(DetectCycle_Degrees, TestSAMPLE1, true, 4, SAMPLE1);
SIMPLE_TEST(DetectCycle_Degrees, TestSAMPLE2, false, 4, SAMPLE2);
SIMPLE_TEST(DetectCycle_Degrees, TestSAMPLE5, true, 10, SAMPLE5);


const UndirectedEdgeArrayType SAMPLE3 = {{0, 1}, {0, 2}, {1, 2}, {0, 3}, {3, 4}};
const ArrayType EXPECTED3 = {0, 1, 2};

const UndirectedEdgeArrayType SAMPLE4 = {{0, 1}, {1, 2}};


THE_BENCHMARK(DetectCycle_Undirected_DFS, 5, SAMPLE3);

SIMPLE_TEST(DetectCycle_Undirected_DFS, TestSAMPLE3, true, 5, SAMPLE3);
SIMPLE_TEST(DetectCycle_Undirected_DFS, TestSAMPLE4, false, 3, SAMPLE4);


THE_BENCHMARK(DetectCycle_Undirected_BFS, 5, SAMPLE3);

SIMPLE_TEST(DetectCycle_Undirected_BFS, TestSAMPLE3, true, 5, SAMPLE3);
SIMPLE_TEST(DetectCycle_Undirected_BFS, TestSAMPLE4, false, 3, SAMPLE4);


THE_BENCHMARK(DetectCycle_Undirected_Degrees, 5, SAMPLE3);

SIMPLE_TEST(DetectCycle_Undirected_Degrees, TestSAMPLE3, EXPECTED3, 5, SAMPLE3);
SIMPLE_TEST(DetectCycle_Undirected_Degrees, TestSAMPLE4, {}, 3, SAMPLE4);
