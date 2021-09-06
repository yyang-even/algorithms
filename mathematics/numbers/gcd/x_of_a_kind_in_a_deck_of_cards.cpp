#include "common_header.h"

#include "hash/hash.h"


namespace {

using ArrayType = std::vector<int>;

/** X of a Kind in a Deck of Cards
 *
 * @reference   https://leetcode.com/problems/x-of-a-kind-in-a-deck-of-cards/
 *
 * In a deck of cards, each card has an integer written on it. Return true if and only
 * if you can choose X >= 2 such that it is possible to split the entire deck into 1 or
 * more groups of cards, where:
 *  Each group has exactly X cards.
 *  All the cards in each group have the same integer.
 */
auto HasGroupsSizeX(const ArrayType &deck) {
    const auto counts = ToFrequencyHashTable(deck);

    int gcd_of_all = 0;
    for (const auto [n, c] : counts) {
        gcd_of_all = std::gcd(gcd_of_all, c);
    }

    return gcd_of_all >= 2;
}

}//namespace


const ArrayType SAMPLE1 = {1, 1, 1, 1, 2, 2, 2, 2, 2, 2};
const ArrayType SAMPLE2 = {1, 2, 3, 4, 4, 3, 2, 1};
const ArrayType SAMPLE3 = {1, 1, 1, 2, 2, 2, 3, 3};
const ArrayType SAMPLE4 = {1};
const ArrayType SAMPLE5 = {1, 1};
const ArrayType SAMPLE6 = {1, 1, 2, 2, 2, 2};


THE_BENCHMARK(HasGroupsSizeX, SAMPLE1);

SIMPLE_TEST(HasGroupsSizeX, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(HasGroupsSizeX, TestSAMPLE2, true, SAMPLE2);
SIMPLE_TEST(HasGroupsSizeX, TestSAMPLE3, false, SAMPLE3);
SIMPLE_TEST(HasGroupsSizeX, TestSAMPLE4, false, SAMPLE4);
SIMPLE_TEST(HasGroupsSizeX, TestSAMPLE5, true, SAMPLE5);
SIMPLE_TEST(HasGroupsSizeX, TestSAMPLE6, true, SAMPLE6);

