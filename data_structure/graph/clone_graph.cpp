#include "common_header.h"


namespace {

using ArrayType = std::set<std::pair<int, int>>;

/** Clone Graph
 *
 * @reference   https://leetcode.com/problems/clone-graph/
 *
 * Given a reference of a node in a connected undirected graph.
 * Return a deep copy (clone) of the graph.
 * Each node in the graph contains a value (int) and a list (List[Node]) of its neighbors.
 *  class Node {
 *      public int val;
 *      public List<Node> neighbors;
 *  }
 * Test case format:
 * For simplicity, each node's value is the same as the node's index (1-indexed). For
 * example, the first node with val == 1, the second node with val == 2, and so on. The
 * graph is represented in the test case using an adjacency list.
 * An adjacency list is a collection of unordered lists used to represent a finite graph.
 * Each list describes the set of neighbors of a node in the graph.
 * The given node will always be the first node with val = 1. You must return the copy of
 * the given node as a reference to the cloned graph.
 * Node.val is unique for each node.
 * There are no repeated edges and no self-loops in the graph.
 * The Graph is connected and all nodes can be visited starting from the given node.
 */
struct GraphNode {
    using ValueType = int;
    using PointerType = std::shared_ptr<GraphNode>;

    std::vector<PointerType> neighbors;
    ValueType value{};

    explicit GraphNode(const ValueType v) : value(v) {}
};

GraphNode::PointerType
CloneGraph(const GraphNode::PointerType node,
           std::unordered_map<int, GraphNode::PointerType> &visited) {
    auto iter = visited.find(node->value);
    if (iter == visited.cend()) {
        const auto new_node = std::make_shared<GraphNode>(node->value);
        iter = visited.emplace(node->value, new_node).first;
        for (const auto neighbor : node->neighbors) {
            new_node->neighbors.push_back(CloneGraph(neighbor, visited));
        }
    }

    return iter->second;
}

inline auto CloneGraph(const GraphNode::PointerType node) {
    if (not node) {
        return node;
    }

    std::unordered_map<int, GraphNode::PointerType> visited;
    return CloneGraph(node, visited);
}

void deleteGraph(const GraphNode::PointerType node, std::unordered_set<int> &visited) {
    if (visited.insert(node->value).second) {
        for (const auto neighbor : node->neighbors) {
            deleteGraph(neighbor, visited);
        }
        node->neighbors.clear();
    }
}

inline void deleteGraph(const GraphNode::PointerType node) {
    if (node) {
        std::unordered_set<int> visited;
        deleteGraph(node, visited);
    }
}

auto buildGraph(const ArrayType &original) {
    std::map<int, GraphNode::PointerType> nodes;
    for (const auto [from, to] : original) {
        const auto from_iter = nodes.emplace(from, std::make_shared<GraphNode>(from)).first;
        const auto to_iter = nodes.emplace(to, std::make_shared<GraphNode>(to)).first;
        from_iter->second->neighbors.push_back(to_iter->second);
    }

    return nodes.cbegin()->second;
}

void traverseGraph(const GraphNode::PointerType node, std::unordered_set<int> &visited,
                   ArrayType &result) {
    if (visited.insert(node->value).second) {
        for (const auto neighbor : node->neighbors) {
            result.emplace(node->value, neighbor->value);
            traverseGraph(neighbor, visited, result);
        }
    }
}

auto testCloneGraph(const ArrayType &original) {
    const auto original_root = buildGraph(original);
    const auto new_root = CloneGraph(original_root);

    ArrayType cloned;
    std::unordered_set<int> visited;
    traverseGraph(new_root, visited, cloned);

    deleteGraph(original_root);
    deleteGraph(new_root);

    return original == cloned;
}


/**
 * @reference   Copy List with Random Pointer
 *              https://leetcode.com/problems/copy-list-with-random-pointer/
 *
 * A linked list of length n is given such that each node contains an additional random
 * pointer, which could point to any node in the list, or null.
 * Construct a deep copy of the list. The deep copy should consist of exactly n brand new
 * nodes, where each new node has its value set to the value of its corresponding original
 * node. Both the next and random pointer of the new nodes should point to new nodes in
 * the copied list such that the pointers in the original list and copied list represent
 * the same list state. None of the pointers in the new list should point to nodes in the
 * original list.
 * For example, if there are two nodes X and Y in the original list, where X.random --> Y,
 * then for the corresponding two nodes x and y in the copied list, x.random --> y.
 * Return the head of the copied linked list.
 * The linked list is represented in the input/output as a list of n nodes. Each node is
 * represented as a pair of [val, random_index] where:
 *  val: an integer representing Node.val
 *  random_index: the index of the node (range from 0 to n-1) that the random pointer
 *      points to, or null if it does not point to any node.
 * Your code will only be given the head of the original linked list.
 */
struct NodeWithRandom {
    using ValueType = int;
    using PointerType = std::shared_ptr<NodeWithRandom>;

    ValueType value;
    PointerType next;
    PointerType::weak_type random;

    constexpr explicit NodeWithRandom(const ValueType v = 0): value(v) {
    }
};

auto CloneList(const NodeWithRandom::PointerType head) {
    if (not head) {
        return head;
    }

    for (auto curr = head; curr; curr = curr->next->next) {
        const auto new_node = std::make_shared<NodeWithRandom>(curr->value);
        new_node->next = curr->next;
        curr->next = new_node;
    }

    const auto new_head = head->next;
    for (auto curr = head; curr; curr = curr->next->next) {
        const auto random = curr->random.lock();
        if (random) {
            curr->next->random = random->next;
        }
    }

    for (auto tail = head; tail; tail = tail->next) {
        const auto new_tail = tail->next;
        tail->next = new_tail->next;
        if (new_tail->next) {
            new_tail->next = new_tail->next->next;
        }
    }

    return new_head;
}

auto buildListWithRandom(const ArrayType &original) {
    std::vector<NodeWithRandom::PointerType> nodes;
    for (const auto [v, _] : original) {
        nodes.push_back(std::make_shared<NodeWithRandom>(v));
    }

    std::size_t i = 0;
    for (const auto [_, random_index] : original) {
        if (i < nodes.size() - 1) {
            nodes[i]->next = nodes[i + 1];
        }
        if (random_index >= 0) {
            nodes[i]->random = nodes[random_index];
        }
        ++i;
    }

    return nodes.front();
}

auto traverseList(const NodeWithRandom::PointerType head) {
    int i = 0;
    std::unordered_map<int, int> nodes;
    for (auto curr = head; curr; curr = curr->next) {
        nodes[curr->value] = i++;
    }

    ArrayType result;
    for (auto curr = head; curr; curr = curr->next) {
        const auto random = curr->random.lock();
        const auto random_index = random ? nodes[random->value] : -1;
        result.emplace(curr->value, random_index);
    }

    return result;
}

inline auto testCloneList(const ArrayType &original) {
    const auto head = buildListWithRandom(original);
    const auto cloned_head = CloneList(head);

    const auto cloned = traverseList(cloned_head);
    return cloned == original;
}

}//namespace


const ArrayType SAMPLE1 = {{1, 2}, {2, 3}, {3, 4}, {4, 1}};


THE_BENCHMARK(testCloneGraph, SAMPLE1);

SIMPLE_TEST(testCloneGraph, TestSAMPLE1, true, SAMPLE1);


const ArrayType SAMPLE1L = {{1, -1}, {2, 0}, {3, 2}, {4, 1}};


THE_BENCHMARK(testCloneList, SAMPLE1L);

SIMPLE_TEST(testCloneList, TestSAMPLE1, true, SAMPLE1L);
