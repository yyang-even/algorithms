#include "common_header.h"


namespace {

using StackType = std::stack<int>;
using ArrayType = std::vector<StackType::value_type>;

/** Sort a stack using a temporary stack
 *
 * @reference   https://www.geeksforgeeks.org/sort-stack-using-temporary-stack/
 *
 * Given a stack of integers, sort it in descending order using another temporary stack.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 3.6.
 *
 * @reference   Sorting array using Stacks
 *              https://www.geeksforgeeks.org/sorting-array-using-stacks/
 * @reference   Sort string of characters using Stack
 *              https://www.geeksforgeeks.org/sort-string-of-characters-using-stack/
 */
auto SortStack(StackType original_stack) {
    StackType temp_stack;
    while (not original_stack.empty()) {
        const auto v = original_stack.top();
        original_stack.pop();

        while (not temp_stack.empty() and temp_stack.top() > v) {
            original_stack.push(temp_stack.top());
            temp_stack.pop();
        }

        temp_stack.push(v);
    }

    return temp_stack;
}


/**
 * @reference   Sort a stack using recursion
 *              https://www.geeksforgeeks.org/sort-a-stack-using-recursion/
 *
 * Given a stack, sort it using recursion. Use of any loop constructs like while, for,
 * ...etc is not allowed.
 */
void SortedInsert(StackType &sorted_stack, const StackType::value_type v) {
    if (not sorted_stack.empty() and sorted_stack.top() > v) {
        const auto temp = sorted_stack.top();
        sorted_stack.pop();
        SortedInsert(sorted_stack, v);
        sorted_stack.push(temp);
    } else {
        sorted_stack.push(v);
    }
}

void SortStack_Recursive_Helper(StackType &a_stack) {
    if (not a_stack.empty()) {
        const auto v = a_stack.top();
        a_stack.pop();

        SortStack_Recursive_Helper(a_stack);
        SortedInsert(a_stack, v);
    }
}

auto SortStack_Recursive(StackType original_stack) {
    SortStack_Recursive_Helper(original_stack);
    return original_stack;
}


auto testSortStack(const std::function<StackType(StackType)> sort,
                   const ArrayType &input) {
    StackType original_stack;
    for (const auto v : input) {
        original_stack.push(v);
    }

    auto result_stack = sort(std::move(original_stack));
    ArrayType results;
    while (not result_stack.empty()) {
        results.push_back(result_stack.top());
        result_stack.pop();
    }

    std::reverse(results.begin(), results.end());
    return results;
}

}//namespace


const ArrayType SAMPLE1 = {34, 3, 31, 98, 92, 23};
const ArrayType EXPECTED1 = {3, 23, 31, 34, 92, 98};

const ArrayType SAMPLE2 = {3, 5, 1, 4, 2, 8};
const ArrayType EXPECTED2 = {1, 2, 3, 4, 5, 8};


THE_BENCHMARK(testSortStack, SortStack, SAMPLE1);

SIMPLE_TEST(testSortStack, TestSAMPLE1, EXPECTED1, SortStack, SAMPLE1);
SIMPLE_TEST(testSortStack, TestSAMPLE2, EXPECTED2, SortStack, SAMPLE2);

SIMPLE_TEST(testSortStack, TestSAMPLE3, EXPECTED1, SortStack_Recursive, SAMPLE1);
SIMPLE_TEST(testSortStack, TestSAMPLE4, EXPECTED2, SortStack_Recursive, SAMPLE2);
