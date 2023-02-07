#include "common_header.h"

#include "graph.h"


using namespace graph;

namespace {

using BoolArray = std::vector<bool>;

/** Minimum Time to Collect All Apples in a Tree
 *
 * @reference   https://leetcode.com/problems/minimum-time-to-collect-all-apples-in-a-tree/
 *
 * Given an undirected tree consisting of n vertices numbered from 0 to n-1, which has some apples in
 * their vertices. You spend 1 second to walk over one edge of the tree. Return the minimum time in
 * seconds you have to spend to collect all apples in the tree, starting at vertex 0 and coming back to
 * this vertex.
 * The edges of the undirected tree are given in the array edges, where edges[i] = [ai, bi] means that
 * exists an edge connecting the vertices ai and bi. Additionally, there is a boolean array hasApple,
 * where hasApple[i] = true means that vertex i has an apple; otherwise, it does not have any apple.
 */
int MinTimeToCollectAllApples(const AdjacencyListGraph::RepresentationType &graph,
                              const int i,
                              const BoolArray &has_apple,
                              const int parent) {
    int totalTime = 0;
    for (const int child : graph[i]) {
        if (child == parent) {
            continue;
        }

        const auto child_time = MinTimeToCollectAllApples(graph, child, has_apple, i);
        if (child_time or has_apple[child]) {
            totalTime += child_time + 2;
        }
    }

    return totalTime;
}

auto MinTimeToCollectAllApples(const std::size_t n,
                               const UndirectedEdgeArrayType &edges,
                               const BoolArray &has_apple) {
    return AdjacencyListGraph {n, edges}.Visit([&has_apple](const auto &graph) {
        return MinTimeToCollectAllApples(graph, 0, has_apple, -1);
    });
}

} //namespace


const UndirectedEdgeArrayType SAMPLE1T = {{0, 1}, {0, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6}};
const BoolArray SAMPLE1A = {false, false, true, false, true, true, false};

const BoolArray SAMPLE2A = {false, false, true, false, false, true, false};

const BoolArray SAMPLE3A = {false, false, false, false, false, false, false};


THE_BENCHMARK(MinTimeToCollectAllApples, 7, SAMPLE1T, SAMPLE1A);

SIMPLE_TEST(MinTimeToCollectAllApples, TestSAMPLE1, 8, 7, SAMPLE1T, SAMPLE1A);
SIMPLE_TEST(MinTimeToCollectAllApples, TestSAMPLE2, 6, 7, SAMPLE1T, SAMPLE2A);
SIMPLE_TEST(MinTimeToCollectAllApples, TestSAMPLE3, 0, 7, SAMPLE1T, SAMPLE3A);
