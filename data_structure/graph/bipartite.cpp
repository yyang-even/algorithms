#include "common_header.h"

#include "graph.h"


using namespace graph;

using ColorArray = std::vector<int>;

namespace {

/** Is Graph Bipartite?
 *
 * @reference   https://leetcode.com/problems/is-graph-bipartite/
 *
 * There is an undirected graph with n nodes, where each node is numbered between 0 and
 * n - 1. You are given a 2D array graph, where graph[u] is an array of nodes that node u
 * is adjacent to. More formally, for each v in graph[u], there is an undirected edge
 * between node u and node v. The graph has the following properties:
 *  There are no self-edges (graph[u] does not contain u).
 *  There are no parallel edges (graph[u] does not contain duplicate values).
 *  If v is in graph[u], then u is in graph[v] (the graph is undirected).
 *  The graph may not be connected, meaning there may be two nodes u and v such that
 *      there is no path between them.
 * A graph is bipartite if the nodes can be partitioned into two independent sets A and B
 * such that every edge in the graph connects a node in set A and a node in set B.
 * Return true if and only if it is bipartite.
 */
bool isBipartite_DFS(const AdjacencyListGraph::RepresentationType &graph,
                     const std::size_t node,
                     const int new_color,
                     ColorArray &colors) {
    colors[node] = new_color;

    for (const auto adjacent_vertex : graph.at(node)) {
        if (colors[adjacent_vertex] == -new_color) {
            continue;
        }

        if (colors[adjacent_vertex] == new_color or
            not isBipartite_DFS(graph, adjacent_vertex, -new_color, colors)) {
            return false;
        }
    }

    return true;
}

bool isBipartite_DFS(const AdjacencyListGraph::RepresentationType &graph) {
    ColorArray colors(graph.size(), 0);

    for (std::size_t i = 0; i < graph.size(); ++i) {
        if (colors[i] == 0 and not isBipartite_DFS(graph, i, 1, colors)) {
            return false;
        }
    }

    return true;
}

}//namespace


const AdjacencyListGraph::RepresentationType SAMPLE1 = {{1, 2, 3}, {0, 2}, {0, 1, 3}, {0, 2}};
const AdjacencyListGraph::RepresentationType SAMPLE2 = {{1, 3}, {0, 2}, {1, 3}, {0, 2}};


THE_BENCHMARK(isBipartite_DFS, SAMPLE1);

SIMPLE_TEST(isBipartite_DFS, TestSAMPLE1, false, SAMPLE1);
SIMPLE_TEST(isBipartite_DFS, TestSAMPLE2, true, SAMPLE2);
