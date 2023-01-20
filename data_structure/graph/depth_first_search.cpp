#include "common_header.h"

#include "graph.h"


using namespace graph;

namespace {

#include "depth_first_search.h"


inline auto DepthFirstSearch_Recursive(const std::size_t number_vertices,
                                       const DirectedEdgeArrayType &edges) {
    ArrayType results;
    GraphTraverse(number_vertices,
                  edges,
                  [&results](const auto &graph, const auto source, auto &visited_vertices) {
                      DepthFirstSearch_Recursive(graph, source, visited_vertices, results);
                      return true;
                  });

    return results;
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 22.3-7.
 * @reference   Iterative Depth First Traversal of Graph
 *              https://www.geeksforgeeks.org/iterative-depth-first-traversal/
 */
void DepthFirstSearch_Iterative(const AdjacencyListGraph::RepresentationType &graph,
                                const std::size_t source,
                                std::vector<bool> &visited_vertices,
                                ArrayType &results) {
    std::stack<std::size_t> gray_vertex_stack;
    gray_vertex_stack.push(source);

    while (not gray_vertex_stack.empty()) {
        const auto vertex = gray_vertex_stack.top();
        gray_vertex_stack.pop();

        visited_vertices[vertex] = true;
        results.push_back(vertex);

        for (const auto adjacent_vertex : graph.at(vertex)) {
            if (not visited_vertices[adjacent_vertex]) {
                gray_vertex_stack.push(adjacent_vertex);
            }
        }
    }
}

inline auto DepthFirstSearch_Iterative(const std::size_t number_vertices,
                                       const DirectedEdgeArrayType &edges) {
    ArrayType results;
    GraphTraverse(number_vertices,
                  edges,
                  [&results](const auto &graph, const auto source, auto &visited_vertices) {
                      DepthFirstSearch_Iterative(graph, source, visited_vertices, results);
                      return true;
                  });

    return results;
}


/**
 * @reference   Implementation of DFS using adjacency matrix
 *              https://www.geeksforgeeks.org/implementation-of-dfs-using-adjacency-matrix/
 */
void DepthFirstSearch_Recursive(const AdjacencyMatrixGraph::RepresentationType &graph,
                                const std::size_t source,
                                std::vector<bool> &visited_vertices,
                                graph::ArrayType &results) {
    visited_vertices[source] = true;
    results.push_back(source);

    for (std::size_t adjacent_vertex = 0; adjacent_vertex < graph.size(); ++adjacent_vertex) {
        if (graph.at(source).at(adjacent_vertex) and not visited_vertices[adjacent_vertex]) {
            DepthFirstSearch_Recursive(graph, adjacent_vertex, visited_vertices, results);
        }
    }
}

inline auto DepthFirstSearch_Recursive_AdjMatrix(const std::size_t number_vertices,
                                                 const DirectedEdgeArrayType &edges) {
    ArrayType results;
    GraphTraverse(AdjacencyMatrixGraph {number_vertices, edges},
                  [&results](const auto &graph, const auto source, auto &visited_vertices) {
                      DepthFirstSearch_Recursive(graph, source, visited_vertices, results);
                      return true;
                  });

    return results;
}


/**
 * @reference   Print the DFS traversal step-wise (Backtracking also)
 *              https://www.geeksforgeeks.org/print-the-dfs-traversal-step-wise-backtracking-also/
 */


/**
 * @reference   Number of Nodes in the Sub-Tree With the Same Label
 *              https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/
 *
 * You are given a tree (i.e. a connected, undirected graph that has no cycles) consisting of n nodes
 * numbered from 0 to n - 1 and exactly n - 1 edges. The root of the tree is the node 0, and each node
 * of the tree has a label which is a lower-case character given in the string labels (i.e. The node
 * with the number i has the label labels[i]).
 *
 * The edges array is given on the form edges[i] = [ai, bi], which means there is an edge between nodes
 * ai and bi in the tree.
 *
 * Return an array of size n where ans[i] is the number of nodes in the subtree of the ith node which
 * have the same label as node i.
 *
 * A subtree of a tree T is the tree consisting of a node in T and all of its descendant nodes.
 */
std::unordered_map<char, int>
CountSubTreesWithSameLabel(const AdjacencyListGraph::RepresentationType &graph,
                           const int i,
                           const std::string_view labels,
                           ArrayType &result) {
    result[i] = 1;

    std::unordered_map<char, int> counts;
    for (const auto child : graph[i]) {
        if (not result[child]) {
            const auto sub_counts = CountSubTreesWithSameLabel(graph, child, labels, result);
            for (const auto [l, c] : sub_counts) {
                counts[l] += c;
            }
        }
    }

    const auto c = labels[i];

    result[i] = ++(counts[c]);

    return counts;
}

auto CountSubTreesWithSameLabel(const std::size_t n,
                                const UndirectedEdgeArrayType &edges,
                                const std::string_view labels) {
    ArrayType result(n, 0);

    AdjacencyListGraph {n, edges}.Visit([labels, &result](const auto &graph) {
        CountSubTreesWithSameLabel(graph, 0, labels, result);
    });

    return result;
}

} //namespace


const DirectedEdgeArrayType SAMPLE1 = {{0, 1}, {0, 2}, {1, 2}, {2, 0}, {2, 3}, {3, 3}};
const ArrayType EXPECTED1 = {0, 1, 2, 3};


THE_BENCHMARK(DepthFirstSearch_Recursive, 4, SAMPLE1);

SIMPLE_TEST(DepthFirstSearch_Recursive, TestSAMPLE1, EXPECTED1, 4, SAMPLE1);


const DirectedEdgeArrayType SAMPLE2 = {{1, 0}, {2, 1}, {3, 4}, {4, 0}};
const ArrayType EXPECTED2 = {0, 1, 2, 3, 4};


THE_BENCHMARK(DepthFirstSearch_Iterative, 5, SAMPLE2);

SIMPLE_TEST(DepthFirstSearch_Iterative, TestSAMPLE2, EXPECTED2, 5, SAMPLE2);


THE_BENCHMARK(DepthFirstSearch_Recursive_AdjMatrix, 4, SAMPLE1);

SIMPLE_TEST(DepthFirstSearch_Recursive_AdjMatrix, TestSAMPLE1, EXPECTED1, 4, SAMPLE1);


const UndirectedEdgeArrayType SAMPLE1T = {{0, 1}, {0, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6}};
const ArrayType EXPECTED1T = {2, 1, 1, 1, 1, 1, 1};

const UndirectedEdgeArrayType SAMPLE2T = {{0, 1}, {1, 2}, {0, 3}};
const ArrayType EXPECTED2T = {4, 2, 1, 1};

const UndirectedEdgeArrayType SAMPLE3T = {{0, 1}, {0, 2}, {1, 3}, {0, 4}};
const ArrayType EXPECTED3T = {3, 2, 1, 1, 1};


THE_BENCHMARK(CountSubTreesWithSameLabel, 7, SAMPLE1T, "abaedcd");

SIMPLE_TEST(CountSubTreesWithSameLabel, TestSAMPLE1, EXPECTED1T, 7, SAMPLE1T, "abaedcd");
SIMPLE_TEST(CountSubTreesWithSameLabel, TestSAMPLE2, EXPECTED2T, 4, SAMPLE2T, "bbbb");
SIMPLE_TEST(CountSubTreesWithSameLabel, TestSAMPLE3, EXPECTED3T, 5, SAMPLE3T, "aabab");
