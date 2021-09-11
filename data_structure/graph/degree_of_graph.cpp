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
 * Given the number of vertices in a Cycle Graph. The task is to find the Degree and the
 * number of Edges of the cycle graph.
 */
inline constexpr auto SumOfDegreesOfCycleGraph(const std::size_t number_vertices) {
    return SumOfDegreesOfUndirectedGraph(number_vertices);
}


inline auto InDegrees(const std::size_t number_vertices,
                      const UndirectedEdgeArrayType &edges) {
    return AdjacencyListGraph(number_vertices, edges).Visit(ToLambda(InDegrees));
}


inline auto OutDegrees(const std::size_t number_vertices,
                       const UndirectedEdgeArrayType &edges) {
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
    return AdjacencyMatrixGraph(number_vertices, edges).Visit(
    [source](const auto & graph) {
        return DegreeOfVertex(graph, source);
    });
}


/**
 * @reference   Find the Town Judge
 *              https://leetcode.com/problems/find-the-town-judge/
 *
 * In a town, there are n people labeled from 1 to n. There is a rumor that one of these
 * people is secretly the town judge. If the town judge exists, then:
 *  The town judge trusts nobody.
 *  Everybody (except for the town judge) trusts the town judge.
 *  There is exactly one person that satisfies properties 1 and 2.
 * You are given an array trust where trust[i] = [ai, bi] representing that the person
 * labeled ai trusts the person labeled bi. Return the label of the town judge if the
 * town judge exists and can be identified, or return -1 otherwise.
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

}//namespace


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
