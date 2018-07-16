#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

template <std::size_t N>
using ArrayType = std::array<int, N>;

/** Shuffle a given array
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 5.3.
 *
 *              https://www.geeksforgeeks.org/shuffle-a-given-array/
 *              https://www.geeksforgeeks.org/shuffle-a-deck-of-cards-3/
 *
 * Given an array, write a program to generate a random permutation of array elements.
 * This question is also asked as “shuffle a deck of cards” or “randomize a given array”.
 *
 * @complexity  O(n)
 */
/** A helper function return a random number in range [from, to]
 */
auto RandomNumber(const int from, const int to) {
    const auto SEED = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine generator(SEED);
    std::uniform_int_distribution<int> distribution(from, to);
    return distribution(generator);
}
template <std::size_t N>
void ShuffleArrayInPlace(ArrayType<N> &array) {
    for (auto i = array.size() - 1; i > 0; --i) {
        auto j = RandomNumber(0, i);
        std::swap(array[i], array[j]);
    }
}


ArrayType<8> VALUES = {1, 2, 3, 4, 5, 6, 7, 8};
SIMPLE_BENCHMARK(ShuffleArrayInPlace, VALUES);


#ifdef WANT_TERMINAL_APP
int main(int argc, char **argv) {
    auto array = VALUES;
    ShuffleArrayInPlace(array);
    std::cout << "Shuffled array: " << array << std::endl;

    return EXIT_SUCCESS;
}
#endif
