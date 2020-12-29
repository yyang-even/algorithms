#include "common_header.h"

#include "graph.h"


using namespace graph;

namespace {

/** Breadth First Search or BFS for a Graph
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 22.2.
 * @reference   Breadth First Search or BFS for a Graph
 *              https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/
 * @reference   BFS using vectors & queue as per the algorithm of CLRS
 *              https://www.geeksforgeeks.org/bfs-using-vectors-queue-per-algorithm-clrs/
 * @reference   BFS using STL for competitive coding
 *              https://www.geeksforgeeks.org/bfs-using-stl-competitive-coding/
 * @reference   BFS for Disconnected Graph
 *              https://www.geeksforgeeks.org/bfs-disconnected-graph/
 *
 * @reference   Breadth First Search without using Queue
 *              https://www.geeksforgeeks.org/breadth-first-search-without-using-queue/
 *
 * @note    This solution still uses a queue implicitly.
 *
 * @reference   Applications of Breadth First Traversal
 *              https://www.geeksforgeeks.org/applications-of-breadth-first-traversal/
 *
 * @reference   Real-time application of Data Structures
 *              https://www.geeksforgeeks.org/real-time-application-of-data-structures/
 *
 * @reference   Six Degrees of Kevin Bacon
 *              John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 5.
 */
void BreadthFirstSearchSingleSource(const AdjacencyListGraph::RepresentationType &graph,
                                    const std::size_t source,
                                    std::vector<bool> &visited_vertices,
                                    ArrayType &results) {
    std::queue<std::size_t> gray_vertex_queue;
    visited_vertices[source] = true;
    gray_vertex_queue.push(source);

    while (not gray_vertex_queue.empty()) {
        const auto vertex = gray_vertex_queue.front();
        results.push_back(vertex);
        gray_vertex_queue.pop();

        for (const auto adjacent_vertex : graph.at(vertex)) {
            if (not visited_vertices[adjacent_vertex]) {
                visited_vertices[adjacent_vertex] = true;
                gray_vertex_queue.push(adjacent_vertex);
            }
        }
    }
}

auto BreadthFirstSearchSingleSource(const AdjacencyListGraph::RepresentationType &graph,
                                    const std::size_t source) {
    ArrayType results;
    std::vector<bool> visited_vertices(graph.size(), false);
    BreadthFirstSearchSingleSource(graph, source, visited_vertices, results);

    return results;
}

auto BreadthFirstSearchSingleSource(const std::size_t number_vertices,
                                    const DirectedEdgeArrayType &edges,
                                    const std::size_t source) {
    return AdjacencyListGraph(number_vertices, edges).Visit(
    [source](const AdjacencyListGraph::RepresentationType & graph) {
        return BreadthFirstSearchSingleSource(graph, source);
    });
}


auto BreadthFirstSearch(const std::size_t number_vertices,
                        const DirectedEdgeArrayType &edges) {
    ArrayType results;
    GraphTraverse(number_vertices, edges,
    [&results](const auto & graph, const auto source, auto & visited_vertices) {
        BreadthFirstSearchSingleSource(graph, source, visited_vertices, results);
        return true;
    });

    return results;
}


/**
 * @reference   Implementation of BFS using adjacency matrix
 *              https://www.geeksforgeeks.org/implementation-of-bfs-using-adjacency-matrix/
 */
void BreadthFirstSearch_AdjMatrix(const AdjacencyMatrixGraph::RepresentationType &graph,
                                  const std::size_t source,
                                  std::vector<bool> &visited_vertices, ArrayType &results) {
    std::queue<std::size_t> gray_vertex_queue;
    visited_vertices[source] = true;
    gray_vertex_queue.push(source);

    while (not gray_vertex_queue.empty()) {
        const auto vertex = gray_vertex_queue.front();
        results.push_back(vertex);
        gray_vertex_queue.pop();

        for (std::size_t adjacent_vertex = 0;
             adjacent_vertex < graph.size();
             ++adjacent_vertex) {
            if (graph.at(source).at(adjacent_vertex) and not visited_vertices[adjacent_vertex]) {
                visited_vertices[adjacent_vertex] = true;
                gray_vertex_queue.push(adjacent_vertex);
            }
        }
    }
}

auto BreadthFirstSearch_AdjMatrix(const std::size_t number_vertices,
                                  const DirectedEdgeArrayType &edges) {
    ArrayType results;
    GraphTraverse(AdjacencyMatrixGraph{number_vertices, edges},
    [&results](const auto & graph, const auto source, auto & visited_vertices) {
        BreadthFirstSearch_AdjMatrix(graph, source, visited_vertices, results);
        return true;
    });

    return results;
}

}//namespace


const DirectedEdgeArrayType SAMPLE1 = {{0, 1}, {0, 2}, {1, 2}, {2, 0}, {2, 3}, {3, 3}};
const ArrayType EXPECTED1 = {2, 0, 3, 1};


SIMPLE_BENCHMARK(BreadthFirstSearchSingleSource, Sample1, 4, SAMPLE1, 2);

SIMPLE_TEST(BreadthFirstSearchSingleSource, TestSAMPLE1, EXPECTED1, 4, SAMPLE1, 2);


const DirectedEdgeArrayType SAMPLE2 = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}};
const ArrayType EXPECTED2 = {0, 1, 2, 3, 4, 5, 6};


SIMPLE_BENCHMARK(BreadthFirstSearch, Sample1, 7, SAMPLE2);

SIMPLE_TEST(BreadthFirstSearch, TestSAMPLE2, EXPECTED2, 7, SAMPLE2);


SIMPLE_BENCHMARK(BreadthFirstSearch_AdjMatrix, Sample1, 7, SAMPLE2);

SIMPLE_TEST(BreadthFirstSearch_AdjMatrix, TestSAMPLE2, EXPECTED2, 7, SAMPLE2);
