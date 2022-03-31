#include "common_header.h"

#include "graph.h"
#include "topological_sort.h"

#include "data_structure/disjoint_set.h"


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

inline auto isReachable(const std::size_t number_vertices,
                        const DirectedEdgeArrayType &edges,
                        const std::size_t source, const std::size_t destination) {
    assert(source < number_vertices);
    assert(destination < number_vertices);

    return AdjacencyListGraph{number_vertices, edges}.Visit(
    [source, destination](const auto & graph) {
        return isReachable(graph, source, destination);
    });
}


/**
 * @reference   Find if Path Exists in Graph
 *              https://leetcode.com/problems/find-if-path-exists-in-graph/
 *
 * There is a bi-directional graph with n vertices, where each vertex is labeled from 0 to
 * n - 1 (inclusive). The edges in the graph are represented as a 2D integer array edges,
 * where each edges[i] = [ui, vi] denotes a bi-directional edge between vertex ui and vertex
 * vi. Every vertex pair is connected by at most one edge, and no vertex has an edge to
 * itself.
 * You want to determine if there is a valid path that exists from vertex source to vertex
 * destination.
 * Given edges and the integers n, source, and destination, return true if there is a valid
 * path from source to destination, or false otherwise.
 */
auto isReachable_DisjointSet(const std::size_t number_vertices,
                             const UndirectedEdgeArrayType &edges,
                             const std::size_t source, const std::size_t destination) {
    DisjointSet_Array disjoint_set{number_vertices};

    for (const auto &an_edge : edges) {
        disjoint_set.Union(an_edge.u, an_edge.v);
    }

    return disjoint_set.Find(source) == disjoint_set.Find(destination);
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


/**
 * @reference   All Paths From Source to Target
 *              https://leetcode.com/problems/all-paths-from-source-to-target/
 *
 * Given a directed acyclic graph (DAG) of n nodes labeled from 0 to n - 1, find all
 * possible paths from node 0 to node n - 1 and return them in any order. The graph is
 * given as follows: graph[i] is a list of all nodes you can visit from node i (i.e.,
 * there is a directed edge from node i to node graph[i][j]).
 */
void AllPathsSourceTarget(const std::vector<ArrayType> &graph, const std::size_t i,
                          ArrayType &path, std::vector<ArrayType> &results) {
    path.push_back(i);

    if (i == graph.size() - 1) {
        results.push_back(path);
    } else {
        for (const auto neighbor : graph[i]) {
            AllPathsSourceTarget(graph, neighbor, path, results);
        }
    }

    path.pop_back();
}

inline auto AllPathsSourceTarget(const std::vector<ArrayType> &graph) {
    std::vector<ArrayType> results;
    ArrayType path;
    AllPathsSourceTarget(graph, 0, path, results);

    return results;
}

}//namespace


const DirectedEdgeArrayType SAMPLE1 = {{0, 1}, {0, 2}, {1, 2}, {2, 0}, {2, 3}, {3, 3}};


THE_BENCHMARK(isReachable, 4, SAMPLE1, 1, 3);

SIMPLE_TEST(isReachable, TestSAMPLE1, true, 4, SAMPLE1, 1, 3);
SIMPLE_TEST(isReachable, TestSAMPLE2, false, 4, SAMPLE1, 3, 1);


const UndirectedEdgeArrayType SAMPLE1U = {{0, 1}, {1, 2}, {2, 0}};
const UndirectedEdgeArrayType SAMPLE2U = {{0, 1}, {0, 2}, {3, 5}, {5, 4}, {4, 3}};


THE_BENCHMARK(isReachable_DisjointSet, 3, SAMPLE1U, 0, 2);

SIMPLE_TEST(isReachable_DisjointSet, TestSAMPLE1, true, 3, SAMPLE1U, 0, 2);
SIMPLE_TEST(isReachable_DisjointSet, TestSAMPLE2, false, 6, SAMPLE1U, 0, 5);


const DirectedEdgeArrayType SAMPLE2 = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {2, 3}, {3, 4}};


THE_BENCHMARK(NumberPaths_DAG, 5, SAMPLE2, 0, 4);

SIMPLE_TEST(NumberPaths_DAG, TestSAMPLE2, 3, 5, SAMPLE2, 0, 4);


const std::vector<ArrayType> SAMPLE1G = {{1, 2}, {3}, {3}, {}};
const std::vector<ArrayType> EXPECTED1 = {{0, 1, 3}, {0, 2, 3}};

const std::vector<ArrayType> SAMPLE2G = {{4, 3, 1}, {3, 2, 4}, {3}, {4}, {}};
const std::vector<ArrayType> EXPECTED2 = {{0, 4}, {0, 3, 4}, {0, 1, 3, 4}, {0, 1, 2, 3, 4}, {0, 1, 4}};

const std::vector<ArrayType> SAMPLE3G = {{1}, {}};
const std::vector<ArrayType> EXPECTED3 = {{0, 1}};

const std::vector<ArrayType> SAMPLE4G = {{1, 2, 3}, {2}, {3}, {}};
const std::vector<ArrayType> EXPECTED4 = {{0, 1, 2, 3}, {0, 2, 3}, {0, 3}};

const std::vector<ArrayType> SAMPLE5G = {{1, 3}, {2}, {3}, {}};
const std::vector<ArrayType> EXPECTED5 = {{0, 1, 2, 3}, {0, 3}};


THE_BENCHMARK(AllPathsSourceTarget, SAMPLE1G);

SIMPLE_TEST(AllPathsSourceTarget, TestSAMPLE1, EXPECTED1, SAMPLE1G);
SIMPLE_TEST(AllPathsSourceTarget, TestSAMPLE2, EXPECTED2, SAMPLE2G);
SIMPLE_TEST(AllPathsSourceTarget, TestSAMPLE3, EXPECTED3, SAMPLE3G);
SIMPLE_TEST(AllPathsSourceTarget, TestSAMPLE4, EXPECTED4, SAMPLE4G);
SIMPLE_TEST(AllPathsSourceTarget, TestSAMPLE5, EXPECTED5, SAMPLE5G);
