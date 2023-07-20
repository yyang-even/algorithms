#include "common_header.h"

#include "graph.h"

#include "data_structure/tree/binary_tree/binary_tree.h"
#include "data_structure/tree/binary_tree/single_order_to_binary_tree.h"


using namespace graph;

namespace {

/** Sum of Distances in Tree
 *
 * @reference   https://leetcode.com/problems/sum-of-distances-in-tree/
 *
 * There is an undirected connected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.
 * You are given the integer n and the array edges where edges[i] = [ai, bi] indicates that there is an
 * edge between nodes ai and bi in the tree.
 * Return an array answer of length n where answer[i] is the sum of the distances between the ith node
 * in the tree and all other nodes.
 */
void CountSubTreeSize(const AdjacencyListGraph::RepresentationType &graph,
                      const int node,
                      const int parent,
                      ArrayType &counts,
                      ArrayType &results) {
    for (const int child : graph[node]) {
        if (child != parent) {
            CountSubTreeSize(graph, child, node, counts, results);
            counts[node] += counts[child];
            results[node] += results[child] + counts[child];
        }
    }
}

void SumOfDistances(const AdjacencyListGraph::RepresentationType &graph,
                    const int node,
                    const int parent,
                    const ArrayType &counts,
                    ArrayType &results) {
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


/**
 * @reference   All Nodes Distance K in Binary Tree
 *              https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/
 *
 * Given the root of a binary tree, the value of a target node target, and an integer k, return an array
 * of the values of all nodes that have a distance k from the target node.
 * You can return the answer in any order.
 * All the values Node.val are unique.
 */
void searchKNode(const BinaryTree::Node::PointerType node, const int k, ArrayType &result) {
    if (not node) {
        return;
    }

    if (k == 0) {
        result.push_back(node->value);
    } else {
        searchKNode(node->left, k - 1, result);
        searchKNode(node->right, k - 1, result);
    }
}

int findTarget(const BinaryTree::Node::PointerType node,
               const BinaryTree::Node::PointerType target,
               const int k,
               ArrayType &result) {
    if (not node) {
        return 0;
    }

    if (node == target) {
        searchKNode(node, k, result);
        return 1;
    } else {
        if (const auto left = findTarget(node->left, target, k, result); left) {
            if (k > left) {
                searchKNode(node->right, k - left - 1, result);
            } else if (k == left) {
                result.push_back(node->value);
            }

            return left + 1;
        } else if (const auto right = findTarget(node->right, target, k, result); right) {
            if (k > right) {
                searchKNode(node->left, k - right - 1, result);
            } else if (k == right) {
                result.push_back(node->value);
            }

            return right + 1;
        }
    }

    return 0;
}

auto DistanceK(const BinaryTree::Node::PointerType root,
               const BinaryTree::Node::PointerType target,
               const int k) {
    ArrayType result;
    findTarget(root, target, k, result);

    return result;
}

} //namespace


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


/**
 *     1
 *    / \
 *   2   3
 *    \
 *     4
 */
const auto SAMPLE1T = LevelOrderToBinaryTree({1, 2, 3, SENTINEL, 4});
const ArrayType EXPECTED1T = {4, 1};

/**
 *       3
 *    /     \
 *   5       1
 *  / \     / \
 * 6   2   0   8
 *    / \
 *   7   4
 */
const auto SAMPLE2T = LevelOrderToBinaryTree({3, 5, 1, 6, 2, 0, 8, SENTINEL, SENTINEL, 7, 4});
const ArrayType EXPECTED2T = {7, 4, 1};


THE_BENCHMARK(DistanceK, SAMPLE1T, SAMPLE1T->left, 1);

SIMPLE_TEST(DistanceK, TestSAMPLE1, EXPECTED1T, SAMPLE1T, SAMPLE1T->left, 1);
SIMPLE_TEST(DistanceK, TestSAMPLE2, EXPECTED2T, SAMPLE2T, SAMPLE2T->left, 2);
