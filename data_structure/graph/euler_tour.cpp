#include "common_header.h"

#include "graph.h"
#include "degree_of_graph.h"
#include "depth_first_search.h"


using namespace graph;

namespace {

enum class EulerianType {
    non,
    path,
    circuit
};


auto FirstNonZeroDegreeVertex(const AdjacencyListGraph::RepresentationType &graph) {
    auto non_zero_degree_vertex = graph.size();
    for (std::size_t i = 0; i < graph.size(); ++i) {
        if (not graph[i].empty()) {
            non_zero_degree_vertex = i;
            break;
        }
    }

    return non_zero_degree_vertex;
}

auto haveAllNonZeroDegreeVerticesBeenVisited(
    const AdjacencyListGraph::RepresentationType &graph,
    const std::vector<bool> &visited_vertices) {
    for (std::size_t i = 0; i < graph.size(); ++i) {
        if (not visited_vertices[i] and not graph[i].empty()) {
            return false;
        }
    }

    return true;
}

/** Eulerian path and circuit for undirected graph
 *
 * @reference   https://www.geeksforgeeks.org/eulerian-path-and-circuit/
 *
 * Eulerian Path is a path in graph that visits every edge exactly once.
 * Eulerian Circuit is an Eulerian Path which starts and ends on the same vertex.
 */
auto areAllNoneZeroDegreeVerticesConnected(
    const AdjacencyListGraph::RepresentationType &graph) {
    const auto non_zero_degree_vertex = FirstNonZeroDegreeVertex(graph);
    if (non_zero_degree_vertex == graph.size()) {
        return true;
    }

    std::vector<bool> visited_vertices(graph.size(), false);
    ArrayType to_be_ignored;
    DepthFirstSearch_Recursive(graph, non_zero_degree_vertex,
                               visited_vertices, to_be_ignored);

    return haveAllNonZeroDegreeVerticesBeenVisited(graph, visited_vertices);
}

auto isEulerian(const std::size_t number_vertices,
                const UndirectedEdgeArrayType &edges) {
    AdjacencyListGraph graph{number_vertices, edges};

    if (not graph.Visit(areAllNoneZeroDegreeVerticesConnected)) {
        return EulerianType::non;
    }

    const auto degrees = graph.Visit(OutDegrees);

    const auto number_odd_degree_vertices = std::count_if(degrees.cbegin(), degrees.cend(),
    [](const auto degree) {
        return degree % 2;
    });

    if (number_odd_degree_vertices > 2) {
        return EulerianType::non;
    }

    return number_odd_degree_vertices ? EulerianType::path : EulerianType::circuit;
}


/** Euler Circuit in a Directed Graph
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Problems 22-3.
 * @reference   Euler Circuit in a Directed Graph
 *              https://www.geeksforgeeks.org/euler-circuit-directed-graph/
 */
auto areAllNonZeroDegreeVerticesStronglyConnected(
    const AdjacencyListGraph::RepresentationType &graph) {
    const auto non_zero_degree_vertex = FirstNonZeroDegreeVertex(graph);
    if (non_zero_degree_vertex == graph.size()) {
        return true;
    }

    ArrayType to_be_ignored;
    {
        std::vector<bool> visited_vertices(graph.size(), false);
        DepthFirstSearch_Recursive(graph, non_zero_degree_vertex,
                                   visited_vertices, to_be_ignored);

        if (not haveAllNonZeroDegreeVerticesBeenVisited(graph, visited_vertices)) {
            return false;
        }
    }

    const auto transpose = GraphTranspose(graph);

    std::vector<bool> visited_vertices(graph.size(), false);
    transpose.Visit(
    [non_zero_degree_vertex, &visited_vertices, &to_be_ignored](const auto & graph) {
        DepthFirstSearch_Recursive(graph, non_zero_degree_vertex,
                                   visited_vertices, to_be_ignored);
    });

    return haveAllNonZeroDegreeVerticesBeenVisited(graph, visited_vertices);
}

auto isEulerianCircuit(const std::size_t number_vertices,
                       const DirectedEdgeArrayType &edges) {
    AdjacencyListGraph graph{number_vertices, edges};

    if (not graph.Visit(areAllNonZeroDegreeVerticesStronglyConnected)) {
        return false;
    }

    const auto in_degrees = graph.Visit(InDegrees);
    const auto out_degrees = graph.Visit(OutDegrees);
    for (std::size_t i = 0; i < number_vertices; ++i) {
        if (out_degrees[i] != in_degrees[i]) {
            return false;
        }
    }

    return true;
}


/**
 * @reference   Find if an array of strings can be chained to form a circle | Set 1
 *              https://www.geeksforgeeks.org/given-array-strings-find-strings-can-chained-form-circle/
 * @reference   Find if an array of strings can be chained to form a circle | Set 2
 *              https://www.geeksforgeeks.org/find-array-strings-can-chained-form-circle-set-2/
 *
 * Given an array of strings, find if the given strings can be chained to form a circle.
 * A string X can be put before another string Y in circle if the last character of X is
 * same as first character of Y.
 */
auto CanStringsFormACircle(const std::vector<std::string_view> &words) {
    DirectedEdgeArrayType edges;
    for (const auto one_word : words) {
        edges.emplace_back(one_word.front() - 'a', one_word.back() - 'a');
    }

    return isEulerianCircuit(26, edges);
}

}//namespace


const UndirectedEdgeArrayType SAMPLE1 = {{1, 0}, {0, 2}, {2, 1}, {0, 3}, {3, 4}};
const UndirectedEdgeArrayType SAMPLE2 = {{1, 0}, {0, 2}, {2, 1}, {0, 3}, {3, 4}, {4, 0}};
const UndirectedEdgeArrayType SAMPLE3 = {{1, 0}, {0, 2}, {2, 1}, {0, 3}, {3, 4}, {1, 3}};
const UndirectedEdgeArrayType SAMPLE4 = {{0, 1}, {1, 2}, {2, 0}};
const UndirectedEdgeArrayType SAMPLE5 = {};


THE_BENCHMARK(isEulerian, 5, SAMPLE1);

SIMPLE_TEST(isEulerian, TestSAMPLE1, EulerianType::path, 5, SAMPLE1);
SIMPLE_TEST(isEulerian, TestSAMPLE2, EulerianType::circuit, 5, SAMPLE2);
SIMPLE_TEST(isEulerian, TestSAMPLE3, EulerianType::non, 5, SAMPLE3);
SIMPLE_TEST(isEulerian, TestSAMPLE4, EulerianType::circuit, 3, SAMPLE4);
SIMPLE_TEST(isEulerian, TestSAMPLE5, EulerianType::circuit, 3, SAMPLE5);


const DirectedEdgeArrayType SAMPLE6 = {{1, 0}, {0, 2}, {2, 1}, {0, 3}, {3, 4}};
const DirectedEdgeArrayType SAMPLE7 = {{1, 0}, {0, 2}, {2, 1}, {0, 3}, {3, 4}, {4, 0}};
const DirectedEdgeArrayType SAMPLE8 = {};


THE_BENCHMARK(isEulerianCircuit, 5, SAMPLE7);

SIMPLE_TEST(isEulerianCircuit, TestSAMPLE6, false, 5, SAMPLE6);
SIMPLE_TEST(isEulerianCircuit, TestSAMPLE7, true, 5, SAMPLE7);
SIMPLE_TEST(isEulerianCircuit, TestSAMPLE8, true, 5, SAMPLE8);


const std::vector<std::string_view> SAMPLE_STRINGS1 = {"geek", "king"};
const std::vector<std::string_view> SAMPLE_STRINGS2 = {"for", "geek", "rig", "kaf"};
const std::vector<std::string_view> SAMPLE_STRINGS3 = {"aab", "bac", "aaa", "cda"};
const std::vector<std::string_view> SAMPLE_STRINGS4 = {"aaa", "bbb", "baa", "aab"};
const std::vector<std::string_view> SAMPLE_STRINGS5 = {"aaa"};
const std::vector<std::string_view> SAMPLE_STRINGS6 = {"aaa", "bbb"};
const std::vector<std::string_view> SAMPLE_STRINGS7 = {"abc", "efg", "cde", "ghi", "ija"};
const std::vector<std::string_view> SAMPLE_STRINGS8 = {"ijk", "kji", "abc", "cba"};


THE_BENCHMARK(CanStringsFormACircle, SAMPLE_STRINGS1);

SIMPLE_TEST(CanStringsFormACircle, TestSAMPLE1, true, SAMPLE_STRINGS1);
SIMPLE_TEST(CanStringsFormACircle, TestSAMPLE2, true, SAMPLE_STRINGS2);
SIMPLE_TEST(CanStringsFormACircle, TestSAMPLE3, true, SAMPLE_STRINGS3);
SIMPLE_TEST(CanStringsFormACircle, TestSAMPLE4, true, SAMPLE_STRINGS4);
SIMPLE_TEST(CanStringsFormACircle, TestSAMPLE5, true, SAMPLE_STRINGS5);
SIMPLE_TEST(CanStringsFormACircle, TestSAMPLE6, false, SAMPLE_STRINGS6);
SIMPLE_TEST(CanStringsFormACircle, TestSAMPLE7, true, SAMPLE_STRINGS7);
SIMPLE_TEST(CanStringsFormACircle, TestSAMPLE8, false, SAMPLE_STRINGS8);
