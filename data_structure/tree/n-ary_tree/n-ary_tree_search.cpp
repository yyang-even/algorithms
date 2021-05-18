#include "common_header.h"

#include "n-ary_tree_search.h"


namespace {

constexpr auto NArySearch_Array =
    Search<n_ary_tree::array_representation::Node::PointerType>;

constexpr auto NArySearch_Sibling =
    Search<n_ary_tree::child_sibling_representation::Node::PointerType>;

}//namespace


const auto SAMPLE1 = MakeTheSampleTree<n_ary_tree::array_representation::Node>();
const auto SAMPLE2 =
    MakeTheSampleTree<n_ary_tree::child_sibling_representation::Node>();


THE_BENCHMARK(NArySearch_Array, SAMPLE1, 9);

SIMPLE_TEST(NArySearch_Array, TestSAMPLE0, nullptr, SAMPLE1, 0);
SIMPLE_TEST(NArySearch_Array, TestSAMPLE1, SAMPLE1, SAMPLE1, 1);
SIMPLE_TEST(NArySearch_Array, TestSAMPLE2, SAMPLE1->children[2], SAMPLE1, 4);
SIMPLE_TEST(NArySearch_Array, TestSAMPLE3, SAMPLE1->children[0]->children[1],
            SAMPLE1, 7);


THE_BENCHMARK(NArySearch_Sibling, SAMPLE2, 9);

SIMPLE_TEST(NArySearch_Sibling, TestSAMPLE0, nullptr, SAMPLE2, 0);
SIMPLE_TEST(NArySearch_Sibling, TestSAMPLE1, SAMPLE2, SAMPLE2, 1);
SIMPLE_TEST(NArySearch_Sibling, TestSAMPLE2,
            SAMPLE2->left_child->right_sibling->right_sibling, SAMPLE2, 4);
SIMPLE_TEST(NArySearch_Sibling, TestSAMPLE3,
            SAMPLE2->left_child->left_child->right_sibling, SAMPLE2, 7);
