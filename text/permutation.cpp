#include "common_header.h"

/** Write a program to print all permutations of a given string
 *
 * @reference   https://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/
 * @reference   Permutations of a given string using STL
 *              https://www.geeksforgeeks.org/permutations-of-a-given-string-using-stl/
 *
 * A permutation, also called an "arrangement number" or "order", is a rearrangement
 * of the elements of an ordered list S into a one-to-one correspondence with S itself.
 * A string of length n has n! permutation.
 *
 * @complexity  O(n * n!)
 */
void PermutationHelper(const std::string &input, std::string::iterator start,
                       std::string::iterator last, std::vector<std::string> &outputs) {
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
auto Permutation(std::string input) {
    std::vector<std::string> outputs;
    PermutationHelper(input, input.begin(), input.begin() + input.size() - 1ul, outputs);
    return outputs;
}


auto PermutationSTL(std::string input) {
    std::vector<std::string> outputs;

    std::sort(input.begin(), input.end());

    do {
        outputs.push_back(input);
    } while (std::next_permutation(input.begin(), input.end()));

    return outputs;
}


const std::vector<std::string> EXPECTED1 = {"abc", "acb", "bac", "bca", "cba", "cab"};

SIMPLE_BENCHMARK(Permutation, std::string("ab4c12ed3"));

SIMPLE_TEST(Permutation, TestSAMPLE1, EXPECTED1, std::string("abc"));


const std::vector<std::string> EXPECTED2 = {"abc", "acb", "bac", "bca", "cab", "cba"};

SIMPLE_BENCHMARK(PermutationSTL, std::string("ab4c12ed3"));

SIMPLE_TEST(PermutationSTL, TestSAMPLE1, EXPECTED2, std::string("abc"));
