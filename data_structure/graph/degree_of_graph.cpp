#include "common_header.h"


namespace {

#include "degree_of_graph.h"


/**
 * @reference   Sum of degrees of all nodes of a undirected graph
 *              https://www.geeksforgeeks.org/sum-of-degrees-of-all-nodes-of-a-undirected-graph/
 */
auto SumOfDegreesOfUndirectedGraph(const std::size_t number_edges) {
    return number_edges * 2;
}


/** Degree of a Cycle Graph
 *
 * @reference   https://www.geeksforgeeks.org/degree-of-a-cycle-graph/
 *
 * Given the number of vertices in a Cycle Graph. The task is to find the
 * Degree and the number of Edges of the cycle graph.
 */
auto SumOfDegreesOfCycleGraph(const std::size_t number_vertices) {
    return SumOfDegreesOfUndirectedGraph(number_vertices);
}


auto InDegrees(const std::size_t number_vertices,
               const AdjacencyListGraph::UndirectedEdgeArrayType &edges) {
    return AdjacencyListGraph(number_vertices, edges).Visit(ToLambda(InDegrees));
}


auto OutDegrees(const std::size_t number_vertices,
                const AdjacencyListGraph::UndirectedEdgeArrayType &edges) {
    return AdjacencyListGraph(number_vertices, edges).Visit(ToLambda(OutDegrees));
}

}//namespace


SIMPLE_BENCHMARK(SumOfDegreesOfCycleGraph, 4);

SIMPLE_TEST(SumOfDegreesOfCycleGraph, TestSAMPLE1, 8, 4);


const AdjacencyListGraph::UndirectedEdgeArrayType SAMPLE1 = {{0, 1}, {1, 2}, {0, 3}, {1, 3}};
const AdjacencyListGraph::ArrayType EXPECTED1 = {2, 3, 1, 2};


SIMPLE_BENCHMARK(InDegrees, 4, SAMPLE1);

SIMPLE_TEST(InDegrees, TestSAMPLE1, EXPECTED1, 4, SAMPLE1);


SIMPLE_BENCHMARK(OutDegrees, 4, SAMPLE1);

SIMPLE_TEST(OutDegrees, TestSAMPLE1, EXPECTED1, 4, SAMPLE1);
