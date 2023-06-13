#include "common_header.h"

#include "graph.h"


using namespace graph;

namespace {

#include "degree_of_graph.h"

/**
 * @reference   Sum of degrees of all nodes of a undirected graph
 *              https://www.geeksforgeeks.org/sum-of-degrees-of-all-nodes-of-a-undirected-graph/
 */
inline constexpr auto SumOfDegreesOfUndirectedGraph(const std::size_t number_edges) {
    return number_edges * 2;
}


/** Degree of a Cycle Graph
 *
 * @reference   https://www.geeksforgeeks.org/degree-of-a-cycle-graph/
 *
 * Given the number of vertices in a Cycle Graph. The task is to find the Degree and the number of Edges
 * of the cycle graph.
 */
inline constexpr auto SumOfDegreesOfCycleGraph(const std::size_t number_vertices) {
    return SumOfDegreesOfUndirectedGraph(number_vertices);
}


inline auto InDegrees(const std::size_t number_vertices, const UndirectedEdgeArrayType &edges) {
    return AdjacencyListGraph(number_vertices, edges).Visit(ToLambda(InDegrees));
}


inline auto OutDegrees(const std::size_t number_vertices, const UndirectedEdgeArrayType &edges) {
    return AdjacencyListGraph(number_vertices, edges).Visit(ToLambda(OutDegrees));
}


/** Find the Degree of a Particular vertex in a Graph
 *
 * @reference   https://www.geeksforgeeks.org/find-degree-particular-vertex-graph/
 */
auto DegreeOfVertex(const AdjacencyMatrixGraph::RepresentationType &graph,
                    const std::size_t source) {
    int out_degree = 0;

    for (std::size_t i = 0; i < graph.size(); ++i) {
        if (graph.at(source).at(i)) {
            ++out_degree;
        }
    }

    return out_degree;
}

auto DegreeOfVertex(const std::size_t number_vertices,
                    const UndirectedEdgeArrayType &edges,
                    const std::size_t source) {
    return AdjacencyMatrixGraph(number_vertices, edges).Visit([source](const auto &graph) {
        return DegreeOfVertex(graph, source);
    });
}


/**
 * @reference   Find the Town Judge
 *              https://leetcode.com/problems/find-the-town-judge/
 *
 * In a town, there are n people labeled from 1 to n. There is a rumor that one of these people is
 * secretly the town judge. If the town judge exists, then:
 *  The town judge trusts nobody.
 *  Everybody (except for the town judge) trusts the town judge.
 *  There is exactly one person that satisfies properties 1 and 2.
 * You are given an array trust where trust[i] = [ai, bi] representing that the person labeled ai trusts
 * the person labeled bi. Return the label of the town judge if the town judge exists and can be
 * identified, or return -1 otherwise.
 */
int FindJudge(const int n, const DirectedEdgeArrayType &trust) {
    int in_degree[n + 1] = {};
    int out_degree[n + 1] = {};

    for (const auto &edge : trust) {
        ++out_degree[edge.from];
        ++in_degree[edge.to];
    }

    for (int i = 1; i <= n; ++i) {
        if (out_degree[i] == 0 and in_degree[i] == n - 1) {
            return i;
        }
    }

    return -1;
}


/**
 * @reference   Destination City
 *              https://leetcode.com/problems/destination-city/
 *
 * You are given the array paths, where paths[i] = [cityAi, cityBi] means there exists a direct path
 * going from cityAi to cityBi. Return the destination city, that is, the city without any path outgoing
 * to another city.
 * It is guaranteed that the graph of paths forms a line without any loop, therefore, there will be
 * exactly one destination city.
 */


/**
 * @reference   Minimum Number of Vertices to Reach All Nodes
 *              https://leetcode.com/problems/minimum-number-of-vertices-to-reach-all-nodes/
 *
 * Given a directed acyclic graph, with n vertices numbered from 0 to n-1, and an array edges where
 * edges[i] = [fromi, toi] represents a directed edge from node fromi to node toi.
 * Find the smallest set of vertices from which all nodes in the graph are reachable. It's guaranteed
 * that a unique solution exists.
 * Notice that you can return the vertices in any order.
 */


/**
 * @reference   Find Players With Zero or One Losses
 *              https://leetcode.com/problems/find-players-with-zero-or-one-losses/
 *
 * You are given an integer array matches where matches[i] = [winneri, loseri] indicates that the player
 * winneri defeated player loseri in a match.
 * Return a list answer of size 2 where:
 *  answer[0] is a list of all players that have not lost any matches.
 *  answer[1] is a list of all players that have lost exactly one match.
 * The values in the two lists should be returned in increasing order.
 * Note:
 *  You should only consider the players that have played at least one match.
 *  The testcases will be generated such that no two matches will have the same outcome.
 */
auto FindPlayers(const DirectedEdgeArrayType &matches) {
    std::map<int, int> lose;
    for (const auto &m : matches) {
        lose.emplace(m.from, 0);
        ++(lose[m.to]);
    }

    ArrayType zero;
    ArrayType one;
    for (const auto &[p, l] : lose) {
        if (l == 0) {
            zero.push_back(p);
        } else if (l == 1) {
            one.push_back(p);
        }
    }

    return std::pair(zero, one);
}


/**
 * @reference   Find Center of Star Graph
 *              https://leetcode.com/problems/find-center-of-star-graph/
 *
 * There is an undirected star graph consisting of n nodes labeled from 1 to n. A star graph is a graph
 * where there is one center node and exactly n - 1 edges that connect the center node with every other
 * node.
 * You are given a 2D integer array edges where each edges[i] = [ui, vi] indicates that there is an edge
 * between the nodes ui and vi. Return the center of the given star graph.
 * 3 <= n <= 10^5
 */
auto FindCenterOfStarGraph(const UndirectedEdgeArrayType &edges) {
    const auto &one_edge = edges.front();
    const auto &another = edges.back();

    return (one_edge.u == another.u or one_edge.u == another.v) ? one_edge.u : one_edge.v;
}

} //namespace


THE_BENCHMARK(SumOfDegreesOfCycleGraph, 4);

SIMPLE_TEST(SumOfDegreesOfCycleGraph, TestSAMPLE1, 8, 4);


const UndirectedEdgeArrayType SAMPLE1 = {{0, 1}, {1, 2}, {0, 3}, {1, 3}};
const ArrayType EXPECTED1 = {2, 3, 1, 2};


THE_BENCHMARK(InDegrees, 4, SAMPLE1);

SIMPLE_TEST(InDegrees, TestSAMPLE1, EXPECTED1, 4, SAMPLE1);


THE_BENCHMARK(OutDegrees, 4, SAMPLE1);

SIMPLE_TEST(OutDegrees, TestSAMPLE1, EXPECTED1, 4, SAMPLE1);


THE_BENCHMARK(DegreeOfVertex, 4, SAMPLE1, 1);

SIMPLE_TEST(DegreeOfVertex, TestSAMPLE1, EXPECTED1[0], 4, SAMPLE1, 0);
SIMPLE_TEST(DegreeOfVertex, TestSAMPLE2, EXPECTED1[1], 4, SAMPLE1, 1);


const DirectedEdgeArrayType SAMPLE1D = {{1, 2}};
const DirectedEdgeArrayType SAMPLE2D = {{1, 3}, {2, 3}};
const DirectedEdgeArrayType SAMPLE3D = {{1, 3}, {2, 3}, {3, 1}};
const DirectedEdgeArrayType SAMPLE4D = {{1, 2}, {2, 3}};
const DirectedEdgeArrayType SAMPLE5D = {{1, 3}, {1, 4}, {2, 3}, {2, 4}, {4, 3}};


THE_BENCHMARK(FindJudge, 3, SAMPLE3D);

SIMPLE_TEST(FindJudge, TestSAMPLE1, 2, 2, SAMPLE1D);
SIMPLE_TEST(FindJudge, TestSAMPLE2, 3, 3, SAMPLE2D);
SIMPLE_TEST(FindJudge, TestSAMPLE3, -1, 3, SAMPLE3D);
SIMPLE_TEST(FindJudge, TestSAMPLE4, -1, 3, SAMPLE4D);
SIMPLE_TEST(FindJudge, TestSAMPLE5, 3, 4, SAMPLE5D);


const UndirectedEdgeArrayType SAMPLE1S = {{1, 2}, {2, 3}, {4, 2}};
const UndirectedEdgeArrayType SAMPLE2S = {{1, 2}, {5, 1}, {1, 3}, {1, 4}};


THE_BENCHMARK(FindCenterOfStarGraph, SAMPLE1S);

SIMPLE_TEST(FindCenterOfStarGraph, TestSAMPLE1, 2, SAMPLE1S);
SIMPLE_TEST(FindCenterOfStarGraph, TestSAMPLE2, 1, SAMPLE2S);


const DirectedEdgeArrayType SAMPLE1M = {
    {1, 3}, {2, 3}, {3, 6}, {5, 6}, {5, 7}, {4, 5}, {4, 8}, {4, 9}, {10, 4}, {10, 9}};
const std::pair<ArrayType, ArrayType> EXPECTED1M = {{1, 2, 10}, {4, 5, 7, 8}};

const DirectedEdgeArrayType SAMPLE2M = {{2, 3}, {1, 3}, {5, 4}, {6, 4}};
const std::pair<ArrayType, ArrayType> EXPECTED2M = {{1, 2, 5, 6}, {}};


THE_BENCHMARK(FindPlayers, SAMPLE1M);

SIMPLE_TEST(FindPlayers, TestSAMPLE1, EXPECTED1M, SAMPLE1M);
SIMPLE_TEST(FindPlayers, TestSAMPLE2, EXPECTED2M, SAMPLE2M);
