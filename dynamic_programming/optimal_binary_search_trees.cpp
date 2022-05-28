#include "common_header.h"

#include "data_structure/tree/binary_tree/binary_tree.h"
#include "data_structure/tree/binary_tree/compare_binary_trees.h"


namespace {

using ArrayType = std::vector<int>;
using TwoDimensionalArrayType =
    std::unordered_map<std::size_t, std::unordered_map<std::size_t, int>>;

/** Optimal Binary Search Trees
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 15.5.
 */
auto OptimalBinarySearchTree(const ArrayType &key_probabilities,
                             const ArrayType &dummy_probabilities,
                             TwoDimensionalArrayType *const roots = nullptr) {
    assert(key_probabilities.size() == dummy_probabilities.size());

    ArrayType::value_type min_costs[dummy_probabilities.size() + 1][dummy_probabilities.size()] =
        {};
    ArrayType::value_type sum_probabilities[dummy_probabilities.size() + 1]
                                           [dummy_probabilities.size()] = {};

    for (ArrayType::size_type i = 0; i < dummy_probabilities.size(); ++i) {
        min_costs[i + 1][i] = dummy_probabilities[i];
        sum_probabilities[i + 1][i] = dummy_probabilities[i];
    }

    for (ArrayType::size_type length = 1; length < dummy_probabilities.size(); ++length) {
        for (ArrayType::size_type i = 1; i <= dummy_probabilities.size() - length; ++i) {
            const auto j = i + length - 1;
            min_costs[i][j] = std::numeric_limits<ArrayType::value_type>::max();
            sum_probabilities[i][j] =
                sum_probabilities[i][j - 1] + key_probabilities[j] + dummy_probabilities[j];
            for (auto r = i; r <= j; ++r) {
                const auto cost =
                    min_costs[i][r - 1] + min_costs[r + 1][j] + sum_probabilities[i][j];
                if (cost < min_costs[i][j]) {
                    min_costs[i][j] = cost;
                    if (roots) {
                        (*roots)[i][j] = r;
                    }
                }
            }
        }
    }

    return min_costs[1][key_probabilities.size() - 1];
}


/**
 * @reference   Optimal Binary Search Tree | DP-24
 *              https://www.geeksforgeeks.org/optimal-binary-search-tree-dp-24/
 *
 * Given a sorted array keys[0.. n-1] of search keys and an array freq[0.. n-1] of frequency counts,
 * where freq[i] is the number of searches to keys[i]. Construct a binary search tree of all keys
 * such that the total cost of all the searches is as small as possible.
 */
inline auto OptimalBinarySearchTreeSimplified(ArrayType freq) {
    freq.insert(freq.cbegin(), 0);
    const ArrayType dummy_probabilities(freq.size(), 0);
    return OptimalBinarySearchTree(freq, dummy_probabilities);
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 15.5-1.
 */
BinaryTree::Node::PointerType ConstructOptimalBinarySearchTree(const ArrayType &keys,
                                                               TwoDimensionalArrayType &roots,
                                                               const ArrayType::size_type i,
                                                               const ArrayType::size_type j) {
    if (i > j) {
        return nullptr;
    }
    if (i == j) {
        return std::make_shared<BinaryTree::Node>(keys[i - 1]);
    }

    const auto node = std::make_shared<BinaryTree::Node>(keys[roots[i][j] - 1]);
    node->left = ConstructOptimalBinarySearchTree(keys, roots, i, roots[i][j] - 1);
    node->right = ConstructOptimalBinarySearchTree(keys, roots, roots[i][j] + 1, j);

    return node;
}

auto ConstructOptimalBinarySearchTree(const ArrayType &key_probabilities,
                                      const ArrayType &dummy_probabilities) {
    TwoDimensionalArrayType roots;
    OptimalBinarySearchTree(key_probabilities, dummy_probabilities, &roots);

    ArrayType keys;
    for (ArrayType::size_type i = 1; i < dummy_probabilities.size(); ++i) {
        keys.push_back(i);
    }

    return ConstructOptimalBinarySearchTree(keys, roots, 1, keys.size());
}

} //namespace


const ArrayType SAMPLE1_P = {0, 15, 10, 5, 10, 20};
const ArrayType SAMPLE1_Q = {5, 10, 5, 5, 5, 10};

const ArrayType SAMPLE2_P = {0, 4, 6, 8, 2, 10, 12, 14};
const ArrayType SAMPLE2_Q = {6, 6, 6, 6, 5, 5, 5, 5};


THE_BENCHMARK(OptimalBinarySearchTree, SAMPLE1_P, SAMPLE1_Q);

SIMPLE_TEST(OptimalBinarySearchTree, TestSAMPLE1, 275, SAMPLE1_P, SAMPLE1_Q);
SIMPLE_TEST(OptimalBinarySearchTree, TestSAMPLE2, 312, SAMPLE2_P, SAMPLE2_Q);


const ArrayType SAMPLE3 = {34, 50};
const ArrayType SAMPLE4 = {34, 8, 50};


THE_BENCHMARK(OptimalBinarySearchTreeSimplified, SAMPLE3);

SIMPLE_TEST(OptimalBinarySearchTreeSimplified, TestSAMPLE3, 118, SAMPLE3);
SIMPLE_TEST(OptimalBinarySearchTreeSimplified, TestSAMPLE4, 142, SAMPLE4);


/**
 *     2
 *    / \
 *   1   5
 *      /
 *     4
 *    /
 *   3
 */
static inline auto MakeTheSampleTree() {
    const BinaryTree binary_tree {2};
    auto &root = *binary_tree.GetRoot();
    SetLeftChild(root, 1);
    auto &right_child = *SetRightChild(root, 5);
    auto &node4 = *SetLeftChild(right_child, 4);
    SetLeftChild(node4, 3);

    return binary_tree.GetRoot();
}

const auto SAMPLE1_LHS = MakeTheSampleTree();
const auto SAMPLE1_RHS = ConstructOptimalBinarySearchTree(SAMPLE1_P, SAMPLE1_Q);


THE_BENCHMARK(ConstructOptimalBinarySearchTree, SAMPLE1_P, SAMPLE1_Q);

SIMPLE_TEST(areIdenticalTrees, TestSAMPLE1, true, SAMPLE1_LHS, SAMPLE1_RHS);
