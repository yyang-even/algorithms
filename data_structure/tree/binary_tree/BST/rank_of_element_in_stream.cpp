#include "common_header.h"

#include "finding/finding.h"


namespace {

using ArrayType = std::vector<int>;

/** Rank of an element in a stream
 *
 * @reference   https://www.geeksforgeeks.org/rank-element-stream/
 *
 * Given a stream of integers, lookup the rank of a given integer x. Rank of an integer
 * in-stream is "Total number of elements less than or equal to x (not including x)".
 * If an element is not found in the stream or is smallest in stream, return -1.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 11.8.
 */
struct BinaryTreeNode {
    using ValueType = int;
    using PointerType = std::shared_ptr<BinaryTreeNode>;

    PointerType left;
    PointerType right;
    ValueType value{};
    int size_of_left_subtree{};

    explicit BinaryTreeNode(const ValueType v) : value(v) {}
};

auto Insert(const BinaryTreeNode::PointerType node, const BinaryTreeNode::ValueType x) {
    if (not node) {
        return std::make_shared<BinaryTreeNode>(x);
    }

    if (x <= node->value) {
        node->left = Insert(node->left, x);
        ++(node->size_of_left_subtree);
    } else {
        node->right = Insert(node->right, x);
    }

    return node;
}

auto GetRank(const BinaryTreeNode::PointerType node,
             const BinaryTreeNode::ValueType x) {
    if (not node) {
        return NOT_FOUND;
    }

    if (node->value == x) {
        return node->size_of_left_subtree;
    }

    if (x < node->value) {
        return GetRank(node->left, x);
    }

    if (const auto right_rank = GetRank(node->right, x); right_rank == NOT_FOUND) {
        return NOT_FOUND;
    } else {
        return node->size_of_left_subtree + 1 + right_rank;
    }
}

auto RankOfElementInStream(const ArrayType &stream,
                           const ArrayType::value_type element) {
    BinaryTreeNode::PointerType root;
    for (const auto v : stream) {
        root = Insert(root, v);
    }

    return GetRank(root, element);
}

}//namespace


const ArrayType SAMPLE1 = {10, 20, 15, 3, 4, 4, 1};
const ArrayType SAMPLE2 = {5, 1, 14, 4, 15, 9, 7, 20, 11};


THE_BENCHMARK(RankOfElementInStream, SAMPLE1, 4);

SIMPLE_TEST(RankOfElementInStream, TestSAMPLE1, 3, SAMPLE1, 4);
SIMPLE_TEST(RankOfElementInStream, TestSAMPLE2, 8, SAMPLE2, 20);
SIMPLE_TEST(RankOfElementInStream, TestSAMPLE3, 0, SAMPLE1, 1);
SIMPLE_TEST(RankOfElementInStream, TestSAMPLE4, NOT_FOUND, SAMPLE1, -1);
