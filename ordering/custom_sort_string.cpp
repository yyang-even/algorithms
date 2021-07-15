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
