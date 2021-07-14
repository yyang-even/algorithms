#pragma once


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 21.
 * @reference   Disjoint Set (Or Union-Find) | Set 1 (Detect Cycle in an Undirected Graph)
 *              https://www.geeksforgeeks.org/union-find/
 * @reference   Union-Find Algorithm | Set 2 (Union By Rank and Path Compression)
 *              https://www.geeksforgeeks.org/union-find-algorithm-set-2-union-by-rank/
 * @reference   Union-Find Algorithm | (Union By Rank and Find by Optimized Path Compression)
 *              https://www.geeksforgeeks.org/union-find-algorithm-union-rank-find-optimized-path-compression/
 *
 * @reference   Disjoint Set Data Structures
 *              https://www.geeksforgeeks.org/disjoint-set-data-structures/
 * @reference   DISJOINT-SET DATA STRUCTURES
 *              https://www.topcoder.com/thrive/articles/Disjoint-set%20Data%20Structures
 *
 * In a room are N persons, and we will define two persons are friends if they are
 * directly or indirectly friends. If A is a friend with B, and B is a friend with C,
 * then A is a friend of C too. A group of friends is a group of persons where any two
 * persons in the group are friends. Given the list of persons that are directly friends
 * find the number of groups of friends and the number of persons in each group. For
 * example N = 5 and the list of friends is: 1-2, 5-4, and 5-1. Here is the figure of
 * the graph that represents the groups of friends. 1 and 2 are friends, then 5 and 4
 * are friends, and then 5 and 1 are friends, but 1 is friend with 2; therefore 5 and 2
 * are friends, etc.
 */
class DisjointSet_Array {
    struct SubSet {
        std::size_t parent = 0;
        int rank = 0;
    };
    std::vector<SubSet> m_subsets;

public:
    explicit DisjointSet_Array(const std::size_t size): m_subsets(size) {
        for (std::size_t i = 0; i < size; ++i) {
            m_subsets[i].parent = i;
        }
    }

    std::size_t Find(const std::size_t i) {
        assert(i < m_subsets.size());

        auto &parent_node = m_subsets[i];
        if (parent_node.parent != i) {
            parent_node.parent = Find(parent_node.parent);
        }
        return parent_node.parent;
    }

    void Union(const std::size_t x_index, const std::size_t y_index) {
        Link(Find(x_index), Find(y_index));
    }

    void Link(const std::size_t x_index, const std::size_t y_index) {
        assert(x_index < m_subsets.size() and y_index < m_subsets.size());

        auto &x_node = m_subsets[x_index];
        auto &y_node = m_subsets[y_index];

        if (x_node.rank < y_node.rank) {
            Adopt(y_index, x_index);
        } else if (x_node.rank > y_node.rank) {
            Adopt(x_index, y_index);
        } else {
            Adopt(x_index, y_index);
            ++(x_node.rank);
        }
    }

    void Adopt(const std::size_t parent_index, const std::size_t child_index) {
        assert(parent_index != child_index);
        assert(m_subsets[parent_index].parent == parent_index and
               m_subsets[child_index].parent == child_index);

        m_subsets[child_index].parent = parent_index;
    }
};


/**
 * @reference   Dynamic Disjoint Set Data Structure for large range values
 *              https://www.geeksforgeeks.org/dynamic-disjoint-set-data-structure-for-large-range-values/
 */
