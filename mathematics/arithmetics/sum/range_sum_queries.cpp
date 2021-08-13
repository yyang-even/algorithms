#include "common_header.h"

#include "range_sum_queries.h"
#include "prefix_sum_array.h"

#include "mathematics/numbers/binary/clear_all_bits_except_the_last_set_bit.h"


namespace {

using ArrayType = std::vector<int>;
using QueryType = std::pair<int, int>;
using QueryArrayType = std::vector<QueryType>;
using OperationArrayType = std::vector<std::pair<bool, QueryType>>;

/** Range sum queries without updates
 *
 * @reference   https://www.geeksforgeeks.org/range-sum-queries-without-updates/
 * @reference   Range Sum Query - Immutable
 *              https://leetcode.com/problems/range-sum-query-immutable/
 *
 * Given an array arr of integers of size n. We need to compute the sum of elements from
 * index i to index j. The queries consisting of i and j index values will be executed
 * multiple times.
 */
auto RangeSumQueries(ArrayType elements, const QueryArrayType &queries) {
    const auto prefix_sums = PrefixSumArray(std::move(elements));

    ArrayType results;
    for (const auto [left, right] : queries) {
        results.push_back(RangeSum(prefix_sums, left, right));
    }

    return results;
}


/** Range Sum Query - Mutable
 *
 * @reference   https://leetcode.com/problems/range-sum-query-mutable/
 * @reference   Segment Tree | Set 1 (Sum of given range)
 *              https://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range/
 *
 * Given an integer array nums, handle multiple queries of the following types:
 *  Update the value of an element in nums.
 *  Calculate the sum of the elements of nums between indices left and right inclusive
 *  where left <= right.
 * Segment tree is a very flexible data structure, because it is used to solve numerous
 * range query problems like finding minimum, maximum, sum, greatest common divisor,
 * least common denominator in array in logarithmic time.
 */
inline constexpr auto ST_LeftChild(const std::size_t i) {
    return i * 2;
}

inline constexpr auto ST_RightChild(const std::size_t i) {
    return ST_LeftChild(i) + 1;
}

inline constexpr auto ST_Parent(const std::size_t i) {
    return i / 2;
}

inline constexpr auto ST_isLeftChild(const std::size_t i) {
    return i % 2 == 0;
}

auto buildSegmentTree(const ArrayType &nums) {
    ArrayType segment_tree(nums.size() * 2, 0);

    if (not nums.empty()) {
        for (std::size_t i = nums.size(), j = 0;  i < 2 * nums.size(); ++i,  ++j) {
            segment_tree[i] = nums[j];
        }

        for (int i = nums.size() - 1; i > 0; --i) {
            segment_tree[i] = segment_tree[ST_LeftChild(i)] + segment_tree[ST_RightChild(i)];
        }
    }

    return segment_tree;
}

auto sumRange_ST(const ArrayType &segment_tree, int left, int right) {
    const auto size = segment_tree.size() / 2;

    left += size;
    right += size;
    int sum = 0;
    while (left <= right) {
        if (not ST_isLeftChild(left)) {
            sum += segment_tree[left++];
        }
        if (ST_isLeftChild(right)) {
            sum += segment_tree[right--];
        }
        left /= 2;
        right /= 2;
    }

    return sum;
}

void update_ST(ArrayType &segment_tree, int index, const int val) {
    const auto size = segment_tree.size() / 2;

    index += size;
    segment_tree[index] = val;
    while (index > 0) {
        auto left = index;
        auto right = index;
        if (ST_isLeftChild(index)) {
            ++right;
        } else {
            --left;
        }
        const auto parent = ST_Parent(index);
        segment_tree[parent] = segment_tree[left] + segment_tree[right];
        index = parent;
    }
}

auto RangeSumQueriesMutable_SegmentTree(const ArrayType &elements,
                                        const OperationArrayType &operations) {
    auto segment_tree = buildSegmentTree(elements);

    ArrayType results;
    for (const auto [is_update, a_query] : operations) {
        if (is_update) {
            update_ST(segment_tree, a_query.first, a_query.second);
        } else {
            results.push_back(sumRange_ST(segment_tree, a_query.first, a_query.second));
        }
    }

    return results;
}


/**
 * @reference   Binary Indexed Tree or Fenwick Tree
 *              https://www.geeksforgeeks.org/binary-indexed-tree-or-fenwick-tree-2/
 *
 * Compared with Segment Tree, Binary Indexed Tree requires less space and is easier to
 * implement.
 *
 * @reference   BINARY INDEXED TREES
 *              https://www.topcoder.com/thrive/articles/Binary%20Indexed%20Trees
 *
 * There are n boxes that undergo the following queries:
 *  1. add marble to box i
 *  2. sum marbles from box k to box l
 * Our goal is to implement those two queries.
 */
void update_BIT(ArrayType &bitree, ArrayType::size_type index, const int diff) {
    ++index;
    while (index < bitree.size()) {
        bitree[index] += diff;
        index += ClearAllBitsExceptTheLastSetBit(index);
    }
}

auto buildBIT(const ArrayType &elements) {
    ArrayType binary_indexed_tree(elements.size() + 1, 0);
    for (ArrayType::size_type i = 0; i < elements.size(); ++i) {
        update_BIT(binary_indexed_tree, i, elements[i]);
    }
    return binary_indexed_tree;
}

auto getSum_BIT(const ArrayType &bitree, int index) {
    int sum = 0;

    ++index;
    while (index > 0) {
        sum += bitree[index];
        index -= ClearAllBitsExceptTheLastSetBit(index);
    }

    return sum;
}

inline auto sumRange_BIT(const ArrayType &bitree, const int i, const int j) {
    return getSum_BIT(bitree, j) - getSum_BIT(bitree, i - 1);
}

auto getOrigin_BIT(const ArrayType &bitree, int index) {
    int sum = bitree[++index];
    if (index > 0) {
        const int z = index - ClearAllBitsExceptTheLastSetBit(index);
        --index;
        while (index != z) {
            sum -= bitree[index];
            index -= ClearAllBitsExceptTheLastSetBit(index);
        }
    }
    return sum;
}

auto
RangeSumQueriesMutable_BIT(const ArrayType &elements,
                           const OperationArrayType &operations) {
    auto bit_tree = buildBIT(elements);

    ArrayType results;
    for (const auto [is_update, a_query] : operations) {
        if (is_update) {
            const auto diff = a_query.second - getOrigin_BIT(bit_tree, a_query.first);
            update_BIT(bit_tree, a_query.first, diff);
        } else {
            results.push_back(sumRange_BIT(bit_tree, a_query.first, a_query.second));
        }
    }

    return results;
}

}//namespace


const ArrayType SAMPLE1 = {1, 2, 3, 4, 5};
const QueryArrayType SAMPLE_Q1 = {{1, 3}, {2, 4}};
const OperationArrayType SAMPLE_O1 = {{false, {1, 3}}, {false, {2, 4}}};
const ArrayType EXPECTED1 = {9, 12};

const QueryArrayType SAMPLE_Q2 = {{0, 4}, {1, 2}};
const ArrayType EXPECTED2 = {15, 5};

const ArrayType SAMPLE3 = {-2, 0, 3, -5, 2, -1};
const QueryArrayType SAMPLE_Q3 = {{0, 2}, {2, 5}, {0, 5}};
const ArrayType EXPECTED3 = {1, -1, -3};


THE_BENCHMARK(RangeSumQueries, SAMPLE1, SAMPLE_Q1);

SIMPLE_TEST(RangeSumQueries, TestSAMPLE1, EXPECTED1, SAMPLE1, SAMPLE_Q1);
SIMPLE_TEST(RangeSumQueries, TestSAMPLE2, EXPECTED2, SAMPLE1, SAMPLE_Q2);
SIMPLE_TEST(RangeSumQueries, TestSAMPLE3, EXPECTED3, SAMPLE3, SAMPLE_Q3);


const ArrayType SAMPLE4 = {1, 3, 5};
const OperationArrayType SAMPLE_O4 = {{false, {0, 2}}, {true, {1, 2}}, {false, {0, 2}}};
const ArrayType EXPECTED4 = {9, 8};


THE_BENCHMARK(RangeSumQueriesMutable_SegmentTree, SAMPLE1, SAMPLE_O1);

SIMPLE_TEST(RangeSumQueriesMutable_SegmentTree, TestSAMPLE1, EXPECTED1,
            SAMPLE1, SAMPLE_O1);
SIMPLE_TEST(RangeSumQueriesMutable_SegmentTree, TestSAMPLE4, EXPECTED4,
            SAMPLE4, SAMPLE_O4);


THE_BENCHMARK(RangeSumQueriesMutable_BIT, SAMPLE1, SAMPLE_O1);

SIMPLE_TEST(RangeSumQueriesMutable_BIT, TestSAMPLE1, EXPECTED1,
            SAMPLE1, SAMPLE_O1);
SIMPLE_TEST(RangeSumQueriesMutable_BIT, TestSAMPLE4, EXPECTED4,
            SAMPLE4, SAMPLE_O4);
