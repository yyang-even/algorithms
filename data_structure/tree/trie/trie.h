#pragma once


/**
 * @reference   Trie | (Insert and Search)
 *              https://www.geeksforgeeks.org/trie-insert-and-search/
 */
class Trie {
    struct Node {
        using PointerType = std::shared_ptr<Node>;

        std::vector<PointerType> children;
        bool isEndOfWord = false;

        Node(const std::size_t size): children(size, PointerType{}) {}
    };

public:
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

private:
    Node root;
};
