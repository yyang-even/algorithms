#pragma once

#include "graph.h"


/** Finding in and out degrees of all vertices in a graph
 *
 * @reference   https://www.geeksforgeeks.org/finding-in-and-out-degrees-of-all-vertices-in-a-graph/
 */
static inline auto InDegrees(const AdjacencyListGraph::RepresentationType &graph) {
    graph::ArrayType in_degrees(graph.size(), 0);

    for (std::size_t i = 0; i < graph.size(); ++i) {
        for (const auto adjacent_vertex : graph[i]) {
            ++in_degrees[adjacent_vertex];
        }
    }

    return in_degrees;
}


static inline auto OutDegrees(const AdjacencyListGraph::RepresentationType &graph) {
    graph::ArrayType out_degrees(graph.size(), 0);

    std::transform(graph.cbegin(), graph.cend(), out_degrees.begin(),
    [](const auto & adjacent_vertices) {
        return adjacent_vertices.size();
    });

    return out_degrees;
}
