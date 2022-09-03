#include "common_header.h"

#include "trie.h"


namespace {

using ArrayType = std::vector<std::string_view>;

/** Stream of Characters
 *
 * @reference   https://leetcode.com/problems/stream-of-characters/
 *
 * Design an algorithm that accepts a stream of characters and checks if a suffix of these characters is
 * a string of a given array of strings words.
 * For example, if words = ["abc", "xyz"] and the stream added the four characters (one by one) 'a',
 * 'x', 'y', and 'z', your algorithm should detect that the suffix "xyz" of the characters "axyz"
 * matches "xyz" from words.
 * Implement the StreamChecker class:
 *  StreamChecker(String[] words) Initializes the object with the strings array words.
 *  boolean query(char letter) Accepts a new character from the stream and returns true if any non-empty
 *      suffix from the stream forms a word that is in words.
 */
class StreamChecker_WaitingList {
    using Node = TrieNode<bool>;

    Node root;
    std::vector<Node::PointerType> waiting_list;

public:
    StreamChecker_WaitingList(const ArrayType &words) noexcept {
        for (const auto w : words) {
            TrieInsert(root, w, true);
        }
    }

    auto query(const char letter) noexcept {
        std::vector<Node::PointerType> new_waiting;

        const auto index = Node::ToIndex(letter);
        bool result = false;
        for (const auto &n : waiting_list) {
            const auto child = n->children[index];
            if (child) {
                new_waiting.push_back(child);
                result = result or child->value;
            }
        }

        const auto child = root.children[index];
        if (child) {
            new_waiting.push_back(child);
            result = result or child->value;
        }

        std::swap(waiting_list, new_waiting);

        return result;
    }
};


class StreamChecker_Reverse {
    using Node = TrieNode<bool>;

    Node root;
    std::size_t max_length = 0;
    std::list<char> stream;

public:
    StreamChecker_Reverse(const ArrayType &words) noexcept {
        for (const auto w : words) {
            TrieInsert(root, w.crbegin(), w.crend(), true);
            max_length = std::max(max_length, w.size());
        }
    }

    auto query(const char letter) noexcept {
        if (stream.size() >= max_length) {
            stream.pop_back();
        }
        stream.push_front(letter);

        const auto *current = &root;
        for (const auto c : stream) {
            const auto index = Node::ToIndex(c);
            const auto child = current->children[index];
            if (not child) {
                return false;
            }

            if (child->value) {
                return true;
            }

            current = child.get();
        }

        return current->value;
    }
};


template<typename StreamChecker>
auto testStreamChecker(const ArrayType &words, const std::string_view queries) {
    StreamChecker sc {words};

    std::vector<bool> result;
    for (const auto c : queries) {
        result.push_back(sc.query(c));
    }

    return result;
}

constexpr auto testStreamChecker_WaitingList = testStreamChecker<StreamChecker_WaitingList>;
constexpr auto testStreamChecker_Reverse = testStreamChecker<StreamChecker_Reverse>;

} //namespace


const ArrayType SAMPLE1 = {"cd", "f", "kl"};
const std::vector EXPECTED1 = {
    false, false, false, true, false, true, false, false, false, false, false, true};


THE_BENCHMARK(testStreamChecker_WaitingList, SAMPLE1, "abcdefghijkl");

SIMPLE_TEST(testStreamChecker_WaitingList, TestSAMPLE1, EXPECTED1, SAMPLE1, "abcdefghijkl");


THE_BENCHMARK(testStreamChecker_Reverse, SAMPLE1, "abcdefghijkl");

SIMPLE_TEST(testStreamChecker_Reverse, TestSAMPLE1, EXPECTED1, SAMPLE1, "abcdefghijkl");
