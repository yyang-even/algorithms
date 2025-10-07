#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Avoid Flood in The City
 *              https://leetcode.com/problems/avoid-flood-in-the-city/
 *
 * Your country has an infinite number of lakes. Initially, all the lakes are empty, but when it rains
 * over the nth lake, the nth lake becomes full of water. If it rains over a lake that is full of water,
 * there will be a flood. Your goal is to avoid floods in any lake.
 * Given an integer array rains where:
 *  rains[i] > 0 means there will be rains over the rains[i] lake.
 *  rains[i] == 0 means there are no rains this day and you can choose one lake this day and dry it.
 * Return an array ans where:
 *  ans.length == rains.length
 *  ans[i] == -1 if rains[i] > 0.
 *  ans[i] is the lake you choose to dry in the ith day if rains[i] == 0.
 * If there are multiple valid answers return any of them. If it is impossible to avoid flood return an
 * empty array.
 * Notice that if you chose to dry a full lake, it becomes empty, but if you chose to dry an empty lake,
 * nothing changes.
 *
 * @tags    #greedy #hash-table #ordered-set #binary-search
 */
ArrayType AvoidFloodInCity(const ArrayType &rains) {
    std::set<int> dry_days;
    std::unordered_map<int, int> full_lake_map;

    ArrayType result(rains.size(), 1);
    for (std::size_t i = 0; i < rains.size(); ++i) {
        const auto lake = rains[i];
        if (lake == 0) {
            dry_days.insert(i);
        } else {
            result[i] = -1;

            const auto [lake_iter, inserted] = full_lake_map.emplace(lake, i);
            if (not inserted) {
                const auto dry_iter = dry_days.lower_bound(lake_iter->second);
                lake_iter->second = i;
                if (dry_iter == dry_days.cend()) {
                    return {};
                }
                result[*dry_iter] = lake;
                dry_days.erase(dry_iter);
            }
        }
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {1, 2, 3, 4};
const ArrayType EXPECTED1 = {-1, -1, -1, -1};

const ArrayType SAMPLE2 = {1, 2, 0, 0, 2, 1};
const ArrayType EXPECTED2 = {-1, -1, 2, 1, -1, -1};

const ArrayType SAMPLE3 = {1, 2, 0, 1, 2};
const ArrayType EXPECTED3 = {};

const ArrayType SAMPLE4 = {69, 0, 0, 0, 69};
const ArrayType EXPECTED4 = {-1, 69, 1, 1, -1};

const ArrayType SAMPLE5 = {1, 2, 0, 2, 3, 0, 1};
const ArrayType EXPECTED5 = {-1, -1, 2, -1, -1, 1, -1};


THE_BENCHMARK(AvoidFloodInCity, SAMPLE1);

SIMPLE_TEST(AvoidFloodInCity, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(AvoidFloodInCity, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(AvoidFloodInCity, TestSAMPLE3, EXPECTED3, SAMPLE3);
SIMPLE_TEST(AvoidFloodInCity, TestSAMPLE4, EXPECTED4, SAMPLE4);
SIMPLE_TEST(AvoidFloodInCity, TestSAMPLE5, EXPECTED5, SAMPLE5);
