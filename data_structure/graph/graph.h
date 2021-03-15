#pragma once

#include "mathematics/matrix/matrix.h"


namespace graph {

using ArrayType = std::vector<std::size_t>;

struct DirectedEdge {
    std::size_t from;
    std::size_t to;
    int weight;

    DirectedEdge(const std::size_t source, const std::size_t destination, const int w = 0) :
        from(source), to(destination), weight(w) {}
};

struct UndirectedEdge {
    std::size_t u;
    std::size_t v;
    int weight;

    UndirectedEdge(const std::size_t source,
                   const std::size_t destination,
                   const int w = 0) :
        u(source), v(destination), weight(w) {}
};

using DirectedEdgeArrayType = std::vector<DirectedEdge>;
using UndirectedEdgeArrayType = std::vector<UndirectedEdge>;


inline auto &operator<<(std::ostream &out, const DirectedEdge &edge) {
    return out << "(" << edge.from << ", " << edge.to << ")";
}

inline auto &operator<<(std::ostream &out, const UndirectedEdge &edge) {
    return out << "(" << edge.u << ", " << edge.v << ")";
}

}//namespace graph


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 22.
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


    AdjacencyListGraph(const std::size_t number_vertices):
        adjacency_list(number_vertices, std::list<std::size_t> {}) {
    }

    template <typename EdgeArrayType>
    AdjacencyListGraph(const std::size_t number_vertices, const EdgeArrayType &edges):
        AdjacencyListGraph(number_vertices) {
        for (const auto &one_edge : edges) {
            AddEdge(one_edge);
        }
    }


    void AddEdge(const graph::DirectedEdge &edge) {
        adjacency_list.at(edge.from).push_back(edge.to);
    }

    void AddEdge(const graph::UndirectedEdge &edge) {
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


/**
 * @reference   C program to implement Adjacency Matrix of a given Graph
 *              https://www.geeksforgeeks.org/c-program-to-implement-adjacency-matrix-of-a-given-graph/
 * @reference   Comparison between Adjacency List and Adjacency Matrix representation of Graph
 *              https://www.geeksforgeeks.org/comparison-between-adjacency-list-and-adjacency-matrix-representation-of-graph/
 */
class AdjacencyMatrixGraph {
public:
    using RepresentationType = MatrixTypeTemplate<bool>;


    AdjacencyMatrixGraph(const std::size_t number_vertices):
        adjacency_matrix(number_vertices, std::vector<bool>(number_vertices, false)) {
    }

    template <typename EdgeArrayType>
    AdjacencyMatrixGraph(const std::size_t number_vertices, const EdgeArrayType &edges):
        AdjacencyMatrixGraph(number_vertices) {
        for (const auto &one_edge : edges) {
            AddEdge(one_edge);
        }
    }


    void AddEdge(const graph::DirectedEdge &edge) {
        adjacency_matrix.at(edge.from).at(edge.to) = true;
    }

    void AddEdge(const graph::UndirectedEdge &edge) {
        adjacency_matrix.at(edge.u).at(edge.v) = true;
        adjacency_matrix.at(edge.v).at(edge.u) = true;
    }


    template<typename Visitor>
    auto Visit(const Visitor visitor) const {
        return visitor(adjacency_matrix);
    }


private:
    RepresentationType adjacency_matrix;
};


/**
 * @reference   Graph implementation using STL for competitive programming | Set 2 (Weighted graph)
 *              https://www.geeksforgeeks.org/graph-implementation-using-stl-for-competitive-programming-set-2-weighted-graph/
 */
class WeightedAdjacencyListGraph {
public:
    struct AdjacentNode {
        std::size_t destination = 0;
        int weight = 0;

        AdjacentNode(const std::size_t to, const int w) : destination(to), weight(w) {}
    };

    using RepresentationType = std::vector<std::list<AdjacentNode>>;


    WeightedAdjacencyListGraph(const std::size_t number_vertices):
        adjacency_list(number_vertices, std::list<AdjacentNode> {}) {
    }

    template <typename EdgeArrayType>
    WeightedAdjacencyListGraph(const std::size_t number_vertices,
                               const EdgeArrayType &edges):
        WeightedAdjacencyListGraph(number_vertices) {
        for (const auto &one_edge : edges) {
            AddEdge(one_edge);
        }
    }


    void AddEdge(const graph::DirectedEdge &edge) {
        adjacency_list.at(edge.from).emplace_back(edge.to, edge.weight);
    }

    void AddEdge(const graph::UndirectedEdge &edge) {
        adjacency_list.at(edge.u).emplace_back(edge.v, edge.weight);
        adjacency_list.at(edge.v).emplace_back(edge.u, edge.weight);
    }


    template<typename Visitor>
    auto Visit(const Visitor visitor) const {
        return visitor(adjacency_list);
    }


private:
    RepresentationType adjacency_list;
};


class WeightedAdjacencyListInGraph {
public:
    struct AdjacentNode {
        std::size_t source = 0;
        int weight = 0;

        AdjacentNode(const std::size_t to, const int w) : source(to), weight(w) {}
    };

    using RepresentationType = std::vector<std::list<AdjacentNode>>;


    WeightedAdjacencyListInGraph(const std::size_t number_vertices):
        adjacency_list(number_vertices, std::list<AdjacentNode> {}) {
    }

    template <typename EdgeArrayType>
    WeightedAdjacencyListInGraph(const std::size_t number_vertices,
                                 const EdgeArrayType &edges):
        WeightedAdjacencyListInGraph(number_vertices) {
        for (const auto &one_edge : edges) {
            AddEdge(one_edge);
        }
    }


    void AddEdge(const graph::DirectedEdge &edge) {
        adjacency_list.at(edge.to).emplace_back(edge.from, edge.weight);
    }

    void AddEdge(const graph::UndirectedEdge &edge) {
        adjacency_list.at(edge.u).emplace_back(edge.v, edge.weight);
        adjacency_list.at(edge.v).emplace_back(edge.u, edge.weight);
    }


    template<typename Visitor>
    auto Visit(const Visitor visitor) const {
        return visitor(adjacency_list);
    }


private:
    RepresentationType adjacency_list;
};


/**
 * @reference   Convert Adjacency Matrix to Adjacency List representation of Graph
 *              https://www.geeksforgeeks.org/convert-adjacency-matrix-to-adjacency-list-representation-of-graph/
 */


/**
 * @reference   Convert Adjacency List to Adjacency Matrix representation of a Graph
 *              https://www.geeksforgeeks.org/convert-adjacency-list-to-adjacency-matrix-representation-of-a-graph/
 */


template <typename RepresentationType, typename Traverser>
static inline void GraphTraverseHelper(const RepresentationType &graph,
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

template <typename GraphType, typename Traverser>
static inline void GraphTraverse(const GraphType &graph, const Traverser traverser) {
    graph.Visit([traverser](const auto & graph) {
        GraphTraverseHelper(graph, traverser);
    });
}

template <typename EdgeArrayType, typename Traverser>
static inline void GraphTraverse(const std::size_t number_vertices,
                                 const EdgeArrayType &edges,
                                 const Traverser traverser) {
    GraphTraverse(AdjacencyListGraph{number_vertices, edges}, traverser);
}


static inline auto GraphTranspose(const AdjacencyListGraph::RepresentationType &graph) {
    AdjacencyListGraph transpose{graph.size()};
    for (std::size_t source = 0; source < graph.size(); ++source) {
        for (const auto adjacent_vertex : graph[source]) {
            transpose.AddEdge(graph::DirectedEdge{adjacent_vertex, source});
        }
    }

    return transpose;
}
