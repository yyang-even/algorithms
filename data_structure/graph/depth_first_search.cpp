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
 * The edges array is given on the form edges[i] = [ai, bi], which means there is an edge between nodes
 * ai and bi in the tree.
 * Return an array of size n where ans[i] is the number of nodes in the subtree of the ith node which
 * have the same label as node i.
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


/**
 * @reference   Minimum Fuel Cost to Report to the Capital
 *              https://leetcode.com/problems/minimum-fuel-cost-to-report-to-the-capital/
 *
 * There is a tree (i.e., a connected, undirected graph with no cycles) structure country network
 * consisting of n cities numbered from 0 to n - 1 and exactly n - 1 roads. The capital city is city 0.
 * You are given a 2D integer array roads where roads[i] = [ai, bi] denotes that there exists a
 * bidirectional road connecting cities ai and bi.
 * There is a meeting for the representatives of each city. The meeting is in the capital city.
 * There is a car in each city. You are given an integer seats that indicates the number of seats in
 * each car.
 * A representative can use the car in their city to travel or change the car and ride with another
 * representative. The cost of traveling between two cities is one liter of fuel.
 * Return the minimum number of liters of fuel to reach the capital city.
 */
int MinFuelCostToCapitcal(const std::size_t i,
                          const std::size_t parent,
                          const AdjacencyListGraph::RepresentationType &graph,
                          const double seats,
                          int &result) {
    int representatives = 1;
    for (const auto neighbor : graph[i]) {
        if (neighbor != parent) {
            representatives += MinFuelCostToCapitcal(neighbor, i, graph, seats, result);
        }
    }

    if (i != 0) {
        result += std::ceil(representatives / seats);
    }

    return representatives;
}

auto MinFuelCostToCapitcal(const UndirectedEdgeArrayType &edges, const int seats) {
    int result = 0;
    AdjacencyListGraph {edges.size() + 1, edges}.Visit([seats, &result](const auto &graph) {
        MinFuelCostToCapitcal(0, -1, graph, seats, result);
    });

    return result;
}


/**
 * @reference   Validate Binary Tree Nodes
 *              https://leetcode.com/problems/validate-binary-tree-nodes/
 *
 * You have n binary tree nodes numbered from 0 to n - 1 where node i has two children leftChild[i] and
 * rightChild[i], return true if and only if all the given nodes form exactly one valid binary tree.
 * If node i has no left child then leftChild[i] will equal -1, similarly for the right child.
 * Note that the nodes have no values and that we only use the node numbers in this problem.
 */
int countNodes(const std::vector<int> &left_child,
               const std::vector<int> &right_child,
               const int i) {
    if (i == -1) {
        return 0;
    }

    return 1 + countNodes(left_child, right_child, left_child[i]) +
           countNodes(left_child, right_child, right_child[i]);
}

bool ValidateBinaryTreeNodes(const int n,
                             const std::vector<int> &left_child,
                             const std::vector<int> &right_child) {
    std::vector<int> indegree(n, 0);
    for (int i = 0; i < n; ++i) {
        if (left_child[i] != -1) {
            ++indegree[left_child[i]];
        }
        if (right_child[i] != -1) {
            ++indegree[right_child[i]];
        }
    }

    int root = -1;
    for (int i = 0; i < n; ++i) {
        if (indegree[i] == 0) {
            if (root != -1) {
                return false;
            }
            root = i;
        } else if (indegree[i] > 1) {
            return false;
        }
    }

    if (root == -1) {
        return false;
    }

    return countNodes(left_child, right_child, root) == n;
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


const UndirectedEdgeArrayType SAMPLE1C = {{0, 1}, {0, 2}, {0, 3}};
const UndirectedEdgeArrayType SAMPLE2C = {{3, 1}, {3, 2}, {1, 0}, {0, 4}, {0, 5}, {4, 6}};
const UndirectedEdgeArrayType SAMPLE3C = {};


THE_BENCHMARK(MinFuelCostToCapitcal, SAMPLE1C, 5);

SIMPLE_TEST(MinFuelCostToCapitcal, TestSAMPLE1, 3, SAMPLE1C, 5);
SIMPLE_TEST(MinFuelCostToCapitcal, TestSAMPLE2, 7, SAMPLE2C, 2);
SIMPLE_TEST(MinFuelCostToCapitcal, TestSAMPLE3, 0, SAMPLE3C, 1);


const std::vector SAMPLE1L = {1, -1, 3, -1};
const std::vector SAMPLE1R = {2, -1, -1, -1};

const std::vector SAMPLE2L = {1, -1, 3, -1};
const std::vector SAMPLE2R = {2, 3, -1, -1};

const std::vector SAMPLE3L = {1, 0};
const std::vector SAMPLE3R = {-1, -1};

const std::vector SAMPLE4L = {1, 0, 3, -1};
const std::vector SAMPLE4R = {-1, -1, -1, -1};


THE_BENCHMARK(ValidateBinaryTreeNodes, SAMPLE1L.size(), SAMPLE1L, SAMPLE1R);

SIMPLE_TEST(ValidateBinaryTreeNodes, TestSAMPLE1, true, SAMPLE1L.size(), SAMPLE1L, SAMPLE1R);
SIMPLE_TEST(ValidateBinaryTreeNodes, TestSAMPLE2, false, SAMPLE2L.size(), SAMPLE2L, SAMPLE2R);
SIMPLE_TEST(ValidateBinaryTreeNodes, TestSAMPLE3, false, SAMPLE3L.size(), SAMPLE3L, SAMPLE3R);
SIMPLE_TEST(ValidateBinaryTreeNodes, TestSAMPLE4, false, SAMPLE4L.size(), SAMPLE4L, SAMPLE4R);
