#include "common_header.h"

#include "graph.h"


namespace {

/** Detect Cycle in a Directed Graph
 *
 * @reference   https://www.geeksforgeeks.org/detect-cycle-in-a-graph/
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


/** Detect cycle in an undirected graph
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 22.4-3.
 */

}//namespace


const AdjacencyListGraph::EdgeArrayType SAMPLE1 = {{0, 1}, {0, 2}, {1, 2}, {2, 0}, {2, 3}, {3, 3}};
const AdjacencyListGraph::EdgeArrayType SAMPLE2 = {{0, 1}, {0, 2}, {1, 2}, {2, 3}};


SIMPLE_BENCHMARK(DetectCycle_DFS, 4, SAMPLE1);

SIMPLE_TEST(DetectCycle_DFS, TestSAMPLE1, true, 4, SAMPLE1);
SIMPLE_TEST(DetectCycle_DFS, TestSAMPLE2, false, 4, SAMPLE2);
