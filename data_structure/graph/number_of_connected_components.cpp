#include "common_header.h"

#include "graph.h"
#include "depth_first_search.h"


using namespace graph;

namespace {

/** Program to count Number of connected components in an undirected graph
 *
 * @reference   https://www.geeksforgeeks.org/program-to-count-number-of-connected-components-in-an-undirected-graph/
 *
 * @reference   Connected Components in an undirected graph
 *              https://www.geeksforgeeks.org/connected-components-in-an-undirected-graph/
 *
 * Given an undirected graph, print all connected components line by line.
 */
auto CountNumberOfConnectedComponents(const std::size_t number_vertices,
                                      const UndirectedEdgeArrayType &edges) {
    unsigned count = 0;
    GraphTraverse(number_vertices, edges,
    [&count](const auto & graph, const auto source, auto & visited_vertices) {
        ArrayType results;
        DepthFirstSearch_Recursive(graph, source, visited_vertices, results);
        ++count;
        return true;
    });

    return count;
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 22.3-12.
 *
 * Show that we can use a depth-first search of an undirected graph G to identify the
 * connected components of G, and that the depth-first forest contains as many trees as
 * G has connected components. More precisely, show how to modify depth-first search so
 * that it assigns to each vertex v an integer label v.cc between 1 and k, where k is
 * the number of connected components of G, such that u.cc = v.cc if and only if u and
 * v are in the same connected component.
 */

}//namespace


const UndirectedEdgeArrayType SAMPLE1 = {{1, 5}, {0, 2}, {2, 4}};
const UndirectedEdgeArrayType SAMPLE2 = {{1, 0}, {2, 3}, {3, 4}};


THE_BENCHMARK(CountNumberOfConnectedComponents, 6, SAMPLE1);

SIMPLE_TEST(CountNumberOfConnectedComponents, TestSAMPLE1, 3, 6, SAMPLE1);
SIMPLE_TEST(CountNumberOfConnectedComponents, TestSAMPLE2, 2, 5, SAMPLE2);
