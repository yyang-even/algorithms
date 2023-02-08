#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Fruit Into Baskets
 *
 * @reference   https://leetcode.com/problems/fruit-into-baskets/
 *
 * You are visiting a farm that has a single row of fruit trees arranged from left to right. The trees
 * are represented by an integer array fruits where fruits[i] is the type of fruit the ith tree
 * produces.
 * You want to collect as much fruit as possible. However, the owner has some strict rules that you must
 * follow:
 *  You only have two baskets, and each basket can only hold a single type of fruit. There is no limit
 *      on the amount of fruit each basket can hold.
 *  Starting from any tree of your choice, you must pick exactly one fruit from every tree (including
 *      the start tree) while moving to the right. The picked fruits must fit in one of your baskets.
 *  Once you reach a tree with fruit that cannot fit in your baskets, you must stop.
 * Given the integer array fruits, return the maximum number of fruits you can pick.
 *
 * Find out the longest length of subarrays with at most 2 different numbers?
 */
auto FruitIntoBaskets(const ArrayType &fruits) {
    std::unordered_map<int, int> count;
    std::size_t i = 0;
    std::size_t j = 0;

    while (j < fruits.size()) {
        ++count[fruits[j++]];
        if (count.size() > 2) {
            const auto to_remove = fruits[i++];
            if (count[to_remove]-- == 1) {
                count.erase(to_remove);
            }
        }
    }

    return j - i;
}

} //namespace


const ArrayType SAMPLE1 = {1, 2, 1};
const ArrayType SAMPLE2 = {0, 1, 2, 2};
const ArrayType SAMPLE3 = {1, 2, 3, 2, 2};
const ArrayType SAMPLE4 = {3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4};
const ArrayType SAMPLE5 = {0, 1, 2};
const ArrayType SAMPLE6 = {1, 1};


THE_BENCHMARK(FruitIntoBaskets, SAMPLE1);

SIMPLE_TEST(FruitIntoBaskets, TestSAMPLE1, 3, SAMPLE1);
SIMPLE_TEST(FruitIntoBaskets, TestSAMPLE2, 3, SAMPLE2);
SIMPLE_TEST(FruitIntoBaskets, TestSAMPLE3, 4, SAMPLE3);
SIMPLE_TEST(FruitIntoBaskets, TestSAMPLE4, 5, SAMPLE4);
SIMPLE_TEST(FruitIntoBaskets, TestSAMPLE5, 2, SAMPLE5);
SIMPLE_TEST(FruitIntoBaskets, TestSAMPLE6, 2, SAMPLE6);
