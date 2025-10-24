#pragma once

#include "degree_of_graph.h"
#include "graph.h"


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 22.4-5.
 * @reference   Kahn’s algorithm for Topological Sorting
 *              https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/
 *
 * @tags    #graph #topological-sort #BFS
 */
static inline auto TopologicalSort_Kahn(const AdjacencyListGraph::RepresentationType &graph) {
    auto in_degrees = InDegrees(graph);

    std::queue<std::size_t> zero_indegree_vertex_queue;
    for (std::size_t i = 0; i < graph.size(); ++i) {
        if (in_degrees[i] == 0) {
            zero_indegree_vertex_queue.push(i);
        }
    }

    std::size_t number_visited_vertex = 0;
    graph::ArrayType results;

    while (not zero_indegree_vertex_queue.empty()) {
        const auto vertex = zero_indegree_vertex_queue.front();
        zero_indegree_vertex_queue.pop();
        results.push_back(vertex);

        for (const auto adjacent_vertex : graph[vertex]) {
            if (--in_degrees[adjacent_vertex] == 0) {
                zero_indegree_vertex_queue.push(adjacent_vertex);
            }
        }

        ++number_visited_vertex;
    }

    return std::pair(number_visited_vertex == graph.size(), results);
}


/** Topological Sorting
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 22.4.
 * @reference   Topological Sorting
 *              https://www.geeksforgeeks.org/topological-sorting/
 *
 * Topological sorting for Directed Acyclic Graph (DAG) is a linear ordering of vertices such that for
 * every directed edge uv, vertex u comes before v in the ordering.
 * Topological Sorting for a graph is not possible if the graph is not a DAG.
 *
 * @tags    #graph #topological-sort #DFS
 */
static inline void TopologicalSort(const AdjacencyListGraph::RepresentationType &graph,
                                   const std::size_t vertex,
                                   std::vector<bool> &visited_vertices,
                                   graph::ArrayType &results) {
    visited_vertices[vertex] = true;

    for (const auto adjacent_vertex : graph.at(vertex)) {
        if (not visited_vertices[adjacent_vertex]) {
            TopologicalSort(graph, adjacent_vertex, visited_vertices, results);
        }
    }

    results.push_back(vertex);
}

static inline void TopologicalSort(const WeightedAdjacencyListGraph::RepresentationType &graph,
                                   const std::size_t vertex,
                                   std::vector<bool> &visited_vertices,
                                   graph::ArrayType &results) {
    visited_vertices[vertex] = true;

    for (const auto &adjacent_node : graph.at(vertex)) {
        if (not visited_vertices[adjacent_node.destination]) {
            TopologicalSort(graph, adjacent_node.destination, visited_vertices, results);
        }
    }

    results.push_back(vertex);
}
