#include "common_header.h"

#include "prefix_sum_array.h"
#include "range_sum_queries.h"

#include "data_structure/heap/segment_tree.h"
#include "mathematics/matrix/matrix.h"
#include "mathematics/numbers/binary/clear_all_bits_except_the_last_set_bit.h"


namespace {

using ArrayType = std::vector<int>;
using QueryType = std::pair<int, int>;
using QueryArrayType = std::vector<QueryType>;
using OperationArrayType = std::vector<std::pair<bool, QueryType>>;
using MatrixQueryType = std::vector<std::tuple<int, int, int, int>>;

/** Range sum queries without updates
 *
 * @reference   https://www.geeksforgeeks.org/range-sum-queries-without-updates/
 * @reference   Range Sum Query - Immutable
 *              https://leetcode.com/problems/range-sum-query-immutable/
 *
 * Given an integer array nums, handle multiple queries of the following type:
 *  Calculate the sum of the elements of nums between indices left and right inclusive where
 *  left <= right.
 * Implement the NumArray class:
 *  NumArray(int[] nums) Initializes the object with the integer array nums.
 *  int sumRange(int left, int right) Returns the sum of the elements of nums between indices
 *  left and right inclusive (i.e. nums[left] + nums[left + 1] + ... + nums[right]).
 */
auto RangeSumQueries(ArrayType elements, const QueryArrayType &queries) {
    const auto prefix_sums = PrefixSumArray(std::move(elements));

    ArrayType results;
    for (const auto &[left, right] : queries) {
        results.push_back(RangeSum(prefix_sums, left, right));
    }

    return results;
}


/**
 * @reference   Range sum query using Sparse Table
 *              https://www.geeksforgeeks.org/range-sum-query-using-sparse-table/
 */


/** Range Sum Query - Mutable
 *
 * @reference   https://leetcode.com/problems/range-sum-query-mutable/
 * @reference   Segment Tree | Set 1 (Sum of given range)
 *              https://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range/
 *
 * Given an integer array nums, handle multiple queries of the following types:
 *  Update the value of an element in nums.
 *  Calculate the sum of the elements of nums between indices left and right inclusive where
 *  left <= right.
 * Implement the NumArray class:
 *  NumArray(int[] nums) Initializes the object with the integer array nums.
 *  void update(int index, int val) Updates the value of nums[index] to be val.
 *  int sumRange(int left, int right) Returns the sum of the elements of nums between indices
 *  left and right inclusive (i.e. nums[left] + nums[left + 1] + ... + nums[right]).
 */
auto buildSegmentTree(const ArrayType &nums) {
    ArrayType segment_tree(nums.size() * 2, 0);

    if (not nums.empty()) {
        for (std::size_t i = nums.size(), j = 0; i < 2 * nums.size(); ++i, ++j) {
            segment_tree[i] = nums[j];
        }

        for (int i = nums.size() - 1; i > 0; --i) {
            segment_tree[i] = segment_tree[LeftChild(i)] + segment_tree[RightChild(i)];
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
        if (not isLeftChild(left)) {
            sum += segment_tree[left++];
        }
        if (isLeftChild(right)) {
            sum += segment_tree[right--];
        }
        left = Parent(left);
        right = Parent(right);
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
        if (isLeftChild(index)) {
            ++right;
        } else {
            --left;
        }
        const auto parent = Parent(index);
        segment_tree[parent] = segment_tree[left] + segment_tree[right];
        index = parent;
    }
}

auto RangeSumQueriesMutable_SegmentTree(const ArrayType &elements,
                                        const OperationArrayType &operations) {
    auto segment_tree = buildSegmentTree(elements);

    ArrayType results;
    for (const auto &[is_update, a_query] : operations) {
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
 * Compared with Segment Tree, Binary Indexed Tree requires less space and is easier to implement.
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
    const auto N = bitree.size();
    while (index < N) {
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

auto RangeSumQueriesMutable_BIT(const ArrayType &elements, const OperationArrayType &operations) {
    auto bit_tree = buildBIT(elements);

    ArrayType results;
    for (const auto &[is_update, a_query] : operations) {
        if (is_update) {
            const auto diff = a_query.second - getOrigin_BIT(bit_tree, a_query.first);
            update_BIT(bit_tree, a_query.first, diff);
        } else {
            results.push_back(sumRange_BIT(bit_tree, a_query.first, a_query.second));
        }
    }

    return results;
}


/**
 * @reference   Sqrt (or Square Root) Decomposition Technique | Set 1 (Introduction)
 *              https://www.geeksforgeeks.org/sqrt-square-root-decomposition-technique-set-1-introduction/
 */


/**
 * @reference   Range Sum Query 2D - Immutable
 *              https://leetcode.com/problems/range-sum-query-2d-immutable/
 *
 * Given a 2D matrix matrix, handle multiple queries of the following type:
 *  Calculate the sum of the elements of matrix inside the rectangle defined by its upper left
 *  corner (row1, col1) and lower right corner (row2, col2).
 * Implement the NumMatrix class:
 *  NumMatrix(int[][] matrix) Initializes the object with the integer matrix matrix.
 *  int sumRegion(int row1, int col1, int row2, int col2) Returns the sum of the elements of
 *  matrix inside the rectangle defined by its upper left corner (row1, col1) and lower right
 *  corner (row2, col2).
 */
class NumMatrix_Row {
    MatrixType prefix_sums;

public:
    NumMatrix_Row(const MatrixType &matrix) noexcept {
        for (const auto &row : matrix) {
            prefix_sums.push_back({0});
            for (const auto n : row) {
                prefix_sums.back().push_back(prefix_sums.back().back() + n);
            }
        }
    }

    auto
    SumRegion(const int row1, const int col1, const int row2, const int col2) const noexcept {
        int result = 0;
        for (auto i = row1; i <= row2; ++i) {
            result += prefix_sums[i][col2 + 1] - prefix_sums[i][col1];
        }

        return result;
    }
};


class NumMatrix_Block {
    MatrixType prefix_sums;

public:
    NumMatrix_Block(const MatrixType &matrix) noexcept :
        prefix_sums(matrix.size() + 1, std::vector(matrix.front().size() + 1, 0)) {
        for (std::size_t r = 0; r < matrix.size(); ++r) {
            for (std::size_t c = 0; c < matrix.front().size(); ++c) {
                prefix_sums[r + 1][c + 1] = prefix_sums[r + 1][c] + prefix_sums[r][c + 1] +
                                            matrix[r][c] - prefix_sums[r][c];
            }
        }
    }

    auto
    SumRegion(const int row1, const int col1, const int row2, const int col2) const noexcept {
        return prefix_sums[row2 + 1][col2 + 1] - prefix_sums[row1][col2 + 1] -
               prefix_sums[row2 + 1][col1] + prefix_sums[row1][col1];
    }
};

template<typename NumMatrixType>
auto test2DRangeSumQuery(const MatrixType &matrix, const MatrixQueryType &queries) {
    NumMatrixType m {matrix};

    ArrayType result;
    for (const auto &[row1, col1, row2, col2] : queries) {
        result.push_back(m.SumRegion(row1, col1, row2, col2));
    }

    return result;
}

constexpr auto test2DRangeSumQuery_Row = test2DRangeSumQuery<NumMatrix_Row>;
constexpr auto test2DRangeSumQuery_Block = test2DRangeSumQuery<NumMatrix_Block>;

} //namespace


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

SIMPLE_TEST(RangeSumQueriesMutable_SegmentTree, TestSAMPLE1, EXPECTED1, SAMPLE1, SAMPLE_O1);
SIMPLE_TEST(RangeSumQueriesMutable_SegmentTree, TestSAMPLE4, EXPECTED4, SAMPLE4, SAMPLE_O4);


THE_BENCHMARK(RangeSumQueriesMutable_BIT, SAMPLE1, SAMPLE_O1);

SIMPLE_TEST(RangeSumQueriesMutable_BIT, TestSAMPLE1, EXPECTED1, SAMPLE1, SAMPLE_O1);
SIMPLE_TEST(RangeSumQueriesMutable_BIT, TestSAMPLE4, EXPECTED4, SAMPLE4, SAMPLE_O4);


// clang-format off
const MatrixType SAMPLE1M = {
    {3, 0, 1, 4, 2},
    {5, 6, 3, 2, 1},
    {1, 2, 0, 1, 5},
    {4, 1, 0, 1, 7},
    {1, 0, 3, 0, 5}
};

const MatrixQueryType SAMPLE1M_Q1 = {{2, 1, 4, 3}, {1, 1, 2, 2}, {1, 2, 2, 4}};

const ArrayType EXPECTED1M = {8, 11, 12};
// clang-format on


THE_BENCHMARK(test2DRangeSumQuery_Row, SAMPLE1M, SAMPLE1M_Q1);

SIMPLE_TEST(test2DRangeSumQuery_Row, TestSAMPLE1, EXPECTED1M, SAMPLE1M, SAMPLE1M_Q1);


THE_BENCHMARK(test2DRangeSumQuery_Block, SAMPLE1M, SAMPLE1M_Q1);

SIMPLE_TEST(test2DRangeSumQuery_Block, TestSAMPLE1, EXPECTED1M, SAMPLE1M, SAMPLE1M_Q1);
