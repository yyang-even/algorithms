#include "common_header.h"

#include "graph.h"
#include "depth_first_search.h"
#include "topological_sort.h"


namespace {

/** Strongly Connected Components
 *
 * @reference   https://www.geeksforgeeks.org/strongly-connected-components/
 *
 * A directed graph is strongly connected if there is a path between all pairs of vertices.
 * A strongly connected component (SCC) of a directed graph is a maximal strongly connected
 * subgraph.
 */
auto StronglyConnectedComponents_Kosaraju(const std::size_t number_vertices,
        const DirectedEdgeArrayType &edges) {
    const auto graph = AdjacencyListGraph{number_vertices, edges};

    AdjacencyListGraph::ArrayType finish_times_stack;
    graph.Visit(
    [&finish_times_stack](const AdjacencyListGraph::RepresentationType & graph) {
        GraphTraverse(graph,
        [&finish_times_stack](const auto & graph, const auto source, auto & visited_vertices) {
            TopologicalSort(graph, source, visited_vertices, finish_times_stack);
            return true;
        });
    });

    const auto transpose = graph.Visit(GraphTranspose);

    std::vector<AdjacencyListGraph::ArrayType> strongly_connected_components;
    std::vector<bool> visited_vertices(number_vertices, false);
    while (not finish_times_stack.empty()) {
        const auto source = finish_times_stack.back();
        finish_times_stack.pop_back();

        if (not visited_vertices[source]) {
            AdjacencyListGraph::ArrayType one_strongly_connected_component;
            transpose.Visit(
            [source, &visited_vertices, &one_strongly_connected_component](const auto & graph) {
                DepthFirstSearch_Recursive(graph, source, visited_vertices, one_strongly_connected_component);
            });

            strongly_connected_components.push_back(std::move(one_strongly_connected_component));
        }
    }

    return strongly_connected_components;
}


/**
 * @reference   Check if a graph is strongly connected | Set 1 (Kosaraju using DFS)
 *              https://www.geeksforgeeks.org/connectivity-in-a-directed-graph/
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

    AdjacencyListGraph::ArrayType to_be_ignored;
    {
        std::vector<bool> visited_vertices(number_vertices, false);
        graph.Visit(
        [&visited_vertices, &to_be_ignored](const auto & graph) {
            DepthFirstSearch_Recursive(graph, 0, visited_vertices, to_be_ignored);
        });

        if (not allVisited(visited_vertices)) {
            return false;
        }
    }

    const auto transpose = graph.Visit(GraphTranspose);

    {
        std::vector<bool> visited_vertices(number_vertices, false);
        transpose.Visit(
        [&visited_vertices, &to_be_ignored](const auto & graph) {
            DepthFirstSearch_Recursive(graph, 0, visited_vertices, to_be_ignored);
        });

        if (not allVisited(visited_vertices)) {
            return false;
        }
    }

    return true;
}

}//namespace


const DirectedEdgeArrayType SAMPLE1 = {{1, 0}, {0, 2}, {2, 1}, {0, 3}, {3, 4}};
const std::vector<AdjacencyListGraph::ArrayType> EXPECTED1 = {{0, 1, 2}, {3}, {4}};


SIMPLE_BENCHMARK(StronglyConnectedComponents_Kosaraju, 5, SAMPLE1);

SIMPLE_TEST(StronglyConnectedComponents_Kosaraju, TestSAMPLE1, EXPECTED1, 5, SAMPLE1);


const DirectedEdgeArrayType SAMPLE2 = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {2, 4}, {4, 2}};
const DirectedEdgeArrayType SAMPLE3 = {{0, 1}, {1, 2}, {2, 3}};


SIMPLE_BENCHMARK(isStronglyConnectedComponents_Kosaraju_DFS, 5, SAMPLE1);

SIMPLE_TEST(isStronglyConnectedComponents_Kosaraju_DFS, TestSAMPLE1, false, 5, SAMPLE1);
SIMPLE_TEST(isStronglyConnectedComponents_Kosaraju_DFS, TestSAMPLE2, true, 5, SAMPLE2);
SIMPLE_TEST(isStronglyConnectedComponents_Kosaraju_DFS, TestSAMPLE3, false, 4, SAMPLE3);
