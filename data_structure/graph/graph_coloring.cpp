#include "common_header.h"


namespace {

using PathType = std::vector<std::vector<int>>;

/**
 * @reference   Flower Planting With No Adjacent
 *              https://leetcode.com/problems/flower-planting-with-no-adjacent/
 *
 * You have n gardens, labeled from 1 to n, and an array paths where paths[i] = [xi, yi] describes a
 * bidirectional path between garden xi to garden yi. In each garden, you want to plant one of 4 types
 * of flowers.
 * All gardens have at most 3 paths coming into or leaving it.
 * Your task is to choose a flower type for each garden such that, for any two gardens connected by a
 * path, they have different types of flowers.
 * Return any such a choice as an array answer, where answer[i] is the type of flower planted in the
 * (i+1)th garden. The flower types are denoted 1, 2, 3, or 4. It is guaranteed an answer exists.
 *
 * @tags    #graph #graph-coloring #greedy
 */
auto GardenNoAdjacent(const int n, const PathType &paths) {
    std::vector<std::vector<int>> graph(n);
    for (const auto &p : paths) {
        graph[p[0] - 1].push_back(p[1] - 1);
        graph[p[1] - 1].push_back(p[0] - 1);
    }

    std::vector<int> gardens(n);
    for (int i = 0; i < n; ++i) {
        bool flowers[5] = {};
        for (const auto n : graph[i]) {
            flowers[gardens[n]] = true;
        }

        for (int f = 1; f < 5; ++f) {
            if (not flowers[f]) {
                gardens[i] = f;
                break;
            }
        }
    }
    return gardens;
}

} //namespace


const PathType SAMPLE1 = {{1, 2}, {2, 3}, {3, 1}};
const std::vector EXPECTED1 = {1, 2, 3};

const PathType SAMPLE2 = {{1, 2}, {3, 4}};
const std::vector EXPECTED2 = {1, 2, 1, 2};

const PathType SAMPLE3 = {{1, 2}, {2, 3}, {3, 4}, {4, 1}, {1, 3}, {2, 4}};
const std::vector EXPECTED3 = {1, 2, 3, 4};


THE_BENCHMARK(GardenNoAdjacent, 3, SAMPLE1);

SIMPLE_TEST(GardenNoAdjacent, TestSAMPLE1, EXPECTED1, 3, SAMPLE1);
SIMPLE_TEST(GardenNoAdjacent, TestSAMPLE2, EXPECTED2, 4, SAMPLE2);
SIMPLE_TEST(GardenNoAdjacent, TestSAMPLE3, EXPECTED3, 4, SAMPLE3);
