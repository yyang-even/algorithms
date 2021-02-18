#include "common_header.h"

#include "graph.h"
#include "topological_sort.h"


using namespace graph;

namespace {

/** Find if there is a path between two vertices in a directed graph
 *
 * @reference   https://www.geeksforgeeks.org/find-if-there-is-a-path-between-two-vertices-in-a-given-graph/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 4.2.
 *
 * @reference   Find if there is a path between two vertices in an undirected graph
 *              https://www.geeksforgeeks.org/find-if-there-is-a-path-between-two-vertices-in-an-undirected-graph/
 */
auto isReachable(const AdjacencyListGraph::RepresentationType &graph,
                 const std::size_t source,
                 const std::size_t destination) {
    if (source == destination) {
        return true;
    }

    std::queue<std::size_t> gray_vertex_queue;
    gray_vertex_queue.push(source);

    std::vector<bool> visited_vertices(graph.size(), false);
    visited_vertices[source] = true;

    while (not gray_vertex_queue.empty()) {
        const auto vertex = gray_vertex_queue.front();
        gray_vertex_queue.pop();

        for (const auto adjacent_vertex : graph.at(vertex)) {
            if (not visited_vertices[adjacent_vertex]) {
                if (adjacent_vertex == destination) {
                    return true;
                }

                visited_vertices[adjacent_vertex] = true;
                gray_vertex_queue.push(adjacent_vertex);
            }
        }
    }

    return false;
}

auto isReachable(const std::size_t number_vertices, const DirectedEdgeArrayType &edges,
                 const std::size_t source, const std::size_t destination) {
    assert(source < number_vertices);
    assert(destination < number_vertices);

    return AdjacencyListGraph{number_vertices, edges}.Visit(
    [source, destination](const auto & graph) {
        return isReachable(graph, source, destination);
    });
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 22.4-2.
 * @reference   Number of paths from source to destination in a directed acyclic graph
 *              https://www.geeksforgeeks.org/number-of-paths-from-source-to-destination-in-a-directed-acyclic-graph/
 */
auto NumberPaths_DAG(const std::size_t number_vertices,
                     const DirectedEdgeArrayType &edges,
                     const std::size_t source, const std::size_t destination) {
    assert(source < number_vertices);
    assert(destination < number_vertices);

    AdjacencyListGraph graph{number_vertices, edges};

    const auto topological_order = graph.Visit(TopologicalSort_Kahn).second;

    ArrayType number_of_paths(number_vertices, 0);
    number_of_paths[destination] = 1;

    for (auto iter = topological_order.crbegin();
         iter != topological_order.crend();
         ++iter) {
        const auto from = *iter;
        graph.Visit([from, &number_of_paths](const auto & graph) {
            for (const auto &adjacent_vertex : graph[from]) {
                number_of_paths[from] += number_of_paths[adjacent_vertex];
            }
        });
    }

    return number_of_paths[source];
}

}//namespace


const DirectedEdgeArrayType SAMPLE1 = {{0, 1}, {0, 2}, {1, 2}, {2, 0}, {2, 3}, {3, 3}};


SIMPLE_BENCHMARK(isReachable, Sample1, 4, SAMPLE1, 1, 3);

SIMPLE_TEST(isReachable, TestSAMPLE1, true, 4, SAMPLE1, 1, 3);
SIMPLE_TEST(isReachable, TestSAMPLE2, false, 4, SAMPLE1, 3, 1);


const DirectedEdgeArrayType SAMPLE2 = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {2, 3}, {3, 4}};


SIMPLE_BENCHMARK(NumberPaths_DAG, Sample1, 5, SAMPLE2, 0, 4);

SIMPLE_TEST(NumberPaths_DAG, TestSAMPLE2, 3, 5, SAMPLE2, 0, 4);
