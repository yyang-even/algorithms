#pragma once


/** Write a Program to Find the Maximum Depth or Height of a Tree
 *
 * @reference   https://www.geeksforgeeks.org/write-a-c-program-to-find-the-maximum-depth-or-height-of-a-tree/
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 5.
 */
static inline unsigned Height_Recursive(const BinaryTree::Node::PointerType node) {
    if (node) {
        const auto left_height = Height_Recursive(node->left);
        const auto right_height = Height_Recursive(node->right);

        return std::max(left_height, right_height) + 1;
    }

    return 0;
}


static inline auto HeightOfLeftmostLeaf(BinaryTree::Node::PointerType node) {
    unsigned height = 0;
    for (; node; ++height, node = node->left);
    return height;
}
