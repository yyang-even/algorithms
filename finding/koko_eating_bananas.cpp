#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Koko Eating Bananas
 *
 * @reference   https://leetcode.com/problems/koko-eating-bananas/
 *
 * Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i]
 * bananas. The guards have gone and will come back in h hours.
 * Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some
 * pile of bananas and eats k bananas from that pile. If the pile has less than k bananas,
 * she eats all of them instead and will not eat any more bananas during this hour.
 * Koko likes to eat slowly but still wants to finish eating all the bananas before the
 * guards return.
 * Return the minimum integer k such that she can eat all the bananas within h hours.
 */
auto MinSpeed(const ArrayType &piles, const int h) {
    int left = 1;
    int right = *std::max_element(piles.cbegin(), piles.cend());

    while (left < right) {
        const auto mid = (left + right) / 2;
        int hour_required = 0;
        for (const auto p : piles) {
            hour_required += (p / mid) + (p % mid != 0);
        }

        if (hour_required <= h) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    return left;
}

}//namespace


const ArrayType SAMPLE1 = {3, 6, 7, 11};
const ArrayType SAMPLE2 = {312884470};
const ArrayType SAMPLE3 = {30, 11, 23, 4, 20};


THE_BENCHMARK(MinSpeed, SAMPLE1, 8);

SIMPLE_TEST(MinSpeed, TestSAMPLE1, 4, SAMPLE1, 8);
SIMPLE_TEST(MinSpeed, TestSAMPLE2, 2, SAMPLE2, 312884469);
SIMPLE_TEST(MinSpeed, TestSAMPLE3, 30, SAMPLE3, 5);
SIMPLE_TEST(MinSpeed, TestSAMPLE4, 23, SAMPLE3, 6);
