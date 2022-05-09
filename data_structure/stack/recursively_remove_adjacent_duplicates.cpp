#include "common_header.h"


namespace {

/** Recursively remove all adjacent duplicates
 *
 * @reference   https://www.geeksforgeeks.org/recursively-remove-adjacent-duplicates-given-string/
 * @reference   Remove first adjacent pairs of similar characters until possible
 *              https://www.geeksforgeeks.org/remove-first-adjacent-pairs-of-similar-characters-until-possible/
 * @reference   Remove all duplicate adjacent characters from a string using Stack
 *              https://www.geeksforgeeks.org/remove-all-duplicate-adjacent-characters-from-a-string-using-stack/
 * @reference   Remove All Adjacent Duplicates In String
 *              https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/
 *
 * You are given a string s consisting of lowercase English letters. A duplicate removal
 * consists of choosing two adjacent and equal letters and removing them. We repeatedly
 * make duplicate removals on s until we no longer can. Return the final string after all
 * such duplicate removals have been made. It can be proven that the answer is unique.
 */
auto RemoveAdjacentDuplicates_Stack(const std::string_view text) {
    std::string results;

    for (const auto c : text) {
        if (results.empty() or results.back() != c) {
            results.push_back(c);
        } else {
            results.pop_back();
        }
    }

    return results;
}


/**
 * @reference   Remove All Adjacent Duplicates in String II
 *              https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/
 *
 * You are given a string s and an integer k, a k duplicate removal consists of choosing
 * k adjacent and equal letters from s and removing them, causing the left and the right
 * side of the deleted substring to concatenate together. We repeatedly make k duplicate
 * removals on s until we no longer can. Return the final string after all such duplicate
 * removals have been made. It is guaranteed that the answer is unique.
 */
auto RemoveAdjacentKDuplicates_Stack(const std::string_view text, const int K) {
    std::vector<std::pair<char, int>> the_stack;

    for (const auto c : text) {
        if (the_stack.empty() or c != the_stack.back().first) {
            the_stack.emplace_back(c, 1);
        } else if (++the_stack.back().second == K) {
            the_stack.pop_back();
        }
    }

    std::string results;
    for (const auto [c, count] : the_stack) {
        results.append(count, c);
    }

    return results;
}


auto RemoveAdjacentKDuplicates_Stack_InPlace(std::string text, const int K) {
    int stack_top = 0;
    std::stack<int> tops;

    const auto N = text.size();
    for (std::size_t i = 0; i < N; ++stack_top, ++i) {
        text[stack_top] = text[i];
        if (stack_top == 0 or text[stack_top] != text[stack_top - 1]) {
            tops.push(stack_top);
        } else if (stack_top - tops.top() + 1 == K) {
            stack_top = tops.top() - 1;
            tops.pop();
        }
    }

    text.resize(stack_top);
    return text;
}

} //namespace


THE_BENCHMARK(RemoveAdjacentDuplicates_Stack, "azxxzy");

SIMPLE_TEST(RemoveAdjacentDuplicates_Stack, TestSAMPLE1, "ay", "azxxzy");
SIMPLE_TEST(RemoveAdjacentDuplicates_Stack, TestSAMPLE2, "gksfor", "geeksforgeeg");
SIMPLE_TEST(RemoveAdjacentDuplicates_Stack, TestSAMPLE3, "ca", "abbaca");
SIMPLE_TEST(RemoveAdjacentDuplicates_Stack, TestSAMPLE4, "a", "aaaaaaaaa");
SIMPLE_TEST(RemoveAdjacentDuplicates_Stack, TestSAMPLE5, "", "aaaaaaaa");


THE_BENCHMARK(RemoveAdjacentKDuplicates_Stack, "azxxzy", 2);

SIMPLE_TEST(RemoveAdjacentKDuplicates_Stack, TestSAMPLE1, "ay", "azxxzy", 2);
SIMPLE_TEST(RemoveAdjacentKDuplicates_Stack, TestSAMPLE2, "gksfor", "geeksforgeeg", 2);
SIMPLE_TEST(RemoveAdjacentKDuplicates_Stack, TestSAMPLE3, "ca", "abbaca", 2);
SIMPLE_TEST(RemoveAdjacentKDuplicates_Stack, TestSAMPLE4, "a", "aaaaaaaaa", 2);
SIMPLE_TEST(RemoveAdjacentKDuplicates_Stack, TestSAMPLE5, "", "aaaaaaaa", 2);
SIMPLE_TEST(RemoveAdjacentKDuplicates_Stack, TestSAMPLE6, "abcd", "abcd", 2);
SIMPLE_TEST(RemoveAdjacentKDuplicates_Stack, TestSAMPLE7, "aa", "deeedbbcccbdaa", 3);
SIMPLE_TEST(RemoveAdjacentKDuplicates_Stack, TestSAMPLE8, "ps", "pbbcggttciiippooaais", 2);


THE_BENCHMARK(RemoveAdjacentKDuplicates_Stack_InPlace, "azxxzy", 2);

SIMPLE_TEST(RemoveAdjacentKDuplicates_Stack_InPlace, TestSAMPLE1, "ay", "azxxzy", 2);
SIMPLE_TEST(RemoveAdjacentKDuplicates_Stack_InPlace, TestSAMPLE2, "gksfor", "geeksforgeeg", 2);
SIMPLE_TEST(RemoveAdjacentKDuplicates_Stack_InPlace, TestSAMPLE3, "ca", "abbaca", 2);
SIMPLE_TEST(RemoveAdjacentKDuplicates_Stack_InPlace, TestSAMPLE4, "a", "aaaaaaaaa", 2);
SIMPLE_TEST(RemoveAdjacentKDuplicates_Stack_InPlace, TestSAMPLE5, "", "aaaaaaaa", 2);
SIMPLE_TEST(RemoveAdjacentKDuplicates_Stack_InPlace, TestSAMPLE6, "abcd", "abcd", 2);
SIMPLE_TEST(RemoveAdjacentKDuplicates_Stack_InPlace, TestSAMPLE7, "aa", "deeedbbcccbdaa", 3);
SIMPLE_TEST(
    RemoveAdjacentKDuplicates_Stack_InPlace, TestSAMPLE8, "ps", "pbbcggttciiippooaais", 2);
