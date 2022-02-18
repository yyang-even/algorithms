#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string>;

/** Print all permutations with repetition of characters
 *
 * @reference   https://www.geeksforgeeks.org/print-all-permutations-with-repetition-of-characters/
 *
 * Given a string of length n, print all permutation of the given string. Repetition of
 * characters is allowed. Print these permutations in lexicographically sorted order.
 */
void PermutationWithRepetitionHelper(const std::string &input,
                                     const std::string &buffer,
                                     const std::string::iterator buffer_iter,
                                     ArrayType &outputs) {
    for (const auto c : input) {
        *buffer_iter = c;

        const auto next = std::next(buffer_iter);
        if (next == buffer.end()) {
            outputs.push_back(buffer);
        } else {
            PermutationWithRepetitionHelper(input, buffer, next, outputs);
        }
    }
}

auto PermutationWithRepetition(std::string input) {
    std::sort(input.begin(), input.end());

    ArrayType outputs;
    auto buffer = input;

    PermutationWithRepetitionHelper(input, buffer, buffer.begin(), outputs);

    return outputs;
}

}//namespace


const ArrayType EXPECTED1 = {"aaa", "aab", "aac", "aba", "abb", "abc", "aca", "acb", "acc", "baa", "bab", "bac", "bba", "bbb", "bbc", "bca", "bcb", "bcc", "caa", "cab", "cac", "cba", "cbb", "cbc", "cca", "ccb", "ccc"};


THE_BENCHMARK(PermutationWithRepetition, "ab4c12ed3");

SIMPLE_TEST(PermutationWithRepetition, TestSAMPLE1, EXPECTED1, "abc");
