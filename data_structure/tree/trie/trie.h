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
    };


    Trie(const std::size_t size = 26): root(size) {}


    void Insert(const std::string &key) {
        auto *current = &root;

        for (const auto c : key) {
            const auto index = c - 'a';
            if (not current->children[index]) {
                current->children[index].reset(new Node{root.children.size()});
            }

            current = current->children[index].get();
        }

        current->isEndOfWord = true;
    }


    auto Search(const std::string &key) const {
        const auto *current = &root;

        for (const auto c : key) {
            const auto index = c - 'a';

            if (not current->children[index]) {
                return false;
            }
            current = current->children[index].get();
        }

        return current and current->isEndOfWord;
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
            const auto index = key[depth] - 'a';
            if (DeleteHelper(node->children[index].get(), key, depth + 1)) {
                node->children[index].reset();
            }
        }

        return node->Empty() and not node->isEndOfWord;
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
