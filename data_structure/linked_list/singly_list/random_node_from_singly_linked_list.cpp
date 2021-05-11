#include "common_header.h"

#include "mathematics/probabilistic/reservoir_sampling.h"


namespace {

using ArrayType = std::forward_list<int>;

/** Select a Random Node from a Singly Linked List
 *
 * @reference   https://www.geeksforgeeks.org/select-a-random-node-from-a-singly-linked-list/
 *
 * Given a singly linked list, select a random node from linked list (the probability
 * of picking a node should be 1/N if there are N nodes in list). You are given a
 * random number generator.
 */
inline auto RandomNodeFromSinglyLinkedList(const ArrayType &stream) {
    return ReservoirSampling(stream, 1).back();
}

}//namespace


const ArrayType VALUES = {1, 2, 3, 4, 5, 6, 7, 8};


THE_BENCHMARK(RandomNodeFromSinglyLinkedList, VALUES);
