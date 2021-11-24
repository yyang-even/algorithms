#include "common_header.h"

#include "data_structure/disjoint_set.h"


namespace {

using ArrayType = std::vector<int>;

/** Largest Component Size by Common Factor
 *
 * @reference   https://leetcode.com/problems/largest-component-size-by-common-factor/
 *
 * You are given an integer array of unique positive integers nums. Consider the following
 * graph:
 *  There are nums.length nodes, labeled nums[0] to nums[nums.length - 1],
 *  There is an undirected edge between nums[i] and nums[j] if nums[i] and nums[j] share
 *  a common factor greater than 1.
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

}//namespace


const ArrayType SAMPLE1 = {4, 6, 15, 35};
const ArrayType SAMPLE2 = {20, 50, 9, 63};
const ArrayType SAMPLE3 = {2, 3, 6, 7, 4, 12, 21, 39};


THE_BENCHMARK(LargestComponentSizeByCommonFactor, SAMPLE1);

SIMPLE_TEST(LargestComponentSizeByCommonFactor, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(LargestComponentSizeByCommonFactor, TestSAMPLE2, 2, SAMPLE2);
SIMPLE_TEST(LargestComponentSizeByCommonFactor, TestSAMPLE3, 8, SAMPLE3);
