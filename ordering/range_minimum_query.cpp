#include "common_header.h"

#include "data_structure/heap/segment_tree.h"


namespace {

using ArrayType = std::vector<int>;
using Range = std::pair<int, int>;
using RangeArray = std::vector<Range>;
using Operation = std::tuple<bool, int, int>;
using OperationArray = std::vector<Operation>;

/** Range Minimum Query
 *
 * @reference   https://www.geeksforgeeks.org/range-minimum-query-for-static-array/
 *
 * We have an array arr[0 . . . n-1]. We should be able to efficiently find the minimum
 * value from index L (query start) to R (query end) where 0 <= L <= R <= n-1. Consider
 * a situation when there are many range queries.
 *
 * @reference   RANGE MINIMUM QUERY AND LOWEST COMMON ANCESTOR
 *              https://www.topcoder.com/thrive/articles/Range%20Minimum%20Query%20and%20Lowest%20Common%20Ancestor
 */
auto buildRMQSparseTable(const ArrayType &elements) {
    std::vector sparse_table(elements.size(), std::vector(100, 0));

    for (std::size_t i = 0; i < elements.size(); ++i) {
        sparse_table[i][0] = i;
    }

    for (int j = 1; (1u << j) <= elements.size(); ++j) {
        for (std::size_t i = 0; (i + (1 << j) - 1) < elements.size(); ++i) {
            if (elements[sparse_table[i][j - 1]] <
                elements[sparse_table[i + (1 << (j - 1))][j - 1]]) {
                sparse_table[i][j] = sparse_table[i][j - 1];
            } else {
                sparse_table[i][j] = sparse_table[i + (1 << (j - 1))][j - 1];
            }
        }
    }

    return sparse_table;
}

auto
RangeMinimumQuery_SparseTable(const ArrayType &elements, const RangeArray &ranges) {
    const auto sparse_table = buildRMQSparseTable(elements);

    ArrayType results;
    for (const auto [left, right] : ranges) {
        int j = std::log2(right - left + 1);

        if (elements[sparse_table[left][j]] <=
            elements[sparse_table[right - (1 << j) + 1][j]]) {
            results.push_back(elements[sparse_table[left][j]]);
        } else {
            results.push_back(elements[sparse_table[right - (1 << j) + 1][j]]);
        }
    }

    return results;
}


/**
 * @reference   Segment Tree | Set 2 (Range Minimum Query)
 *              https://www.geeksforgeeks.org/segment-tree-set-1-range-minimum-query/
 */
auto buildST_Recursive(const ArrayType &nums, const int left, const int right,
                       ArrayType &segment_tree, const int node) {
    if (left == right) {
        return segment_tree[node] = nums[left];
    }

    const auto mid = (left + right) / 2;
    return segment_tree[node] =
               std::min(buildST_Recursive(nums, left, mid, segment_tree, LeftChild(node)),
                        buildST_Recursive(nums, mid + 1, right, segment_tree, RightChild(node)));
}

inline auto buildST_Recursive(const ArrayType &nums) {
    ArrayType segment_tree(nums.size() * 2, 0);
    buildST_Recursive(nums, 0, nums.size() - 1, segment_tree, ST_root);
    return segment_tree;
}

auto RangeMinimumQuery_ST_Recursive(const ArrayType &segment_tree, const int node,
                                    const int left, const int right,
                                    const int query_left, const int query_right) {
    if (query_left <= left and query_right >= right) {
        return segment_tree[node];
    }

    if (right < query_left or left > query_right) {
        return INT_MAX;
    }

    const auto mid = (left + right) / 2;
    return std::min(
               RangeMinimumQuery_ST_Recursive(segment_tree, LeftChild(node), left, mid,
                                              query_left, query_right),
               RangeMinimumQuery_ST_Recursive(segment_tree, RightChild(node), mid + 1, right,
                                              query_left, query_right));
}

auto
RangeMinimumQuery_ST_Recursive(const ArrayType &nums, const RangeArray &ranges) {
    const auto segment_tree = buildST_Recursive(nums);

    ArrayType results;
    for (const auto [left, right] : ranges) {
        results.push_back(RangeMinimumQuery_ST_Recursive(segment_tree, ST_root,
                                                         0, nums.size() - 1, left, right));
    }

    return results;
}


/**
 * @reference   Iterative Segment Tree (Range Minimum Query)
 *              https://www.geeksforgeeks.org/iterative-segment-tree-range-minimum-query/
 */
auto buildST_Iterative(const ArrayType &nums) {
    ArrayType segment_tree(nums.size() * 2, 0);

    for (std::size_t i = 0; i < nums.size(); ++i) {
        segment_tree[nums.size() + i] = nums[i];
    }

    for (int i = nums.size() - 1; i > 0; --i) {
        segment_tree[i] = std::min(segment_tree[LeftChild(i)],
                                   segment_tree[RightChild(i)]);
    }

    return segment_tree;
}

auto RMQ_Query(const ArrayType &segment_tree, int left, int right) {
    const auto N = segment_tree.size() / 2;
    left += N;
    right += N;

    int result = INT_MAX;
    while (left <= right) {
        if (not isLeftChild(left)) {
            result = std::min(result, segment_tree[left++]);
        }

        if (isLeftChild(right)) {
            result = std::min(result, segment_tree[right--]);
        }

        left = Parent(left);
        right = Parent(right);
    }

    return result;
}

void RMQ_Update(ArrayType &segment_tree, std::size_t index, const int value) {
    const auto N = segment_tree.size() / 2;
    index += N;

    segment_tree[index] = value;

    while (index > ST_root) {
        index >>= 1;
        segment_tree[index] = std::min(segment_tree[LeftChild(index)],
                                       segment_tree[RightChild(index)]);
    }
}

auto
RangeMinimumQuery_ST_Iterative(const ArrayType &nums,
                               const OperationArray &operations) {
    auto segment_tree = buildST_Iterative(nums);

    ArrayType results;
    for (const auto [is_query, x, y] : operations) {
        if (is_query) {
            results.push_back(RMQ_Query(segment_tree, x, y));
        } else {
            RMQ_Update(segment_tree, x, y);
        }
    }

    return results;
}

}//namespace


const ArrayType SAMPLE1 = {7, 2, 3, 0, 5, 10, 3, 12, 18};
const RangeArray SAMPLE1Q = {{0, 4}, {4, 7}, {7, 8}};
const ArrayType EXPECTED1 = {0, 3, 12};


THE_BENCHMARK(RangeMinimumQuery_SparseTable, SAMPLE1, SAMPLE1Q);

SIMPLE_TEST(RangeMinimumQuery_SparseTable, TestSAMPLE1, EXPECTED1, SAMPLE1, SAMPLE1Q);


THE_BENCHMARK(RangeMinimumQuery_ST_Recursive, SAMPLE1, SAMPLE1Q);

SIMPLE_TEST(RangeMinimumQuery_ST_Recursive, TestSAMPLE1, EXPECTED1, SAMPLE1, SAMPLE1Q);


const ArrayType SAMPLE2 = {2, 6, 10, 4, 7, 28, 9, 11, 6, 33};
const OperationArray SAMPLE2o = {{true, 0, 5}, {false, 3, 1}, {true, 2, 6}};
const ArrayType EXPECTED2 = {2, 1};

const ArrayType SAMPLE3 = {2, 6, 7, 5, 18, 86, 54, 2};
const OperationArray SAMPLE3o = {{true, 2, 7}, {false, 3, 4}, {true, 2, 6}};
const ArrayType EXPECTED3 = {2, 4};


THE_BENCHMARK(RangeMinimumQuery_ST_Iterative, SAMPLE2, SAMPLE2o);

SIMPLE_TEST(RangeMinimumQuery_ST_Iterative, TestSAMPLE2, EXPECTED2, SAMPLE2, SAMPLE2o);
SIMPLE_TEST(RangeMinimumQuery_ST_Iterative, TestSAMPLE3, EXPECTED3, SAMPLE3, SAMPLE3o);
