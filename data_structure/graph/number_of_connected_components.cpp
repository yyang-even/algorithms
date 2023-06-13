#include "common_header.h"

#include "depth_first_search.h"
#include "graph.h"

#include "data_structure/disjoint_set.h"


using namespace graph;
using IndexPair = std::pair<int, int>;
using PairArray = std::vector<IndexPair>;

namespace {

/** Program to count Number of connected components in an undirected graph
 *
 * @reference   https://www.geeksforgeeks.org/program-to-count-number-of-connected-components-in-an-undirected-graph/
 *
 * @reference   Connected Components in an undirected graph
 *              https://www.geeksforgeeks.org/connected-components-in-an-undirected-graph/
 *
 * Given an undirected graph, print all connected components line by line.
 *
 * @reference   Find Weakly Connected Components in a Directed Graph
 *              https://www.geeksforgeeks.org/find-weakly-connected-components-in-a-directed-graph/
 *
 * A directed graph G = (V, E) is weakly connected if the underlying undirected graph is connected.
 *
 * @reference   Number of Provinces
 *              https://leetcode.com/problems/number-of-provinces/
 *
 * There are n cities. Some of them are connected, while some are not. If city a is connected directly
 * with city b, and city b is connected directly with city c, then city a is connected indirectly with
 * city c.
 * A province is a group of directly or indirectly connected cities and no other cities outside of the
 * group.
 * You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city and the jth
 * city are directly connected, and isConnected[i][j] = 0 otherwise.
 * Return the total number of provinces.
 */
auto CountNumberOfConnectedComponents(const std::size_t number_vertices,
                                      const UndirectedEdgeArrayType &edges) {
    unsigned count = 0;
    GraphTraverse(number_vertices,
                  edges,
                  [&count](const auto &graph, const auto source, auto &visited_vertices) {
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
 * Show that we can use a depth-first search of an undirected graph G to identify the connected
 * components of G, and that the depth-first forest contains as many trees as G has connected
 * components. More precisely, show how to modify depth-first search so that it assigns to each vertex v
 * an integer label v.cc between 1 and k, where k is the number of connected components of G, such that
 * u.cc = v.cc if and only if u and v are in the same connected component.
 */


/**
 * @reference   Keys and Rooms
 *              https://leetcode.com/problems/keys-and-rooms/
 *
 * There are n rooms labeled from 0 to n - 1 and all the rooms are locked except for room 0. Your goal
 * is to visit all the rooms. However, you cannot enter a locked room without having its key.
 * When you visit a room, you may find a set of distinct keys in it. Each key has a number on it,
 * denoting which room it unlocks, and you can take all of them with you to unlock the other rooms.
 * Given an array rooms where rooms[i] is the set of keys that you can obtain if you visited room i,
 * return true if you can visit all the rooms, or false otherwise.
 */


/** Largest Component Size by Common Factor
 *
 * @reference   https://leetcode.com/problems/largest-component-size-by-common-factor/
 *
 * You are given an integer array of unique positive integers nums. Consider the following graph:
 *  There are nums.length nodes, labeled nums[0] to nums[nums.length - 1],
 *  There is an undirected edge between nums[i] and nums[j] if nums[i] and nums[j] share a common factor
 *  greater than 1.
 * Return the size of the largest connected component in the graph.
 * 1 <= nums[i] <= 10^5
 */
auto LargestComponentSizeByCommonFactor(const ArrayType &nums) {
    DisjointSet_Array disjoint_set(100001);

    for (const auto v : nums) {
        for (int i = 2; i <= std::sqrt(v); ++i) {
            if (v % i == 0) {
                disjoint_set.Union(v, i);
                disjoint_set.Union(v, v / i);
            }
        }
    }

    std::unordered_map<int, int> component_size_map;
    int result = 0;
    for (const auto v : nums) {
        const auto component_id = disjoint_set.Find(v);
        result = std::max(result, ++component_size_map[component_id]);
    }

    return result;
}


/**
 * @reference   Smallest String With Swaps
 *              https://leetcode.com/problems/smallest-string-with-swaps/
 *
 * You are given a string s, and an array of pairs of indices in the string pairs where pairs[i] =
 * [a, b] indicates 2 indices(0-indexed) of the string.
 * You can swap the characters at any pair of indices in the given pairs any number of times.
 * Return the lexicographically smallest string that s can be changed to after using the swaps.
 */
auto SmallestStrWithSwaps(const std::string_view s, const PairArray &pairs) {
    DisjointSet_Array disjoint_set(s.size());
    for (const auto &[u, v] : pairs) {
        disjoint_set.Union(u, v);
    }

    std::unordered_map<int, std::vector<int>> components;
    for (std::size_t i = 0; i < s.size(); ++i) {
        components[disjoint_set.Find(i)].push_back(i);
    }

    std::string result(s.size(), 0);
    for (const auto &[_, indices] : components) {
        std::string chars;
        for (const auto i : indices) {
            chars.push_back(s[i]);
        }
        std::sort(chars.begin(), chars.end());

        for (std::size_t i = 0; i < indices.size(); ++i) {
            result[indices[i]] = chars[i];
        }
    }

    return result;
}


/**
 * @reference   Largest Number After Digit Swaps by Parity
 *              https://leetcode.com/problems/largest-number-after-digit-swaps-by-parity/
 *
 * You are given a positive integer num. You may swap any two digits of num that have the same parity
 * (i.e. both odd digits or both even digits).
 * Return the largest possible value of num after any number of swaps.
 */
constexpr auto LargestNumberAfterSwaps(const unsigned num) {
    int counts[10] = {};
    for (auto n = num; n > 0; n /= 10) {
        ++counts[n % 10];
    }

    int indices[2] = {0, 1};
    int result = 0;
    for (unsigned n = num, i = 1; n > 0; n /= 10, i *= 10) {
        const int parity = n % 10 % 2;
        while (counts[indices[parity]] == 0) {
            indices[parity] += 2;
        }

        result += i * indices[parity];
        --counts[indices[parity]];
    }

    return result;
}


/**
 * @reference   Evaluate Division
 *              https://leetcode.com/problems/evaluate-division/
 *
 * You are given an array of variable pairs equations and an array of real numbers values, where
 * equations[i] = [Ai, Bi] and values[i] represent the equation Ai / Bi = values[i].  Each Ai or Bi is a
 * string that represents a single variable.
 * You are also given some queries, where queries[j] = [Cj, Dj] represents the jth query where you must
 * find the answer for Cj / Dj = ?.
 * Return the answers to all queries. If a single answer cannot be determined, return -1.0.
 * Note: The input is always valid. You may assume that evaluating the queries will not result in
 * division by zero and that there is no contradiction.
 */
using StrPair = std::pair<std::string_view, std::string_view>;
using StrPairArray = std::vector<StrPair>;
using DoubleArray = std::vector<double>;
using DisjointSet = std::unordered_map<std::string_view, std::pair<std::string_view, double>>;

DisjointSet::mapped_type Find(DisjointSet &disjoint_set, const std::string_view x) {
    if (x != disjoint_set[x].first) {
        auto &[x_p, x_v] = disjoint_set[x];
        const auto [p_p, p_v] = Find(disjoint_set, x_p);
        x_p = p_p;
        x_v *= p_v;
    }

    return disjoint_set[x];
}

void Union(DisjointSet &disjoint_set,
           const std::string_view a,
           const std::string_view b,
           const double v) {
    disjoint_set.emplace(a, std::pair(a, 1.0));
    disjoint_set.emplace(b, std::pair(b, 1.0));
    const auto [a_p, a_v] = Find(disjoint_set, a);
    const auto [b_p, b_v] = Find(disjoint_set, b);
    disjoint_set[a_p] = {b_p, v * b_v / a_v};
}

auto EvaluateDivision(const StrPairArray &equations,
                      const DoubleArray &values,
                      const StrPairArray &queries) {
    DisjointSet disjoint_set;
    for (std::size_t i = 0; i < equations.size(); ++i) {
        const auto [a, b] = equations[i];
        Union(disjoint_set, a, b, values[i]);
    }

    DoubleArray results;
    for (const auto &[a, b] : queries) {
        const auto a_iter = disjoint_set.find(a);
        const auto b_iter = disjoint_set.find(b);
        if (a_iter != disjoint_set.cend() and b_iter != disjoint_set.cend()) {
            const auto [a_p, a_v] = Find(disjoint_set, a);
            const auto [b_p, b_v] = Find(disjoint_set, b);
            results.push_back(a_v / b_v);
        } else {
            results.push_back(-1.0);
        }
    }

    return results;
}


/**
 * @reference   Lexicographically Smallest Equivalent String
 *              https://leetcode.com/problems/lexicographically-smallest-equivalent-string/
 *
 * You are given two strings of the same length s1 and s2 and a string baseStr.
 * We say s1[i] and s2[i] are equivalent characters.
 *  For example, if s1 = "abc" and s2 = "cde", then we have 'a' == 'c', 'b' == 'd', and 'c' == 'e'.
 * Equivalent characters follow the usual rules of any equivalence relation:
 *  Reflexivity: 'a' == 'a'.
 *  Symmetry: 'a' == 'b' implies 'b' == 'a'.
 *  Transitivity: 'a' == 'b' and 'b' == 'c' implies 'a' == 'c'.
 * For example, given the equivalency information from s1 = "abc" and s2 = "cde", "acd" and "aab" are
 * equivalent strings of baseStr = "eed", and "aab" is the lexicographically smallest equivalent string
 * of baseStr.
 * Return the lexicographically smallest equivalent string of baseStr by using the equivalency
 * information from s1 and s2.
 */
auto Find(std::vector<int> &disjoint_set, const int x) {
    if (disjoint_set[x] == -1)
        return x;
    return disjoint_set[x] = Find(disjoint_set, disjoint_set[x]);
}

void Union(std::vector<int> &disjoint_set, int x, int y) {
    x = Find(disjoint_set, x);
    y = Find(disjoint_set, y);

    if (x != y) {
        disjoint_set[std::max(x, y)] = std::min(x, y);
    }
}

auto SmallestEquivalentString(const std::string_view s1,
                              const std::string_view s2,
                              std::string baseStr) {
    std::vector disjoint_set(26, -1);

    for (std::size_t i = 0; i < s1.size(); ++i) {
        Union(disjoint_set, s1[i] - 'a', s2[i] - 'a');
    }

    for (auto &c : baseStr) {
        c = Find(disjoint_set, c - 'a') + 'a';
    }

    return baseStr;
}


/**
 * @reference   Number of Operations to Make Network Connected
 *              https://leetcode.com/problems/number-of-operations-to-make-network-connected/
 *
 * There are n computers numbered from 0 to n - 1 connected by ethernet cables connections forming a
 * network where connections[i] = [ai, bi] represents a connection between computers ai and bi. Any
 * computer can reach any other computer directly or indirectly through the network.
 * You are given an initial computer network connections. You can extract certain cables between two
 * directly connected computers, and place them between any pair of disconnected computers to make them
 * directly connected.
 * Return the minimum number of times you need to do this in order to make all the computers connected.
 * If it is not possible, return -1.
 */
int NumOperationsToMakeNetworkConnected(const std::size_t n,
                                        const UndirectedEdgeArrayType &connections) {
    if (connections.size() + 1 < n) {
        return -1;
    }

    return CountNumberOfConnectedComponents(n, connections) - 1;
}


/**
 * @reference   Count Unreachable Pairs of Nodes in an Undirected Graph
 *              https://leetcode.com/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/
 *
 * You are given an integer n. There is an undirected graph with n nodes, numbered from 0 to n - 1. You
 * are given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected
 * edge connecting nodes ai and bi.
 * Return the number of pairs of different nodes that are unreachable from each other.
 */
void CountUnreachablePairsOfNodes(const AdjacencyListGraph::RepresentationType &graph,
                                  const int i,
                                  std::vector<bool> &visited,
                                  long long &number_nodes) {
    visited[i] = true;
    ++number_nodes;

    for (const auto n : graph[i]) {
        if (not visited[n]) {
            CountUnreachablePairsOfNodes(graph, n, visited, number_nodes);
        }
    }
}

auto CountUnreachablePairsOfNodes(const std::size_t n, const UndirectedEdgeArrayType &edges) {
    AdjacencyListGraph graph {n, edges};

    return graph.Visit([](const auto &graph) {
        std::vector<bool> visited_vertices(graph.size(), false);
        long long result = 0;
        long long total_nodes = 0;
        for (std::size_t i = 0; i < graph.size(); ++i) {
            if (not visited_vertices[i]) {
                long long number_nodes = 0;
                CountUnreachablePairsOfNodes(graph, i, visited_vertices, number_nodes);

                result += total_nodes * number_nodes;
                total_nodes += number_nodes;
            }
        }

        return result;
    });
}


/**
 * @reference   Minimum Score of a Path Between Two Cities
 *              https://leetcode.com/problems/minimum-score-of-a-path-between-two-cities/
 *
 * You are given a positive integer n representing n cities numbered from 1 to n. You are also given a
 * 2D array roads where roads[i] = [ai, bi, distancei] indicates that there is a bidirectional road
 * between cities ai and bi with a distance equal to distancei. The cities graph is not necessarily
 * connected.
 * The score of a path between two cities is defined as the minimum distance of a road in this path.
 * Return the minimum possible score of a path between cities 1 and n.
 * Note:
 *  A path is a sequence of roads between two cities.
 *  It is allowed for a path to contain the same road multiple times, and you can visit cities 1 and n
 *  multiple times along the path.
 *  The test cases are generated such that there is at least one path between 1 and n.
 */
void MinScorePath(const WeightedAdjacencyListGraph::RepresentationType &graph,
                  const std::size_t i,
                  std::vector<bool> &visited,
                  int &result) {
    visited[i] = true;
    for (const auto &neighbor : graph[i]) {
        result = std::min(result, neighbor.weight);
        if (not visited[neighbor.destination]) {
            MinScorePath(graph, neighbor.destination, visited, result);
        }
    }
}

auto MinScorePath(const std::size_t n, const UndirectedEdgeArrayType &roads) {
    return WeightedAdjacencyListGraph {n + 1, roads}.Visit([](const auto &graph) {
        int result = INT_MAX;
        std::vector<bool> visited(graph.size(), false);
        MinScorePath(graph, 1, visited, result);

        return result;
    });
}

} //namespace


const UndirectedEdgeArrayType SAMPLE1 = {{1, 5}, {0, 2}, {2, 4}};
const UndirectedEdgeArrayType SAMPLE2 = {{1, 0}, {2, 3}, {3, 4}};


THE_BENCHMARK(CountNumberOfConnectedComponents, 6, SAMPLE1);

SIMPLE_TEST(CountNumberOfConnectedComponents, TestSAMPLE1, 3, 6, SAMPLE1);
SIMPLE_TEST(CountNumberOfConnectedComponents, TestSAMPLE2, 2, 5, SAMPLE2);


const ArrayType SAMPLE1L = {4, 6, 15, 35};
const ArrayType SAMPLE2L = {20, 50, 9, 63};
const ArrayType SAMPLE3L = {2, 3, 6, 7, 4, 12, 21, 39};


THE_BENCHMARK(LargestComponentSizeByCommonFactor, SAMPLE1L);

SIMPLE_TEST(LargestComponentSizeByCommonFactor, TestSAMPLE1, 4, SAMPLE1L);
SIMPLE_TEST(LargestComponentSizeByCommonFactor, TestSAMPLE2, 2, SAMPLE2L);
SIMPLE_TEST(LargestComponentSizeByCommonFactor, TestSAMPLE3, 8, SAMPLE3L);


const PairArray SAMPLE1P = {{0, 3}, {1, 2}};
const PairArray SAMPLE2P = {{0, 3}, {1, 2}, {0, 2}};
const PairArray SAMPLE3P = {{0, 1}, {1, 2}};


THE_BENCHMARK(SmallestStrWithSwaps, "dcab", SAMPLE1P);

SIMPLE_TEST(SmallestStrWithSwaps, TestSAMPLE1, "bacd", "dcab", SAMPLE1P);
SIMPLE_TEST(SmallestStrWithSwaps, TestSAMPLE2, "abcd", "dcab", SAMPLE2P);
SIMPLE_TEST(SmallestStrWithSwaps, TestSAMPLE3, "abc", "cba", SAMPLE3P);


THE_BENCHMARK(LargestNumberAfterSwaps, 1234);

SIMPLE_TEST(LargestNumberAfterSwaps, TestSAMPLE1, 3412, 1234);
SIMPLE_TEST(LargestNumberAfterSwaps, TestSAMPLE2, 87655, 65875);


const StrPairArray SAMPLE1E = {{"a", "b"}, {"b", "c"}};
const DoubleArray SAMPLE1V = {2.0, 3.0};
const StrPairArray SAMPLE1Q = {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};
const DoubleArray EXPECTED1 = {6.00000, 0.50000, -1.00000, 1.00000, -1.00000};

const StrPairArray SAMPLE2E = {{"a", "b"}, {"b", "c"}, {"bc", "cd"}};
const DoubleArray SAMPLE2V = {1.5, 2.5, 5.0};
const StrPairArray SAMPLE2Q = {{"a", "c"}, {"c", "b"}, {"bc", "cd"}, {"cd", "bc"}};
const DoubleArray EXPECTED2 = {3.75000, 0.40000, 5.00000, 0.20000};

const StrPairArray SAMPLE3E = {{"a", "b"}};
const DoubleArray SAMPLE3V = {0.5};
const StrPairArray SAMPLE3Q = {{"a", "b"}, {"b", "a"}, {"a", "c"}, {"x", "y"}};
const DoubleArray EXPECTED3 = {0.50000, 2.00000, -1.00000, -1.00000};


THE_BENCHMARK(EvaluateDivision, SAMPLE1E, SAMPLE1V, SAMPLE1Q);

SIMPLE_TEST(EvaluateDivision, TestSAMPLE1, EXPECTED1, SAMPLE1E, SAMPLE1V, SAMPLE1Q);
SIMPLE_TEST(EvaluateDivision, TestSAMPLE2, EXPECTED2, SAMPLE2E, SAMPLE2V, SAMPLE2Q);
SIMPLE_TEST(EvaluateDivision, TestSAMPLE3, EXPECTED3, SAMPLE3E, SAMPLE3V, SAMPLE3Q);


THE_BENCHMARK(SmallestEquivalentString, "parker", "morris", "parser");

SIMPLE_TEST(SmallestEquivalentString, TestSAMPLE1, "makkek", "parker", "morris", "parser");
SIMPLE_TEST(SmallestEquivalentString, TestSAMPLE2, "hdld", "hello", "world", "hold");
SIMPLE_TEST(
    SmallestEquivalentString, TestSAMPLE3, "aauaaaaada", "leetcode", "programs", "sourcecode");


const UndirectedEdgeArrayType SAMPLE1C = {{0, 1}, {0, 2}, {1, 2}};
const UndirectedEdgeArrayType SAMPLE2C = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}};
const UndirectedEdgeArrayType SAMPLE3C = {{0, 1}, {0, 2}, {0, 3}, {1, 2}};


THE_BENCHMARK(NumOperationsToMakeNetworkConnected, 4, SAMPLE1C);

SIMPLE_TEST(NumOperationsToMakeNetworkConnected, TestSAMPLE1, 1, 4, SAMPLE1C);
SIMPLE_TEST(NumOperationsToMakeNetworkConnected, TestSAMPLE2, 2, 6, SAMPLE2C);
SIMPLE_TEST(NumOperationsToMakeNetworkConnected, TestSAMPLE3, -1, 6, SAMPLE3C);


const UndirectedEdgeArrayType SAMPLE1U = {{0, 1}, {0, 2}, {1, 2}};
const UndirectedEdgeArrayType SAMPLE2U = {{0, 2}, {0, 5}, {2, 4}, {1, 6}, {5, 4}};


THE_BENCHMARK(CountUnreachablePairsOfNodes, 3, SAMPLE1U);

SIMPLE_TEST(CountUnreachablePairsOfNodes, TestSAMPLE1, 0, 3, SAMPLE1U);
SIMPLE_TEST(CountUnreachablePairsOfNodes, TestSAMPLE2, 14, 7, SAMPLE2U);


const UndirectedEdgeArrayType SAMPLE1S = {{1, 2, 9}, {2, 3, 6}, {2, 4, 5}, {1, 4, 7}};
const UndirectedEdgeArrayType SAMPLE2S = {{1, 2, 2}, {1, 3, 4}, {3, 4, 7}};
const UndirectedEdgeArrayType SAMPLE3S = {{4, 5, 7468},
                                          {6, 2, 7173},
                                          {6, 3, 8365},
                                          {2, 3, 7674},
                                          {5, 6, 7852},
                                          {1, 2, 8547},
                                          {2, 4, 1885},
                                          {2, 5, 5192},
                                          {1, 3, 4065},
                                          {1, 4, 7357}};


THE_BENCHMARK(MinScorePath, 4, SAMPLE1S);

SIMPLE_TEST(MinScorePath, TestSAMPLE1, 5, 4, SAMPLE1S);
SIMPLE_TEST(MinScorePath, TestSAMPLE2, 2, 4, SAMPLE2S);
SIMPLE_TEST(MinScorePath, TestSAMPLE3, 1885, 6, SAMPLE3S);
