#include "common_header.h"

#include "graph.h"
#include "depth_first_search.h"
#include "topological_sort.h"


using namespace graph;

namespace {

/** Strongly Connected Components
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 22.5.
 * @reference   https://www.geeksforgeeks.org/strongly-connected-components/
 *
 * A directed graph is strongly connected if there is a path between all pairs of
 * vertices. A strongly connected component (SCC) of a directed graph is a maximal
 * strongly connected subgraph.
 */
auto StronglyConnectedComponents_Kosaraju(const std::size_t number_vertices,
                                          const DirectedEdgeArrayType &edges) {
    const auto graph = AdjacencyListGraph{number_vertices, edges};

    ArrayType finish_times_stack;
    GraphTraverse(graph,
    [&finish_times_stack](const auto & graph, const auto source, auto & visited_vertices) {
        TopologicalSort(graph, source, visited_vertices, finish_times_stack);
        return true;
    });

    const auto transpose = graph.Visit(GraphTranspose);

    std::vector<ArrayType> strongly_connected_components;
    std::vector<bool> visited_vertices(number_vertices, false);
    while (not finish_times_stack.empty()) {
        const auto source = finish_times_stack.back();
        finish_times_stack.pop_back();

        if (not visited_vertices[source]) {
            ArrayType one_strongly_connected_component;
            transpose.Visit(
            [source, &visited_vertices, &one_strongly_connected_component](const auto & graph) {
                DepthFirstSearch_Recursive(
                    graph, source, visited_vertices, one_strongly_connected_component);
            });

            strongly_connected_components.push_back(std::move(one_strongly_connected_component));
        }
    }

    return strongly_connected_components;
}


/**
 * @reference   Check if a graph is strongly connected | Set 1 (Kosaraju using DFS)
 *              https://www.geeksforgeeks.org/connectivity-in-a-directed-graph/
 *
 * @reference   Check if a given directed graph is strongly connected | Set 2 (Kosaraju using BFS)
 *              https://www.geeksforgeeks.org/check-given-directed-graph-strongly-connected-set-2-kosaraju-using-bfs/
 *
 * @note    Simply replace DepthFirstSearch_Recursive() with
 *  BreadthFirstSearchSingleSource().
 */
auto allVisited(const std::vector<bool> &visited_vertices) {
    for (const auto visited : visited_vertices) {
        if (not visited) {
            return false;
        }
    }

    return true;
}

auto isStronglyConnectedComponents_Kosaraju_DFS(const std::size_t number_vertices,
                                                const DirectedEdgeArrayType &edges) {
    const auto graph = AdjacencyListGraph{number_vertices, edges};

    ArrayType to_be_ignored;
    {
        std::vector<bool> visited_vertices(number_vertices, false);
        graph.Visit([&visited_vertices, &to_be_ignored](const auto & graph) {
            DepthFirstSearch_Recursive(graph, 0, visited_vertices, to_be_ignored);
        });

        if (not allVisited(visited_vertices)) {
            return false;
        }
    }

    const auto transpose = graph.Visit(GraphTranspose);

    {
        std::vector<bool> visited_vertices(number_vertices, false);
        transpose.Visit([&visited_vertices, &to_be_ignored](const auto & graph) {
            DepthFirstSearch_Recursive(graph, 0, visited_vertices, to_be_ignored);
        });

        if (not allVisited(visited_vertices)) {
            return false;
        }
    }

    return true;
}


/**
 * @reference   Check if a directed graph is connected or not
 *              https://www.geeksforgeeks.org/check-if-a-directed-graph-is-connected-or-not/
 */
auto isConnected(const std::size_t number_vertices,
                 const DirectedEdgeArrayType &edges) {
    const auto graph = AdjacencyListGraph{number_vertices, edges};

    ArrayType to_be_ignored;
    std::vector<bool> visited_vertices_correct_direction(number_vertices, false);
    graph.Visit(
    [&visited_vertices_correct_direction, &to_be_ignored](const auto & graph) {
        DepthFirstSearch_Recursive(graph, 0, visited_vertices_correct_direction, to_be_ignored);
    });

    const auto transpose = graph.Visit(GraphTranspose);

    std::vector<bool> visited_vertices_reverse_direction(number_vertices, false);
    transpose.Visit(
    [&visited_vertices_reverse_direction, &to_be_ignored](const auto & graph) {
        DepthFirstSearch_Recursive(graph, 0, visited_vertices_reverse_direction, to_be_ignored);
    });

    for (std::size_t i = 0; i < number_vertices; ++i) {
        if (not visited_vertices_correct_direction[i] and
            not visited_vertices_reverse_direction[i]) {
            return false;
        }
    }

    return true;
}

}//namespace


const DirectedEdgeArrayType SAMPLE1 = {{1, 0}, {0, 2}, {2, 1}, {0, 3}, {3, 4}};
const std::vector<ArrayType> EXPECTED1 = {{0, 1, 2}, {3}, {4}};


THE_BENCHMARK(StronglyConnectedComponents_Kosaraju, 5, SAMPLE1);

SIMPLE_TEST(StronglyConnectedComponents_Kosaraju, TestSAMPLE1, EXPECTED1, 5, SAMPLE1);


const DirectedEdgeArrayType SAMPLE2 = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {2, 4}, {4, 2}};
const DirectedEdgeArrayType SAMPLE3 = {{0, 1}, {1, 2}, {2, 3}};


THE_BENCHMARK(isStronglyConnectedComponents_Kosaraju_DFS, 5, SAMPLE1);

SIMPLE_TEST(isStronglyConnectedComponents_Kosaraju_DFS, TestSAMPLE1, false, 5, SAMPLE1);
SIMPLE_TEST(isStronglyConnectedComponents_Kosaraju_DFS, TestSAMPLE2, true, 5, SAMPLE2);
SIMPLE_TEST(isStronglyConnectedComponents_Kosaraju_DFS, TestSAMPLE3, false, 4, SAMPLE3);


const DirectedEdgeArrayType SAMPLE4 = {{0, 1}, {0, 2}, {1, 2}};
const DirectedEdgeArrayType SAMPLE5 = {{0, 1}, {0, 2}, {1, 2}, {2, 3}};


THE_BENCHMARK(isConnected, 5, SAMPLE1);

SIMPLE_TEST(isConnected, TestSAMPLE1, true, 5, SAMPLE1);
SIMPLE_TEST(isConnected, TestSAMPLE2, true, 5, SAMPLE2);
SIMPLE_TEST(isConnected, TestSAMPLE3, true, 4, SAMPLE3);
SIMPLE_TEST(isConnected, TestSAMPLE4, false, 4, SAMPLE4);
SIMPLE_TEST(isConnected, TestSAMPLE5, true, 4, SAMPLE5);
