#include "common_header.h"

#include "data_structure/tree/binary_tree/binary_tree.h"


namespace {

using ArrayType = std::vector<int>;

struct Data {
    std::string::value_type character{};
    ArrayType::value_type frequency{};
};

using NodeType = BinaryTreeNode<Data>;
using CodesMap = std::unordered_map<std::string::value_type, std::string>;


inline auto operator>(const NodeType::PointerType lhs,
                      const NodeType::PointerType rhs) {
    return lhs->value.frequency > rhs->value.frequency;
}

/** Huffman Coding
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 16.3.
 * @reference   Huffman Coding | Greedy Algo-3
 *              https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
 * @reference   Huffman Coding using Priority Queue
 *              https://www.geeksforgeeks.org/huffman-coding-using-priority-queue/
 */
auto BuildHuffmanTree(const std::string &characters, const ArrayType &frequencies) {
    assert(not characters.empty());
    assert(characters.size() == frequencies.size());

    std::priority_queue<NodeType::PointerType, std::vector<NodeType::PointerType>, std::greater<NodeType::PointerType>>
            min_frequency_queue;
    for (std::string::size_type i = 0; i < characters.size(); ++i) {
        min_frequency_queue.push(std::make_shared<NodeType>(Data{characters[i], frequencies[i]}));
    }

    while (min_frequency_queue.size() > 1) {
        auto left_child = min_frequency_queue.top();
        min_frequency_queue.pop();

        auto right_child = min_frequency_queue.top();
        min_frequency_queue.pop();

        auto new_node = std::make_shared<NodeType>(Data{'\0', left_child->value.frequency + right_child->value.frequency});
        new_node->left = std::move(left_child);
        new_node->right = std::move(right_child);
        min_frequency_queue.push(std::move(new_node));
    }

    return min_frequency_queue.top();
}

void HuffmanCodes(const NodeType::PointerType node, const std::string &prefix,
                  CodesMap &codes) {
    bool is_leaf = true;

    if (node->left) {
        is_leaf = false;
        HuffmanCodes(node->left, prefix + '0', codes);
    }

    if (node->right) {
        is_leaf = false;
        HuffmanCodes(node->right, prefix + '1', codes);
    }

    if (is_leaf) {
        codes[node->value.character] = prefix;
    }
}

inline auto
HuffmanCoding(const std::string &characters, const ArrayType &frequencies) {
    const auto huffman_tree = BuildHuffmanTree(characters, frequencies);

    CodesMap huffman_codes;
    HuffmanCodes(huffman_tree, "", huffman_codes);

    return huffman_codes;
}

}//namespace


const auto SAMPLE1_CHAR = "abcdef";
const ArrayType SAMPLE1_FREQ = {45, 13, 12, 16, 9, 5};
const CodesMap EXPECTED1 = {{'a', "0"}, {'b', "101"}, {'c', "100"}, {'d', "111"}, {'e', "1101"}, {'f', "1100"}};


THE_BENCHMARK(HuffmanCoding, SAMPLE1_CHAR, SAMPLE1_FREQ);

SIMPLE_TEST(HuffmanCoding, TestSAMPLE0, EXPECTED1, SAMPLE1_CHAR, SAMPLE1_FREQ);
