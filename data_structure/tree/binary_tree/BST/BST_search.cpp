#include "common_header.h"

#include "binary_search_tree.h"


namespace {

/** Binary Search Tree | Set 1 (Search and Insertion)
 *
 * @reference   https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
 */
auto BSTSearch(const BinaryTree::Node::PointerType node,
               const BinaryTree::Node::ValueType x) {
    if (not node) {
        return false;
    }
    if (node->value == x) {
        return true;
    }

    return node->value > x ? BSTSearch(node->left, x) : BSTSearch(node->right, x);
}

}//namespace


const auto SAMPLE1 = MakeTheSampleBST().GetRoot();


SIMPLE_BENCHMARK(BSTSearch, SAMPLE1, -1);
SIMPLE_BENCHMARK(BSTSearch, SAMPLE1, 1);

SIMPLE_TEST(BSTSearch, TestSAMPLE1, true, SAMPLE1, 4);
SIMPLE_TEST(BSTSearch, TestSAMPLE2, true, SAMPLE1, 1);
SIMPLE_TEST(BSTSearch, TestSAMPLE3, false, SAMPLE1, -1);
