#include "common_header.h"

#include "graph.h"


using namespace graph;

namespace {

/** Sum of Distances in Tree
 *
 * @reference   https://leetcode.com/problems/sum-of-distances-in-tree/
 *
 * There is an undirected connected tree with n nodes labeled from 0 to n - 1 and n - 1
 * edges. You are given the integer n and the array edges where edges[i] = [ai, bi]
 * indicates that there is an edge between nodes ai and bi in the tree. Return an array
 * answer of length n where answer[i] is the sum of the distances between the ith node
 * in the tree and all other nodes.
 */
void CountSubTreeSize(const AdjacencyListGraph::RepresentationType &graph,
                      const int node, const int parent,
                      ArrayType &counts, ArrayType &results) {
    for (const int child : graph[node]) {
        if (child != parent) {
            CountSubTreeSize(graph, child, node, counts, results);
            counts[node] += counts[child];
            results[node] += results[child] + counts[child];
        }
    }
}

void SumOfDistances(const AdjacencyListGraph::RepresentationType &graph,
                    const int node, const int parent,
                    const ArrayType &counts, ArrayType &results) {
    for (const int child : graph[node]) {
        if (child != parent) {
            results[child] = results[node] - counts[child] + graph.size() - counts[child];
            SumOfDistances(graph, child, node, counts, results);
        }
    }
}

auto SumOfDistances(const AdjacencyListGraph::RepresentationType &graph) {
    ArrayType counts(graph.size(), 1);
    ArrayType results(graph.size(), 0);

    CountSubTreeSize(graph, 0, -1, counts, results);
    SumOfDistances(graph, 0, -1, counts, results);
    return results;
}

inline auto SumOfDistances(const std::size_t number_vertices,
                           const UndirectedEdgeArrayType &edges) {
    return AdjacencyListGraph(number_vertices, edges).Visit(ToLambda(SumOfDistances));
}

}//namespace


/**
 *    0
 *  /   \
 * 1     2
 *     / | \
 *    3  4  5
 */
const UndirectedEdgeArrayType SAMPLE1 = {{0, 1}, {0, 2}, {2, 3}, {2, 4}, {2, 5}};
const ArrayType EXPECTED1 = {8, 12, 6, 10, 10, 10};

const UndirectedEdgeArrayType SAMPLE2 = {};
const ArrayType EXPECTED2 = {0};

/**
 *   0
 *  /
 * 1
 */
const UndirectedEdgeArrayType SAMPLE3 = {{1, 0}};
const ArrayType EXPECTED3 = {1, 1};


THE_BENCHMARK(SumOfDistances, EXPECTED1.size(), SAMPLE1);

SIMPLE_TEST(SumOfDistances, TestSAMPLE1, EXPECTED1, EXPECTED1.size(), SAMPLE1);
SIMPLE_TEST(SumOfDistances, TestSAMPLE2, EXPECTED2, EXPECTED2.size(), SAMPLE2);
SIMPLE_TEST(SumOfDistances, TestSAMPLE3, EXPECTED3, EXPECTED3.size(), SAMPLE3);
