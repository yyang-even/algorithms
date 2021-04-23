#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string>;

/** Write a program to print all permutations of a given string
 *
 * @reference   https://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/
 * @reference   Permutations of a given string using STL
 *              https://www.geeksforgeeks.org/permutations-of-a-given-string-using-stl/
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 7.
 * @reference   Section VI. Five Algorithm Approaches.
 *              Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *
 * A permutation, also called an "arrangement number" or "order", is a rearrangement of
 * the elements of an ordered list S into a one-to-one correspondence with S itself. A
 * string of length n has n! permutation.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 9.5.
 *
 * @complexity  O(n * n!)
 */
void PermutationHelper(const std::string &input, std::string::iterator start,
                       std::string::iterator last, ArrayType &outputs) {
    if (start == last) {
        outputs.push_back(input);
    } else {
        for (auto iter = start; iter <= last; ++iter) {
            std::iter_swap(start, iter);
            PermutationHelper(input, start + 1, last, outputs);
            std::iter_swap(start, iter);
        }
    }
}

inline auto Permutation(std::string input) {
    assert(not input.empty());

    ArrayType outputs;
    PermutationHelper(input, input.begin(), std::prev(input.end()), outputs);
    return outputs;
}


auto PermutationSTL(std::string input) {
    ArrayType outputs;

    std::sort(input.begin(), input.end());

    do {
        outputs.push_back(input);
    } while (std::next_permutation(input.begin(), input.end()));

    return outputs;
}

}//namespace


const ArrayType EXPECTED1 = {"abc", "acb", "bac", "bca", "cba", "cab"};


THE_BENCHMARK(Permutation, "ab4c12ed3");

SIMPLE_TEST(Permutation, TestSAMPLE1, EXPECTED1, "abc");


const ArrayType EXPECTED2 = {"abc", "acb", "bac", "bca", "cab", "cba"};


THE_BENCHMARK(PermutationSTL, "ab4c12ed3");

SIMPLE_TEST(PermutationSTL, TestSAMPLE1, EXPECTED2, "abc");
