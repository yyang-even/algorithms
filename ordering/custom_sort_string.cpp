#include "common_header.h"


namespace {

/** Custom Sort String
 *
 * @reference   https://leetcode.com/problems/custom-sort-string/
 *
 * order and str are strings composed of lowercase letters. In order, no letter occurs
 * more than once. order was sorted in some custom order previously. We want to permute
 * the characters of str so that they match the order that order was sorted. More
 * specifically, if x occurs before y in order, then x should occur before y in the
 * returned string. Return any permutation of str (as a string) that satisfies this
 * property.
 *  order has length at most 26, and no character is repeated in order.
 *  str has length at most 200.
 *  order and str consist of lowercase letters only.
 *
 * @reference   Sort a string according to the order defined by another string
 *              https://www.geeksforgeeks.org/sort-string-according-order-defined-another-string/
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

    std::sort(str.begin(), str.end(),
    [&order_list](const auto one, const auto another) {
        return order_list[one - 'a'] < order_list[another - 'a'];
    });

    return str;
}


/**
 * @reference   Relative Sort Array
 *              https://leetcode.com/problems/relative-sort-array/
 *
 * Given two arrays arr1 and arr2, the elements of arr2 are distinct, and all elements in
 * arr2 are also in arr1. Sort the elements of arr1 such that the relative ordering of
 * items in arr1 are the same as in arr2. Elements that do not appear in arr2 should be
 * placed at the end of arr1 in ascending order.
 * 0 <= arr1[i], arr2[i] <= 1000
 */


/**
 * @reference   Single Row Keyboard
 *              https://codedestine.com/single-row-keyboard-string-problem/
 *
 * There is a special keyboard with all keys in a single row. You have given a string
 * keyboard of length 26 indicating the layout of the keyboard (indexed from 0 to 25),
 * initially your finger is at index 0. To type a character, you have to move your finger
 * to the index of the desired character. The time taken to move your finger from index i
 * to index j is |i – j|. You want to type a string word. Write a program to calculate
 * how much time it takes to type it with one finger.
 */


/**
 * @reference   Sort Integers by The Number of 1 Bits
 *              https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits/
 *
 * You are given an integer array arr. Sort the integers in the array in ascending order
 * by the number of 1's in their binary representation and in case of two or more integers
 * have the same number of 1's you have to sort them in ascending order. Return the array
 * after sorting it.
 */

}//namespace


THE_BENCHMARK(CustomSortString, "cba", "abcd");

SIMPLE_TEST(CustomSortString, TestSAMPLE1, "cbad", "cba", "abcd");
SIMPLE_TEST(CustomSortString, TestSAMPLE2, "bca", "bca", "abc");
SIMPLE_TEST(CustomSortString, TestSAMPLE3, "bbbcccaaa", "bxyzca", "abcabcabc");
SIMPLE_TEST(CustomSortString, TestSAMPLE4, "codijak",
            "wcyuogmlrdfphitxjakqvzbnes", "jcdokai");


THE_BENCHMARK(CustomSortString_Sort, "cba", "abcd");

SIMPLE_TEST(CustomSortString_Sort, TestSAMPLE1, "cbad", "cba", "abcd");
SIMPLE_TEST(CustomSortString_Sort, TestSAMPLE2, "bca", "bca", "abc");
SIMPLE_TEST(CustomSortString_Sort, TestSAMPLE3, "bbbcccaaa", "bxyzca", "abcabcabc");
SIMPLE_TEST(CustomSortString_Sort, TestSAMPLE4, "codijak",
            "wcyuogmlrdfphitxjakqvzbnes", "jcdokai");
