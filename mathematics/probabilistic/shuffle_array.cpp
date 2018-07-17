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
template <std::size_t N>
void ShuffleArrayInPlace(ArrayType<N> &array) {
    for (auto i = array.size() - 1; i > 0; --i) {
        auto j = Random_Number<decltype(i)>(0, i);
        std::swap(array[i], array[j]);
    }
}

/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 5.3.
 *
 * @complexity  O(nlgn)
 */
template <std::size_t N>
auto ShuffleArrayBySorting(const ArrayType<N> &array) {
    const int PRIORITY_BOUND = pow(array.size(), 3.0);

    std::vector<std::pair<typename ArrayType<N>::value_type, std::size_t> > priorities;
    for (typename ArrayType<N>::size_type i = 0; i < array.size(); ++i) {
        priorities.emplace_back(Random_Number(0, PRIORITY_BOUND), i);
    }

    std::sort(priorities.begin(), priorities.end(), [](const auto a, const auto b) {
        return a.first < b.first;
    });

    ArrayType<N> output;
    for (typename ArrayType<N>::size_type i = 0; i < array.size(); ++i) {
        output[i] = array[priorities[i].second];
    }

    return output;
}


ArrayType<8> VALUES = {1, 2, 3, 4, 5, 6, 7, 8};
SIMPLE_BENCHMARK(ShuffleArrayInPlace, VALUES);
SIMPLE_BENCHMARK(ShuffleArrayBySorting, VALUES);


#ifdef WANT_TERMINAL_APP
int main(int argc, char **argv) {
    ShuffleArrayInPlace(VALUES);
    std::cout << "Shuffled array in place: " << VALUES << std::endl;

    const auto output = ShuffleArrayBySorting(VALUES);
    std::cout << "Shuffled array by sorting: " << output << std::endl;

    return EXIT_SUCCESS;
}
#endif
