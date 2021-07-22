#include "common_header.h"

#include "binary_search_tree.h"


namespace {

using OutputType = std::unordered_set<int>;

/** Find the closest element in Binary Search Tree
 *
 * @reference   https://www.geeksforgeeks.org/find-closest-element-binary-search-tree/
 *
 * Given a binary search tree and a target node K. The task is to find the node with
 * minimum absolute difference with given target value K.
 *
 * @reference   Find the closest element in Binary Search Tree | Space Efficient Method
 *              https://www.geeksforgeeks.org/find-the-closest-element-in-binary-search-tree-space-efficient-method/
 *
 * @reference   Closest Binary Search Tree Value
 *              https://www.programcreek.com/2014/05/leetcode-closest-binary-search-tree-value-java/
 */
void ClosestNode(const BinaryTree::Node::PointerType node,
                 const int key,
                 int &min_diff, int &result) {
    if (not node) {
        return;
    }

    if (node->value == key) {
        result = key;
        return;
    }

    const auto diff = std::abs(node->value - key);
    if (min_diff > diff) {
        min_diff = diff;
        result = node->value;
    }

    if (key < node->value) {
        ClosestNode(node->left, key, min_diff, result);
    } else {
        ClosestNode(node->right, key, min_diff, result);
    }
}

inline auto ClosestNode(const BinaryTree::Node::PointerType root,
                        const int key) {
    int min_diff = INT_MAX;
    int result = 0;
    ClosestNode(root, key, min_diff, result);

    return result;
}


auto ClosestNode_Iterative(BinaryTree::Node::PointerType node,
                           const int key) {
    int min_diff = INT_MAX;
    int result = 0;

    while (node) {
        if (key == node->value) {
            return key;
        } else {
            const auto diff = std::abs(node->value - key);
            if (diff < min_diff) {
                min_diff = diff;
                result = node->value;
            }
            if (key > node->value) {
                node = node->right;
            } else {
                node = node->left;
            }
        }
    }

    return result;
}


/**
 * @reference   Closest Binary Search Tree Value II
 *              https://kennyzhuang.gitbooks.io/leetcode-lock/content/270_closest_binary_search_tree_value_ii.html
 *
 * Given a non-empty binary search tree and a target value, find k values in the BST
 * that are closest to the target. Note: Given target value is a floating point. You may
 * assume k is always valid, that is: k ≤ total nodes. You are guaranteed to have only
 * one unique set of k values in the BST that are closest to the target.
 * Follow up: Assume that the BST is balanced, could you solve it in less than O(n)
 * runtime (where n = total nodes)?
 */
void KClosestNodes_Inorder(const BinaryTree::Node::PointerType node,
                           const double target, const std::size_t K,
                           BinaryTree::ArrayType &results) {
    if (not node) {
        return;
    }

    KClosestNodes_Inorder(node->left, target, K, results);

    if (results.size() < K) {
        results.push_back(node->value);
    } else if (std::abs(node->value - target) < std::abs(results.front() - target)) {
        results.erase(results.begin());
        results.push_back(node->value);
    } else {
        return;
    }

    KClosestNodes_Inorder(node->right, target, K, results);
}

inline auto
KClosestNodes_Inorder(const BinaryTree::Node::PointerType root,
                      const double target, const std::size_t K) {
    BinaryTree::ArrayType results;
    KClosestNodes_Inorder(root, target, K, results);
    return results;
}


void getPredecessor(std::stack<BinaryTree::Node::PointerType> &predecessors) {
    const auto node = predecessors.top();
    predecessors.pop();

    if (node->left) {
        predecessors.push(node->left);
        while (predecessors.top()->right) {
            predecessors.push(predecessors.top()->right);
        }
    }
}

void getSuccessor(std::stack<BinaryTree::Node::PointerType> &successor) {
    const auto node = successor.top();
    successor.pop();

    if (node->right) {
        successor.push(node->right);
        while (successor.top()->left) {
            successor.push(successor.top()->left);
        }
    }
}

auto KClosestNodes(BinaryTree::Node::PointerType node,
                   const double target, int k) {
    OutputType results;
    std::stack<BinaryTree::Node::PointerType> predecessors, successor;

    while (node) {
        if (node->value <= target) {
            predecessors.push(node);
            node = node->right;
        } else {
            successor.push(node);
            node = node->left;
        }
    }

    while (k-- > 0) {
        if (successor.empty() or
            (not predecessors.empty() and
             (target - predecessors.top()->value < successor.top()->value - target))) {
            results.insert(predecessors.top()->value);
            getPredecessor(predecessors);
        } else {
            results.insert(successor.top()->value);
            getSuccessor(successor);
        }
    }

    return results;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleBST().GetRoot();


THE_BENCHMARK(ClosestNode, SAMPLE1, 5);

SIMPLE_TEST(ClosestNode, TestSAMPLE1, 4, SAMPLE1, 4);
SIMPLE_TEST(ClosestNode, TestSAMPLE2, 3, SAMPLE1, 3);
SIMPLE_TEST(ClosestNode, TestSAMPLE3, 1, SAMPLE1, 1);
SIMPLE_TEST(ClosestNode, TestSAMPLE4, 5, SAMPLE1, 5);
SIMPLE_TEST(ClosestNode, TestSAMPLE5, 5, SAMPLE1, 10);
SIMPLE_TEST(ClosestNode, TestSAMPLE6, 1, SAMPLE1, -10);


THE_BENCHMARK(ClosestNode_Iterative, SAMPLE1, 5);

SIMPLE_TEST(ClosestNode_Iterative, TestSAMPLE1, 4, SAMPLE1, 4);
SIMPLE_TEST(ClosestNode_Iterative, TestSAMPLE2, 3, SAMPLE1, 3);
SIMPLE_TEST(ClosestNode_Iterative, TestSAMPLE3, 1, SAMPLE1, 1);
SIMPLE_TEST(ClosestNode_Iterative, TestSAMPLE4, 5, SAMPLE1, 5);
SIMPLE_TEST(ClosestNode_Iterative, TestSAMPLE5, 5, SAMPLE1, 10);
SIMPLE_TEST(ClosestNode_Iterative, TestSAMPLE6, 1, SAMPLE1, -10);


using InitializerType = std::initializer_list<int>;

const InitializerType EXPECTED1 = {3, 4};
const InitializerType EXPECTED2 = {3, 4, 5};


THE_BENCHMARK(KClosestNodes_Inorder, SAMPLE1, 3.7, 2);

SIMPLE_TEST(KClosestNodes_Inorder, TestSAMPLE1, EXPECTED1, SAMPLE1, 3.7, 2);
SIMPLE_TEST(KClosestNodes_Inorder, TestSAMPLE2, EXPECTED2, SAMPLE1, 3.7, 3);


THE_BENCHMARK(KClosestNodes, SAMPLE1, 3.7, 2);

SIMPLE_TEST(KClosestNodes, TestSAMPLE1, EXPECTED1, SAMPLE1, 3.7, 2);
SIMPLE_TEST(KClosestNodes, TestSAMPLE2, EXPECTED2, SAMPLE1, 3.7, 3);
