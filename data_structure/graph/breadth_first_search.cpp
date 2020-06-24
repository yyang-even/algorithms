#include "common_header.h"

#include "graph.h"


namespace {

/** Breadth First Search or BFS for a Graph
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 22.2.
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
 */
void BreadthFirstSearchSingleSource(const AdjacencyListGraph::RepresentationType &graph,
                                    const std::size_t source,
                                    std::vector<bool> &visited_vertices,
                                    AdjacencyListGraph::ArrayType &results) {
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
    AdjacencyListGraph::ArrayType results;
    std::vector<bool> visited_vertices(graph.size(), false);
    BreadthFirstSearchSingleSource(graph, source, visited_vertices, results);

    return results;
}

auto BreadthFirstSearchSingleSource(const std::size_t number_vertices,
                                    const AdjacencyListGraph::EdgeArrayType &edges,
                                    const std::size_t source) {
    return AdjacencyListGraph(number_vertices, edges).Visit(
    [source](const AdjacencyListGraph::RepresentationType & graph) {
        return BreadthFirstSearchSingleSource(graph, source);
    });
}

auto BreadthFirstSearch(const std::size_t number_vertices,
                        const AdjacencyListGraph::EdgeArrayType &edges) {
    return GraphTraverse(number_vertices, edges, ToLambda(BreadthFirstSearchSingleSource));
}

}//namespace


const AdjacencyListGraph::EdgeArrayType SAMPLE1 = {{0, 1}, {0, 2}, {1, 2}, {2, 0}, {2, 3}, {3, 3}};
const AdjacencyListGraph::ArrayType EXPECTED1 = {2, 0, 3, 1};


SIMPLE_BENCHMARK(BreadthFirstSearchSingleSource, 4, SAMPLE1, 2);

SIMPLE_TEST(BreadthFirstSearchSingleSource, TestSAMPLE1, EXPECTED1, 4, SAMPLE1, 2);


const AdjacencyListGraph::EdgeArrayType SAMPLE2 = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}};
const AdjacencyListGraph::ArrayType EXPECTED2 = {0, 1, 2, 3, 4, 5, 6};


SIMPLE_BENCHMARK(BreadthFirstSearch, 7, SAMPLE2);

SIMPLE_TEST(BreadthFirstSearch, TestSAMPLE2, EXPECTED2, 7, SAMPLE2);
