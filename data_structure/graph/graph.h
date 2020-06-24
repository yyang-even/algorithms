#pragma once


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 22.
 * @reference   Graph and its representations
 *              https://www.geeksforgeeks.org/graph-and-its-representations/
 * @reference   Mathematics | Graph Theory Basics – Set 1
 *              https://www.geeksforgeeks.org/mathematics-graph-theory-basics-set-1/
 * @reference   Mathematics | Graph Theory Basics – Set 2
 *              https://www.geeksforgeeks.org/mathematics-graph-theory-basics/
 * @reference   Graph Types and Applications
 *              https://www.geeksforgeeks.org/graph-types-and-applications/
 * @reference   Applications of Graph Data Structure
 *              https://www.geeksforgeeks.org/applications-of-graph-data-structure/
 */
class AdjacencyListGraph {
public:
    using RepresentationType = std::vector<std::list<std::size_t>>;
    using EdgeType = std::pair<std::size_t, std::size_t>;
    using EdgeArrayType = std::vector<EdgeType>;
    using ArrayType = std::vector<std::size_t>;

    AdjacencyListGraph(const std::size_t number_vertices, const EdgeArrayType &edges) {
        adjacency_list.resize(number_vertices);

        for (const auto &one_edge : edges) {
            AddEdge(one_edge);
        }
    }

    void AddEdge(const EdgeType &edge) {
        adjacency_list.at(edge.first).push_back(edge.second);
    }

    template<typename Visitor>
    auto Visit(const Visitor visitor) const {
        return visitor(adjacency_list);
    }

private:
    RepresentationType adjacency_list;
};


template <typename Traverser>
static inline auto GraphTraverse(const AdjacencyListGraph::RepresentationType &graph,
                                 const Traverser traverser) {
    AdjacencyListGraph::ArrayType results;
    std::vector<bool> visited_vertices(graph.size(), false);
    for (std::size_t i = 0; i < graph.size(); ++i) {
        if (not visited_vertices[i]) {
            traverser(graph, i, visited_vertices, results);
        }
    }

    return results;
}

template <typename Traverser>
static inline auto GraphTraverse(const std::size_t number_vertices,
                                 const AdjacencyListGraph::EdgeArrayType &edges,
                                 const Traverser traverser) {
    return AdjacencyListGraph(number_vertices, edges).Visit(
    [traverser](const AdjacencyListGraph::RepresentationType & graph) {
        return GraphTraverse(graph, traverser);
    });
}
