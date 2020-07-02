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
    struct DirectedEdge {
        std::size_t from;
        std::size_t to;
    };

    struct UndirectedEdge {
        std::size_t u;
        std::size_t v;
    };

    using RepresentationType = std::vector<std::list<std::size_t>>;
    using DirectedEdgeArrayType = std::vector<DirectedEdge>;
    using UndirectedEdgeArrayType = std::vector<UndirectedEdge>;
    using ArrayType = std::vector<std::size_t>;


    template <typename EdgeArrayType>
    AdjacencyListGraph(const std::size_t number_vertices, const EdgeArrayType &edges) {
        adjacency_list.resize(number_vertices);

        for (const auto &one_edge : edges) {
            AddEdge(one_edge);
        }
    }


    void AddEdge(const DirectedEdge &edge) {
        adjacency_list.at(edge.from).push_back(edge.to);
    }

    void AddEdge(const UndirectedEdge &edge) {
        adjacency_list.at(edge.u).push_back(edge.v);
        adjacency_list.at(edge.v).push_back(edge.u);
    }


    template<typename Visitor>
    auto Visit(const Visitor visitor) const {
        return visitor(adjacency_list);
    }


private:
    RepresentationType adjacency_list;
};


inline auto &operator<<(std::ostream &out, const AdjacencyListGraph::DirectedEdge &edge) {
    return out << "(" << edge.from << ", " << edge.to << ")";
}

inline auto &operator<<(std::ostream &out, const AdjacencyListGraph::UndirectedEdge &edge) {
    return out << "(" << edge.u << ", " << edge.v << ")";
}


template <typename Traverser>
static inline void GraphTraverse(const AdjacencyListGraph::RepresentationType &graph,
                                 const Traverser traverser) {
    std::vector<bool> visited_vertices(graph.size(), false);
    for (std::size_t i = 0; i < graph.size(); ++i) {
        if (not visited_vertices[i]) {
            if (not traverser(graph, i, visited_vertices)) {
                break;
            }
        }
    }
}

template <typename EdgeArrayType, typename Traverser>
static inline void GraphTraverse(const std::size_t number_vertices,
                                 const EdgeArrayType &edges,
                                 const Traverser traverser) {
    AdjacencyListGraph(number_vertices, edges).Visit(
    [traverser](const AdjacencyListGraph::RepresentationType & graph) {
        GraphTraverse(graph, traverser);
    });
}
