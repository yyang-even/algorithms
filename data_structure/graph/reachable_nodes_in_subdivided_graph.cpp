#include "common_header.h"

#include "graph.h"


using namespace graph;

namespace {

/** Reachable Nodes In Subdivided Graph
 *
 * @reference   https://leetcode.com/problems/reachable-nodes-in-subdivided-graph/
 *
 * You are given an undirected graph (the "original graph") with n nodes labeled from 0
 * to n - 1. You decide to subdivide each edge in the graph into a chain of nodes, with
 * the number of new nodes varying between each edge. The graph is given as a 2D array
 * of edges where edges[i] = [ui, vi, cnti] indicates that there is an edge between nodes
 * ui and vi in the original graph, and cnti is the total number of new nodes that you
 * will subdivide the edge into. Note that cnti == 0 means you will not subdivide the
 * edge. To subdivide the edge [ui, vi], replace it with (cnti + 1) new edges and cnti
 * new nodes. The new nodes are x1, x2, ..., xcnti, and the new edges are [ui, x1],
 * [x1, x2], [x2, x3], ..., [xcnti+1, xcnti], [xcnti, vi]. In this new graph, you want
 * to know how many nodes are reachable from the node 0, where a node is reachable if
 * the distance is maxMoves or less. Given the original graph and maxMoves, return the
 * number of nodes that are reachable from node 0 in the new graph.
 */
auto ReachableNodesInSubdividedGraph(
    const WeightedAdjacencyListGraph::RepresentationType &graph,
    const int max_moves,
    const UndirectedEdgeArrayType &edges) {

    std::priority_queue<std::pair<int, int>> q;
    q.emplace(max_moves, 0);
    std::vector<int> moves_left(graph.size(), INT_MIN);
    int result = 0;
    while (not q.empty()) {
        const auto [move, node] = q.top();
        q.pop();

        if (moves_left[node] == INT_MIN) {
            moves_left[node] = move;
            ++result;
            for (const auto &neighbor : graph[node]) {
                if (moves_left[neighbor.destination] == INT_MIN) {
                    const auto remaining = move - neighbor.weight - 1;
                    if (remaining >= 0) {
                        q.emplace(remaining, neighbor.destination);
                    }
                }
            }
        }
    }

    for (const auto &an_edge : edges) {
        const auto u_reachable = moves_left[an_edge.u] == INT_MIN ? 0 : moves_left[an_edge.u];
        const auto v_reachable = moves_left[an_edge.v] == INT_MIN ? 0 : moves_left[an_edge.v];
        result += std::min(an_edge.weight, u_reachable + v_reachable);
    }

    return result;
}

inline auto
ReachableNodesInSubdividedGraph(const std::size_t number_vertices,
                                const UndirectedEdgeArrayType &edges,
                                const int max_moves) {
    return WeightedAdjacencyListGraph{number_vertices, edges}.Visit(
    [max_moves, &edges](const auto & graph) {
        return ReachableNodesInSubdividedGraph(graph, max_moves, edges);
    });
}

}//namespace


const UndirectedEdgeArrayType SAMPLE1 = {{0, 1, 10}, {0, 2, 1}, {1, 2, 2}};
const UndirectedEdgeArrayType SAMPLE2 = {{0, 1, 4}, {1, 2, 6}, {0, 2, 8}, {1, 3, 1}};
const UndirectedEdgeArrayType SAMPLE3 = {{1, 2, 4}, {1, 4, 5}, {1, 3, 1}, {2, 3, 4}, {3, 4, 5}};


THE_BENCHMARK(ReachableNodesInSubdividedGraph, 5, SAMPLE3, 17);

SIMPLE_TEST(ReachableNodesInSubdividedGraph, TestSAMPLE1, 13, 3, SAMPLE1, 6);
SIMPLE_TEST(ReachableNodesInSubdividedGraph, TestSAMPLE2, 23, 4, SAMPLE2, 10);
SIMPLE_TEST(ReachableNodesInSubdividedGraph, TestSAMPLE3, 1, 5, SAMPLE3, 17);
