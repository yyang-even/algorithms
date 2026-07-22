#include "common_header.h"


namespace {

/**
 * @reference   Custom Sort String
 *              https://leetcode.com/problems/custom-sort-string/
 *
 * You are given two strings order and s. All the characters of order are unique and were sorted in some
 * custom order previously.
 * Permute the characters of s so that they match the order that order was sorted. More specifically, if
 * a character x occurs before a character y in order, then x should occur before y in the permuted
 * string.
 * Return any permutation of s that satisfies this property.
 *
 * @reference   Sort a string according to the order defined by another string
 *              https://www.geeksforgeeks.org/sort-string-according-order-defined-another-string/
 *
 * @tags    #hash-table #sorting
 */
constexpr auto SIZE = 'z' - 'a' + 1;

auto CustomSortString(const std::string_view order, std::string str) {
    int counts[SIZE] = {};
    for (const auto c : str) {
        ++counts[c - 'a'];
    }

    int i = 0;
    for (const auto c : order) {
        while (counts[c - 'a']-- > 0) {
            str[i++] = c;
        }
    }

    for (int j = 0; j < SIZE; ++j) {
        while (counts[j]-- > 0) {
            str[i++] = 'a' + j;
        }
    }

    return str;
}


auto CustomSortString_Sort(const std::string_view order, std::string str) {
    std::vector order_list(SIZE, order.size());
    for (std::size_t i = 0; i < order.size(); ++i) {
        order_list[order[i] - 'a'] = i;
    }

    std::sort(str.begin(), str.end(), [&order_list](const auto one, const auto another) {
        return order_list[one - 'a'] < order_list[another - 'a'];
    });

    return str;
}


/**
 * @reference   Relative Sort Array
 *              https://leetcode.com/problems/relative-sort-array/
 *
 * Given two arrays arr1 and arr2, the elements of arr2 are distinct, and all elements in arr2 are also
 * in arr1.
 * Sort the elements of arr1 such that the relative ordering of items in arr1 are the same as in arr2.
 * Elements that do not appear in arr2 should be placed at the end of arr1 in ascending order.
 * 0 <= arr1[i], arr2[i] <= 1000
 *
 * @tags    #hash-table #sorting
 */


/**
 * @reference   Single Row Keyboard
 *              https://leetcode.ca/all/1165.html
 *
 * There is a special keyboard with all keys in a single row.
 * Given a string keyboard of length 26 indicating the layout of the keyboard (indexed from 0 to 25),
 * initially your finger is at index 0. To type a character, you have to move your finger to the index
 * of the desired character. The time taken to move your finger from index i to index j is |i - j|.
 * You want to type a string word. Write a function to calculate how much time it takes to type it with
 * one finger.
 *
 * @tags    #hash-table
 */


/**
 * @reference   Sort Integers by The Number of 1 Bits
 *              https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits/
 *
 * You are given an integer array arr. Sort the integers in the array in ascending order by the number
 * of 1's in their binary representation and in case of two or more integers have the same number of 1's
 * you have to sort them in ascending order.
 * Return the array after sorting it.
 *
 * @tags    #hash-table #sorting
 */

} //namespace


THE_BENCHMARK(CustomSortString, "cba", "abcd");

SIMPLE_TEST(CustomSortString, TestSAMPLE1, "cbad", "cba", "abcd");
SIMPLE_TEST(CustomSortString, TestSAMPLE2, "bca", "bca", "abc");
SIMPLE_TEST(CustomSortString, TestSAMPLE3, "bbbcccaaa", "bxyzca", "abcabcabc");
SIMPLE_TEST(CustomSortString, TestSAMPLE4, "codijak", "wcyuogmlrdfphitxjakqvzbnes", "jcdokai");


THE_BENCHMARK(CustomSortString_Sort, "cba", "abcd");

SIMPLE_TEST(CustomSortString_Sort, TestSAMPLE1, "cbad", "cba", "abcd");
SIMPLE_TEST(CustomSortString_Sort, TestSAMPLE2, "bca", "bca", "abc");
SIMPLE_TEST(CustomSortString_Sort, TestSAMPLE3, "bbbcccaaa", "bxyzca", "abcabcabc");
SIMPLE_TEST(
    CustomSortString_Sort, TestSAMPLE4, "codijak", "wcyuogmlrdfphitxjakqvzbnes", "jcdokai");
