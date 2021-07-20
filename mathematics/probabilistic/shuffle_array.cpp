#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Shuffle a given array using Fisher–Yates shuffle Algorithm
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 5.3.
 *
 * @reference   Shuffle a deck of cards
 *              https://www.geeksforgeeks.org/shuffle-a-deck-of-cards-3/
 * @reference   Shuffle a given array using Fisher–Yates shuffle Algorithm
 *              https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/
 *
 * Given an array, write a program to generate a random permutation of array elements.
 * This question is also asked as "shuffle a deck of cards" or "randomize a given array".
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 18.2.
 *
 * @reference   Shuffle an Array
 *              https://leetcode.com/problems/shuffle-an-array/
 *
 * Given an integer array nums, design an algorithm to randomly shuffle the array. All
 * permutations of the array should be equally likely as a result of the shuffling.
 * Implement the Solution class:
 *  Solution(int[] nums) Initializes the object with the integer array nums.
 *  int[] reset() Resets the array to its original configuration and returns it.
 *  int[] shuffle() Returns a random shuffling of the array.
 *
 * @complexity  O(n)
 */
void ShuffleArray_InPlace(ArrayType &array) {
    for (auto i = array.size() - 1; i > 0; --i) {
        const auto j = Random_Number(0, i);
        std::swap(array[i], array[j]);
    }
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 5.3.
 *
 * @complexity  O(nlgn)
 */
auto ShuffleArray_BySorting(const ArrayType &array) {
    const int PRIORITY_BOUND = pow(array.size(), 3.0);

    std::vector<std::pair<int, std::size_t>> priorities;
    for (std::size_t i = 0; i < array.size(); ++i) {
        priorities.emplace_back(Random_Number(0, PRIORITY_BOUND), i);
    }

    std::sort(priorities.begin(), priorities.end(), [](const auto & a, const auto & b) {
        return a.first < b.first;
    });

    ArrayType output;
    for (std::size_t i = 0; i < array.size(); ++i) {
        output[i] = array[priorities[i].second];
    }

    return output;
}

}//namespace


ArrayType VALUES = {1, 2, 3, 4, 5, 6, 7, 8};


THE_BENCHMARK(ShuffleArray_InPlace, VALUES);


THE_BENCHMARK(ShuffleArray_BySorting, VALUES);


#ifdef WANT_TERMINAL_APP
int main(int, char **) {
    ShuffleArray_InPlace(VALUES);
    std::cout << "Shuffled array in place: " << VALUES << std::endl;

    std::cout <<
              "Shuffled array by sorting: " <<
              ShuffleArray_BySorting(VALUES) << std::endl;

    return EXIT_SUCCESS;
}
#endif
