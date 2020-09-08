#pragma once

#include "graph.h"


/** Depth First Search or DFS for a Graph
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 22.3.
 * @reference   Depth First Search or DFS for a Graph
 *              https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/
 * @reference   Graph implementation using STL for competitive programming | Set 1 (DFS of Unweighted and Undirected)
 *              https://www.geeksforgeeks.org/graph-implementation-using-stl-for-competitive-programming-set-1-dfs-of-unweighted-and-undirected/
 * @reference   Applications of Depth First Search
 *              https://www.geeksforgeeks.org/applications-of-depth-first-search/
 *
 * @reference   DFS for a n-ary tree (acyclic graph) represented as adjacency list
 *              https://www.geeksforgeeks.org/dfs-n-ary-tree-acyclic-graph-represented-adjacency-list/
 */
static inline void DepthFirstSearch_Recursive(const AdjacencyListGraph::RepresentationType &graph,
                                              const std::size_t vertex,
                                              std::vector<bool> &visited_vertices,
                                              graph::ArrayType &results) {
    visited_vertices[vertex] = true;
    results.push_back(vertex);

    for (const auto adjacent_vertex : graph.at(vertex)) {
        if (not visited_vertices[adjacent_vertex]) {
            DepthFirstSearch_Recursive(graph, adjacent_vertex, visited_vertices, results);
        }
    }
}
