#include "common_header.h"

#include "n-ary_tree_search.h"


namespace {

/**
 * @reference   Left-Child Right-Sibling Representation of Tree
 *              https://www.geeksforgeeks.org/left-child-right-sibling-representation-tree/
 */
inline auto
KthChild(const n_ary_tree::array_representation::Node::PointerType root,
         const n_ary_tree::array_representation::Node::ValueType x, const std::size_t k) {
    const auto parent = Search(root, x);
    if (parent and parent->children.size() > k) {
        return parent->children[k]->value;
    }

    return -1;
}


auto KthChild(const n_ary_tree::child_sibling_representation::Node::PointerType root,
              const n_ary_tree::child_sibling_representation::Node::ValueType x, std::size_t k) {
    auto node = Search(root, x);
    if (node) {
        for (node = node->left_child; node and k; node = node->right_sibling, --k);
    }

    return node ? node->value : -1;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleTree<n_ary_tree::array_representation::Node>();
const auto SAMPLE2 =
    MakeTheSampleTree<n_ary_tree::child_sibling_representation::Node>();


SIMPLE_BENCHMARK(KthChild, Sample1, SAMPLE1, 1, 2);

SIMPLE_TEST(KthChild, TestSAMPLE10, -1, SAMPLE1, 0, 0);
SIMPLE_TEST(KthChild, TestSAMPLE11, 2, SAMPLE1, 1, 0);
SIMPLE_TEST(KthChild, TestSAMPLE12, 4, SAMPLE1, 1, 2);
SIMPLE_TEST(KthChild, TestSAMPLE13, 5, SAMPLE1, 1, 3);
SIMPLE_TEST(KthChild, TestSAMPLE14, -1, SAMPLE1, 1, 9);


SIMPLE_BENCHMARK(KthChild, Sample2, SAMPLE2, 1, 2);

SIMPLE_TEST(KthChild, TestSAMPLE20, -1, SAMPLE2, 0, 0);
SIMPLE_TEST(KthChild, TestSAMPLE21, 2, SAMPLE2, 1, 0);
SIMPLE_TEST(KthChild, TestSAMPLE22, 4, SAMPLE2, 1, 2);
SIMPLE_TEST(KthChild, TestSAMPLE23, 5, SAMPLE2, 1, 3);
SIMPLE_TEST(KthChild, TestSAMPLE24, -1, SAMPLE2, 1, 9);
