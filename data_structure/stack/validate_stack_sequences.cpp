#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Validate Stack Sequences
 *
 * @reference   https://leetcode.com/problems/validate-stack-sequences/
 *
 * Given two integer arrays pushed and popped each with distinct values, return true if
 * this could have been the result of a sequence of push and pop operations on an initially
 * empty stack, or false otherwise.
 * All the elements of pushed are unique.
 * popped.length == pushed.length
 * popped is a permutation of pushed.
 */
auto ValidateStackSequences(const ArrayType &pushed, const ArrayType &popped) {
    std::stack<int> s;

    std::size_t j = 0;
    for (const auto v : pushed) {
        s.push(v);

        while (not s.empty() and s.top() == popped[j]) {
            s.pop();
            ++j;
        }
    }

    return j == popped.size();
}

}//namespace


const ArrayType SAMPLE1I = {1, 2, 3, 4, 5};
const ArrayType SAMPLE1J = {4, 5, 3, 2, 1};

const ArrayType SAMPLE2J = {4, 3, 5, 1, 2};


THE_BENCHMARK(ValidateStackSequences, SAMPLE1I, SAMPLE1J);

SIMPLE_TEST(ValidateStackSequences, TestSAMPLE1, true, SAMPLE1I, SAMPLE1J);
SIMPLE_TEST(ValidateStackSequences, TestSAMPLE2, false, SAMPLE1I, SAMPLE2J);

