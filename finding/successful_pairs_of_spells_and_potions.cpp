#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Successful Pairs of Spells and Potions
 *
 * @reference   https://leetcode.com/problems/successful-pairs-of-spells-and-potions/
 *
 * You are given two positive integer arrays spells and potions, of length n and m respectively, where
 * spells[i] represents the strength of the ith spell and potions[j] represents the strength of the jth
 * potion.
 * You are also given an integer success. A spell and potion pair is considered successful if the
 * product of their strengths is at least success.
 * Return an integer array pairs of length n where pairs[i] is the number of potions that will form a
 * successful pair with the ith spell.
 */
auto SuccessfulPairsOfSpellsAndPotions_BinarySearch(const ArrayType &spells,
                                                    ArrayType potions,
                                                    const double success) {
    std::sort(potions.begin(), potions.end());

    ArrayType results;
    for (const auto s : spells) {
        const long long min_potion = std::ceil(success / s);
        const auto iter = std::lower_bound(potions.cbegin(), potions.cend(), min_potion);
        results.push_back(potions.cend() - iter);
    }

    return results;
}


auto SuccessfulPairsOfSpellsAndPotions_TwoPointers(const ArrayType &spells,
                                                   ArrayType potions,
                                                   const long long success) {
    std::vector<std::pair<long long, int>> sorted_spells;
    for (std::size_t i = 0; i < spells.size(); ++i) {
        sorted_spells.emplace_back(spells[i], i);
    }

    std::sort(sorted_spells.begin(), sorted_spells.end());
    std::sort(potions.begin(), potions.end());

    std::vector results(spells.size(), 0);
    int potion_i = potions.size() - 1;
    for (const auto &[s, i] : sorted_spells) {
        while (potion_i >= 0 and s * potions[potion_i] >= success) {
            --potion_i;
        }
        results[i] = potions.size() - (potion_i + 1);
    }

    return results;
}

} //namespace


const ArrayType SAMPLE1S = {5, 1, 3};
const ArrayType SAMPLE1P = {1, 2, 3, 4, 5};
const ArrayType EXPECTED1 = {4, 0, 3};

const ArrayType SAMPLE2S = {3, 1, 2};
const ArrayType SAMPLE2P = {8, 5, 8};
const ArrayType EXPECTED2 = {2, 0, 2};


THE_BENCHMARK(SuccessfulPairsOfSpellsAndPotions_BinarySearch, SAMPLE1S, SAMPLE1P, 7);

SIMPLE_TEST(SuccessfulPairsOfSpellsAndPotions_BinarySearch,
            TestSAMPLE1,
            EXPECTED1,
            SAMPLE1S,
            SAMPLE1P,
            7);
SIMPLE_TEST(SuccessfulPairsOfSpellsAndPotions_BinarySearch,
            TestSAMPLE2,
            EXPECTED2,
            SAMPLE2S,
            SAMPLE2P,
            16);


THE_BENCHMARK(SuccessfulPairsOfSpellsAndPotions_TwoPointers, SAMPLE1S, SAMPLE1P, 7);

SIMPLE_TEST(
    SuccessfulPairsOfSpellsAndPotions_TwoPointers, TestSAMPLE1, EXPECTED1, SAMPLE1S, SAMPLE1P, 7);
SIMPLE_TEST(SuccessfulPairsOfSpellsAndPotions_TwoPointers,
            TestSAMPLE2,
            EXPECTED2,
            SAMPLE2S,
            SAMPLE2P,
            16);
