#pragma once


void CloneBinaryTree(const BinaryTree::Node::PointerType source_node, BinaryTree::Node &new_node) {
    assert(source_node);

    if (source_node->left) {
        SetLeftChild(new_node, source_node->left->value);
        CloneBinaryTree(source_node->left, *(new_node.left));
    }

    if (source_node->right) {
        SetRightChild(new_node, source_node->right->value);
        CloneBinaryTree(source_node->right, *(new_node.right));
    }
}

auto CloneBinaryTree(const BinaryTree::Node::PointerType source_root) {
    if (source_root) {
        BinaryTree new_tree{source_root->value};
        CloneBinaryTree(source_root, *new_tree.GetRoot());
        return new_tree;
    }

    return BinaryTree{};
}
