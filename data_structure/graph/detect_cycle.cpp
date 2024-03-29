#include "common_header.h"

#include "graph.h"
#include "topological_sort.h"

#include "data_structure/disjoint_set.h"


using namespace graph;

namespace {

/** Detect Cycle in a Directed Graph
 *
 * @reference   https://www.geeksforgeeks.org/detect-cycle-in-a-graph/
 * @reference   Detect Cycle in a directed graph using colors
 *              https://www.geeksforgeeks.org/detect-cycle-direct-graph-using-colors/
 * @reference   C Program to Detect Cycle in a Directed Graph
 *              https://www.geeksforgeeks.org/c-program-for-detect-cycle-in-a-directed-graph/
 */
bool DetectCycle_DFS(const AdjacencyListGraph::RepresentationType &graph,
                     const std::size_t source,
                     std::vector<bool> &visited_vertices,
                     std::vector<bool> &in_stack_vertices) {
    visited_vertices[source] = true;
    in_stack_vertices[source] = true;

    for (const auto adjacent_vertex : graph.at(source)) {
        if (not visited_vertices[adjacent_vertex] and
            DetectCycle_DFS(graph, adjacent_vertex, visited_vertices, in_stack_vertices)) {
            return true;
        } else if (in_stack_vertices[adjacent_vertex]) {
            return true;
        }
    }

    in_stack_vertices[source] = false;
    return false;
}

inline auto DetectCycle_DFS(const std::size_t number_vertices,
                            const DirectedEdgeArrayType &edges) {
    std::vector<bool> in_stack_vertices(number_vertices, false);
    bool result = false;

    GraphTraverse(number_vertices, edges,
                  [&in_stack_vertices, &result]
    (const auto & graph, const auto source, auto & visited_vertices) {
        result = DetectCycle_DFS(graph, source, visited_vertices, in_stack_vertices);
        return not result;
    });

    return result;
}


/**
 * @reference   Detect Cycle in a Directed Graph using BFS
 *              https://www.geeksforgeeks.org/detect-cycle-in-a-directed-graph-using-bfs/
 */
inline auto DetectCycle_Degrees(const std::size_t number_vertices,
                                const DirectedEdgeArrayType &edges) {
    return not AdjacencyListGraph(number_vertices, edges).Visit(TopologicalSort_Kahn).first;
}


/**
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 16.4.
 *
 * Design a class which provides a lock only if there are no possible deadlocks.
 */


/** Detect cycle in an undirected graph
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 22.4-3.
 * @reference   Detect cycle in an undirected graph
 *              https://www.geeksforgeeks.org/detect-cycle-undirected-graph/
 */
bool DetectCycle_Undirected_DFS(const AdjacencyListGraph::RepresentationType &graph,
                                const std::size_t source,
                                std::vector<bool> &visited_vertices,
                                const std::size_t parent = -1) {
    visited_vertices[source] = true;

    for (const auto adjacent_vertex : graph.at(source)) {
        if (not visited_vertices[adjacent_vertex]) {
            if (DetectCycle_Undirected_DFS(graph, adjacent_vertex, visited_vertices, source)) {
                return true;
            }
        } else if (adjacent_vertex != parent) {
            return true;
        }
    }

    return false;
}

inline auto DetectCycle_Undirected_DFS(const std::size_t number_vertices,
                                       const UndirectedEdgeArrayType &edges) {
    bool result = false;

    GraphTraverse(number_vertices, edges,
    [&result](const auto & graph, const auto source, auto & visited_vertices) {
        result = DetectCycle_Undirected_DFS(graph, source, visited_vertices);
        return not result;
    });

    return result;
}


/**
 * @reference   Detect cycle in an undirected graph using BFS
 *              https://www.geeksforgeeks.org/detect-cycle-in-an-undirected-graph-using-bfs/
 */
bool DetectCycle_Undirected_BFS(const AdjacencyListGraph::RepresentationType &graph,
                                const std::size_t source,
                                std::vector<bool> &visited_vertices) {
    ArrayType parents(graph.size(), -1);
    std::queue<std::size_t> gray_vertex_queue;
    visited_vertices[source] = true;
    gray_vertex_queue.push(source);

    while (not gray_vertex_queue.empty()) {
        const auto vertex = gray_vertex_queue.front();
        gray_vertex_queue.pop();

        for (const auto adjacent_vertex : graph.at(vertex)) {
            if (not visited_vertices[adjacent_vertex]) {
                visited_vertices[adjacent_vertex] = true;
                gray_vertex_queue.push(adjacent_vertex);
                parents[adjacent_vertex] = vertex;
            } else if (parents[vertex] != adjacent_vertex) {
                return true;
            }
        }
    }

    return false;
}

inline auto DetectCycle_Undirected_BFS(const std::size_t number_vertices,
                                       const UndirectedEdgeArrayType &edges) {
    bool result = false;

    GraphTraverse(number_vertices, edges,
    [&result](const auto & graph, const auto source, auto & visited_vertices) {
        result = DetectCycle_Undirected_BFS(graph, source, visited_vertices);
        return not result;
    });

    return result;
}


/**
 * @reference   Detect cycle in the graph using degrees of nodes of graph
 *              https://www.geeksforgeeks.org/detect-cycle-in-the-graph-using-degrees-of-nodes-of-graph/
 *
 * Given a graph, the task is to detect a cycle in the graph using degrees of the nodes
 * in the graph and print all the nodes that are involved in any of the cycles. If there
 * is no cycle in the graph then print -1.
 */
auto
DetectCycle_Undirected_Degrees(const AdjacencyListGraph::RepresentationType &graph) {
    auto degrees = OutDegrees(graph);

    std::vector<bool> visited_vertices(graph.size(), false);

    std::queue<std::size_t> one_indegree_vertex_queue;
    for (std::size_t i = 0; i < graph.size(); ++i) {
        if (degrees[i] == 0) {
            visited_vertices[i] = true;
        } else if (degrees[i] == 1) {
            one_indegree_vertex_queue.push(i);
        }
    }

    while (not one_indegree_vertex_queue.empty()) {
        const auto vertex = one_indegree_vertex_queue.front();
        one_indegree_vertex_queue.pop();
        visited_vertices[vertex] = true;

        for (const auto adjacent_vertex : graph[vertex]) {
            if (--degrees[adjacent_vertex] == 1) {
                one_indegree_vertex_queue.push(adjacent_vertex);
            }
        }
    }

    ArrayType results;
    const auto N = visited_vertices.size();
    for (std::size_t i = 0; i < N; ++i) {
        if (not visited_vertices[i]) {
            results.push_back(i);
        }
    }

    return results;
}

inline auto DetectCycle_Undirected_Degrees(const std::size_t number_vertices,
                                           const UndirectedEdgeArrayType &edges) {
    return AdjacencyListGraph(number_vertices, edges).Visit
           (ToLambda(DetectCycle_Undirected_Degrees));
}


/**
 * @reference   Redundant Connection
 *              https://leetcode.com/problems/redundant-connection/
 *
 * In this problem, a tree is an undirected graph that is connected and has no cycles.
 * You are given a graph that started as a tree with n nodes labeled from 1 to n, with
 * one additional edge added. The added edge has two different vertices chosen from
 * 1 to n, and was not an edge that already existed. The graph is represented as an
 * array edges of length n where edges[i] = [ai, bi] indicates that there is an edge
 * between nodes ai and bi in the graph. Return an edge that can be removed so that the
 * resulting graph is a tree of n nodes. If there are multiple answers, return the
 * answer that occurs last in the input.
 */
auto DetectCycle_Undirected_DisjointSet(const std::size_t number_vertices,
                                        const UndirectedEdgeArrayType &edges) {
    DisjointSet_Array disjoint_set{number_vertices};

    for (const auto &an_edge : edges) {
        const auto u_set = disjoint_set.Find(an_edge.u);
        const auto v_set = disjoint_set.Find(an_edge.v);

        if (u_set == v_set) {
            return true;
        }

        disjoint_set.Link(u_set, v_set);
    }

    return false;
}


/**
 * @reference   Redundant Connection II
 *              https://leetcode.com/problems/redundant-connection-ii/
 * @reference   LeetCode 685. Redundant Connection II
 *              http://zxi.mytechroad.com/blog/graph/leetcode-685-redundant-connection-ii/
 *
 * In this problem, a rooted tree is a directed graph such that, there is exactly one
 * node (the root) for which all other nodes are descendants of this node, plus every
 * node has exactly one parent, except for the root node which has no parents. The given
 * input is a directed graph that started as a rooted tree with n nodes (with distinct
 * values from 1 to n), with one additional directed edge added. The added edge has two
 * different vertices chosen from 1 to n, and was not an edge that already existed. The
 * resulting graph is given as a 2D-array of edges. Each element of edges is a pair
 * [ui, vi] that represents a directed edge connecting nodes ui and vi, where ui is a
 * parent of child vi. Return an edge that can be removed so that the resulting graph is
 * a rooted tree of n nodes. If there are multiple answers, return the answer that
 * occurs last in the given 2D-array.
 */
auto RedundantConnection_Directed(const DirectedEdgeArrayType &edges) {
    std::vector<const DirectedEdge *> parents(edges.size() + 1, nullptr);
    const DirectedEdge *one_candidate = nullptr;
    const DirectedEdge *another_candidate = nullptr;
    for (const auto &an_edge : edges) {
        if (parents[an_edge.to]) {
            one_candidate = parents[an_edge.to];
            another_candidate = &an_edge;
            break;
        }

        parents[an_edge.to] = &an_edge;
    }

    DisjointSet_Array disjoint_set{edges.size() + 1};
    for (const auto &an_edge : edges) {
        if (another_candidate == &an_edge) {
            continue;
        }

        const auto u_set = disjoint_set.Find(an_edge.from);
        const auto v_set = disjoint_set.Find(an_edge.to);

        if (u_set == v_set) {
            return one_candidate ? *one_candidate : an_edge;
        }

        disjoint_set.Link(u_set, v_set);
    }

    assert(another_candidate);
    return *another_candidate;
}

}//namespace


const DirectedEdgeArrayType SAMPLE1 = {{0, 1}, {0, 2}, {1, 2}, {2, 0}, {2, 3}, {3, 3}};
const DirectedEdgeArrayType SAMPLE2 = {{0, 1}, {0, 2}, {1, 2}, {2, 3}};
const DirectedEdgeArrayType SAMPLE5 = {{1, 2}, {2, 3}, {3, 4}, {1, 3}, {3, 5}, {7, 5}, {5, 9}, {9, 2}};


THE_BENCHMARK(DetectCycle_DFS, 4, SAMPLE1);

SIMPLE_TEST(DetectCycle_DFS, TestSAMPLE1, true, 4, SAMPLE1);
SIMPLE_TEST(DetectCycle_DFS, TestSAMPLE2, false, 4, SAMPLE2);
SIMPLE_TEST(DetectCycle_DFS, TestSAMPLE5, true, 10, SAMPLE5);


THE_BENCHMARK(DetectCycle_Degrees, 4, SAMPLE1);

SIMPLE_TEST(DetectCycle_Degrees, TestSAMPLE1, true, 4, SAMPLE1);
SIMPLE_TEST(DetectCycle_Degrees, TestSAMPLE2, false, 4, SAMPLE2);
SIMPLE_TEST(DetectCycle_Degrees, TestSAMPLE5, true, 10, SAMPLE5);


const UndirectedEdgeArrayType SAMPLE3 = {{0, 1}, {0, 2}, {1, 2}, {0, 3}, {3, 4}};
const ArrayType EXPECTED3 = {0, 1, 2};

const UndirectedEdgeArrayType SAMPLE4 = {{0, 1}, {1, 2}};


THE_BENCHMARK(DetectCycle_Undirected_DFS, 5, SAMPLE3);

SIMPLE_TEST(DetectCycle_Undirected_DFS, TestSAMPLE3, true, 5, SAMPLE3);
SIMPLE_TEST(DetectCycle_Undirected_DFS, TestSAMPLE4, false, 3, SAMPLE4);


THE_BENCHMARK(DetectCycle_Undirected_BFS, 5, SAMPLE3);

SIMPLE_TEST(DetectCycle_Undirected_BFS, TestSAMPLE3, true, 5, SAMPLE3);
SIMPLE_TEST(DetectCycle_Undirected_BFS, TestSAMPLE4, false, 3, SAMPLE4);


THE_BENCHMARK(DetectCycle_Undirected_DisjointSet, 5, SAMPLE3);

SIMPLE_TEST(DetectCycle_Undirected_DisjointSet, TestSAMPLE3, true, 5, SAMPLE3);
SIMPLE_TEST(DetectCycle_Undirected_DisjointSet, TestSAMPLE4, false, 3, SAMPLE4);


THE_BENCHMARK(DetectCycle_Undirected_Degrees, 5, SAMPLE3);

SIMPLE_TEST(DetectCycle_Undirected_Degrees, TestSAMPLE3, EXPECTED3, 5, SAMPLE3);
SIMPLE_TEST(DetectCycle_Undirected_Degrees, TestSAMPLE4, {}, 3, SAMPLE4);


const DirectedEdgeArrayType SAMPLE6 = {{1, 2}, {1, 3}, {2, 3}};
const DirectedEdge EXPECTED6 = {2, 3};

const DirectedEdgeArrayType SAMPLE7 = {{1, 2}, {2, 3}, {3, 4}, {4, 1}, {1, 5}};
const DirectedEdge EXPECTED7 = {4, 1};

const DirectedEdgeArrayType SAMPLE8 = {{2, 1}, {3, 1}, {4, 2}, {1, 4}};
const DirectedEdge EXPECTED8 = {2, 1};

const DirectedEdgeArrayType SAMPLE9 = {{3, 1}, {2, 1}, {4, 2}, {1, 4}};


THE_BENCHMARK(RedundantConnection_Directed, SAMPLE6);

SIMPLE_TEST(RedundantConnection_Directed, TestSAMPLE6, EXPECTED6, SAMPLE6);
SIMPLE_TEST(RedundantConnection_Directed, TestSAMPLE7, EXPECTED7, SAMPLE7);
SIMPLE_TEST(RedundantConnection_Directed, TestSAMPLE8, EXPECTED8, SAMPLE8);
SIMPLE_TEST(RedundantConnection_Directed, TestSAMPLE9, EXPECTED8, SAMPLE9);
