#pragma once


/**
 * @reference   Trie | (Insert and Search)
 *              https://www.geeksforgeeks.org/trie-insert-and-search/
 * @reference   Trie Data Structure using smart pointer and OOP in C++
 *              https://www.geeksforgeeks.org/trie-data-structure-using-smart-pointer-and-oop-in-c/
 * @reference   Advantages of Trie Data Structure
 *              https://www.geeksforgeeks.org/advantages-trie-data-structure/
 */
class Trie {
public:
    struct Node {
        using PointerType = std::shared_ptr<Node>;

        std::vector<PointerType> children;
        bool isEndOfWord = false;

        Node(const std::size_t size): children(size, PointerType{}) {}

        auto Empty() const {
            for (const auto &kid : children) {
                if (kid) {
                    return false;
                }
            }

            return true;
        }

        static std::vector<PointerType>::size_type ToIndex(const char c) {
            return c - 'a';
        }

        static char ToChar(const std::vector<PointerType>::size_type i) {
            return i + 'a';
        }
    };


    Trie(const std::size_t size = 26): root(size) {}


    void Insert(const std::string &key) {
        auto *current = &root;

        for (const auto c : key) {
            const auto index = Node::ToIndex(c);
            if (not current->children[index]) {
                current->children[index].reset(new Node{root.children.size()});
            }

            current = current->children[index].get();
        }

        current->isEndOfWord = true;
    }


    /**
     * @reference   Insertion in a Trie recursively
     *              https://www.geeksforgeeks.org/insertion-in-a-trie-recursively/
     */
    void Insert_Recursive(const std::string &key) {
        Insert_Recursive_Helper(&root, key, 0);
    }


    auto Search(const std::string &key) const {
        const auto *current = &root;

        for (const auto c : key) {
            const auto index = Node::ToIndex(c);

            if (not current->children[index]) {
                return false;
            }
            current = current->children[index].get();
        }

        return current and current->isEndOfWord;
    }


    /**
     * @reference   Search in a trie Recursively
     *              https://www.geeksforgeeks.org/search-in-a-trie-recursively/
     */
    auto Search_Recursive(const std::string &key) const {
        return Search_Recursive_Helper(&root, key, 0);
    }


    /**
     * @reference   Trie | (Delete)
     *              https://www.geeksforgeeks.org/trie-delete/
     */
    void Delete(const std::string &key) {
        DeleteHelper(&root, key);
    }


    template<typename Visitor>
    auto Visit(const Visitor visitor) const {
        return visitor(root);
    }

private:
    bool DeleteHelper(Node *node, const std::string &key, const std::string::size_type depth = 0) {
        if (not node) {
            return false;
        }

        if (depth == key.size()) {
            if (node->isEndOfWord) {
                node->isEndOfWord = false;
            }
        } else {
            const auto index = Node::ToIndex(key[depth]);
            if (DeleteHelper(node->children[index].get(), key, depth + 1)) {
                node->children[index].reset();
            }
        }

        return node->Empty() and not node->isEndOfWord;
    }


    void Insert_Recursive_Helper(Node *node, const std::string &key, const std::string::size_type i) {
        if (i < key.size()) {
            const auto index = Node::ToIndex(key[i]);
            if (not node->children[index]) {
                node->children[index].reset(new Node{root.children.size()});
            }

            Insert_Recursive_Helper(node->children[index].get(), key, i + 1);
        } else {
            node->isEndOfWord = true;
        }
    }


    bool Search_Recursive_Helper(const Node *node, const std::string &key,
                                 const std::string::size_type i) const {
        if (not node or i > key.size()) {
            return false;
        }

        if (node->isEndOfWord and i == key.size()) {
            return true;
        }

        const auto index = Node::ToIndex(key[i]);
        return Search_Recursive_Helper(node->children[index].get(), key, i + 1);
    }


    Node root;
};


static inline auto BuildTrie(const std::vector<std::string> &keys) {
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
 */
