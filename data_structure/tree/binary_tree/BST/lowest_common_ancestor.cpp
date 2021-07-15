#include "common_header.h"

#include "binary_search_tree.h"
#include "data_structure/tree/binary_tree/binary_tree_search.h"


namespace {

/**
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 5.
 * @reference   Lowest Common Ancestor in a Binary Search Tree.
 *              https://www.geeksforgeeks.org/lowest-common-ancestor-in-a-binary-search-tree/
 * @reference   Lowest Common Ancestor of a Binary Search Tree
 *              https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
 *
 * Given values of two values n1 and n2 in a Binary Search Tree, find the Lowest Common
 * Ancestor (LCA). You may assume that both the values exist in the tree.
 */
auto LowestCommonAncestor_BST_Recursive(const BinaryTree::Node::PointerType node,
                                        const BinaryTree::Node::ValueType x,
                                        const BinaryTree::Node::ValueType y) {
    if (not node) {
        return node;
    }

    if (node->value > x and node->value > y) {
        return LowestCommonAncestor_BST_Recursive(node->left, x, y);
    }

    if (node->value < x and node->value < y) {
        return LowestCommonAncestor_BST_Recursive(node->right, x, y);
    }

    return node;
}


auto LowestCommonAncestor_BST_Iterative(const BinaryTree::Node::PointerType root,
                                        const BinaryTree::Node::ValueType x,
                                        const BinaryTree::Node::ValueType y) {
    auto node = root;
    while (node) {
        if (node->value > x and node->value > y) {
            node = node->left;
        } else if (node->value < x and node->value < y) {
            node = node->right;
        } else {
            break;
        }
    }

    return node;
}


/**
 * @reference   Lowest Common Ancestor in a Binary Tree | Set 1
 *              https://www.geeksforgeeks.org/lowest-common-ancestor-binary-tree-set-1/
 *
 * Given a binary tree (not a binary search tree) and two values say n1 and n2, write a
 * program to find the least common ancestor. You may assume that both the values exist
 * in the tree.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 4.7.
 *
 * @reference   Print the path common to the two paths from the root to the two given nodes
 *              https://www.geeksforgeeks.org/print-path-common-two-paths-root-two-given-nodes/
 * @reference   Print common nodes on path from root (or common ancestors)
 *              https://www.geeksforgeeks.org/print-common-nodes-path-root-common-ancestors/
 * @reference   Lowest Common Ancestor of a Binary Tree
 *              https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
 *
 * @reference   Lowest Common Ancestor of a Binary Tree II
 *              http://leetcode.libaoj.in/lowest-common-ancestor-of-a-binary-tree-ii.html
 *
 * Given the root of a binary tree, return the lowest common ancestor (LCA) of two given
 * nodes, p and q. If either node p or q does not exist in the tree, return null. All
 * values of the nodes in the tree are unique.
 */
auto LowestCommonAncestor_CommonPath(const BinaryTree::Node::PointerType root,
                                     const BinaryTree::Node::ValueType x,
                                     const BinaryTree::Node::ValueType y) {
    BinaryTree::ArrayType path_x, path_y;
    BinaryTreeSearch_Preorder(root, x, &path_x);
    BinaryTreeSearch_Preorder(root, y, &path_y);

    BinaryTree::ArrayType::size_type i = 0;
    for (; i < path_x.size() and i < path_y.size(); ++i) {
        if (path_x[i] != path_y[i]) {
            break;
        }
    }

    return i ? path_x[i - 1] : -1;
}


auto LowestCommonAncestor_SingleTraversal(const BinaryTree::Node::PointerType node,
                                          const BinaryTree::Node::ValueType x,
                                          const BinaryTree::Node::ValueType y) {
    if (not node or node->value == x or node->value == y) {
        return node;
    }

    const auto left_LCA = LowestCommonAncestor_SingleTraversal(node->left, x, y);
    const auto right_LCA = LowestCommonAncestor_SingleTraversal(node->right, x, y);

    if (left_LCA and right_LCA) {
        return node;
    }

    return left_LCA ? left_LCA : right_LCA;
}


auto
LowestCommonAncestor_Iterative_Backtracking(const BinaryTree::Node::PointerType root,
                                            const BinaryTree::Node::ValueType x,
                                            const BinaryTree::Node::ValueType y) {
    assert(root);

    std::queue<BinaryTree::Node::PointerType> q;
    std::unordered_map<BinaryTree::Node::ValueType, BinaryTree::Node::PointerType>
    parents_map;
    parents_map.emplace(root->value, nullptr);
    q.push(root);

    BinaryTree::Node::PointerType x_node;
    BinaryTree::Node::PointerType y_node;
    while (not q.empty() and not(x_node and y_node)) {
        const auto node = q.front();
        q.pop();

        if (node->value == x) {
            x_node = node;
        }
        if (node->value == y) {
            y_node = node;
        }

        if (node->left) {
            q.push(node->left);
            parents_map.emplace(node->left->value, node);
        }

        if (node->right) {
            q.push(node->right);
            parents_map.emplace(node->right->value, node);
        }
    }

    std::unordered_set<BinaryTree::Node::PointerType> ancestors;
    for (; x_node; x_node = parents_map[x_node->value]) {
        ancestors.insert(x_node);
    }

    for (; ancestors.find(y_node) == ancestors.cend(); y_node = parents_map[y_node->value]);

    return y_node;
}


/**
 * @reference   Lowest Common Ancestor in a Binary Tree | Set 2 (Using Parent Pointer)
 *              https://www.geeksforgeeks.org/lowest-common-ancestor-in-a-binary-tree-set-2-using-parent-pointer/
 * @reference   LeetCode 1650. Lowest Common Ancestor of a Binary Tree III
 *              https://zhenchaogan.gitbook.io/leetcode-solution/leetcode-1650-lowest-common-ancestor-of-a-binary-tree-iii
 *
 * Given two nodes of a binary tree p and q, return their lowest common ancestor (LCA).
 * Each node will have a reference to its parent node.
 *
 * @note    This is essentially the same as Intersection of Two Linked Lists.
 */


template <typename LCA, typename... Args>
inline constexpr auto
TestLowestCommonAncestor(const LCA lowest_common_ancestor,
                         const BinaryTree::Node::PointerType root,
                         Args &&...args) {
    const auto LCA_node = lowest_common_ancestor(root, std::forward<Args>(args)...);
    if (LCA_node) {
        return LCA_node->value;
    } else {
        return -1;
    }
}


auto LowestCommonAncestor_MayNotExist_Helper(const BinaryTree::Node::PointerType node,
                                             const BinaryTree::Node::ValueType x,
                                             const BinaryTree::Node::ValueType y,
                                             bool &x_exist, bool &y_exist) {
    if (not node) {
        return node;
    }
    if (node->value == x) {
        x_exist = true;
        return node;
    }
    if (node->value == y) {
        y_exist = true;
        return node;
    }

    const auto left_LCA =
        LowestCommonAncestor_MayNotExist_Helper(node->left, x, y, x_exist, y_exist);
    const auto right_LCA =
        LowestCommonAncestor_MayNotExist_Helper(node->right, x, y, x_exist, y_exist);

    if (left_LCA and right_LCA) {
        return node;
    }

    return left_LCA ? left_LCA : right_LCA;
}

inline auto
LowestCommonAncestor_MayNotExist(const BinaryTree::Node::PointerType root,
                                 const BinaryTree::Node::ValueType x,
                                 const BinaryTree::Node::ValueType y) {
    bool x_exist = false;
    bool y_exist = false;
    const auto candidate =
        LowestCommonAncestor_MayNotExist_Helper(root, x, y, x_exist, y_exist);

    if ((x_exist and y_exist) or
        (x_exist and BinaryTreeSearch_Preorder(candidate, y)) or
        (y_exist and BinaryTreeSearch_Preorder(candidate, x))) {
        return candidate;
    }
    return BinaryTree::Node::PointerType{};
}


/**
 * @reference   Least Common Ancestor of any number of nodes in Binary Tree
 *              https://www.geeksforgeeks.org/least-common-ancestor-of-any-number-of-nodes-in-binary-tree/
 * @reference   1676 - Lowest Common Ancestor of a Binary Tree IV
 *              https://leetcode.ca/2020-07-02-1676-Lowest-Common-Ancestor-of-a-Binary-Tree-IV/
 *
 * Given the root of a binary tree and an array of TreeNode objects nodes, return the
 * lowest common ancestor (LCA) of all the nodes in nodes. All the nodes will exist in
 * the tree, and all values of the tree’s nodes are unique.
 */
std::size_t
LowestCommonAncestorOfNodes(const BinaryTree::Node::PointerType node,
                            const BinaryTree::ArrayType &keys,
                            BinaryTree::ArrayType &ancestors) {
    if (not node) {
        return 0;
    }

    const auto matching_nodes =
        (std::find(keys.cbegin(), keys.cend(), node->value) != keys.cend()) +
        LowestCommonAncestorOfNodes(node->left, keys, ancestors) +
        LowestCommonAncestorOfNodes(node->right, keys, ancestors);

    if (matching_nodes == keys.size()) {
        ancestors.push_back(node->value);
    }

    return matching_nodes;
}

inline auto
LowestCommonAncestorOfNodes(const BinaryTree::Node::PointerType root,
                            const BinaryTree::ArrayType &keys) {
    BinaryTree::ArrayType ancestors;
    LowestCommonAncestorOfNodes(root, keys, ancestors);

    return ancestors.empty() ? -1 : ancestors.front();
}


auto LowestCommonAncestorOfNodes_AllExist(const BinaryTree::Node::PointerType node,
                                          const BinaryTree::ArrayType &keys) {
    if (not node or
        (std::find(keys.cbegin(), keys.cend(), node->value) != keys.cend())) {
        return node;
    }

    const auto left_LCA = LowestCommonAncestorOfNodes_AllExist(node->left, keys);
    const auto right_LCA = LowestCommonAncestorOfNodes_AllExist(node->right, keys);

    if (left_LCA and right_LCA) {
        return node;
    }

    return left_LCA ? left_LCA : right_LCA;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleBST().GetRoot();


THE_BENCHMARK(LowestCommonAncestor_BST_Recursive, SAMPLE1, 1, 3);

SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLER1, 2,
            LowestCommonAncestor_BST_Recursive, SAMPLE1, 1, 3);
SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLER2, 2,
            LowestCommonAncestor_BST_Recursive, SAMPLE1, 2, 3);
SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLER3, 4,
            LowestCommonAncestor_BST_Recursive, SAMPLE1, 3, 5);


THE_BENCHMARK(LowestCommonAncestor_BST_Iterative, SAMPLE1, 1, 3);

SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLEI1, 2,
            LowestCommonAncestor_BST_Iterative, SAMPLE1, 1, 3);
SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLEI2, 2,
            LowestCommonAncestor_BST_Iterative, SAMPLE1, 2, 3);
SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLEI3, 4,
            LowestCommonAncestor_BST_Iterative, SAMPLE1, 3, 5);


THE_BENCHMARK(LowestCommonAncestor_CommonPath, SAMPLE1, 1, 3);

SIMPLE_TEST(LowestCommonAncestor_CommonPath, TestSAMPLE1, 2, SAMPLE1, 1, 3);
SIMPLE_TEST(LowestCommonAncestor_CommonPath, TestSAMPLE2, 2, SAMPLE1, 2, 3);
SIMPLE_TEST(LowestCommonAncestor_CommonPath, TestSAMPLE3, 4, SAMPLE1, 3, 5);
SIMPLE_TEST(LowestCommonAncestor_CommonPath, TestSAMPLE4, -1, SAMPLE1, 3, 9);


THE_BENCHMARK(LowestCommonAncestor_SingleTraversal, SAMPLE1, 1, 3);

SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLES1, 2,
            LowestCommonAncestor_SingleTraversal, SAMPLE1, 1, 3);
SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLES2, 2,
            LowestCommonAncestor_SingleTraversal, SAMPLE1, 2, 3);
SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLES3, 4,
            LowestCommonAncestor_SingleTraversal, SAMPLE1, 3, 5);


THE_BENCHMARK(LowestCommonAncestor_Iterative_Backtracking, SAMPLE1, 1, 3);

SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLESi1, 2,
            LowestCommonAncestor_Iterative_Backtracking, SAMPLE1, 1, 3);
SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLESi2, 2,
            LowestCommonAncestor_Iterative_Backtracking, SAMPLE1, 2, 3);
SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLESi3, 4,
            LowestCommonAncestor_Iterative_Backtracking, SAMPLE1, 3, 5);


THE_BENCHMARK(LowestCommonAncestor_MayNotExist, SAMPLE1, 1, 3);

SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLE1M, 2,
            LowestCommonAncestor_MayNotExist, SAMPLE1, 1, 3);
SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLE2M, 2,
            LowestCommonAncestor_MayNotExist, SAMPLE1, 2, 3);
SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLE3M, 4,
            LowestCommonAncestor_MayNotExist, SAMPLE1, 3, 5);
SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLE4M, -1,
            LowestCommonAncestor_MayNotExist, SAMPLE1, 3, 9);


const BinaryTree::ArrayType SAMPLE1K = {1, 2, 3};
const BinaryTree::ArrayType SAMPLE2K = {2, 3};
const BinaryTree::ArrayType SAMPLE3K = {3, 5};
const BinaryTree::ArrayType SAMPLE4K = {1, 3};
const BinaryTree::ArrayType SAMPLE5K = {2, 3, 4};
const BinaryTree::ArrayType SAMPLE6K = {1, 3, 5};
const BinaryTree::ArrayType SAMPLE7K = {1, 3, 5, 99};


THE_BENCHMARK(LowestCommonAncestorOfNodes, SAMPLE1, SAMPLE1K);

SIMPLE_TEST(LowestCommonAncestorOfNodes, TestSAMPLE1, 2, SAMPLE1, SAMPLE1K);
SIMPLE_TEST(LowestCommonAncestorOfNodes, TestSAMPLE2, 2, SAMPLE1, SAMPLE2K);
SIMPLE_TEST(LowestCommonAncestorOfNodes, TestSAMPLE3, 4, SAMPLE1, SAMPLE3K);
SIMPLE_TEST(LowestCommonAncestorOfNodes, TestSAMPLE4, 2, SAMPLE1, SAMPLE4K);
SIMPLE_TEST(LowestCommonAncestorOfNodes, TestSAMPLE5, 4, SAMPLE1, SAMPLE5K);
SIMPLE_TEST(LowestCommonAncestorOfNodes, TestSAMPLE6, 4, SAMPLE1, SAMPLE6K);
SIMPLE_TEST(LowestCommonAncestorOfNodes, TestSAMPLE7, -1, SAMPLE1, SAMPLE7K);


THE_BENCHMARK(LowestCommonAncestorOfNodes_AllExist, SAMPLE1, SAMPLE1K);

SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLE1A, 2,
            LowestCommonAncestorOfNodes_AllExist, SAMPLE1, SAMPLE1K);
SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLE2A, 2,
            LowestCommonAncestorOfNodes_AllExist, SAMPLE1, SAMPLE2K);
SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLE3A, 4,
            LowestCommonAncestorOfNodes_AllExist, SAMPLE1, SAMPLE3K);
SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLE4A, 2,
            LowestCommonAncestorOfNodes_AllExist, SAMPLE1, SAMPLE4K);
SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLE5A, 4,
            LowestCommonAncestorOfNodes_AllExist, SAMPLE1, SAMPLE5K);
SIMPLE_TEST(TestLowestCommonAncestor, TestSAMPLE6A, 4,
            LowestCommonAncestorOfNodes_AllExist, SAMPLE1, SAMPLE6K);
