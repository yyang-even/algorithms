#include "common_header.h"

#include "binary_search_tree.h"
#include "flatten_BST.h"

#include "data_structure/tree/binary_tree/binary_tree_traversals.h"
#include "data_structure/tree/binary_tree/clone_binary_tree.h"
#include "data_structure/tree/binary_tree/compare_binary_trees.h"


namespace {

using QueueType = std::queue<BinaryTree::Node::PointerType>;

/** Convert BST to Min Heap
 *
 * @reference   Convert BST to Min Heap
 *              https://www.geeksforgeeks.org/convert-bst-min-heap/
 *
 * Given a binary search tree which is also a complete binary tree. The problem is to
 * convert the given BST into a Min Heap with the condition that all the values in the
 * left subtree of a node should be less than all the values in the right subtree of the
 * node. This condition is applied on all the nodes in the so converted Min Heap.
 *
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 5.
 *
 * You are given a set of integers in an unordered binary tree. Use an array sorting
 * routine to transform the tree into a heap that uses a balanced binary tree as its
 * underling data structure.
 */
auto ToMinHeap(const BinaryTree::Node::PointerType root) {
    BinaryTree::ArrayType inorder_array;
    InorderTraversal_Recursive(root, inorder_array);

    assert(std::is_sorted(inorder_array.cbegin(), inorder_array.cend()));

    auto cbegin = inorder_array.cbegin();
    LevelOrderTraversal_LevelAware_Helper(root, [&cbegin](auto & node) {
        node.value = *(cbegin++);
        return true;
    });

    return root;
}


/**
 * @reference   Convert BST to Max Heap
 *              https://www.geeksforgeeks.org/convert-bst-to-max-heap/
 */


/**
 * @reference   Convert BST into a Min-Heap without using array
 *              https://www.geeksforgeeks.org/in-place-convert-bst-into-a-min-heap/
 */
inline auto NextChild(BinaryTree::Node::PointerType &head, QueueType &parent_nodes) {
    assert(head);

    const auto child = head;
    head = head->right;
    child->right = nullptr;
    parent_nodes.push(child);

    return child;
}

auto SortedListToHeap(BinaryTree::Node::PointerType head) {
    const auto root = head;

    if (head) {
        QueueType parent_nodes;
        NextChild(head, parent_nodes);

        while (head) {
            const auto parent = parent_nodes.front();
            parent_nodes.pop();

            parent->left = NextChild(head, parent_nodes);

            if (head) {
                parent->right = NextChild(head, parent_nodes);
            }
        }
    }

    return root;
}

inline auto ToMinHeap_InPlace(const BinaryTree::Node::PointerType root) {
    const auto sorted_list =
        FlattenBSTtoSortedList(root, FlattenBSTtoSortedList_Increasing);

    return SortedListToHeap(sorted_list);
}

}


/**
 *     1
 *    / \
 *   2   3
 *  / \
 * 4   5
 */
static inline auto MakeTheExpectedMinHeap() {
    const BinaryTree binary_tree{1};
    auto &root = *binary_tree.GetRoot();
    auto &left_child = *SetLeftChild(root, 2);
    SetRightChild(root, 3);
    SetLeftChild(left_child, 4);
    SetRightChild(left_child, 5);

    return binary_tree;
}


const auto SAMPLE = MakeTheSampleBST().GetRoot();
const auto EXPECTED = MakeTheExpectedMinHeap().GetRoot();


THE_BENCHMARK(ToMinHeap, CloneBinaryTree(SAMPLE).GetRoot());

SIMPLE_TEST(areIdenticalTrees, TestSAMPLE1, true,
            EXPECTED, ToMinHeap(CloneBinaryTree(SAMPLE).GetRoot()));


THE_BENCHMARK(ToMinHeap_InPlace, CloneBinaryTree(SAMPLE).GetRoot());

SIMPLE_TEST(areIdenticalTrees, TestSAMPLE2, true,
            EXPECTED, ToMinHeap_InPlace(CloneBinaryTree(SAMPLE).GetRoot()));
