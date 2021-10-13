#pragma once


/**
 * @reference   Trie | (Insert and Search)
 *              https://www.geeksforgeeks.org/trie-insert-and-search/
 * @reference   Trie Data Structure using smart pointer and OOP in C++
 *              https://www.geeksforgeeks.org/trie-data-structure-using-smart-pointer-and-oop-in-c/
 * @reference   Advantages of Trie Data Structure
 *              https://www.geeksforgeeks.org/advantages-trie-data-structure/
 *
 * @reference   Implement Trie (Prefix Tree)
 *              https://leetcode.com/problems/implement-trie-prefix-tree/
 *
 * A trie (pronounced as "try") or prefix tree is a tree data structure used to efficiently
 * store and retrieve keys in a dataset of strings. There are various applications of this
 * data structure, such as autocomplete and spellchecker. Implement the Trie class:
 *  Trie() Initializes the trie object.
 *  void insert(String word) Inserts the string word into the trie.
 *  boolean search(String word) Returns true if the string word is in the trie (i.e., was
 *      inserted before), and false otherwise.
 *  boolean startsWith(String prefix) Returns true if there is a previously inserted string
 *      word that has the prefix prefix, and false otherwise.
 * word and prefix consist only of lowercase English letters.
 */
template <typename T>
struct TrieNode {
    using ValueType = T;
    using PointerType = std::shared_ptr<TrieNode>;

    std::vector<PointerType> children;
    T value = {};

    explicit TrieNode(const std::size_t size = 26): children(size, PointerType{}) {}

    auto Empty() const {
        for (const auto &kid : children) {
            if (kid) {
                return false;
            }
        }

        return true;
    }

    static constexpr std::size_t ToIndex(const char c) {
        return c - 'a';
    }

    static constexpr char ToChar(const std::size_t i) {
        return i + 'a';
    }
};


template <typename NodeType>
void TrieInsert(NodeType &root, const std::string_view key,
                const typename NodeType::ValueType value) {
    auto *current = &root;

    for (const auto c : key) {
        const auto index = NodeType::ToIndex(c);
        if (not current->children[index]) {
            current->children[index].reset(new NodeType{root.children.size()});
        }

        current = current->children[index].get();
    }

    current->value = value;
}


template <typename NodeType>
typename NodeType::ValueType
TrieGet(const NodeType &root, const std::string_view key) {
    const auto *current = &root;

    for (const auto c : key) {
        const auto index = NodeType::ToIndex(c);

        if (not current->children[index]) {
            return {};
        }
        current = current->children[index].get();
    }

    return current->value;
}


class Trie {
public:
    using Node = TrieNode<bool>;

    explicit Trie(const std::size_t size = 26): root(size) {}


    void Insert(const std::string_view key) {
        TrieInsert(root, key, true);
    }


    /**
     * @reference   Insertion in a Trie recursively
     *              https://www.geeksforgeeks.org/insertion-in-a-trie-recursively/
     */
    void Insert_Recursive(const std::string_view key) {
        Insert_Recursive_Helper(&root, key, 0);
    }


    bool Search(const std::string_view key) const {
        return TrieGet(root, key);
    }


    /**
     * @reference   Search in a trie Recursively
     *              https://www.geeksforgeeks.org/search-in-a-trie-recursively/
     */
    auto Search_Recursive(const std::string_view key) const {
        return Search_Recursive_Helper(&root, key, 0);
    }


    /**
     * @reference   Trie | (Delete)
     *              https://www.geeksforgeeks.org/trie-delete/
     */
    void Delete(const std::string_view key) {
        DeleteHelper(&root, key);
    }


    template<typename Visitor>
    constexpr auto Visit(const Visitor visitor) const {
        return visitor(root);
    }

private:
    bool DeleteHelper(Node *node, const std::string_view key,
                      const std::size_t depth = 0) {
        if (not node) {
            return false;
        }

        if (depth == key.size()) {
            if (node->value) {
                node->value = false;
            }
        } else {
            const auto index = Node::ToIndex(key[depth]);
            if (DeleteHelper(node->children[index].get(), key, depth + 1)) {
                node->children[index].reset();
            }
        }

        return node->Empty() and not node->value;
    }


    void Insert_Recursive_Helper(Node *node, const std::string_view key,
                                 const std::size_t i) {
        if (i < key.size()) {
            const auto index = Node::ToIndex(key[i]);
            if (not node->children[index]) {
                node->children[index].reset(new Node{root.children.size()});
            }

            Insert_Recursive_Helper(node->children[index].get(), key, i + 1);
        } else {
            node->value = true;
        }
    }


    bool Search_Recursive_Helper(const Node *node, const std::string_view key,
                                 const std::size_t i) const {
        if (not node or i > key.size()) {
            return false;
        }

        if (node->value and i == key.size()) {
            return true;
        }

        const auto index = Node::ToIndex(key[i]);
        return Search_Recursive_Helper(node->children[index].get(), key, i + 1);
    }


    Node root;
};

template <typename Strings>
static inline constexpr auto BuildTrie(const Strings &keys) {
    Trie dictionary;

    for (const auto &one_key : keys) {
        dictionary.Insert(one_key);
    }

    return dictionary;
}


/**
 * @reference   Implement a Dictionary using Trie
 *              https://www.geeksforgeeks.org/implement-a-dictionary-using-trie/
 * @reference   Data Structure for Dictionary and Spell Checker?
 *              https://www.geeksforgeeks.org/data-structure-dictionary-spell-checker/
 */


/**
 * @reference   Trie memory optimization using hash map
 *              https://www.geeksforgeeks.org/trie-memory-optimization-using-hash-map/
 */


/**
 * @reference   Frequency of a string in an array of strings
 *              https://www.geeksforgeeks.org/frequency-of-a-string-in-an-array-of-strings/
 *
 * You are given a collection of strings and a list of queries. For every query there is
 * a string given. We need to print the number of times the given string occurs in the
 * collection of strings.
 *
 * @reference   Calculate the frequency of each word in the given string
 *              https://www.geeksforgeeks.org/calculate-the-frequency-of-each-word-in-the-given-string/
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 17.9.
 *
 * Design a method to find the frequency of occurrences of any given word in a book.
 */
