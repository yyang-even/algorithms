#include "common_header.h"

#include "graph.h"

#include "data_structure/disjoint_set.h"


using namespace graph;
using PointType = std::pair<int, int>;
using PointsArray = std::vector<PointType>;


namespace {

/** Minimum Spanning Tree
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 23.
 * @reference   Minimum Spanning Tree
 *              https://www.hackerearth.com/practice/algorithms/graphs/minimum-spanning-tree/tutorial/
 * @reference   Kruskal’s Minimum Spanning Tree Algorithm | Greedy Algo-2
 *              https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/
 * @reference   Prim’s Minimum Spanning Tree (MST) | Greedy Algo-5
 *              https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/
 * @reference   Prim’s MST for Adjacency List Representation | Greedy Algo-6
 *              https://www.geeksforgeeks.org/prims-mst-for-adjacency-list-representation-greedy-algo-6/
 */
auto MinimumSpanningTree_Kruskal(const std::size_t number_vertices,
                                 UndirectedEdgeArrayType edges) {
    std::sort(edges.begin(), edges.end(), [](const auto &one, const auto &other) {
        return one.weight < other.weight;
    });

    DisjointSet_Array disjoint_set {number_vertices};
    std::size_t edge_selected = 0;
    int result = 0;
    for (const auto &an_edge : edges) {
        if (edge_selected >= number_vertices - 1) {
            break;
        }

        const auto u_set = disjoint_set.Find(an_edge.u);
        const auto v_set = disjoint_set.Find(an_edge.v);

        if (u_set != v_set) {
            result += an_edge.weight;
            ++edge_selected;
            disjoint_set.Link(u_set, v_set);
        }
    }

    return result;
}


using WeightIndexPair = std::pair<int, std::size_t>;

auto MinimumSpanningTree_Prim(const WeightedAdjacencyListGraph::RepresentationType &graph) {
    std::priority_queue<WeightIndexPair,
                        std::vector<WeightIndexPair>,
                        std::greater<WeightIndexPair>>
        q;
    q.emplace(0, 0);
    std::vector selected(graph.size(), false);

    int result = 0;
    while (not q.empty()) {
        const auto [weight, node] = q.top();
        q.pop();

        if (selected[node]) {
            continue;
        }

        result += weight;
        selected[node] = true;

        for (const auto adjacent_node : graph[node]) {
            if (not selected[adjacent_node.destination]) {
                q.emplace(adjacent_node.weight, adjacent_node.destination);
            }
        }
    }

    return result;
}

auto MinimumSpanningTree_Prim(const std::size_t number_vertices,
                              const UndirectedEdgeArrayType &edges) {
    return WeightedAdjacencyListGraph(number_vertices, edges)
        .Visit(ToLambda(MinimumSpanningTree_Prim));
}


/**
 * @reference   Min Cost to Connect All Points
 *              https://leetcode.com/problems/min-cost-to-connect-all-points/
 *
 * You are given an array points representing integer coordinates of some points on a 2D-plane,
 * where points[i] = [xi, yi].
 * The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between them:
 * |xi - xj| + |yi - yj|, where |val| denotes the absolute value of val.
 * Return the minimum cost to make all points connected. All points are connected if there is
 * exactly one simple path between any two points.
 */
auto MinCostToConnectAllPoints(const PointsArray &points) {
    UndirectedEdgeArrayType edges;
    for (std::size_t i = 0; i < points.size(); ++i) {
        for (auto j = i + 1; j < points.size(); ++j) {
            const auto weight = std::abs(points[i].first - points[j].first) +
                                std::abs(points[i].second - points[j].second);
            edges.emplace_back(i, j, weight);
        }
    }

    return MinimumSpanningTree_Kruskal(points.size(), edges);
}


auto MinCostToConnectAllPoints_Prim(const PointsArray &points) {
    std::vector min_distances(points.size(), INT_MAX);
    min_distances[0] = 0;

    std::size_t point_selected = 0;
    std::vector selected(points.size(), false);
    int result = 0;
    while (point_selected++ < points.size()) {
        int min_cost = INT_MAX;
        int node = -1;
        for (std::size_t i = 0; i < points.size(); ++i) {
            if (not selected[i] and min_cost > min_distances[i]) {
                min_cost = min_distances[i];
                node = i;
            }
        }

        result += min_cost;
        selected[node] = true;

        for (std::size_t i = 0; i < points.size(); ++i) {
            if (not selected[i]) {
                const auto weight = std::abs(points[node].first - points[i].first) +
                                    std::abs(points[node].second - points[i].second);

                if (min_distances[i] > weight) {
                    min_distances[i] = weight;
                }
            }
        }
    }

    return result;
}

} //namespace


const UndirectedEdgeArrayType SAMPLE1 = {{0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4}};


THE_BENCHMARK(MinimumSpanningTree_Kruskal, 4, SAMPLE1);

SIMPLE_TEST(MinimumSpanningTree_Kruskal, TestSAMPLE1, 19, 4, SAMPLE1);


THE_BENCHMARK(MinimumSpanningTree_Prim, 4, SAMPLE1);

SIMPLE_TEST(MinimumSpanningTree_Prim, TestSAMPLE1, 19, 4, SAMPLE1);


const PointsArray SAMPLE1P = {{0, 0}, {2, 2}, {3, 10}, {5, 2}, {7, 0}};
const PointsArray SAMPLE2P = {{3, 12}, {-2, 5}, {-4, 1}};


THE_BENCHMARK(MinCostToConnectAllPoints, SAMPLE1P);

SIMPLE_TEST(MinCostToConnectAllPoints, TestSAMPLE1, 20, SAMPLE1P);
SIMPLE_TEST(MinCostToConnectAllPoints, TestSAMPLE2, 18, SAMPLE2P);


THE_BENCHMARK(MinCostToConnectAllPoints_Prim, SAMPLE1P);

SIMPLE_TEST(MinCostToConnectAllPoints_Prim, TestSAMPLE1, 20, SAMPLE1P);
SIMPLE_TEST(MinCostToConnectAllPoints_Prim, TestSAMPLE2, 18, SAMPLE2P);
