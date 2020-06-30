#include "common_header.h"

#include "graph.h"
#include "topological_sort.h"


namespace {

/** Detect Cycle in a Directed Graph
 *
 * @reference   https://www.geeksforgeeks.org/detect-cycle-in-a-graph/
 * @reference   Detect Cycle in a directed graph using colors
 *              https://www.geeksforgeeks.org/detect-cycle-direct-graph-using-colors/
 */
bool DetectCycle_DFS(const AdjacencyListGraph::RepresentationType &graph,
                     const std::size_t source,
                     std::vector<bool> &visited_vertices,
                     std::vector<bool> &in_stack_vertices) {
    if (not visited_vertices[source]) {
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
    }

    in_stack_vertices[source] = false;
    return false;
}

auto DetectCycle_DFS(const std::size_t number_vertices,
                     const AdjacencyListGraph::EdgeArrayType &edges) {
    std::vector<bool> in_stack_vertices(number_vertices, false);
    bool result = false;

    GraphTraverse(number_vertices, edges,
    [&in_stack_vertices, &result](const auto & graph, const auto source, auto & visited_vertices) {
        result = DetectCycle_DFS(graph, source, visited_vertices, in_stack_vertices);
        return not result;
    });

    return result;
}


/**
 * @reference   Detect Cycle in a Directed Graph using BFS
 *              https://www.geeksforgeeks.org/detect-cycle-in-a-directed-graph-using-bfs/
 */
auto DetectCycle_BFS(const std::size_t number_vertices,
                     const AdjacencyListGraph::EdgeArrayType &edges) {
    return not AdjacencyListGraph(number_vertices, edges).Visit(ToLambda(TopologicalSort_Kahn)).first;
}


/** Detect cycle in an undirected graph
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 22.4-3.
 *
 * @reference   Detect cycle in the graph using degrees of nodes of graph
 *              https://www.geeksforgeeks.org/detect-cycle-in-the-graph-using-degrees-of-nodes-of-graph/
 *
 * Given a graph, the task is to detect a cycle in the graph using degrees of the nodes in the graph
 * and print all the nodes that are involved in any of the cycles. If there is no cycle in the graph
 * then print -1.
 */

}//namespace


const AdjacencyListGraph::EdgeArrayType SAMPLE1 = {{0, 1}, {0, 2}, {1, 2}, {2, 0}, {2, 3}, {3, 3}};
const AdjacencyListGraph::EdgeArrayType SAMPLE2 = {{0, 1}, {0, 2}, {1, 2}, {2, 3}};


SIMPLE_BENCHMARK(DetectCycle_DFS, 4, SAMPLE1);

SIMPLE_TEST(DetectCycle_DFS, TestSAMPLE1, true, 4, SAMPLE1);
SIMPLE_TEST(DetectCycle_DFS, TestSAMPLE2, false, 4, SAMPLE2);


SIMPLE_BENCHMARK(DetectCycle_BFS, 4, SAMPLE1);

SIMPLE_TEST(DetectCycle_BFS, TestSAMPLE1, true, 4, SAMPLE1);
SIMPLE_TEST(DetectCycle_BFS, TestSAMPLE2, false, 4, SAMPLE2);
