#include "reservoir_sampling.h"


namespace {

template <std::size_t N>
using ArrayType = std::array<int, N>;


/** Select a random number from stream, with O(1) space
 *
 * @reference   https://www.geeksforgeeks.org/select-a-random-number-from-stream-with-o1-space/
 *
 * Given a stream of numbers, generate a random number from the stream. You are allowed
 * to use only O(1) space and the input is in the form of stream, so can't store the
 * previously seen numbers.
 */
template <typename Container>
inline constexpr auto RandomNumberFromStream(const Container &stream) {
    return ReservoirSampling(stream, 1).back();
}


/**
 * @reference   Linked List Random Node
 *              https://leetcode.com/problems/linked-list-random-node/
 *
 * Given a singly linked list, return a random node's value from the linked list. Each
 * node must have the same probability of being chosen. Implement the Solution class:
 *  Solution(ListNode head) Initializes the object with the integer array nums.
 *  int getRandom() Chooses a node randomly from the list and returns its value. All the
 *  nodes of the list should be equally likely to be choosen.
 * Follow up:
 *  What if the linked list is extremely large and its length is unknown to you?
 *  Could you solve this efficiently without using extra space?
 */

}//namespace


ArrayType<8> VALUES = {1, 2, 3, 4, 5, 6, 7, 8};


THE_BENCHMARK(ReservoirSampling, VALUES, 3);


THE_BENCHMARK(RandomNumberFromStream, VALUES);


#ifdef WANT_TERMINAL_APP
int main(int, char **) {
    std::cout << "Selected Samples: " << ReservoirSampling(VALUES, 3) << std::endl;
    std::cout <<
              "Selected Random Number from Stream: " <<
              RandomNumberFromStream(VALUES) << std::endl;

    return EXIT_SUCCESS;
}
#endif
