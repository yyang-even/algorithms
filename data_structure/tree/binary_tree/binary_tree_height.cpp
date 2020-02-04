#include "common_header.h"

#include "binary_tree.h"


namespace {

/** Write a Program to Find the Maximum Depth or Height of a Tree
 *
 * @reference   https://www.geeksforgeeks.org/write-a-c-program-to-find-the-maximum-depth-or-height-of-a-tree/
 */
unsigned Height(const BinaryTree::Node::PointerType node) {
    if (node) {
        const auto left_height = Height(node->left);
        const auto right_height = Height(node->right);

        return std::max(left_height, right_height) + 1;
    }

    return 0;
}

}//namespace


const auto SAMPLE1 = MakeTheSampleTree().GetRoot();


SIMPLE_BENCHMARK(Height, SAMPLE1);

SIMPLE_TEST(Height, TestSAMPLE1, 3, SAMPLE1);
