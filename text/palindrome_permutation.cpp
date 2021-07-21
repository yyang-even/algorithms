#include "common_header.h"


namespace {

using ArrayType = std::unordered_multiset<std::string>;

/** Palindrome Permutation
 *
 * @reference   https://cheonhyangzhang.gitbooks.io/leetcode-solutions/content/266-palindrome-permutation.html
 *
 * Given a string, determine if a permutation of the string could form a palindrome.
 */
auto hasPalindromePermutation(const std::string_view text) {
    int counts[256] = {};
    int number_odd = 0;
    for (const int c : text) {
        if (++counts[c] % 2 == 0) {
            --number_odd;
        } else {
            ++number_odd;
        }
    }

    return number_odd <= 1;
}


/**
 * @reference   Palindrome Permutation II
 *              https://bohenan.gitbooks.io/leetcode/content/chapter1/palindrome-permutation-ii.html
 *
 * Given a strings, return all the palindromic permutations (without duplicates) of it.
 * Return an empty list if no palindromic permutation could be form.
 *
 * @reference   Print all palindrome permutations of a string
 *              https://www.geeksforgeeks.org/print-all-palindrome-permutations-of-a-string/
 */
auto allPalindromePermutation(const std::string_view text) {
    int counts[256] = {};
    for (const int c : text) {
        ++counts[c];
    }

    char mid = 0;
    std::string half;
    ArrayType results;
    for (int i = 'a'; i <= 'z'; ++i) {
        if (counts[i] % 2 == 1) {
            if (mid) {
                return results;
            }
            mid = i;
        }

        half.append(counts[i] / 2, i);
    }

    do {
        auto a_palindrome = half;
        if (mid) {
            a_palindrome.push_back(mid);
        }
        a_palindrome.append(half.crbegin(), half.crend());
        results.insert(std::move(a_palindrome));
    } while (std::next_permutation(half.begin(), half.end()));

    return results;
}

}//namespace


THE_BENCHMARK(hasPalindromePermutation, "carerac");

SIMPLE_TEST(hasPalindromePermutation, TestSAMPLE1, true, "carerac");
SIMPLE_TEST(hasPalindromePermutation, TestSAMPLE2, true, "aab");
SIMPLE_TEST(hasPalindromePermutation, TestSAMPLE3, true, "aa");
SIMPLE_TEST(hasPalindromePermutation, TestSAMPLE4, false, "code");


const ArrayType EXPECTED0 = {};
const ArrayType EXPECTED1 = {"abcba", "bacab"};
const ArrayType EXPECTED2 = {"aabdcdbaa", "aadbcbdaa", "abadcdaba", "abdacadba", "adabcbada", "adbacabda", "baadcdaab", "badacadab", "bdaacaadb", "daabcbaad", "dabacabad", "dbaacaabd"};
const ArrayType EXPECTED3 = {"abba", "baab"};


THE_BENCHMARK(allPalindromePermutation, "aabbcadad");

SIMPLE_TEST(allPalindromePermutation, TestSAMPLE0, EXPECTED0, "abc");
SIMPLE_TEST(allPalindromePermutation, TestSAMPLE1, EXPECTED1, "aabcb");
SIMPLE_TEST(allPalindromePermutation, TestSAMPLE2, EXPECTED2, "aabbcadad");
SIMPLE_TEST(allPalindromePermutation, TestSAMPLE3, EXPECTED3, "aabb");
