#include "common_header.h"

#include "graph.h"


using namespace graph;


namespace {

using ArrayType = std::vector<int>;

/** Reorder Routes to Make All Paths Lead to the City Zero
 *
 * @reference   https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/
 *
 * There are n cities numbered from 0 to n - 1 and n - 1 roads such that there is only one way to travel
 * between two different cities (this network form a tree). Last year, The ministry of transport decided
 * to orient the roads in one direction because they are too narrow.
 * Roads are represented by connections where connections[i] = [ai, bi] represents a road from city ai
 * to city bi.
 * This year, there will be a big event in the capital (city 0), and many people want to travel to this
 * city.
 * Your task consists of reorienting some roads such that each city can visit the city 0. Return the
 * minimum number of edges changed.
 * It's guaranteed that each city can reach city 0 after reorder.
 */
void MakeAllPathsLeadToCityZero(const std::vector<std::vector<std::pair<int, int>>> &graph,
                                const int i,
                                const int parent,
                                int &result) {
    for (const auto &[child, direction] : graph[i]) {
        if (child != parent) {
            result += direction;
            MakeAllPathsLeadToCityZero(graph, child, i, result);
        }
    }
}

auto MakeAllPathsLeadToCityZero(const int N, const DirectedEdgeArrayType &connections) {
    std::vector graph(N, std::vector<std::pair<int, int>> {});
    for (const auto &e : connections) {
        graph[e.from].emplace_back(e.to, 1);
        graph[e.to].emplace_back(e.from, 0);
    }

    int result = 0;
    MakeAllPathsLeadToCityZero(graph, 0, -1, result);

    return result;
}

} //namespace


const DirectedEdgeArrayType SAMPLE1 = {{0, 1}, {1, 3}, {2, 3}, {4, 0}, {4, 5}};
const DirectedEdgeArrayType SAMPLE2 = {{1, 0}, {1, 2}, {3, 2}, {3, 4}};
const DirectedEdgeArrayType SAMPLE3 = {{1, 0}, {2, 0}};


THE_BENCHMARK(MakeAllPathsLeadToCityZero, 6, SAMPLE1);

SIMPLE_TEST(MakeAllPathsLeadToCityZero, TestSAMPLE1, 3, 6, SAMPLE1);
SIMPLE_TEST(MakeAllPathsLeadToCityZero, TestSAMPLE2, 2, 5, SAMPLE2);
SIMPLE_TEST(MakeAllPathsLeadToCityZero, TestSAMPLE3, 0, 3, SAMPLE3);
