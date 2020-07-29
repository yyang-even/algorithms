#include "common_header.h"

#include "graph.h"
#include "degree_of_graph.h"
#include "depth_first_search.h"


using namespace graph;

namespace {

enum class EulerianType {
    non,
    path,
    circuit
};

/** Eulerian path and circuit for undirected graph
 *
 * @reference   https://www.geeksforgeeks.org/eulerian-path-and-circuit/
 *
 * Eulerian Path is a path in graph that visits every edge exactly once.
 * Eulerian Circuit is an Eulerian Path which starts and ends on the same vertex.
 */
auto areAllNoneZeroDegreeVerticesConnected(const AdjacencyListGraph::RepresentationType &graph) {
    std::vector<bool> visited_vertices(graph.size(), false);
    auto non_zero_degree_vertex = graph.size();
    for (std::size_t i = 0; i < graph.size(); ++i) {
        if (not graph[i].empty()) {
            non_zero_degree_vertex = i;
            break;
        }
    }

    if (non_zero_degree_vertex == graph.size()) {
        return true;
    }

    ArrayType to_be_ignored;
    DepthFirstSearch_Recursive(graph, non_zero_degree_vertex, visited_vertices, to_be_ignored);

    for (std::size_t i = 0; i < graph.size(); ++i) {
        if (not visited_vertices[i] and not graph[i].empty()) {
            return false;
        }
    }

    return true;
}

auto isEulerian(const std::size_t number_vertices, const UndirectedEdgeArrayType &edges) {
    AdjacencyListGraph graph{number_vertices, edges};

    if (not graph.Visit(areAllNoneZeroDegreeVerticesConnected)) {
        return EulerianType::non;
    }

    const auto degrees = graph.Visit(OutDegrees);

    const auto number_odd_degree_vertices = std::count_if(degrees.cbegin(), degrees.cend(),
    [](const auto degree) {
        return degree % 2;
    });

    if (number_odd_degree_vertices > 2) {
        return EulerianType::non;
    }

    return number_odd_degree_vertices ? EulerianType::path : EulerianType::circuit;
}

}//namespace


const UndirectedEdgeArrayType SAMPLE1 = {{1, 0}, {0, 2}, {2, 1}, {0, 3}, {3, 4}};
const UndirectedEdgeArrayType SAMPLE2 = {{1, 0}, {0, 2}, {2, 1}, {0, 3}, {3, 4}, {4, 0}};
const UndirectedEdgeArrayType SAMPLE3 = {{1, 0}, {0, 2}, {2, 1}, {0, 3}, {3, 4}, {1, 3}};
const UndirectedEdgeArrayType SAMPLE4 = {{0, 1}, {1, 2}, {2, 0}};
const UndirectedEdgeArrayType SAMPLE5 = {};


SIMPLE_BENCHMARK(isEulerian, 5, SAMPLE1);

SIMPLE_TEST(isEulerian, TestSAMPLE1, EulerianType::path, 5, SAMPLE1);
SIMPLE_TEST(isEulerian, TestSAMPLE2, EulerianType::circuit, 5, SAMPLE2);
SIMPLE_TEST(isEulerian, TestSAMPLE3, EulerianType::non, 5, SAMPLE3);
SIMPLE_TEST(isEulerian, TestSAMPLE4, EulerianType::circuit, 3, SAMPLE4);
SIMPLE_TEST(isEulerian, TestSAMPLE5, EulerianType::circuit, 3, SAMPLE5);
